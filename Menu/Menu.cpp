#include "..\\stdafx.h"
#include "..\\include\\Menu\\Menu.h"
using namespace OwLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MenuA::Adjust(MenuA *menu)
{
	NativeBase *native = GetNative();
	if (AutoSize())
	{
		int contentHeight = menu->GetContentHeight();
		int cy = GetMaximumSize().cy;
		menu->SetHeight(min(contentHeight, cy));
	}
	POINT location = menu->GetLocation();
	SIZE size = menu->GetSize();
	SIZE displaySize = native->GetDisplaySize();
	if (location.x < 0)
	{
		location.x = 0;
	}
	if (location.y < 0)
	{
		location.y = 0;
	}
	if (location.x + size.cx > displaySize.cx)
	{
		location.x = displaySize.cx - size.cx;
	}
	if (location.y + size.cy > displaySize.cy)
	{
		location.y = displaySize.cy - size.cy;
	}
	menu->SetLocation(location);
	menu->Update();
}

bool MenuA::CheckDivFocused(vector<MenuItemA*> items)
{
	int count = (int)items.size();
	for (int i = 0; i < count; i++)
	{
		MenuItemA *ma = items[i];
		MenuA *dropDownMenu = ma->GetDropDownMenu();
		if (dropDownMenu && CheckFocused(dropDownMenu))
		{
			return true;
		}
		vector<MenuItemA*> list = ma->GetItems();
		if (CheckDivFocused(list))
		{
			return true;
		}
	}
	return false;
}

bool MenuA::CheckFocused(ControlA *control)
{
	if (control->IsFocused())
	{
		return true;
	}
	vector<ControlA*> controls = control->GetControls();
	int count = (int)controls.size();
	if (count)
	{
		for (int i = 0; i < count; i++)
		{
			if (CheckFocused(controls[i]))
			{
				return true;
			}
		}
	}
	return false;
}

bool MenuA::CloseMenus(vector<MenuItemA*> items)
{
	int itemSize = (int)items.size();
	bool close = false;
	for (int i = 0; i < itemSize; i++)
	{
		MenuItemA *item = items[i];
		vector<MenuItemA*> list = item->GetItems();
		if (CloseMenus(list))
		{
			close = true;
		}
		MenuA *dropDownMenu = item->GetDropDownMenu();
		if ((dropDownMenu) && dropDownMenu->IsVisible())
		{
			dropDownMenu->Hide();
			close = true;
		}
	}
	return close;
}

void MenuA::CallMenuItemMouseEvent(int eventID, MenuItemA *item, const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	map<int, vector<void*>*>::iterator sIter = ControlA::m_events.find(eventID);
	map<int, vector<void*>*>::iterator sIterInvoker = ControlA::m_invokes.find(eventID);
	if(sIter != ControlA::m_events.end() && sIterInvoker != ControlA::m_invokes.end())
	{
		vector<void*>* list = sIter->second;
		vector<void*>* invokerList = sIterInvoker->second;
 		int count = (int)list->size();
		int count2 = (int)invokerList->size();
		assert(count == count2);
		for(int i = 0; i < count; i++)
		{
			MenuItemMouseEvent event2 = (MenuItemMouseEvent)(*list)[i];
			if(event2)
			{
				(event2)(this, item, mp, button, clicks, delta, (*invokerList)[i]);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MenuA::MenuA()
{
	m_autoHide = true;
	m_parentItem = 0;
	m_popup = false;
	m_timerID = ControlA::GetNewTimerID();
	SetAutoSize(true);
	SetLayoutStyle(LayoutStyleA_TopToBottom);
	SIZE maxSize = { 2000, 500 };
	SetMaximumSize(maxSize);
	SetShowHScrollBar(true);
	SetShowVScrollBar(true);
	SetTopMost(true);
	SIZE size = { 200, 200 };
	SetSize(size);
}

MenuA::~MenuA()
{
	m_parentItem = 0;
	StopTimer(m_timerID);
	ClearItems();
}

bool MenuA::AutoHide()
{
	return m_autoHide;
}

void MenuA::SetAutoHide(bool autoHide)
{
	m_autoHide = autoHide;
}

MenuItemA* MenuA::GetParentItem()
{
	return m_parentItem;
}

void MenuA::SetParentItem(MenuItemA *parentItem)
{
	m_parentItem = parentItem;
}

bool MenuA::IsPopup()
{
	return m_popup;
}

void MenuA::SetPopup(bool popup)
{
	m_popup = popup;
	if(m_popup)
	{
		SetVisible(false);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MenuA::AddItem(MenuItemA *item)
{
	item->SetParentMenu(this);
	item->OnAddingItem(-1);
	m_items.push_back(item);
}

void MenuA::ClearItems()
{
	vector<MenuItemA*> itemsCopy;
	int itemSize = (int)m_items.size();
	for (int i = 0; i < itemSize; i++)
	{
		itemsCopy.push_back(m_items[i]);
	}
	vector<MenuItemA*>::iterator sIter = itemsCopy.begin();
	for(; sIter != itemsCopy.end(); ++sIter)
	{
		(*sIter)->OnRemovingItem();
		delete *sIter;
		*sIter = 0;
	}
	itemsCopy.clear();
	m_items.clear();
}

MenuA* MenuA::CreateDropDownMenu()
{
	MenuA *menuA = new MenuA();
	menuA->SetPopup(true);
	menuA->SetShowHScrollBar(true);
	menuA->SetShowVScrollBar(true);
	return menuA;
}

String MenuA::GetControlType()
{
	return L"Menu";
}

vector<wstring> MenuA::GetEventNames()
{
	vector<wstring> ws;
	ws.push_back(L"MenuItemClick");
	return ws;
}

vector<MenuItemA*> MenuA::GetItems()
{
	return m_items;
}

void MenuA::GetProperty(const String& name, String *value, String *type)
{
	if (name == L"popup")
	{
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(IsPopup());
	}
	else
	{
		LayoutDivA::GetProperty(name, value, type);
	}
}

vector<String> MenuA::GetPropertyNames()
{
	vector<String> propertyNames = LayoutDivA::GetPropertyNames();
	propertyNames.push_back(L"Popup");
	return propertyNames;
}

void MenuA::InsertItem(int index, MenuItemA *item)
{
	item->SetParentMenu(this);
	item->OnAddingItem(index);
	m_items.insert(m_items.begin() + index, item);
}

bool MenuA::OnAutoHide()
{
	return true;
}

void MenuA::OnLoad()
{
	ControlA::OnLoad();
}

void MenuA::OnMenuItemClick(MenuItemA *item, const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	if ((int)item->GetItems().size() == 0)
	{
		CallMenuItemMouseEvent(EVENTID::MENUITEMCLICK, item, mp, button, clicks, delta);
		CloseMenus(m_items);
		if (m_popup)
		{
			Hide();
		}
		else
		{
			GetNative()->Invalidate();
		}
	}
	else
	{
		OnMenuItemMouseMove(item, mp, button, clicks, delta);
	}
}

void MenuA::OnMenuItemMouseMove(MenuItemA *item, const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	NativeBase *native = GetNative();
	vector<MenuItemA*> items;
	MenuItemA *parentItem = item->GetParentItem();
	if (parentItem)
	{
		items = parentItem->GetItems();
	}
	else
	{
		items = m_items;
	}
	CloseMenus(items);
	if ((int)item->GetItems().size() > 0)
	{
		MenuA *dropDownMenu = item->GetDropDownMenu();
		if (dropDownMenu)
		{
			dropDownMenu->SetNative(native);
			LayoutStyleA layoutStyle = GetLayoutStyle();
			POINT point = { native->ClientX(item) + item->GetWidth(), native->ClientY(item) };
			switch (layoutStyle)
			{
			case LayoutStyleA_LeftToRight:
			case LayoutStyleA_RightToLeft:
				point.x = native->ClientX(item);
				point.y = native->ClientY(item) + item->GetHeight();
				break;
			}
			dropDownMenu->SetOpacity(GetOpacity());
			dropDownMenu->SetLocation(point);
			dropDownMenu->BringToFront();
			dropDownMenu->Focus();
			dropDownMenu->Show();
			Adjust(dropDownMenu);
		}
	}
	native->Invalidate();
}

void MenuA::OnMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	LayoutDivA::OnMouseDown(mp, button, clicks, delta);
	CloseMenus(m_items);
	GetNative()->Invalidate();
}

void MenuA::OnTimer(int timerID)
{
	LayoutDivA::OnTimer(timerID);
	if ((m_timerID == timerID && !m_parentItem
		&& IsVisible() && !CheckFocused(this))
		&& (!CheckDivFocused(m_items) && OnAutoHide()))
	{
		CloseMenus(m_items);
		if (m_popup)
		{
			Hide();
		}
		else
		{
			GetNative()->Invalidate();
		}
	}
}

void MenuA::OnVisibleChanged()
{
	LayoutDivA::OnVisibleChanged();
	if (IsVisible())
	{
		if (m_popup)
		{
			HScrollBarA *hScrollBar = GetHScrollBar();
			VScrollBarA *vScrollBar = GetVScrollBar();
			if (hScrollBar)
			{
				hScrollBar->SetPos(0);
			}
			if (vScrollBar)
			{
				vScrollBar->SetPos(0);
			}
			Focus();
			Adjust(this);
		}
		StartTimer(m_timerID, 10);
	}
	else
	{
		StopTimer(m_timerID);
		CloseMenus(m_items);
		NativeBase *native = GetNative();
		if (native)
		{
			native->Invalidate();
		}
	}
}

void MenuA::RemoveItem(MenuItemA *item)
{
	item->OnRemovingItem();
	vector<MenuItemA*>::iterator sIter = m_items.begin();
	for(; sIter != m_items.end(); ++sIter)
	{
		if(item = *sIter)
		{
			m_items.erase(sIter);
			delete *sIter;
			*sIter = 0;  
		}
	}
}

void MenuA::SetProperty(const String& name, const String& value)
{
	if (name == L"popup")
	{
		SetPopup(CStr::ConvertStrToBool(value));
	}
	else
	{
		LayoutDivA::SetProperty(name, value);
	}
}