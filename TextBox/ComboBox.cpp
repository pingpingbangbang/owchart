#include "..\\stdafx.h"
#include "..\\include\\TextBox\\ComboBox.h"
using namespace OwLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ComboBoxMenu::ComboBoxMenu()
{
	m_comboBox = 0;
}

ComboBoxMenu::~ComboBoxMenu()
{
	m_comboBox = 0;
}

ComboBoxA* ComboBoxMenu::GetComboBox()
{
	return m_comboBox;
}

void ComboBoxMenu::SetComboBox( ComboBoxA *comboBox )
{
	m_comboBox = comboBox;
}

bool ComboBoxMenu::OnAutoHide()
{
	if (m_comboBox && m_comboBox->IsFocused())
	{
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ComboBoxA::DropDownButtonMouseDown( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	ComboBoxA *pThis = (ComboBoxA*)pInvoke;
	if(pThis)
	{
		pThis->OnDropDownOpening();
	}
}

void ComboBoxA::MenuItemClick( void *sender, MenuItemA *item, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	ComboBoxA *pThis = (ComboBoxA *)pInvoke;
	if(pThis)
	{
		pThis->SetText(item->GetText());
		vector<MenuItemA*> items = pThis->GetItems();
		int count = (int)items.size();
		for (int i = 0; i < count; i++)
		{
			if (items[i] == item)
			{
				pThis->SetSelectedIndex(i);
				break;
			}
		}
		pThis->SetSelectionStart((int)pThis->GetText().length());
		pThis->Invalidate();
	}
}

void ComboBoxA::MenuKeyDown( void *sender, char key, void *pInvoke )
{
	if (key == '\r')
	{
		ComboBoxA *pThis = (ComboBoxA*)sender;
		if(pThis)
		{
			pThis->OnSelectedIndexChanged();
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ComboBoxA::ComboBoxA()
{
	m_dropDownButton = 0;
	m_dropDownMenu = 0;
	m_dropDownButtonMouseDownEvent = &DropDownButtonMouseDown;
	m_menuItemClickEvent = &MenuItemClick;
	m_menuKeyDownEvent = &MenuKeyDown;
}

ComboBoxA::~ComboBoxA()
{
	if (m_dropDownButton && m_dropDownButtonMouseDownEvent)
	{
		m_dropDownButton->UnRegisterEvent(m_dropDownButtonMouseDownEvent, EVENTID::MOUSEDOWN);
		m_dropDownButtonMouseDownEvent = 0;
	}
	if (m_dropDownMenu)
	{
		if (m_menuItemClickEvent)
		{
			m_dropDownMenu->UnRegisterEvent(m_menuItemClickEvent, EVENTID::MENUITEMCLICK);
			m_menuItemClickEvent = 0;
		}
		if (m_menuKeyDownEvent)
		{
			m_dropDownMenu->UnRegisterEvent(m_menuKeyDownEvent, EVENTID::KEYDOWN);
			m_menuKeyDownEvent = 0;
		}
		GetNative()->RemoveControl(m_dropDownMenu);
		delete m_dropDownMenu;
		m_dropDownMenu = 0;
	}
}

ButtonA* ComboBoxA::GetDropDownButton()
{
	return m_dropDownButton;
}

ComboBoxMenu* ComboBoxA::GetDropDownMenu()
{
	return m_dropDownMenu;
}

int ComboBoxA::GetSelectedIndex()
{
	if (m_dropDownMenu)
	{
		vector<MenuItemA*> items = m_dropDownMenu->GetItems();
		int count = (int)items.size();
		for (int i = 0; i < count; i++)
		{
			MenuItemA *menuItemA = items[i];
			if (menuItemA->IsChecked())
			{
				return i;
			}
		}
	}
	return -1;
}

void ComboBoxA::SetSelectedIndex( int selectedIndex )
{
	if (m_dropDownMenu)
	{
		vector<MenuItemA*> items = m_dropDownMenu->GetItems();
		int count = (int)items.size();
		bool flag = false;
		for (int i = 0; i < count; i++)
		{
			MenuItemA *menuItemA = items[i];
			if (i == selectedIndex)
			{
				if (!menuItemA->IsChecked())
				{
					flag = true;
					menuItemA->SetChecked(true);
				}
				SetText(menuItemA->GetText());
			}
			else
			{
				menuItemA->SetChecked(false);
			}
		}
		if (flag)
		{
			OnSelectedIndexChanged();
		}
	}
}

String ComboBoxA::GetSelectedText()
{
	if (m_dropDownMenu)
	{
		vector<MenuItemA*> items = m_dropDownMenu->GetItems();
		int count = (int)items.size();
		for (int i = 0; i < count; i++)
		{
			MenuItemA *menuItemA = items[i];
			if (menuItemA->IsChecked())
			{
				return menuItemA->GetText();
			}
		}
	}
	return L"";
}

void ComboBoxA::SetSelectedText( const String& selectedText )
{
	if (m_dropDownMenu)
	{
		vector<MenuItemA*> items = m_dropDownMenu->GetItems();
		int count = (int)items.size();
		bool flag = false;
		for (int i = 0; i < count; i++)
		{
			MenuItemA *menuItemA = items[i];
			if (menuItemA->GetText() == selectedText)
			{
				if (!menuItemA->IsChecked())
				{
					flag = true;
					menuItemA->SetChecked(true);
				}
				SetText(menuItemA->GetText());
			}
			else
			{
				menuItemA->SetChecked(false);
			}
		}
		if (flag)
		{
			OnSelectedIndexChanged();
		}
	}
}

String ComboBoxA::GetSelectedValue()
{
	if (m_dropDownMenu)
	{
		vector<MenuItemA*> items = m_dropDownMenu->GetItems();
		int count = (int)items.size();
		for (int i = 0; i < count; i++)
		{
			MenuItemA *menuItemA = items[i];
			if (menuItemA->IsChecked())
			{
				return menuItemA->GetValue();
			}
		}
	}
	return L"";
}

void ComboBoxA::SetSelectedValue( const String& selectedValue )
{
	if (m_dropDownMenu)
	{
		vector<MenuItemA*> items = m_dropDownMenu->GetItems();
		int count = (int)items.size();
		bool flag = false;
		for (int i = 0; i < count; i++)
		{
			MenuItemA *menuItemA = items[i];
			if (menuItemA->GetValue() == selectedValue)
			{
				if (!menuItemA->IsChecked())
				{
					flag = true;
					menuItemA->SetChecked(true);
				}
				SetText(menuItemA->GetText());
			}
			else
			{
				menuItemA->SetChecked(false);
			}
		}
		if (flag)
		{
			OnSelectedIndexChanged();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ComboBoxA::AddItem( MenuItemA *item )
{
	if (m_dropDownMenu)
	{
		m_dropDownMenu->AddItem(item);
	}
}

void ComboBoxA::ClearItems()
{
	if (m_dropDownMenu)
	{
		m_dropDownMenu->ClearItems();
	}
}

String ComboBoxA::GetControlType()
{
	return L"ComboBox";
}

vector<wstring> ComboBoxA::GetEventNames()
{
	vector<wstring> ws;
	ws.push_back(L"SelectedIndexChanged");
	return ws;
}

vector<MenuItemA*> ComboBoxA::GetItems()
{
	if (m_dropDownMenu)
	{
		return m_dropDownMenu->GetItems();
	}
	return vector<MenuItemA*>();
}

void ComboBoxA::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"selectedindex")
	{
		*type = L"int";
		*value = CStr::ConvertIntToStr(GetSelectedIndex());
	}
	else if (name == L"selectedtext")
	{
		*type = L"text";
		*value = GetSelectedText();
	}
	else if (name == L"selectedvalue")
	{
		*type = L"text";
		*value = GetSelectedValue();
	}
	else
	{
		TextBoxA::GetProperty(name, value, type);
	}
}

vector<String> ComboBoxA::GetPropertyNames()
{
	vector<String> propertyNames = TextBoxA::GetPropertyNames();
	propertyNames.push_back(L"SelectedIndex");
	propertyNames.push_back(L"SelectedText");
	propertyNames.push_back(L"SelectedValue");
	return propertyNames;
}

void ComboBoxA::InsertItem( int index, MenuItemA *item )
{
	if (m_dropDownMenu)
	{
		m_dropDownMenu->InsertItem(index, item);
	}
}

void ComboBoxA::OnDropDownOpening()
{
	m_dropDownMenu->SetNative(GetNative());
	POINT pp = {0, GetHeight()};
	POINT point = PointToNative(pp);
	m_dropDownMenu->SetLocation(point);
	SIZE sz = {GetWidth(), m_dropDownMenu->GetContentHeight()};
	m_dropDownMenu->SetSize(sz);
	m_dropDownMenu->SetVisible(true);
	m_dropDownMenu->BringToFront();
	m_dropDownMenu->Invalidate();
}

void ComboBoxA::OnKeyDown( char key )
{
	TextBoxA::OnKeyDown(key);
	ControlHost *host = GetNative()->GetHost();
	if ((((!host->IsKeyPress(0x10) 
		&& !host->IsKeyPress(0x11)) 
		&& (!host->IsKeyPress(0x12) 
		&& GetLinesCount() <= 1)) 
		&& (((key == '\r') || (key == '&')) || (key == '(')))
		&& m_dropDownMenu)
	{
		m_dropDownMenu->OnKeyDown(key);
	}
}

void ComboBoxA::OnLoad()
{
	TextBoxA::OnLoad();
	ControlHost *host = GetNative()->GetHost();
	if (!m_dropDownButton)
	{
		m_dropDownButton = (ButtonA*)host->CreateInternalControl(this, L"dropdownbutton");
		AddControl(m_dropDownButton);
		m_dropDownButton->RegisterEvent(m_dropDownButtonMouseDownEvent, EVENTID::MOUSEDOWN, this);
	}
	if (!m_dropDownMenu)
	{
		m_dropDownMenu = (ComboBoxMenu*)host->CreateInternalControl(this, L"dropdownmenu");
		GetNative()->AddControl(m_dropDownMenu);
		m_dropDownMenu->SetVisible(false);
		m_dropDownMenu->RegisterEvent(m_menuItemClickEvent, EVENTID::MENUITEMCLICK, this);
		m_dropDownMenu->RegisterEvent(m_menuKeyDownEvent, EVENTID::KEYDOWN, this);
	}
	else
	{
		m_dropDownMenu->SetNative(GetNative());
	}
}

void ComboBoxA::OnSelectedIndexChanged()
{
	CallEvents(EVENTID::SELECTEDINDEXCHANGED);
}

void ComboBoxA::OnMouseWheel( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	TextBoxA::OnMouseWheel(mp, button, clicks, delta);
	if (GetLinesCount() <= 1 && m_dropDownMenu)
	{
		m_dropDownMenu->OnMouseWheel(m_dropDownMenu->GetMousePoint(), button, clicks, delta);
	}
}

void ComboBoxA::RemoveItem( MenuItemA *item )
{
	if (m_dropDownMenu)
	{
		m_dropDownMenu->RemoveItem(item);
	}
}

void ComboBoxA::SetProperty( const String& name, const String& value )
{
	if (name == L"selectedindex")
	{
		SetSelectedIndex(CStr::ConvertStrToInt(value));
	}
	else if (name == L"selectedtext")
	{
		SetSelectedText(value);
	}
	else if (name == L"selectedvalue")
	{
		SetSelectedValue(value);
	}
	else
	{
		TextBoxA::SetProperty(name, value);
	}
}

void ComboBoxA::Update()
{
	TextBoxA::Update();
	int width = GetWidth();
	int height = GetHeight();
	if (m_dropDownButton)
	{
		int dWidth = m_dropDownButton->GetWidth();
		POINT pt = {width - dWidth, 0};
		m_dropDownButton->SetLocation(pt);
		SIZE sz = {dWidth, height};
		m_dropDownButton->SetSize(sz);
		PADDING pd(0, 0, dWidth, 0);
		SetPadding(pd);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////