#include "..\\stdafx.h"
#include "..\\include\\Window\\Window.h"
#include "..\\include\\Base\\CMathLib.h"
using namespace OwLib;

void WindowA::CallWindowClosingEvents( int eventID, bool *cancel )
{
	if (m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			WindowClosingEvent event2 = WindowClosingEvent(list->at(i));
			if (event2)
			{
				event2(this, cancel, &eventID);
			}
		}
	}
}

CursorsA WindowA::GetResizeCursor( int state )
{
	switch (state)
	{
	case 0:
		return CursorsA_SizeNWSE;

	case 1:
		return CursorsA_SizeNESW;

	case 2:
		return CursorsA_SizeNESW;

	case 3:
		return CursorsA_SizeNWSE;

	case 4:
		return CursorsA_SizeWE;

	case 5:
		return CursorsA_SizeNS;

	case 6:
		return CursorsA_SizeWE;

	case 7:
		return CursorsA_SizeNS;
	}
	return CursorsA_Arrow;
}

vector<RECT> WindowA::GetResizePoints()
{
	int width = GetWidth();
	int height = GetHeight();
	vector<RECT> vec;
	RECT rc1 = {0, 0, m_borderWidth * 2, m_borderWidth * 2};
	RECT rc2 = {0, height - (m_borderWidth * 2), m_borderWidth * 2, height};
	RECT rc3 = {width - (m_borderWidth * 2), 0, width, m_borderWidth * 2};
	RECT rc4 = {width - (m_borderWidth * 2), height - (m_borderWidth * 2), width, height};
	RECT rc5 = {0, 0, m_borderWidth, height};
	RECT rc6 = {0, 0, width, m_borderWidth};
	RECT rc7 = {width - m_borderWidth, 0, width, height};
	RECT rc8 = {0, height - m_borderWidth, width, height };
	vec.push_back(rc1);
	vec.push_back(rc2);
	vec.push_back(rc3);
	vec.push_back(rc4);
	vec.push_back(rc5);
	vec.push_back(rc6);
	vec.push_back(rc7);
	vec.push_back(rc8);
	return vec;
}

int WindowA::GetResizeState()
{
	POINT mousePoint = GetMousePoint();
	vector<RECT> resizePoints = GetResizePoints();
	int length = (int)resizePoints.size();
	for (int i = 0; i < length; i++)
	{
		RECT rect = resizePoints[i];
		if (mousePoint.x >= rect.left && mousePoint.x <= rect.right && mousePoint.y >= rect.top && mousePoint.y <= rect.bottom)
		{
			return i;
		}
	}
	return -1;
}

WindowA::WindowA()
{
	m_borderWidth = 2;
	m_canResize = false;
	m_captionHeight = 20;
	m_frame = 0;
	m_isDialog = false;
	m_resizePoint = -1;
	m_shadowColor = COLOR::ARGB(25, 255, 255, 255);
	m_shadowSize = 10;
	m_startMousePoint.x = 0;
	m_startMousePoint.y = 0;
	m_startRect.bottom = 0;
	m_startRect.left = 0;
	m_startRect.right = 0;
	m_startRect.top = 0;
	SetAllowDrag(true);
	SetWindow(true);
	SetVisible(false);
}

WindowA::~WindowA()
{
	if (m_frame)
	{
		m_frame->RemoveControl(this);
		GetNative()->RemoveControl(m_frame);
		delete m_frame;
	}
	m_frame = 0;
}

int WindowA::GetBorderWidth()
{
	return m_borderWidth;
}

void WindowA::SetBorderWidth( int borderWidth )
{
	m_borderWidth = borderWidth;
}

int WindowA::GetCaptionHeight()
{
	return m_captionHeight;
}

void WindowA::SetCaptionHeight( int captionHeight )
{
	m_captionHeight = captionHeight;
}

bool WindowA::CanResize()
{
	return m_canResize;
}

void WindowA::SetCanResize( bool canResize )
{
	m_canResize = canResize;
}

WindowFrameA* WindowA::GetFrame()
{
	return m_frame;
}

void WindowA::SetFrame( WindowFrameA *frame )
{
	m_frame = frame;
}

bool WindowA::IsDialog()
{
	return m_isDialog;
}

_int64 WindowA::GetShadowColor()
{
	return m_shadowColor;
}

void WindowA::SetShadowColor( _int64 shadowColor )
{
	m_shadowColor = shadowColor;
}

int WindowA::GetShadowSize()
{
	return m_shadowSize;
}

void WindowA::SetShadowSize( int shadowSize )
{
	m_shadowSize = shadowSize;
}

void WindowA::BringToFront()
{
	ControlA::BringToFront();
	if (m_frame)
	{
		m_frame->BringToFront();
	}
}

void WindowA::Close()
{
	bool cancel = false;
	OnWindowClosing(&cancel);
	if (!cancel)
	{
		if (m_frame)
		{
			m_frame->RemoveControl(this);
			GetNative()->RemoveControl(m_frame);
			delete m_frame;
			m_frame = 0;
			SetParent(0);
		}
		else
		{
			GetNative()->RemoveControl(this);
		}
		OnWindowClosed();
	}
}

String WindowA::GetControlType()
{
	return L"Window";
}

RECT WindowA::GetDynamicPaintRect()
{
	SIZE oldSize = m_oldSize;
	if (oldSize.cx == 0 && oldSize.cy == 0)
	{
		oldSize = GetSize();
	}
	RECT rect;
	rect.left = m_oldLocation.x;
	rect.top = m_oldLocation.y;
	rect.right = m_oldLocation.x + oldSize.cx;
	rect.bottom = m_oldLocation.y + oldSize.cy;
	RECT rect2;
	rect2.left = m_location.x;
	rect2.top = m_location.y;
	rect2.right = m_location.x + GetWidth();
	rect2.bottom = m_location.y + GetHeight();
	RECT rc;
	rc.left = min(rect.left, rect2.left) - m_shadowSize - 10;
	rc.top = min(rect.top, rect2.top) - m_shadowSize - 10;
	rc.right = (max(rect.right, rect2.right) + m_shadowSize) + 10;
	rc.bottom = (max(rect.bottom, rect2.bottom) + m_shadowSize) + 10;
	return rc;
}

vector<wstring> WindowA::GetEventNames()
{
	vector<wstring> events = ControlA::GetEventNames();
	events.push_back(L"WindowClosed");
	events.push_back(L"WindowClosing");
	return events;
}

void WindowA::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"borderwidth")
	{
		*type = L"int";
		*value = CStr::ConvertIntToStr(GetBorderWidth());
	}
	else if (name == L"canresize")
	{
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(CanResize());
	}
	else if (name == L"captionheight")
	{
		*type = L"int";
		*value = CStr::ConvertIntToStr(GetCaptionHeight());
	}
	else if (name == L"shadowcolor")
	{
		*type = L"color";
		*value = CStr::ConvertColorToStr(GetShadowColor());
	}
	else if (name == L"shadowsize")
	{
		*type = L"int";
		*value = CStr::ConvertIntToStr(GetShadowSize());
	}
	else
	{
		ControlA::GetProperty(name, value, type);
	}
}

vector<String> WindowA::GetPropertyNames()
{
	vector<wstring> propertyNames = ControlA::GetEventNames();
	propertyNames.push_back(L"BorderWidth");
	propertyNames.push_back(L"CanResize");
	propertyNames.push_back(L"CaptionHeight");
	propertyNames.push_back(L"ShadowColor");
	propertyNames.push_back(L"ShadowSize");
	return propertyNames;
}

bool WindowA::OnDragBegin()
{
	POINT mousePoint = GetMousePoint();
	int width = GetWidth();
	int height = GetHeight();
	if (mousePoint.y > m_captionHeight)
	{
		return false;
	}
	if (m_resizePoint != -1)
	{
		return false;
	}
	return ControlA::OnDragBegin();
}

void WindowA::OnDragReady( POINT *startOffset )
{
	startOffset->x = 0;
	startOffset->y = 0;
}

void WindowA::OnMouseDown( POINT mp, MouseButtonsA button, int clicks, int delta )
{
	ControlA::OnMouseDown(mp, button, clicks, delta);
	if (button == MouseButtonsA_Left && clicks == 1 && m_canResize)
	{
		m_resizePoint = GetResizeState();
		SetCursor(GetResizeCursor(m_resizePoint));
		m_startMousePoint = GetNative()->GetMousePoint();
		m_startRect = GetBounds();
	}
	Invalidate();
}

void WindowA::OnMouseMove( POINT mp, MouseButtonsA button, int clicks, int delta )
{
	ControlA::OnMouseMove(mp, button, clicks, delta);
	if (m_canResize)
	{
		POINT mousePoint = GetNative()->GetMousePoint();
		if (m_resizePoint != -1)
		{
			int left = m_startRect.left;
			int top = m_startRect.top;
			int right = m_startRect.right;
			int bottom = m_startRect.bottom;
			CMathLib::M137(m_resizePoint, &left, &top, &right, &bottom, &mousePoint, &m_startMousePoint);
			RECT rect = {left, top, right, bottom};
			SetBounds(rect);
			GetNative()->Invalidate();
		}
		else
		{
			SetCursor(GetResizeCursor(GetResizeState()));
		}
	}
}

void WindowA::OnMouseUp( POINT mp, MouseButtonsA button, int clicks, int delta )
{
	ControlA::OnMouseUp(mp, button, clicks, delta);
	m_resizePoint = -1;
	Invalidate();
}

void WindowA::OnPaintForeground( CPaint *paint, const RECT& clipRect )
{
	String text = GetText();
	if (!text.empty())
	{
		int width = GetWidth();
		FONT *font = GetFont();
		SIZE size = paint->TextSize(text.c_str(), font);
		POINT point = {0, 0};
		point.x = 5;
		point.y = (m_captionHeight - size.cy) / 2;
		RECT rect = {point.x, point.y, point.x + size.cx, point.y + size.cy};
		paint->DrawText(text.c_str(), GetPaintingForeColor(), font, rect);
	}
}

void WindowA::OnVisibleChanged()
{
	ControlA::OnVisibleChanged();
	NativeBase *native = GetNative();
	if (native)
	{
		if (IsVisible())
		{
			if (m_frame == 0)
			{
				m_frame = new WindowFrameA();
			}
			native->RemoveControl(this);
			native->AddControl(m_frame);
			m_frame->SetSize(native->GetDisplaySize());
			if (!m_frame->ContainsControl(this))
			{
				m_frame->AddControl(this);
			}
		}
		else if (m_frame != 0)
		{
			m_frame->RemoveControl(this);
			native->RemoveControl(m_frame);
		}
	}
}

void WindowA::OnWindowClosing( bool *cancel )
{
	CallWindowClosingEvents(EVENTID::WINDOWCLOSING, cancel);
}

void WindowA::OnWindowClosed()
{
	CallEvents(EVENTID::WINDOWCLOSED);
}

void WindowA::SendToBack()
{
	SendToBack();
	if (m_frame)
	{
		m_frame->SendToBack();
	}
}

void WindowA::SetProperty( const String& name, const String& value )
{
	if (name == L"borderwidth")
	{
		SetBorderWidth(CStr::ConvertStrToInt(value));
	}
	else if (name == L"canresize")
	{
		SetCanResize(CStr::ConvertStrToBool(value));
	}
	else if (name == L"captionheight")
	{
		SetCaptionHeight(CStr::ConvertStrToInt(value));
	}
	else if (name == L"shadowcolor")
	{
		SetShadowColor(CStr::ConvertStrToColor(value));
	}
	else if (name == L"shadowsize")
	{
		SetShadowSize(CStr::ConvertStrToInt(value));
	}
	else
	{
		ControlA::SetProperty(name, value);
	}
}

void WindowA::ShowDialog()
{
	m_isDialog = true;
	Show();
}