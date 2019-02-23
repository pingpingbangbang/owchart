#include "..\\stdafx.h"
#include "..\\include\\Calendar\\MonthDiv.h"
using namespace OwLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MonthDiv::MonthDiv(CalendarA *calendar)
{
	m_am_Direction = 0;
	m_am_Tick = 0;
	m_am_TotalTick = 40;
	m_year = 0;
	m_calendar = calendar;
	OnLoad();
}

MonthDiv::~MonthDiv()
{
	m_calendar = 0;
	m_monthButtons.clear();
	m_monthButtons_am.clear();
}

CalendarA* MonthDiv::GetCalendar()
{
	return m_calendar;
}

void MonthDiv::SetCalendar(CalendarA *calendar)
{
	m_calendar = calendar;
}

int MonthDiv::GetYear()
{
	return m_year;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MonthDiv::Hide()
{
	int count = (int)m_monthButtons.size();
	for (int i = 0; i < count; i++)
	{
		MonthButton *button = m_monthButtons[i];
		button->SetVisible(false);
	}
}

void MonthDiv::OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	int count = (int)m_monthButtons.size();
	for (int i = 0; i < count; i++)
	{
		MonthButton *monthButton = m_monthButtons[i];
		if (monthButton->IsVisible())
		{
			RECT bounds = monthButton->GetBounds();
			if ((mp.x >= bounds.left && mp.x <= bounds.right) && (mp.y >= bounds.top && mp.y <= bounds.bottom))
			{
				monthButton->OnClick(mp, button, clicks, delta);
				return;
			}
		}
	}
	int countAm = (int)m_monthButtons_am.size();
	for (int j = 0; j < countAm; j++)
	{
		MonthButton *monthButtonAm = m_monthButtons_am[j];
		if (monthButtonAm->IsVisible())
		{
			RECT rectAm = monthButtonAm->GetBounds();
			if ((mp.x >= rectAm.left && mp.x <= rectAm.right) && (mp.y >= rectAm.top && mp.y <= rectAm.bottom))
			{
				monthButtonAm->OnClick(mp, button, clicks, delta);
				return;
			}
		}
	}
}

void MonthDiv::OnLoad()
{
	if (m_calendar)
	{
		ControlHost *host = m_calendar->GetNative()->GetHost();
		if (((int)m_monthButtons.size() == 0) || ((int)m_monthButtons_am.size() == 0))
		{
			m_monthButtons.clear();
			m_monthButtons_am.clear();
			for (int i = 0; i < 12; i++)
			{
				MonthButton *item = new MonthButton(m_calendar);
				item->SetMonth(i + 1);
				m_monthButtons.push_back(item);
				MonthButton *itemAm = new MonthButton(m_calendar);
				item->SetMonth(i + 1);
				itemAm->SetVisible(false);
				m_monthButtons_am.push_back(itemAm);
			}
		}
	}
}

void MonthDiv::OnPaint(CPaint *paint, const RECT& clipRect)
{
	int count = (int)m_monthButtons.size();
	for (int i = 0; i < count; i++)
	{
		MonthButton *button = m_monthButtons[i];
		if (button->IsVisible())
		{
			RECT bounds = button->GetBounds();
			button->OnPaintBackground(paint, bounds);
			button->OnPaintForeground(paint, bounds);
			button->OnPaintBorder(paint, bounds);
		}
	}
	int countAm = (int)m_monthButtons_am.size();
	for (int j = 0; j < countAm; j++)
	{
		MonthButton *buttonAm = m_monthButtons_am[j];
		if (buttonAm->IsVisible())
		{
			RECT rectAm = buttonAm->GetBounds();
			buttonAm->OnPaintBackground(paint, rectAm);
			buttonAm->OnPaintForeground(paint, rectAm);
			buttonAm->OnPaintBorder(paint, rectAm);
		}
	}
}

void MonthDiv::OnResetDiv(int state)
{
	if (m_calendar)
	{
		int year = m_year;
		int preYear = m_year - 1;
		int nextYear = m_year + 1;
		int x = 0;
		int height = m_calendar->GetHeadDiv()->GetHeight();
		int width = m_calendar->GetWidth();
		int dayHeight = m_calendar->GetHeight() - m_calendar->GetTimeDiv()->GetHeight();
		int pureHeight = dayHeight - height;
		if (pureHeight < 1)
		{
			pureHeight = 1;
		}
		int curHeight = 0;
		vector<MonthButton*> monthButtons;
		if (m_am_Direction == 1)
		{
			curHeight = (pureHeight * m_am_Tick) / m_am_TotalTick;
			if (state == 1)
			{
				year = nextYear;
				preYear = year - 1;
				nextYear = year + 1;
			}
		}
		else if (m_am_Direction == 2)
		{
			curHeight = (-pureHeight * m_am_Tick) / m_am_TotalTick;
			if (state == 1)
			{
				year = preYear;
				preYear = year - 1;
				nextYear = year + 1;
			}
		}
		if (state == 0)
		{
			monthButtons = m_monthButtons;
		}
		else if (state == 1)
		{
			monthButtons = m_monthButtons_am;
		}
		int cy = pureHeight / 3;
		int count = (int)monthButtons.size();
		for (int i = 0; i < count; i++)
		{
			if (i == 8)
			{
				cy = dayHeight - height;
			}
			MonthButton *button = monthButtons[i];
			button->SetYear(year);
			int num14 = 0;
			if (state == 1)
			{
				if (m_am_Tick <= 0)
				{
					button->SetVisible(false);
					continue;
				}
				else
				{
					button->SetVisible(true);
					if (m_am_Direction == 1)
					{
						num14 = curHeight - pureHeight;
					}
					else if (m_am_Direction == 2)
					{
						num14 = curHeight + pureHeight;
					}
				}
			}
			else
			{
				num14 = curHeight;
			}
			if (((i + 1) % 4) == 0)
			{
				POINT point = {x, height + num14};
				SIZE size = {width - x, cy};
				RECT rect = {point.x, point.y, point.x + size.cx, point.y + size.cy};
				button->SetBounds(rect);
				x = 0;
				if (i != 0 && i != count - 1)
				{
					height += cy;
				}
			}
			else
			{
				POINT point2 = {x, height + num14};
				SIZE size2 = {(width / 4) + (((i + 1) % 4) % 2), cy};
				RECT rect = {point2.x, point2.y, point2.x + size2.cx, point2.y + size2.cy};
				button->SetBounds(rect);
				x += size2.cx;
			}
		}
	}
}

void MonthDiv::OnTimer()
{
	if (m_am_Tick > 0)
	{
		m_am_Tick = (int) ((m_am_Tick * 2.0) / 3.0);
		if (m_calendar)
		{
			m_calendar->Update();
			m_calendar->Invalidate();
		}
	}
}

void MonthDiv::SelectYear(int year)
{
	if (m_calendar && m_year != year)
	{
		if (year > m_year)
		{
			m_am_Direction = 1;
		}
		else
		{
			m_am_Direction = 2;
		}
		if (m_calendar->UseAnimation())
		{
			m_am_Tick = m_am_TotalTick;
		}
		m_year = year;
	}
}

void MonthDiv::Show()
{
	int count = (int)m_monthButtons.size();
	for (int i = 0; i < count; i++)
	{
		MonthButton *button = m_monthButtons[i];
		button->SetVisible(true);
	}
}

void MonthDiv::Update()
{
	OnResetDiv(0);
	OnResetDiv(1);
}