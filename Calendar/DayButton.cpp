#include "..\\stdafx.h"
#include "..\\include\\Calendar\\DayButton.h"
using namespace OwLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_int64 DayButton::GetPaintingBackColor()
{
	if (m_selected)
	{
		return COLOR_PUSHEDCONTROL;
	}
	if (m_inThisMonth)
	{
		return COLOR_HOVEREDCONTROL;
	}
	return COLOR_CONTROL;
}

_int64 DayButton::GetPaintingBorderColor()
{
	return COLOR_CONTROLBORDER;
}

_int64 DayButton::GetPaintingForeColor()
{
	return COLOR_CONTROLTEXT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DayButton::DayButton(CalendarA *calendar)
{
	m_bounds.left = 0;
	m_bounds.top = 0;
	m_bounds.right = 0;
	m_bounds.bottom = 0;
	m_calendar = calendar;
	m_day = 0;
	m_selected = false;
	m_inThisMonth = false;
	m_visible = true;
}

DayButton::~DayButton()
{
	m_calendar = 0;
}

RECT DayButton::GetBounds()
{
	return m_bounds;
}

void DayButton::SetBounds(const RECT& bounds)
{
	m_bounds = bounds;
}

CalendarA* DayButton::GetCalendar()
{
	return m_calendar;
}

void DayButton::SetCalendar(CalendarA *calendar)
{
	m_calendar = calendar;
}

CDay* DayButton::GetDay()
{
	return m_day;
}

void DayButton::SetDay(CDay *day)
{
	m_day = day;
}

bool DayButton::InThisMonth()
{
	return m_inThisMonth;
}

void DayButton::SetThisMonth(bool inThisMonth)
{
	m_inThisMonth = inThisMonth;
}

bool DayButton::IsSelected()
{
	return m_selected;
}

void DayButton::SetSelected(bool selected)
{
	m_selected = selected;
}

bool DayButton::IsVisible()
{
	return m_visible;
}

void DayButton::SetVisible(bool visible)
{
	m_visible = visible;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DayButton::OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	if (m_calendar && m_day)
	{
		m_calendar->SetSelectedDay(m_day);
	}
}

void DayButton::OnPaintBackGround(CPaint *paint, const RECT& clipRect)
{
	_int64 paintingBackColor = GetPaintingBackColor();
	paint->FillRect(paintingBackColor, m_bounds);
}

void DayButton::OnPaintBorder(CPaint *paint, const RECT& clipRect)
{
	_int64 paintingBorderColor = GetPaintingBorderColor();
	paint->DrawLine(paintingBorderColor, 1, 0, m_bounds.left, m_bounds.bottom - 1, 
		m_bounds.right - 1, m_bounds.bottom - 1);
	paint->DrawLine(paintingBorderColor, 1, 0, m_bounds.right - 1, m_bounds.top,
		m_bounds.right - 1, m_bounds.bottom - 1);
}

void DayButton::OnPaintForeground(CPaint *paint, const RECT& clipRect)
{
	if (m_day)
	{
		int width = m_bounds.right - m_bounds.left;
		int height = m_bounds.bottom - m_bounds.top;
		String text = CStr::ConvertIntToStr(m_day->GetDay());
		FONT *font = m_calendar->GetFont();
		SIZE size = paint->TextSize(text.c_str(), font);
		RECT rect;
		rect.left = m_bounds.left + ((width - size.cx) / 2);
		rect.top = m_bounds.top + ((height - size.cy) / 2);
		rect.right = rect.left + size.cx;
		rect.bottom = rect.top + size.cy;
		paint->DrawText(text.c_str(), GetPaintingForeColor(), font, rect);
	}
}