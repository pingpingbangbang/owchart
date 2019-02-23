#include "..\\stdafx.h"
#include "..\\include\\ScrollBar\\ScrollBar.h"
using namespace OwLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBarA::AddButtonMouseDown( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	ScrollBarA *pThis = (ScrollBarA*)pInvoke;
	if(pThis)
	{
		pThis->OnAddButtonMouseDown(mp, button, clicks, delta);
	}
}

void ScrollBarA::AddButtonMouseUp( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	ScrollBarA *pThis = (ScrollBarA*)pInvoke;
	if(pThis)
	{
		pThis->OnAddButtonMouseUp( mp, button, clicks, delta);
	}
}

void ScrollBarA::ReduceButtonMouseDown( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	ScrollBarA *pThis = (ScrollBarA*)pInvoke;
	if(pThis)
	{
		pThis->OnReduceButtonMouseDown(mp, button, clicks, delta);
	}
}

void ScrollBarA::ReduceButtonMouseUp( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	ScrollBarA *pThis = (ScrollBarA*)pInvoke;
	if(pThis)
	{
		pThis->OnReduceButtonMouseUp(mp, button, clicks, delta);
	}
}

void ScrollBarA::ScrollButtonDragging( void *sender, void *pInvoke )
{
	ScrollBarA *pThis = (ScrollBarA*)pInvoke;
	if(pThis)
	{
		pThis->OnDragScroll();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScrollBarA::ScrollBarA()
{
	m_addButton = 0;
	m_addSpeed = 0;
	m_backButton = 0;
	m_contentSize = 0;
	m_isAdding = false;
	m_isReducing = false;
	m_lineSize = 10;
	m_pageSize = 0;
	m_pos = 0;
	m_reduceButton = 0;
	m_scrollButton = 0;
	m_tick = 0;
	m_timerID = GetNewTimerID();
	m_addButtonMouseDownEvent = &AddButtonMouseDown;
	m_addButtonMouseUpEvent = &AddButtonMouseUp;
	m_reduceButtonMouseDownEvent = &ReduceButtonMouseDown;
	m_reduceButtonMouseUpEvent = &ReduceButtonMouseUp;
	m_scrollButtonDraggingEvent = &ScrollButtonDragging;

	SetCanFocus(false);
	SetDisplayOffset(false);
	SIZE sz = {20, 20};
	SetSize(sz);
	SetTopMost(true);
}

ScrollBarA::~ScrollBarA()
{
	StopTimer(m_timerID);
	if (m_addButton)
	{
		if (m_addButtonMouseDownEvent)
		{
			m_addButton->UnRegisterEvent(m_addButtonMouseDownEvent, EVENTID::MOUSEDOWN);
			m_addButtonMouseDownEvent = 0;
		}
		if (m_addButtonMouseUpEvent)
		{
			m_addButton->UnRegisterEvent(m_addButtonMouseUpEvent, EVENTID::MOUSEUP);
			m_addButtonMouseUpEvent = 0;
		}
	}
	if (m_scrollButton && m_scrollButtonDraggingEvent)
	{
		m_scrollButton->UnRegisterEvent(m_scrollButtonDraggingEvent, EVENTID::DRAGGING);
		m_scrollButtonDraggingEvent = 0;
	}
	if (m_reduceButton)
	{
		if (m_reduceButtonMouseDownEvent)
		{
			m_reduceButton->UnRegisterEvent(m_reduceButtonMouseDownEvent, EVENTID::MOUSEDOWN);
			m_reduceButtonMouseDownEvent = 0;
		}
		if (m_reduceButtonMouseUpEvent)
		{
			m_reduceButton->UnRegisterEvent(m_reduceButtonMouseUpEvent, EVENTID::MOUSEUP);
			m_reduceButtonMouseUpEvent = 0;
		}
	}
	m_addButton = 0;
	m_backButton = 0;
	m_reduceButton = 0;
	m_scrollButton = 0;
}

ButtonA* ScrollBarA::GetAddButton()
{
	return m_addButton;
}

int ScrollBarA::GetAddSpeed()
{
	return m_addSpeed;
}

void ScrollBarA::SetAddSpeed( int addSpeed )
{
	m_addSpeed = addSpeed;
	if (m_addSpeed != 0)
	{
		StartTimer(m_timerID, 10);
	} 
	else
	{
		StopTimer(m_timerID);
	}
}

ButtonA* ScrollBarA::GetBackButton()
{
	return m_backButton;
}

int ScrollBarA::GetContentSize()
{
	return m_contentSize;
}

void ScrollBarA::SetContentSize( int contentWidth )
{
	m_contentSize = contentWidth;
}

bool ScrollBarA::IsAdding()
{
	return m_isAdding;
}

void ScrollBarA::SetIsAdding( bool isAdding )
{
	m_isAdding = isAdding;
	m_tick = 0;
	if (m_isAdding)
	{
		StartTimer(m_timerID, 100);
	}
	else
	{
		StopTimer(m_timerID);
	}
}

bool ScrollBarA::IsReducing()
{
	return m_isReducing;
}

void ScrollBarA::SetIsReducing( bool isReducing )
{
	m_isReducing = isReducing;
	m_tick = 0;
	if (m_isReducing)
	{
		StartTimer(m_timerID, 100);
	}
	else
	{
		StopTimer(m_timerID);
	}
}

int ScrollBarA::GetLineSize()
{
	return m_lineSize;
}

void ScrollBarA::SetLineSize( int lineSize )
{
	m_lineSize = lineSize;
}

int ScrollBarA::GetPageSize()
{
	return m_pageSize;
}

void ScrollBarA::SetPageSize( int pageSize )
{
	m_pageSize = pageSize;
}

int ScrollBarA::GetPos()
{
	return m_pos;
}

void ScrollBarA::SetPos( int pos )
{
	m_pos = pos;   
	if (m_pos > (m_contentSize - m_pageSize))
	{
		m_pos = m_contentSize - m_pageSize;
	}
	if (m_pos < 0)
	{
		m_pos = 0;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonA* ScrollBarA::GetReduceButton()
{
	return m_reduceButton;
}

ButtonA* ScrollBarA::GetScrollButton()
{
	return m_scrollButton;
}

vector<wstring> ScrollBarA::GetEventNames()
{
	vector<wstring> ws;
	ws.push_back(L"Scrolled");
	return ws;

}
String ScrollBarA::GetControlType()
{
	return L"ScrollBar";
}

void ScrollBarA::LineAdd()
{
	m_pos += m_lineSize;
	if (m_pos > m_contentSize - m_pageSize)
	{
		m_pos = m_contentSize - m_pageSize;
	}
	Update();
	OnScrolled();
}

void ScrollBarA::LineReduce()
{
	m_pos -= m_lineSize;
	if (m_pos < 0)
	{
		m_pos = 0;
	}
	Update();
	OnScrolled();
}

void ScrollBarA::OnAddButtonMouseDown( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	LineAdd();
	SetIsAdding(true);
}

void ScrollBarA::OnAddButtonMouseUp( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	SetIsAdding(false);
}

void ScrollBarA::OnAddSpeedScrollEnd()
{

}

void ScrollBarA::OnAddSpeedScrollStart( DWORD startTime, DWORD nowTime, int start, int end )
{
	int diff = (int) ((nowTime - startTime) / 1000000);
	if (diff > 0 && diff < 800)
	{
		int sub = (5000 * (abs((int) (start - end)) / 20)) / diff;
		if (start > end)
		{
			m_addSpeed += sub;
		}
		else if (start < end)
		{
			m_addSpeed -= sub;
		}
	}
}

int ScrollBarA::OnAddSpeedScrolling()
{
	int num = m_addSpeed / 10;
	if (num == 0)
	{
		num = (m_addSpeed > 0) ? 1 : -1;
	}
	return num;
}

void ScrollBarA::OnDragScroll()
{
	if (m_scrollButton->GetLeft() < 0)
	{
		m_scrollButton->SetLeft(0);
	}
	if (m_scrollButton->GetTop() < 0)
	{
		m_scrollButton->SetTop(0);
	}
	if (m_scrollButton->GetRight() > m_backButton->GetWidth())
	{
		m_scrollButton->SetLeft(m_backButton->GetWidth() - m_scrollButton->GetWidth());
	}
	if (m_scrollButton->GetBottom() > m_backButton->GetHeight())
	{
		m_scrollButton->SetTop(m_backButton->GetHeight() - m_scrollButton->GetHeight());
	}
}

void ScrollBarA::OnLoad()
{
	ControlA::OnLoad();
	ControlHost *host = GetNative()->GetHost();
	if (!m_addButton)
	{
		m_addButton = (ButtonA*)host->CreateInternalControl(this, L"addbutton");
		m_addButton->RegisterEvent(m_addButtonMouseDownEvent, EVENTID::MOUSEDOWN, this);
		m_addButton->RegisterEvent(m_addButtonMouseUpEvent, EVENTID::MOUSEUP, this);
		AddControl(m_addButton);
	}
	if (!m_backButton)
	{
		m_backButton = (ButtonA*)host->CreateInternalControl(this, L"backbutton");
		AddControl(m_backButton);
	}
	if (!m_reduceButton)
	{
		m_reduceButton = (ButtonA*)host->CreateInternalControl(this, L"reducebutton");
		m_reduceButton->RegisterEvent(m_reduceButtonMouseDownEvent, EVENTID::MOUSEDOWN, this);
		m_reduceButton->RegisterEvent(m_reduceButtonMouseUpEvent, EVENTID::MOUSEUP, this);
		AddControl(m_reduceButton);
	}
	if (!m_scrollButton)
	{
		m_scrollButton = (ButtonA*)host->CreateInternalControl(this, L"scrollbutton");
		m_scrollButton->SetAllowDrag(true);
		m_scrollButton->RegisterEvent(m_scrollButtonDraggingEvent, EVENTID::DRAGGING, this);
		m_backButton->AddControl(m_scrollButton);
	}
}

void ScrollBarA::OnReduceButtonMouseDown( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	LineReduce();
	SetIsReducing(true);
}

void ScrollBarA::OnReduceButtonMouseUp( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	SetIsReducing(false);
}

void ScrollBarA::OnScrolled()
{
	ControlA::CallEvents(EVENTID::SCROLLED);
	ControlA *parent = GetParent();
	if (parent)
	{
		parent->Invalidate();
	}
}

void ScrollBarA::OnVisibleChanged()
{
	ControlA::OnVisibleChanged();
	if (!IsVisible())
	{
		m_pos = 0;
	}
}

void ScrollBarA::PageAdd()
{
	m_pos += m_pageSize;
	if (m_pos > m_contentSize - m_pageSize)
	{
		m_pos = m_contentSize - m_pageSize;
	}
	Update();
	OnScrolled();
}

void ScrollBarA::PageReduce()
{
	m_pos -= m_pageSize;
	if (m_pos < 0)
	{
		m_pos = 0;
	}
	Update();
	OnScrolled();
}

void ScrollBarA::ScrollToBegin()
{
	m_pos = 0;
	Update();
	OnScrolled();
}

void ScrollBarA::ScrollToEnd()
{
	m_pos = m_contentSize - m_pageSize;
	if (m_pos < 0)
	{
		m_pos = 0;
	}
	Update();
	OnScrolled();
}

void ScrollBarA::OnTimer( int timerID )
{
	ControlA::OnTimer(timerID);
	if (m_timerID == timerID)
	{
		if (m_isAdding)
		{
			if (m_tick > 5)
			{
				PageAdd();
			}
			else
			{
				LineAdd();
			}
		}
		if (m_isReducing)
		{
			if (m_tick > 5)
			{
				PageReduce();
			}
			else
			{
				LineReduce();
			}
		}
		if (m_addSpeed != 0)
		{
			int num = OnAddSpeedScrolling();
			m_pos += num;
			Update();
			OnScrolled();
			m_addSpeed -= num;
			if (abs(m_addSpeed) < 3)
			{
				m_addSpeed = 0;
			}
			if (m_addSpeed == 0)
			{
				OnAddSpeedScrollEnd();
				StopTimer(m_timerID);
				if (GetParent())
				{
					GetParent()->Invalidate();
				}
			}
		}
		m_tick++;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////