#include "..\\stdafx.h"
#include "..\\include\\Calendar\\ArrowButton.h"
using namespace OwLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ArrowButton::ArrowButton(CalendarA *calendar)
{
	m_calendar = calendar;
	SetBackColor(COLOR_EMPTY);
	SetBorderColor(COLOR_EMPTY);
	SIZE size = {16, 16};
	SetSize(size);
	m_toLast = true;
}

ArrowButton::~ArrowButton()
{
	m_calendar = 0;
}

CalendarA* ArrowButton::GetCalendar()
{
	return m_calendar;
}

void ArrowButton::SetCalendar(CalendarA *calendar)
{
	m_calendar = calendar;
}

bool ArrowButton::IsToLast()
{
	return m_toLast;
}

void ArrowButton::SetToLast(bool toLast)
{
	m_toLast = toLast;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String ArrowButton::GetControlType()
{
	return L"ArrowButton";
}

void ArrowButton::OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	ControlA::OnClick(mp, button, clicks, delta);
	if (m_calendar)
	{
		switch (m_calendar->GetMode())
		{
		case CalendarMode_Day:
			if (m_toLast)
			{
				m_calendar->GoLastMonth();
			}
			else
			{
				m_calendar->GoNextMonth();
			}
			break;

		case CalendarMode_Month:
			{
				MonthDiv *monthDiv = m_calendar->GetMonthDiv();
				if (monthDiv)
				{
					int year = monthDiv->GetYear();
					if (m_toLast)
					{
						monthDiv->SelectYear(year - 1);
					}
					else
					{
						monthDiv->SelectYear(year + 1);
					}
				}
				break;
			}
		case CalendarMode_Year:
			{
				YearDiv *yearDiv = m_calendar->GetYearDiv();
				if (yearDiv)
				{
					int startYear = yearDiv->GetStartYear();
					if (m_toLast)
					{
						yearDiv->SelectStartYear(startYear - 12);
					}
					else
					{
						yearDiv->SelectStartYear(startYear + 12);
					}
				}
				break;
			}
		}
		m_calendar->Invalidate();
	}
}

void ArrowButton::OnPaintForeground(CPaint *paint, const RECT& clipRect)
{
	int width = GetWidth();
	int height = GetHeight();
	POINT point = {0, 0};
	POINT point2 = {0, 0};
	POINT point3 = {0, 0};
	if (m_toLast)
	{
		point.x = 0;
		point.y = height / 2;
		point2.x = width;
		point2.y = 0;
		point3.x = width;
		point3.y = height;
	}
	else
	{
		point.x = 0;
		point.y = 0;
		point2.x = 0;
		point2.y = height;
		point3.x = width;
		point3.y = height / 2;
	}
	POINT *points = new POINT[3];
	points[0] = point;
	points[1] = point2;
	points[2] = point3;
	paint->FillPolygon(GetPaintingBackColor(), points, 3);
}