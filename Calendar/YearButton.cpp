#include "..\\stdafx.h"
#include "..\\include\\Calendar\\YearButton.h"
using namespace OwLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_int64 YearButton::GetPaintingBackColor()
{
	return COLOR_CONTROL;
}

_int64 YearButton::GetPaintingBorderColor()
{
	return COLOR_CONTROLBORDER;
}

_int64 YearButton::GetPaintingForeColor()
{
	return COLOR_CONTROLTEXT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
YearButton::YearButton(CalendarA *calendar)
{
	m_bounds.left = 0;
	m_bounds.top = 0;
	m_bounds.right = 0;
	m_bounds.bottom = 0;
	m_calendar = calendar;
	m_visible = true;
	m_year = 0;
}

YearButton::~YearButton()
{
	m_calendar = 0;
}

RECT YearButton::GetBounds()
{
	return m_bounds;
}

void YearButton::SetBounds(const RECT& bounds)
{
	m_bounds = bounds;
}

CalendarA* YearButton::GetCalendar()
{
	return m_calendar;
}

void YearButton::SetCalendar(CalendarA *calendar)
{
	m_calendar = calendar;
}

bool YearButton::IsVisible()
{
	return m_visible;
}

void YearButton::SetVisible(bool visible)
{
	m_visible = visible;
}

int YearButton::GetYear()
{
	return m_year;
}

void YearButton::SetYear(int year)
{
	m_year = year;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void YearButton::OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	if (m_calendar)
	{
		m_calendar->SetMode(CalendarMode_Month);
		m_calendar->GetMonthDiv()->SelectYear(m_year);
		m_calendar->Update();
		m_calendar->Invalidate();
	}
}

void YearButton::OnPaintBackGround(CPaint *paint, const RECT& clipRect)
{
	_int64 paintingBackColor = GetPaintingBackColor();
	paint->FillRect(paintingBackColor, m_bounds);
}

void YearButton::OnPaintBorder(CPaint *paint, const RECT& clipRect)
{
	_int64 paintingBorderColor = GetPaintingBorderColor();
	paint->DrawLine(paintingBorderColor, 1, 0, 
		m_bounds.left, 
		m_bounds.bottom - 1, 
		m_bounds.right - 1, 
		m_bounds.bottom - 1);
	paint->DrawLine(paintingBorderColor, 1, 0,
		m_bounds.right - 1, 
		m_bounds.top,
		m_bounds.right - 1, 
		m_bounds.bottom - 1);
}

void YearButton::OnPaintForeground(CPaint *paint, const RECT& clipRect)
{
	int width = m_bounds.right - m_bounds.left;
	int height = m_bounds.bottom - m_bounds.top;
	String text = CStr::ConvertIntToStr(m_year);
	FONT *font = m_calendar->GetFont();
	SIZE size = paint->TextSize(text.c_str(), font);
	RECT rect;
	rect.left = m_bounds.left + (width - size.cx) / 2;
	rect.top = m_bounds.top + (height - size.cy) / 2;
	rect.right = rect.left + size.cx;
	rect.bottom = rect.top + size.cy;
	paint->DrawText(text.c_str(), GetPaintingForeColor(), font, rect);
}