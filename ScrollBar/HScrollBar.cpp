#include "..\\stdafx.h"
#include "..\\include\\ScrollBar\\HScrollBar.h"
using namespace OwLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HScrollBarA::BackButtonMouseDown( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	HScrollBarA *pThis = (HScrollBarA*)pInvoke;
	if(pThis)
	{
		pThis->OnBackButtonMouseDown(mp, button, clicks, delta);
	}
}

void HScrollBarA::BackButtonMouseUp( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	HScrollBarA *pThis = (HScrollBarA*)pInvoke;
	if(pThis)
	{
		pThis->OnBackButtonMouseUp(mp, button, clicks, delta);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HScrollBarA::HScrollBarA()
{
	m_backButtonMouseDownEvent = &BackButtonMouseDown;
	m_backButtonMouseUpEvent = &BackButtonMouseUp;
}

HScrollBarA::~HScrollBarA()
{
	if (m_backButton)
	{
		if (m_backButtonMouseDownEvent)
		{
			m_backButton->UnRegisterEvent(m_backButtonMouseDownEvent, EVENTID::MOUSEDOWN);
			m_backButtonMouseDownEvent = 0;
		}
		if (m_backButtonMouseUpEvent)
		{
			m_backButton->UnRegisterEvent(m_backButtonMouseUpEvent, EVENTID::MOUSEUP);
			m_backButtonMouseUpEvent = 0;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String HScrollBarA::GetControlType()
{
	return L"HScrollBar";
}

void HScrollBarA::OnBackButtonMouseDown( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	ButtonA *scrollButton = GetScrollButton();
	if (mp.x < scrollButton->GetLeft())
	{
		PageReduce();
		SetIsReducing(true);
	}
	else if (mp.x > scrollButton->GetRight())
	{
		PageAdd();
		SetIsAdding(true);
	}
}

void HScrollBarA::OnBackButtonMouseUp( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	SetIsAdding(false);
	SetIsReducing(false);
}

void HScrollBarA::OnDragScroll()
{
	bool flag = false;
	ButtonA *backButton = GetBackButton();
	ButtonA *scrollButton = GetScrollButton();
	int width = backButton->GetWidth();
	int contentSize = GetContentSize();
	if (scrollButton->GetRight() > width)
	{
		flag = true;
	}
	ScrollBarA::OnDragScroll();
	if (flag)
	{
		SetPos(contentSize);
	}
	else
	{
		SetPos((int) (contentSize * scrollButton->GetLeft() / (_int64) width));
	}
	OnScrolled();
}

void HScrollBarA::OnLoad()
{
	bool flag = false;
	if (GetBackButton() != 0)
	{
		flag = true;
	}
	ScrollBarA::OnLoad();
	if (!flag)
	{
		ButtonA *backButton = GetBackButton();
		backButton->RegisterEvent(m_backButtonMouseDownEvent, EVENTID::MOUSEDOWN, this);
		backButton->RegisterEvent(m_backButtonMouseUpEvent, EVENTID::MOUSEUP, this);
	}
}

void HScrollBarA::Update()
{
	if (GetNative())
	{
		ButtonA *addButton = GetAddButton();
		ButtonA *backButton = GetBackButton();
		ButtonA *reduceButton = GetReduceButton();
		ButtonA *scrollButton = GetScrollButton();
		int width = GetWidth();
		int height = GetHeight();
		int contentSize = GetContentSize();
		if (contentSize > 0 && addButton && backButton && reduceButton && scrollButton)
		{
			int pos = GetPos();
			int pageSize = GetPageSize();
			if (pos > contentSize - pageSize)
			{
				pos = contentSize - pageSize;
			}
			if (pos < 0)
			{
				pos = 0;
			}
			int abWidth = addButton->IsVisible() ? addButton->GetWidth() : 0;
			SIZE abSize = {abWidth, height};
			addButton->SetSize(abSize);
			POINT abPoint = {width - abWidth, 0};
			addButton->SetLocation(abPoint);
			int rbWidth = reduceButton->IsVisible() ? reduceButton->GetWidth() : 0;
			SIZE rbSize = {rbWidth, height};
			reduceButton->SetSize(rbSize);
			POINT rbPoint = {0, 0};
			reduceButton->SetLocation(rbPoint);
			int backWidth = width - abWidth - rbWidth;
			SIZE backSize = {backWidth, height};
			backButton->SetSize(backSize);
			POINT backPoint = {rbWidth, 0};
			backButton->SetLocation(backPoint);
			int scrollWidth = backWidth * pageSize / contentSize;
			int scrollPos = backWidth * pos / contentSize;
			if (scrollWidth < 10)
			{
				scrollWidth = 10;
				if (scrollPos + scrollWidth > backWidth)
				{
					scrollPos = backWidth - scrollWidth;
				}
			}
			SIZE scrollSize = {scrollWidth, height};
			scrollButton->SetSize(scrollSize);
			POINT scrollPoint = {scrollPos, 0};
			scrollButton->SetLocation(scrollPoint);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////