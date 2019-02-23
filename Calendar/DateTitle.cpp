#include "..\\stdafx.h"
#include "..\\include\\Calendar\\DateTitle.h"
using namespace OwLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DateTitle::DateTitle(CalendarA *calendar)
{
	m_calendar = calendar;
	SetBackColor(COLOR_EMPTY);
	SetBorderColor(COLOR_EMPTY);
	FONT font(L"Simsun", 22, true, false, false);
	SetFont(&font);
	SIZE size = {180, 30};
	SetSize(size);
}

DateTitle::~DateTitle()
{
	m_calendar = 0;
}

CalendarA* DateTitle::GetCalendar()
{
	return m_calendar;
}

void DateTitle::SetCalendar(CalendarA *calendar)
{
	m_calendar = calendar;
}

String DateTitle::GetControlType()
{
	return L"DateTitle";
}

void DateTitle::OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	ButtonA::OnClick(mp, button, clicks, delta);
	if (m_calendar)
	{
		switch (m_calendar->GetMode())
		{
		case CalendarMode_Day:
			m_calendar->SetMode(CalendarMode_Month);
			break;

		case CalendarMode_Month:
			m_calendar->SetMode(CalendarMode_Year);
			break;
		}
		m_calendar->Update();
		m_calendar->Invalidate();
	}
}

void DateTitle::OnPaintForeground(CPaint *paint, const RECT& clipRect)
{
	if (m_calendar)
	{
		int width = GetWidth();
		int height = GetHeight();
		FONT *font = GetFont();
		wchar_t charText[100] = {0};
		switch (m_calendar->GetMode())
		{
		case CalendarMode_Day:
			{
				CMonth *month = m_calendar->GetMonth();
				swprintf_s(charText, 99, L"%d定%d埖", month->GetYear(), month->GetMonth());
				break;
			}
		case CalendarMode_Month:
			swprintf_s(charText, 99, L"%d定", m_calendar->GetMonthDiv()->GetYear());
			break;
		case CalendarMode_Year:
			{
				int startYear = m_calendar->GetYearDiv()->GetStartYear();
				swprintf_s(charText, 99, L"%d定 - %d定", startYear, startYear + 12);
				break;
			}
		}
		String text(charText);
		SIZE size = paint->TextSize(text.c_str(), font);
		RECT rect;
		rect.left = (width - size.cx) / 2;
		rect.top = (height - size.cy) / 2;
		rect.right = rect.left + size.cx + 1;
		rect.bottom = rect.top + size.cy + 1;
		paint->DrawText(text.c_str(), GetPaintingForeColor(), font, rect);
	}
}