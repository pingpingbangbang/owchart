#include "..\\stdafx.h"
#include "..\\include\\Layout\\Div.h"
#include "..\\include\\Grid\\GridColumn.h"
using namespace OwLib;

void DivA::ScrollButtonKeyDown( void *sender, char key, void *pInvoke )
{
	DivA *divA = (DivA *)pInvoke;
	if(divA)
	{
		divA->OnKeyDown(key);
	}
}

void DivA::ScrollButtonMouseWheel( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	DivA *divA = (DivA *)pInvoke;
	if(divA)
	{
		divA->OnMouseWheel(mp, button, clicks, delta);
	}
}

DivA::DivA()
{
	m_allowDragScroll = false;
	m_hScrollBar = 0;
	m_isDragScrolling = false;
	m_isDragScrolling2 = false;
	m_readyToDragScroll = false;
	m_scrollButtonKeyDownEvent = &ScrollButtonKeyDown;
	m_scrollButtonMouseWheelEvent = &ScrollButtonMouseWheel;
	m_showHScrollBar = false;
	m_showVScrollBar = false;
	m_startMovePoint.x = 0;
	m_startMovePoint.y = 0;
	m_startMovePosX = 0;
	m_startMovePosY = 0;
	m_startMoveTime = 0;
	m_vScrollBar = 0;
	SIZE sz = {200, 200};
	SetSize(sz);
}

DivA::~DivA()
{
	m_hScrollBar = 0;
	m_scrollButtonKeyDownEvent = 0;
	m_scrollButtonMouseWheelEvent = 0;
	m_vScrollBar = 0;
}

bool DivA::AllowDragScroll()
{
	return m_allowDragScroll;
}

void DivA::SetAllowDragScroll( bool allowDragScroll )
{
	m_allowDragScroll = allowDragScroll;
}

HScrollBarA* DivA::GetHScrollBar()
{
	NativeBase* base = GetNative();
	if (!base || !m_showHScrollBar)
	{
		return 0;
	}
	if (!m_hScrollBar)
	{
		ControlHost *host = base->GetHost();
		m_hScrollBar = (HScrollBarA *)host->CreateInternalControl(this, L"hscrollbar");
		AddControl(m_hScrollBar);
		m_hScrollBar->GetAddButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_hScrollBar->GetAddButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		m_hScrollBar->GetBackButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_hScrollBar->GetBackButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		m_hScrollBar->GetReduceButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_hScrollBar->GetReduceButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		m_hScrollBar->GetScrollButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_hScrollBar->GetScrollButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
	}
	return m_hScrollBar;
}

bool DivA::ShowHScrollBar()
{
	return m_showHScrollBar;
}

void DivA::SetShowHScrollBar( bool showHScrollBar )
{
	m_showHScrollBar = showHScrollBar;
}

bool DivA::IsDragScrolling()
{
	return m_isDragScrolling;
}

bool DivA::ShowVScrollBar()
{
	return m_showVScrollBar;
}

void DivA::SetShowVScrollBar( bool showVScrollBar )
{
	m_showVScrollBar = showVScrollBar;
}

VScrollBarA* DivA::GetVScrollBar()
{
	if (!GetNative() || !m_showVScrollBar)
	{
		return 0;
	}
	if (!m_vScrollBar)
	{
		ControlHost *host = GetNative()->GetHost();
		m_vScrollBar = (VScrollBarA *)host->CreateInternalControl(this, L"vscrollbar");
		AddControl(m_vScrollBar);
		m_vScrollBar->GetAddButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_vScrollBar->GetAddButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		m_vScrollBar->GetBackButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_vScrollBar->GetBackButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		m_vScrollBar->GetReduceButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_vScrollBar->GetReduceButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		m_vScrollBar->GetScrollButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_vScrollBar->GetScrollButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
	}
	return m_vScrollBar;
}

int DivA::GetContentHeight()
{
	HScrollBarA *hScrollBar = GetHScrollBar();
	VScrollBarA *vScrollBar = GetVScrollBar();
	int hmax = 0;
	vector<ControlA*> controls = GetControls();
	int count = (int)controls.size();
	for (int i = 0; i < count; i++)
	{
		ControlA *control = controls[i];
		if ((control->IsVisible() && (control != hScrollBar)) && (control != vScrollBar))
		{
			int bottom = control->GetBottom();
			if (bottom > hmax)
			{
				hmax = bottom;
			}
		}
	}
	return hmax;
}

int DivA::GetContentWidth()
{
	HScrollBarA *hScrollBar = GetHScrollBar();
	VScrollBarA *vScrollBar = GetVScrollBar();
	int wmax = 0;
	vector<ControlA*> controls = GetControls();
	int count = (int)controls.size();
	for (int i = 0; i < count; i++)
	{
		ControlA *control = controls[i];
		if ((control->IsVisible() && (control != hScrollBar)) && (control != vScrollBar))
		{
			int right = control->GetRight();
			if (right > wmax)
			{
				wmax = right;
			}
		}
	}
	return wmax;
}

String DivA::GetControlType()
{
	return L"Div";
}

POINT DivA::GetDisplayOffset()
{
	POINT point = {0, 0};
	if (IsVisible())
	{
		point.x = m_hScrollBar && m_hScrollBar->IsVisible() ? m_hScrollBar->GetPos() : 0;
		point.y = m_vScrollBar && m_vScrollBar->IsVisible() ? m_vScrollBar->GetPos() : 0;
	}
	return point;
}

void DivA::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"allowdragscroll")
	{
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(AllowDragScroll());
	}
	else if (name == L"showhscrollbar")
	{
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(ShowHScrollBar());
	}
	else if (name == L"showvscrollbar")
	{
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(ShowVScrollBar());
	}
	else
	{
		ControlA::GetProperty(name, value, type);
	}
}

vector<String> DivA::GetPropertyNames()
{
	vector<String> propertyNames = ControlA::GetPropertyNames();
	propertyNames.push_back(L"AllowDragScroll");
	propertyNames.push_back(L"ShowHScrollBar");
	propertyNames.push_back(L"ShowVScrollBar");
	return propertyNames;
}

void DivA::LineDown()
{
	if (m_vScrollBar && m_vScrollBar->IsVisible())
	{
		m_vScrollBar->LineAdd();
	}
}

void DivA::LineLeft()
{
	if (m_hScrollBar && m_hScrollBar->IsVisible())
	{
		m_hScrollBar->LineReduce();
	}
}

void DivA::LineRight()
{
	if (m_hScrollBar && m_hScrollBar->IsVisible())
	{
		m_hScrollBar->LineAdd();
	}
}

void DivA::LineUp()
{
	if (m_vScrollBar && m_vScrollBar->IsVisible())
	{
		m_vScrollBar->LineReduce();
	}
}

void DivA::OnDragReady( POINT *startOffset )
{
	startOffset->x = 0;
	startOffset->y = 0;
}

void DivA::OnDragScrollEnd()
{
	m_allowDragScroll = false;
	if (m_readyToDragScroll)
	{
		DWORD now = GetTickCount();
		POINT mousePoint = GetNative()->GetMousePoint();
		if (m_hScrollBar && m_hScrollBar->IsVisible())
		{
			m_hScrollBar->OnAddSpeedScrollStart(m_startMoveTime, now, m_startMovePoint.x, mousePoint.x);
		}
		if (m_vScrollBar && m_vScrollBar->IsVisible())
		{
			m_vScrollBar->OnAddSpeedScrollStart(m_startMoveTime, now, m_startMovePoint.y, mousePoint.y);
		}
		m_readyToDragScroll = false;
		Invalidate();
	}
}

void DivA::OnDragScrolling()
{
	int width = GetWidth();
	int height = GetHeight();
	if (m_allowDragScroll && m_readyToDragScroll)
	{
		if (!OnDragScrollPermit())
		{
			m_readyToDragScroll = false;
		}
		else
		{
			bool paint = false;
			POINT newPoint = GetNative()->GetMousePoint();
			if (m_hScrollBar && m_hScrollBar->IsVisible())
			{
				if (abs(m_startMovePoint.x - newPoint.x) > width / 10) {
					m_isDragScrolling2 = true;
				}
				int newPos = m_startMovePosX + m_startMovePoint.x - newPoint.x;
				if (newPos != m_hScrollBar->GetPos())
				{
					m_hScrollBar->SetPos(newPos);
					m_hScrollBar->Update();
					paint = true;
				}
			}
			if (m_vScrollBar && m_vScrollBar->IsVisible())
			{
				if (abs(m_startMovePoint.y - newPoint.y) > height / 10) {
					m_isDragScrolling2 = true;
				}
				int vPos = m_startMovePosY + m_startMovePoint.y - newPoint.y;
				if (vPos != m_vScrollBar->GetPos())
				{
					m_vScrollBar->SetPos(vPos);
					m_vScrollBar->Update();
					paint = true;
				}
			}
			if (paint)
			{
				m_isDragScrolling = true;
				Invalidate();
			}
		}
	}
}

bool DivA::OnDragScrollPermit()
{
	ControlA *focusedControl = GetNative()->GetFocusedControl();
	if (focusedControl)
	{
		if (focusedControl->IsDragging())
		{
			return false;
		}
		if (dynamic_cast<GridColumn*>(focusedControl))
		{
			return false;
		}
		if (focusedControl->GetParent() && dynamic_cast<ScrollBarA*>(focusedControl->GetParent()))
		{
			return false;
		}
	}
	return true;
}

void DivA::OnDragScrollStart()
{
	m_isDragScrolling = false;
	m_isDragScrolling2 = false;
	ControlA *focusedControl = GetNative()->GetFocusedControl();
	if (m_hScrollBar && m_hScrollBar->IsVisible())
	{
		if((focusedControl == m_hScrollBar->GetAddButton() && 
			m_hScrollBar->GetAddButton()->IsVisible())
			|| (focusedControl == m_hScrollBar->GetBackButton() && 
			m_hScrollBar->GetBackButton()->IsVisible())
			|| (focusedControl == m_hScrollBar->GetReduceButton() && 
			m_hScrollBar->GetReduceButton()->IsVisible())
			|| (focusedControl == m_hScrollBar->GetScrollButton() && 
			m_hScrollBar->GetScrollButton()->IsVisible()))
		{
			m_hScrollBar->SetAddSpeed(0);
		}
	}
	else if (m_vScrollBar && m_vScrollBar->IsVisible())
	{
		if((focusedControl == m_vScrollBar->GetAddButton() && 
			m_hScrollBar->GetAddButton()->IsVisible())
			|| (focusedControl == m_vScrollBar->GetBackButton() && 
			m_vScrollBar->GetBackButton()->IsVisible())
			|| (focusedControl == m_vScrollBar->GetReduceButton() && 
			m_hScrollBar->GetReduceButton()->IsVisible())
			|| (focusedControl == m_vScrollBar->GetScrollButton() && 
			m_vScrollBar->GetScrollButton()->IsVisible()))
		{
			m_hScrollBar->SetAddSpeed(0);
		}
	}
	else if (m_allowDragScroll)
	{
		if (m_hScrollBar && m_hScrollBar->IsVisible())
		{
			m_startMovePosX = m_hScrollBar->GetPos();
			m_hScrollBar->SetAddSpeed(0);
			m_readyToDragScroll = true;
		}
		if (m_vScrollBar && m_vScrollBar->IsVisible())
		{
			m_startMovePosY = m_vScrollBar->GetPos();
			m_vScrollBar->SetAddSpeed(0);
			m_readyToDragScroll = true;
		}
		if (m_readyToDragScroll)
		{
			m_startMovePoint = GetNative()->GetMousePoint();
			m_startMoveTime =  GetTickCount();
		}
	}
}

void DivA::OnKeyDown( char key )
{
	ControlA::OnKeyDown(key);
	ControlHost *host = GetNative()->GetHost();
	if ((!host->IsKeyPress(0x10) && !host->IsKeyPress(0x11)) && !host->IsKeyPress(0x12))
	{
		if (key == '&')
		{
			LineUp();
		}
		else if (key == '(')
		{
			LineDown();
		}
		Invalidate();
	}
}

void DivA::OnMouseDown( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	ControlA::OnMouseDown(mp, button, clicks, delta);
	if (!m_allowPreviewsEvent)
	{
		OnDragScrollStart();
	}
}

void DivA::OnMouseMove( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	ControlA::OnMouseMove(mp, button, clicks, delta);
	if (!m_allowPreviewsEvent)
	{
		OnDragScrolling();
	}
}

void DivA::OnMouseUp( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	ControlA::OnMouseUp(mp, button, clicks, delta);
	if (!m_allowPreviewsEvent)
	{
		OnDragScrollEnd();
	}
}

void DivA::OnMouseWheel( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	ControlA::OnMouseWheel(mp, button, clicks, delta);
	if (delta > 0)
	{
		LineUp();
		Invalidate();
	}
	else if (delta < 0)
	{
		LineDown();
		Invalidate();
	}
}

bool DivA::OnPreviewsMouseEvent( int eventID, const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	if (m_allowPreviewsEvent)
	{
		if (eventID == EVENTID::MOUSEDOWN)
		{
			OnDragScrollStart();
		}
		else if (eventID == EVENTID::MOUSEMOVE)
		{
			OnDragScrolling();
		}
		else if (eventID == EVENTID::MOUSEUP)
		{
			bool isDragScrolling = m_isDragScrolling;
			OnDragScrollEnd();
			if(isDragScrolling)
			{
				if(!m_isDragScrolling2)
				{
					return false;
				}
			}
		}
	}
	return false;
}

void DivA::PageDown()
{
	if (m_vScrollBar && m_vScrollBar->IsVisible())
	{
		m_vScrollBar->PageAdd();
	}
}

void DivA::PageLeft()
{
	if (m_hScrollBar && m_hScrollBar->IsVisible())
	{
		m_hScrollBar->PageReduce();
	}
}

void DivA::PageRight()
{
	if (m_hScrollBar && m_hScrollBar->IsVisible())
	{
		m_hScrollBar->PageAdd();
	}
}

void DivA::PageUp()
{
	if (m_vScrollBar && m_vScrollBar->IsVisible())
	{
		m_vScrollBar->PageReduce();
	}
}

void DivA::SetProperty( const String& name, const String& value )
{
	if (name == L"allowdragscroll")
	{
		SetAllowDragScroll(CStr::ConvertStrToBool(value));
	}
	else if (name == L"showhscrollbar")
	{
		SetShowHScrollBar(CStr::ConvertStrToBool(value));
	}
	else if (name == L"showvscrollbar")
	{
		SetShowVScrollBar(CStr::ConvertStrToBool(value));
	}
	else
	{
		ControlA::SetProperty(name, value);
	}
}

void DivA::Update()
{
	ControlA::Update();
	UpdateScrollBar();
}

void DivA::UpdateScrollBar()
{
	if (GetNative())
	{
		HScrollBarA *hScrollBar = GetHScrollBar();
		VScrollBarA *vScrollBar = GetVScrollBar();
		if (IsVisible())
		{
			int width = GetWidth();
			int height = GetHeight();
			int cy = hScrollBar ? hScrollBar->GetHeight(): 0;
			int cx = vScrollBar ? vScrollBar->GetWidth() : 0;
			int contentWidth = GetContentWidth();
			int contentHeight = GetContentHeight();
			if (hScrollBar)
			{
				hScrollBar->SetContentSize(contentWidth);
				SIZE sz = {width - cx, cy};
				hScrollBar->SetSize(sz);
				hScrollBar->SetPageSize(width - cx);
				POINT pptt = {0, height - cy};
				hScrollBar->SetLocation(pptt);
				if (contentWidth <= width)
				{
					hScrollBar->SetVisible(false);
				}
				else
				{
					hScrollBar->SetVisible(true);
				}
			}
			if (vScrollBar)
			{
				vScrollBar->SetContentSize(contentHeight);
				SIZE sz = {cx, height - cy};
				vScrollBar->SetSize(sz);
				vScrollBar->SetPageSize(height - cy);
				POINT pptt = {width - cx, 0};
				vScrollBar->SetLocation(pptt);
				int num7 = (hScrollBar && hScrollBar->IsVisible()) ? (height - cy) : height;
				if (contentHeight <= num7)
				{
					vScrollBar->SetVisible(false);
				}
				else
				{
					vScrollBar->SetVisible(true);
				}
			}
			if (hScrollBar && vScrollBar)
			{
				if (hScrollBar->IsVisible() && !vScrollBar->IsVisible())
				{
					hScrollBar->SetWidth(width);
					hScrollBar->SetPageSize(width);
				}
				else if (!hScrollBar->IsVisible() && vScrollBar->IsVisible())
				{
					vScrollBar->SetHeight(height);
					vScrollBar->SetPageSize(height);
				}
			}
			if (hScrollBar && hScrollBar->IsVisible())
			{
				hScrollBar->Update();
			}
			if (vScrollBar && vScrollBar->IsVisible())
			{
				vScrollBar->Update();
			}
		}
	}
}
