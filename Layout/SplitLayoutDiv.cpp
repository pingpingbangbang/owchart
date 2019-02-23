#include "..\\stdafx.h"
#include "..\\include\\Layout\\SplitLayoutDiv.h"
using namespace OwLib;

void SplitLayoutDivA::SplitterDragging( void *sender, void *pInvoke )
{
	SplitLayoutDivA* div = (SplitLayoutDivA*)pInvoke;
	if(div)
	{
		div->OnSplitterDragging();
	}
}

SplitLayoutDivA::SplitLayoutDivA()
{
	m_oldSize.cx = 0;
	m_oldSize.cy = 0;
	m_firstControl = 0;
	m_secondControl = 0;
	m_splitMode = SizeTypeA_AbsoluteSize;
	m_splitPercent = -1.0f;
	m_splitter = 0;
	m_splitterDraggingEvent = &SplitterDragging;
}

SplitLayoutDivA::~SplitLayoutDivA()
{
	m_firstControl = 0;
	m_secondControl = 0;
	if (m_splitter && m_splitterDraggingEvent)
	{
		m_splitter->UnRegisterEvent(m_splitterDraggingEvent, EVENTID::DRAGGING);
		m_splitterDraggingEvent = 0;
	}
	m_splitter = 0;
}

ControlA* SplitLayoutDivA::GetFirstControl()
{
	return m_firstControl;
}

void SplitLayoutDivA::SetFirstControl( ControlA *firstControl )
{
	m_firstControl = firstControl;
}

ControlA* SplitLayoutDivA::GetSecondControl()
{
	return m_secondControl;
}

void SplitLayoutDivA::SetSecondControl( ControlA *secondControl )
{
	m_secondControl = secondControl;
}

SizeTypeA SplitLayoutDivA::GetSplitMode()
{
	return m_splitMode;
}

void SplitLayoutDivA::SetSplitMode( SizeTypeA splitMode )
{
	m_splitMode = splitMode;
}

ButtonA* SplitLayoutDivA::GetSplitter()
{
	return m_splitter;
}

String SplitLayoutDivA::GetControlType()
{
	return L"SplitLayoutDiv";
}

void SplitLayoutDivA::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"candragsplitter")
	{
		*type = L"bool";
		if (m_splitter)
		{
			*value = CStr::ConvertBoolToStr(m_splitter->AllowDrag());
		}
		else
		{
			*value = L"False";
		}
	}
	else if (name == L"splitmode")
	{
		*type = L"enum:SizeTypeA";
		if (GetSplitMode() == SizeTypeA_AbsoluteSize)
		{
			*value = L"AbsoluteSize";
		}
		else
		{
			*value = L"PercentSize";
		}
	}
	else if (name.find(L"splitter-") != -1)
	{
		if (m_splitter)
		{
			m_splitter->GetProperty(name.substr(9), value, type);
		}
	}
	else if (name == L"splitterposition")
	{
		*type = L"rect";
		if (m_splitter)
		{
			*value = CStr::ConvertRectToStr(m_splitter->GetBounds());
		}
		*value = L"0,0,0,0";
	}
	else if (name == L"splittervisible")
	{
		*type = L"bool";
		if (m_splitter)
		{
			*value = CStr::ConvertBoolToStr(m_splitter->IsVisible());
		}
		else
		{
			*value = L"False";
		}
	}
	else
	{
		LayoutDivA::GetProperty(name, value, type);
	}
}

vector<String> SplitLayoutDivA::GetPropertyNames()
{
	vector<String> propertyNames = LayoutDivA::GetPropertyNames();
	propertyNames.push_back(L"CanDragSplitter");
	propertyNames.push_back(L"SplitMode");
	propertyNames.push_back(L"Splitter");
	propertyNames.push_back(L"SplitterPosition");
	propertyNames.push_back(L"SplitterVisible");
	return propertyNames;
}

void SplitLayoutDivA::OnLoad()
{
	ControlA::OnLoad();
	if (!m_splitter)
	{
		ControlHost *host = GetNative()->GetHost();
		m_splitter = (ButtonA*)host->CreateInternalControl(this, L"splitter");
		m_splitter->RegisterEvent(m_splitterDraggingEvent, EVENTID::DRAGGING, this);
		AddControl(m_splitter);
	}
	m_oldSize = GetSize();
}

bool SplitLayoutDivA::OnResetLayout()
{
	bool flag = false;
	if (!GetNative() || !m_splitter || !m_firstControl|| !m_secondControl)
	{
		m_oldSize = GetSize();
		return flag;
	}
	RECT rect = {0, 0, 0, 0};
	int width = GetWidth();
	int height = GetHeight();
	RECT fRect = {0, 0, 0, 0};
	RECT sRect = {0, 0, 0, 0};
	SIZE size = {0, 0};
	if (m_splitter->IsVisible())
	{
		size.cx = m_splitter->GetWidth();
		size.cy = m_splitter->GetHeight();
	}
	LayoutStyleA layoutStyle = GetLayoutStyle();
	switch (layoutStyle)
	{
	case LayoutStyleA_BottomToTop:
		
		if ((m_splitMode != SizeTypeA_AbsoluteSize) && (m_oldSize.cy != 0))
		{
			if (m_splitMode == SizeTypeA_PercentSize)
			{
				rect.left = 0;
				if (CStr::ValueEqual(m_splitPercent, -1.0f))
				{
					m_splitPercent = (m_splitter->GetTop() / m_oldSize.cy);
				}
				rect.top = ((int)(height * m_splitPercent));
				rect.right = width;
				rect.bottom = rect.top + size.cy;
			}
		}
		else
		{
			rect.left = 0;
			rect.top = (height - (m_oldSize.cy - m_splitter->GetTop()));
			rect.right = width;
			rect.bottom = rect.top + size.cy;
		}
		fRect.left = 0;
		fRect.top = rect.bottom;
		fRect.right = width;
		fRect.bottom = height;
		sRect.left = 0;
		sRect.top = 0;
		sRect.right = width;
		sRect.bottom = rect.top;
		break;

	case LayoutStyleA_LeftToRight:
		if ((m_splitMode != SizeTypeA_AbsoluteSize) && (m_oldSize.cx != 0))
		{
			if (m_splitMode == SizeTypeA_PercentSize)
			{
				if (CStr::ValueEqual(m_splitPercent, -1.0f))
				{
					m_splitPercent = ((float) m_splitter->GetLeft()) / ((float) m_oldSize.cx);
				}
				rect.left = (int) (width * m_splitPercent);
				rect.top = 0;
				rect.right = rect.left + size.cx;
				rect.bottom = height;
			}
		}
		else
		{
			rect.left = m_splitter->GetLeft();
			rect.top = 0;
			rect.right = rect.left + size.cx;
			rect.bottom = height;
		}
		fRect.left = 0;
		fRect.top = 0;
		fRect.right = rect.left;
		fRect.bottom = height;
		sRect.left = rect.right;
		sRect.top = 0;
		sRect.right = width;
		sRect.bottom = height;
        break;

	case LayoutStyleA_RightToLeft:
		if ((m_splitMode != SizeTypeA_AbsoluteSize) && (m_oldSize.cx != 0))
		{
			if (m_splitMode == SizeTypeA_PercentSize)
			{
				if (CStr::ValueEqual(m_splitPercent, -1.0f))
				{
					m_splitPercent = ((float) m_splitter->GetLeft()) / ((float) m_oldSize.cx);
				}
				rect.left = (int) (width * m_splitPercent);
				rect.top = 0;
				rect.right = rect.left + size.cx;
				rect.bottom = height;
			}
		}
		else
		{
			rect.left = width - (m_oldSize.cx - m_splitter->GetLeft());
			rect.top = 0;
			rect.right = rect.left + size.cx;
			rect.bottom = height;
		}
		fRect.left = rect.right;
		fRect.top = 0;
		fRect.right = width;
		fRect.bottom = height;
		sRect.left = 0;
		sRect.top = 0;
		sRect.right = rect.left;
		sRect.bottom = height;
        break;

	case LayoutStyleA_TopToBottom:
		if ((m_splitMode != SizeTypeA_AbsoluteSize) && (m_oldSize.cy != 0))
		{
			if (m_splitMode == SizeTypeA_PercentSize)
			{
				rect.left = 0;
				if (CStr::ValueEqual(m_splitPercent, -1.0f))
				{
					m_splitPercent = ((float) m_splitter->GetTop()) / ((float) m_oldSize.cy);
				}
				rect.top = (int) (height * m_splitPercent);
				rect.right = width;
				rect.bottom = rect.top + size.cy;
			}
		}
		else
		{
			rect.left = 0;
			rect.top = m_splitter->GetTop();
			rect.right = width;
			rect.bottom = rect.top + size.cy;
		}
		fRect.left = 0;
		fRect.top = 0;
		fRect.right = width;
		fRect.bottom = rect.top;
		sRect.left = 0;
		sRect.top = rect.bottom;
		sRect.right = width;
		sRect.bottom = height;
        break;

	default:
        break;
	}
	if (m_splitter->IsVisible())
	{
		RECT spRect = m_splitter->GetBounds();
		if ((spRect.left != rect.left || spRect.top != rect.top) || (spRect.right != rect.right || spRect.bottom != rect.bottom))
		{
			m_splitter->SetBounds(rect);
			flag = true;
		}
		if (m_splitter->AllowDrag())
		{
			switch (layoutStyle)
			{
			case LayoutStyleA_LeftToRight:
			case LayoutStyleA_RightToLeft:
				m_splitter->SetCursor(CursorsA_SizeWE);
				break;

			default:
				m_splitter->SetCursor(CursorsA_SizeNS);
				break;
			}
			m_splitter->BringToFront();
		}
	}
	RECT bounds = m_firstControl->GetBounds();
	if ((bounds.left != fRect.left || bounds.top != fRect.top) || (bounds.right != fRect.right || bounds.bottom != fRect.bottom))
	{
		flag = true;
		m_firstControl->SetBounds(fRect);
		m_firstControl->Update();
	}
	RECT scRect = m_secondControl->GetBounds();
	if ((scRect.left != sRect.left || scRect.top != sRect.top) || (scRect.right != sRect.right || scRect.bottom != sRect.bottom))
	{
		flag = true;
		m_secondControl->SetBounds(sRect);
		m_secondControl->Update();
	}
	m_oldSize = GetSize();
	return flag;
}

void SplitLayoutDivA::OnSplitterDragging()
{
	m_splitPercent = -1.0f;
	Update();
	Invalidate();
}

void SplitLayoutDivA::SetProperty( const String& name, const String& value )
{
	if (name == L"candragsplitter")
	{
		if (m_splitter)
		{
			m_splitter->SetAllowDrag(CStr::ConvertStrToBool(value));
		}
	}
	else if (name == L"splitmode")
	{
		String temp = CStr::ToLower(value);
		if (temp == L"absolutesize")
		{
			SetSplitMode(SizeTypeA_AbsoluteSize);
		}
		else
		{
			SetSplitMode(SizeTypeA_PercentSize);
		}
	}
	else if (name.find(L"splitter-") != -1)
	{
		if (m_splitter)
		{
			m_splitter->SetProperty(name.substr(9), value);
		}
	}
	else if (name == L"splitterposition")
	{
		if (m_splitter)
		{
			m_splitter->SetBounds(CStr::ConvertStrToRect(value));
		}
	}
	else if (name == L"splittervisible")
	{
		if (m_splitter)
		{
			m_splitter->SetVisible(CStr::ConvertStrToBool(value));
		}
	}
	else
	{
		LayoutDivA::SetProperty(name, value);
	}
}

void SplitLayoutDivA::Update()
{
	OnResetLayout();
	int count = (int)m_controls.size();
	for (int i = 0; i < count; i++)
	{
		m_controls[i]->Update();
	}
}