#include "..\\stdafx.h"
#include "..\\include\\Menu\\MenuItem.h"
using namespace OwLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MenuItemA::MenuItemA()
{
	m_checked = false;
	m_dropDownMenu = 0;
	m_parentItem = 0;
	m_parentMenu = 0;
	m_text = L"";
	FONT font(L"ËÎÌו", 12, false, false, false);
	SetFont(&font);
	SIZE size = { 200, 25 };
	SetSize(size);
}

MenuItemA::MenuItemA(const String& text)
{
	m_checked = false;
	m_dropDownMenu = 0;
	m_parentItem = 0;
	m_parentMenu = 0;
	m_text = text;

	FONT font(L"ËÎÌו", 12, false, false, false);
	SetFont(&font);
	SIZE size = { 200, 25 };
	SetSize(size);
}

MenuItemA::~MenuItemA()
{
	ClearItems();
	m_dropDownMenu = 0;
	m_parentItem = 0;
	m_parentMenu = 0;
}

bool MenuItemA::IsChecked()
{
	return m_checked;
}

void MenuItemA::SetChecked(bool checked)
{
	m_checked = checked;
}

MenuA* MenuItemA::GetDropDownMenu()
{
	return m_dropDownMenu;
}

void MenuItemA::SetDropDownMenu(MenuA *dropDownMenu)
{
	m_dropDownMenu = dropDownMenu;
}

MenuItemA* MenuItemA::GetParentItem()
{
	return m_parentItem;
}

void MenuItemA::SetParentItem(MenuItemA *parentItem)
{
	m_parentItem = parentItem;
}

MenuA* MenuItemA::GetParentMenu()
{
	return m_parentMenu;
}

void MenuItemA::SetParentMenu(MenuA *parentMenu)
{
	m_parentMenu = parentMenu;
}

String MenuItemA::GetValue()
{
	return m_value;
}

void MenuItemA::SetValue(const String& value)
{
	m_value = value;
}

void MenuItemA::AddItem(MenuItemA *item)
{
	item->SetParentItem(this);
	item->SetParentMenu(GetParentMenu());
	item->OnAddingItem(-1);
	m_items.push_back(item);
}

void MenuItemA::ClearItems()
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

String MenuItemA::GetControlType()
{
	return L"MenuItem";
}

vector<MenuItemA*> MenuItemA::GetItems()
{
	return m_items;
}

void MenuItemA::GetProperty(const String& name, String *value, String *type)
{
	if (name == L"checked")
	{
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(IsChecked());
	}
	else if (name == L"value")
	{
		*type = L"String";
		*value = GetValue();
	}
	else
	{
		ButtonA::GetProperty(name, value, type);
	}
}

vector<String> MenuItemA::GetPropertyNames()
{
	vector<String> propertyNames = ButtonA::GetPropertyNames();
	propertyNames.push_back(L"Checked");
	propertyNames.push_back(L"Value");
	return propertyNames;
}

void MenuItemA::InsertItem(int index, MenuItemA *item)
{
	item->SetParentItem(this);
	item->SetParentMenu(GetParentMenu());
	item->OnAddingItem(index);
	m_items.insert(m_items.begin() + index, item);
}

void MenuItemA::OnAddingItem(int index)
{
	MenuA *dropDownMenu = 0;
	if (m_parentItem)
	{
		dropDownMenu = m_parentItem->GetDropDownMenu();
		if (!dropDownMenu)
		{
			dropDownMenu = m_parentMenu->CreateDropDownMenu();
			dropDownMenu->SetVisible(false);
			m_parentItem->SetDropDownMenu(dropDownMenu);
			dropDownMenu->SetParentItem(m_parentItem);
			m_parentMenu->GetNative()->AddControl(dropDownMenu);
		}
	}
	else
	{
		dropDownMenu = m_parentMenu;
	}
	if (dropDownMenu)
	{
		if (index != -1)
		{
			dropDownMenu->InsertControl(index, this);
		}
		else
		{
			dropDownMenu->AddControl(this);
		}
		int itemSize = (int)m_items.size();
		for (int i = 0; i < itemSize; i++)
		{
			m_items[i]->OnAddingItem(-1);
		}
	}
}

void MenuItemA::OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	ButtonA::OnClick(mp, button, clicks, delta);
	if (m_parentMenu)
	{
		m_parentMenu->OnMenuItemClick(this, mp, button, clicks, delta);
	}
}

void MenuItemA::OnMouseMove(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	ButtonA::OnMouseMove(mp, button, clicks, delta);
	if (m_parentMenu)
	{
		m_parentMenu->OnMenuItemMouseMove(this, mp, button, clicks, delta);
	}
}

void MenuItemA::OnPaintForeground(CPaint *paint, const RECT& clipRect)
{
	int width = GetWidth();
	int height = GetHeight();
	if (width > 0 && height > 0)
	{
		int right = width;
		int midY = height / 2;
		String text = GetText();
		int tRight = 0;
		_int64 foreColor = GetPaintingForeColor();
		if ((int)text.length() > 0)
		{
			FONT *font = GetFont();
			SIZE tSize = paint->TextSize(text.c_str(), font);
			RECT tRect;
			tRect.left = 10;
			tRect.top = (midY - tSize.cy / 2) + 2;
			tRect.right = tRect.left + tSize.cx;
			tRect.bottom = tRect.top + tSize.cy;
			paint->DrawText(text.c_str(), foreColor, font, tRect);
			tRight = tRect.right + 4;
		}
		if (m_checked)
		{
			RECT eRect = { tRight, height / 2 - 4, tRight + 8, height / 2 + 4 };
			paint->FillEllipse(foreColor, eRect);
		}
		int count = (int)m_items.size();
		if (count > 0)
		{
			POINT point = {0, 0};
			POINT point2 = {0, 0};
			POINT point3 = {0, 0};
			MenuA *parentMenu = m_parentMenu;
			if (m_parentItem)
			{
				parentMenu = m_parentItem->GetDropDownMenu();
			}
			switch (parentMenu->GetLayoutStyle())
			{
			case LayoutStyleA_LeftToRight:
			case LayoutStyleA_RightToLeft:
				point.x = right - 25;
				point.y = midY - 2;
				point2.x = right - 14;
				point2.y = midY - 2;
				point3.x = right - 20;
				point3.y = midY + 4;
				break;

			default:
				point.x = right - 15;
				point.y = midY;
				point2.x = right - 25;
				point2.y = midY - 5;
				point3.x = right - 25;
				point3.y = midY + 5;
				break;
			}
			POINT points[3] = { point, point2, point3 };
			paint->FillPolygon(foreColor, points, 3);
		}
	}
}

void MenuItemA::OnRemovingItem()
{
	MenuA *dropDownMenu;
	if (m_parentItem)
	{
		dropDownMenu = m_parentItem->GetDropDownMenu();
	}
	else
	{
		dropDownMenu = m_parentMenu;
	}
	if (dropDownMenu)
	{
		int count = (int)m_items.size();
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				m_items[i]->OnRemovingItem();
			}
		}
		dropDownMenu->RemoveControl(this);
	}
	if (m_dropDownMenu)
	{
		m_parentMenu->GetNative()->RemoveControl(m_dropDownMenu);
		delete m_dropDownMenu;
		m_dropDownMenu = 0;
	}
}

void MenuItemA::RemoveItem(MenuItemA *item)
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

void MenuItemA::SetProperty(const String& name, const String& value)
{
	if (name == L"checked")
	{
		SetChecked(CStr::ConvertStrToBool(value));
	}
	else if (name == L"value")
	{
		SetValue(value);
	}
	else
	{
		ButtonA::SetProperty(name, value);
	}
}