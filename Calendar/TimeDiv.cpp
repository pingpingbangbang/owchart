#include "..\\stdafx.h"
#include "..\\include\\Calendar\\TimeDiv.h"
using namespace OwLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TimeDiv::SelectedTimeChanged(void *sender, void *pInvoke)
{
	TimeDiv *div = (TimeDiv*)pInvoke;
	if(div)
	{
		div->OnSelectedTimeChanged();
	}
}

_int64 TimeDiv::GetPaintingBackColor()
{
	return COLOR_CONTROL;
}

_int64 TimeDiv::GetPaintingBorderColor()
{
	return COLOR_CONTROLBORDER;
}

_int64 TimeDiv::GetPaintingForeColor()
{
	return COLOR_CONTROLTEXT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TimeDiv::TimeDiv(CalendarA *calendar)
{
	m_calendar = calendar;
	m_height = 40;
	m_spinHour = 0;
	m_spinMinute = 0;
	m_spinSecond = 0;
	OnLoad();
}

TimeDiv::~TimeDiv()
{
	m_calendar = 0;
	m_spinHour = 0;
	m_spinMinute = 0;
	m_spinSecond = 0;
}

CalendarA* TimeDiv::GetCalendar()
{
	return m_calendar;
}

void TimeDiv::SetCalendar(CalendarA *calendar)
{
	m_calendar = calendar;
}

int TimeDiv::GetHeight()
{
	return m_height;
}

void TimeDiv::SetHeight(int height)
{
	m_height = height;
}

int TimeDiv::GetHour()
{
	if (m_spinHour)
	{
		return (int)m_spinHour->GetValue();
	}
	return 0;
}

void TimeDiv::SetHour(int hour)
{
	if (m_spinHour)
	{
		m_spinHour->SetValue(hour);
	}
}

int TimeDiv::GetMinute()
{
	if (m_spinMinute)
	{
		return (int)m_spinMinute->GetValue();
	}
	return 0;
}

void TimeDiv::SetMinute(int minute)
{
	if (m_spinMinute)
	{
		m_spinMinute->SetValue(minute);
	}
}

int TimeDiv::GetSecond()
{
	if (m_spinSecond)
	{
		return (int)m_spinSecond->GetValue();
	}
	return 0;
}

void TimeDiv::SetSecond(int second)
{
	if (m_spinSecond)
	{
		m_spinSecond->SetValue(second);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TimeDiv::OnLoad()
{
	if (m_calendar)
	{
		ControlHost *host = m_calendar->GetNative()->GetHost();
		if (!m_spinHour)
		{
			m_spinHour = new SpinA();
			m_spinHour->SetMaximum(23.0);
			m_spinHour->SetTextAlign(HorizontalAlignA_Right);
			m_calendar->AddControl(m_spinHour);
			m_spinHour->RegisterEvent(SelectedTimeChanged, EVENTID::SELECTEDTIMECHANGED, this);
		}
		if (!m_spinMinute)
		{
			m_spinMinute = new SpinA();
			m_spinMinute->SetMaximum(59.0);
			m_spinMinute->SetTextAlign(HorizontalAlignA_Right);
			m_calendar->AddControl(m_spinMinute);
			m_spinMinute->RegisterEvent(SelectedTimeChanged, EVENTID::SELECTEDTIMECHANGED, this);
		}
		if (!m_spinSecond)
		{
			m_spinSecond = new SpinA();
			m_spinSecond->SetMaximum(59.0);
			m_spinSecond->SetTextAlign(HorizontalAlignA_Right);
			m_calendar->AddControl(m_spinSecond);
			m_spinSecond->RegisterEvent(SelectedTimeChanged, EVENTID::SELECTEDTIMECHANGED, this);
		}
	}
}

void TimeDiv::OnPaint(CPaint *paint, const RECT& clipRect)
{
	int width = m_calendar->GetWidth();
	int height = m_calendar->GetHeight();
	int num3 = height - m_height;
	RECT rect = {0, height - m_height, width, height};
	paint->FillRect(GetPaintingBackColor(), rect);
	if (m_height > 0)
	{
		_int64 paintingForeColor = GetPaintingForeColor();
		FONT *font = m_calendar->GetFont();
		SIZE size = paint->TextSize(L"时", font);
		RECT rectHour;
		rectHour.left = (width / 3) - size.cx;
		rectHour.top = (num3 + (m_height / 2)) - (size.cy / 2);
		rectHour.right = rectHour.left + size.cx;
		rectHour.bottom = rectHour.top + size.cy;
		paint->DrawText(L"时", paintingForeColor, font, rectHour);
		size = paint->TextSize(L"分", font);
		RECT rectMinute;
		rectMinute.left = ((width * 2) / 3) - size.cx;
		rectMinute.top = (num3 + (m_height / 2)) - (size.cy / 2);
		rectMinute.right = rectHour.left + size.cx;
		rectMinute.bottom = rectHour.top + size.cy;
		paint->DrawText(L"分", paintingForeColor, font, rectMinute);
		size = paint->TextSize(L"秒", font);
		RECT rectSecond;
		rectSecond.left = (width - size.cx) - 5;
		rectSecond.top = (num3 + (m_height / 2)) - (size.cy / 2);
		rectSecond.right = rectHour.left + size.cx;
		rectSecond.bottom = rectHour.top + size.cy;
		paint->DrawText(L"秒", paintingForeColor, font, rectSecond);
	}
}

void TimeDiv::OnSelectedTimeChanged()
{
	if (m_calendar)
	{
		m_calendar->OnSelectedTimeChanged();
	}
}

void TimeDiv::OnTimer()
{
}

void TimeDiv::Update()
{
	if (m_height > 0)
	{
		int width = m_calendar->GetWidth();
		int height = m_calendar->GetHeight() - m_height;
		int x = 5;
		if (m_spinHour)
		{
			m_spinHour->SetVisible(true);
			POINT point = {x, (height + (m_height / 2)) - (m_spinHour->GetRight() / 2)};
			m_spinHour->SetLocation(point);
			m_spinHour->SetWidth(((width - 15) / 3) - 20);
		}
		if (m_spinMinute)
		{
			m_spinMinute->SetVisible(true);
			POINT point = {(width / 3) + 5, (height + (m_height / 2)) - (m_spinMinute->GetHeight() / 2)};
			m_spinMinute->SetLocation(point);
			m_spinMinute->SetWidth(((width - 15) / 3) - 20);
		}
		if (m_spinSecond)
		{
			m_spinSecond->SetVisible(true);
			POINT point = {((width * 2) / 3) + 5, (height + (m_height / 2)) - (m_spinSecond->GetHeight() / 2)};
			m_spinSecond->SetLocation(point);
			m_spinSecond->SetWidth(((width - 15) / 3) - 20);
		}
	}
	else
	{
		if (m_spinHour)
		{
			m_spinHour->SetVisible(false);
		}
		if (m_spinMinute)
		{
			m_spinMinute->SetVisible(false);
		}
		if (m_spinSecond)
		{
			m_spinSecond->SetVisible(false);
		}
	}
}