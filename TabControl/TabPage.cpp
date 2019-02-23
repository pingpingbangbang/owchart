#include "..\\stdafx.h"
#include "..\\include\\TabControl\\TabPage.h"
using namespace OwLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TabPageA::DragHeaderBegin(void *sender, void *pInvoke)
{
	TabPageA *page = (TabPageA*)pInvoke;
	if(page)
	{
		TabControlA *tabControl = page->GetTabControl();
		if(tabControl)
		{
			tabControl->OnDragTabHeaderBegin(page);
		}
	}
}

void TabPageA::DragHeaderEnd(void *sender, void *pInvoke)
{
	TabPageA *page = (TabPageA*)pInvoke;
	if(page)
	{
		TabControlA *tabControl = page->GetTabControl();
		if(tabControl)
		{
			tabControl->OnDragTabHeaderEnd(page);
		}
	}
}

void TabPageA::DraggingHeader(void *sender, void *pInvoke)
{
	TabPageA *page = (TabPageA*)pInvoke;
	if(page)
	{
		TabControlA *tabControl = page->GetTabControl();
		if(tabControl)
		{
			tabControl->OnDraggingTabHeader(page);
		}
	}
}

void TabPageA::HeaderMouseDown(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke)
{
	TabPageA *page = (TabPageA*)pInvoke;
	if(page)
	{
		TabControlA *tabControl = page->GetTabControl();
		if(tabControl)
		{
			tabControl->SetSelectedTabPage(page);
			tabControl->Invalidate();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TabPageA::TabPageA()
{
	m_headerButton = 0;
	m_headerLocation.x = 0;
	m_headerLocation.y = 0;
	m_tabControl = 0;

	m_dragHeaderBeginEvent = &DragHeaderBegin;
	m_dragHeaderEndEvent = &DragHeaderEnd;
	m_draggingHeaderEvent = &DraggingHeader;
	m_headerMouseDownEvent = &HeaderMouseDown;
}

TabPageA::~TabPageA()
{

	if (m_dragHeaderBeginEvent)
	{
		if (m_headerButton)
		{
			m_headerButton->UnRegisterEvent(m_dragHeaderBeginEvent, EVENTID::DRAGBEGIN);
		}
		m_dragHeaderBeginEvent = 0;
	}
	if (m_dragHeaderEndEvent)
	{
		if (m_headerButton)
		{
			m_headerButton->UnRegisterEvent(m_dragHeaderEndEvent, EVENTID::DRAGEND);
		}
		m_dragHeaderEndEvent = 0;
	}
	if (m_draggingHeaderEvent)
	{
		if (m_headerButton)
		{
			m_headerButton->UnRegisterEvent(m_draggingHeaderEvent, EVENTID::DRAGGING);
		}
		m_draggingHeaderEvent = 0;
	}
	if (m_headerMouseDownEvent)
	{
		if (m_headerButton)
		{
			m_headerButton->UnRegisterEvent(m_headerMouseDownEvent, EVENTID::MOUSEDOWN);
		}
		m_headerMouseDownEvent = 0;
	}
	m_headerButton = 0;
	m_tabControl = 0;
}

ButtonA* TabPageA::GetHeaderButton()
{
	return m_headerButton;
}

void TabPageA::SetHeaderButton(ButtonA *headerButton)
{
	m_headerButton = headerButton;
}

POINT TabPageA::GetHeaderLocation()
{
	return m_headerLocation;
}

void TabPageA::SetHeaderLocation(POINT headerLocation)
{
	m_headerLocation = headerLocation;
}

bool TabPageA::IsHeaderVisible()
{
	return (m_headerButton && m_headerButton->IsVisible());
}

void TabPageA::SetHeaderVisible(bool visible)
{
	if (m_headerButton)
	{
		m_headerButton->SetVisible(visible);
	}
}

TabControlA* TabPageA::GetTabControl()
{
	return m_tabControl;
}

void TabPageA::SetTabControl(TabControlA *tabControl)
{
	m_tabControl = tabControl;
}

String TabPageA::GetControlType()
{
	return L"TabPage";
}

void TabPageA::GetProperty(const String& name, String *value, String *type)
{
	if (name == L"headersize")
	{
		*type = L"size";
		if (m_headerButton)
		{
			*value = CStr::ConvertSizeToStr(m_headerButton->GetSize());
		}
		else
		{
			*value = L"0,0";
		}
	}
	else if (name == L"headervisible")
	{
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(IsHeaderVisible());
	}
	else if(name.find(L"header-") != -1)
	{
		if (m_headerButton)
		{
			m_headerButton->GetProperty(name.substr(7), value, type);
		}
	}
	else
	{
		DivA::GetProperty(name, value, type);
	}
}

vector<String> TabPageA::GetPropertyNames()
{
	vector<String> propertyNames = DivA::GetPropertyNames();
	propertyNames.push_back(L"Header");
	propertyNames.push_back(L"HeaderSize");
	propertyNames.push_back(L"HeaderVisible");
	return propertyNames;
}

void TabPageA::OnLoad()
{
	DivA::OnLoad();
	if (m_tabControl)
	{
		if (!m_headerButton)
		{
			ControlHost *host = GetNative()->GetHost();
			m_headerButton = dynamic_cast<ButtonA*>(host->CreateInternalControl(this, L"headerbutton"));
			m_headerButton->RegisterEvent(m_dragHeaderBeginEvent, EVENTID::DRAGBEGIN, this);
			m_headerButton->RegisterEvent(m_dragHeaderEndEvent, EVENTID::DRAGEND, this);
			m_headerButton->RegisterEvent(m_draggingHeaderEvent, EVENTID::DRAGGING, this);
			m_headerButton->RegisterEvent(m_headerMouseDownEvent, EVENTID::MOUSEDOWN, this);
		}
		if (!m_tabControl->ContainsControl(m_headerButton))
		{
			m_tabControl->AddControl(m_headerButton);
		}
	}
}

void TabPageA::OnTextChanged()
{
	DivA::OnTextChanged();
	if (m_headerButton)
	{
		m_headerButton->SetText(GetText());
	}
}

void TabPageA::SetProperty(const String& name, const String& value)
{
	if (name == L"headersize")
	{
		if (m_headerButton)
		{
			m_headerButton->SetSize(CStr::ConvertStrToSize(value));
		}
	}
	else if (name == L"headervisible")
	{
		SetHeaderVisible(CStr::ConvertStrToBool(value));
	}
	else if(name.find(L"header-") != -1)
	{
		if (m_headerButton) 
		{
			m_headerButton->SetProperty(name.substr(7), value);
		}
	}
	else
	{
		DivA::SetProperty(name, value);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////