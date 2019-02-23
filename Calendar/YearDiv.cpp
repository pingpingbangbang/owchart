#include "..\\stdafx.h"
#include "..\\include\\Calendar\\YearDiv.h"

using namespace OwLib;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
YearDiv::YearDiv(CalendarA *calendar)
{
	m_am_Direction = 0;
	m_am_Tick = 0;
	m_am_TotalTick = 40;
	m_calendar = calendar;
	m_startYear = 0;
	OnLoad();
}

YearDiv::~YearDiv()
{
	m_calendar = 0;
	m_yearButtons.clear();
	m_yearButtons_am.clear();
}

CalendarA* YearDiv::GetCalendar()
{
	return m_calendar;
}

void YearDiv::SetCalendar(CalendarA *calendar)
{
	m_calendar = calendar;
}

int YearDiv::GetStartYear()
{
	return m_startYear;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void YearDiv::Hide()
{
	int count = (int)m_yearButtons.size();
	for (int i = 0; i < count; i++)
	{
		YearButton *button = m_yearButtons[i];
		button->SetVisible(false);
	}
}

void YearDiv::OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	int count = (int)m_yearButtons.size();
	for (int i = 0; i < count; i++)
	{
		YearButton *button2 = m_yearButtons[i];
		if (button2->IsVisible())
		{
			RECT bounds = button2->GetBounds();
			if ((mp.x >= bounds.left && mp.x <= bounds.right) 
				&& (mp.y >= bounds.top && mp.y <= bounds.bottom))
			{
				button2->OnClick(mp, button, clicks, delta);
				return;
			}
		}
	}
	int countAm = (int)m_yearButtons_am.size();
	for (int j = 0; j < countAm; j++)
	{
		YearButton *buttonAm = m_yearButtons_am[j];
		if (buttonAm->IsVisible())
		{
			RECT rectAm = buttonAm->GetBounds();
			if ((mp.x >= rectAm.left && mp.x <= rectAm.right)
				&& (mp.y >= rectAm.top && mp.y <= rectAm.bottom))
			{
				buttonAm->OnClick(mp, button, clicks, delta);
				return;
			}
		}
	}
}

void YearDiv::OnLoad()
{
	if (m_calendar)
	{
		if ((int)m_yearButtons.size() == 0 || (int)m_yearButtons_am.size() == 0)
		{
			m_yearButtons.clear();
			m_yearButtons_am.clear();
			ControlHost *host = m_calendar->GetNative()->GetHost();
			for (int i = 0; i < 12; i++)
			{
				YearButton *item = new YearButton(m_calendar);
				m_yearButtons.push_back(item);
				YearButton *itemAm = new YearButton(m_calendar);
				itemAm->SetVisible(false);
				m_yearButtons_am.push_back(itemAm);
			}
		}
	}
}

void YearDiv::OnPaint(CPaint *paint, const RECT& clipRect)
{
	int count = (int)m_yearButtons.size();
	for (int i = 0; i < count; i++)
	{
		YearButton *button = m_yearButtons[i];
		if (button->IsVisible())
		{
			RECT bounds = button->GetBounds();
			button->OnPaintBackground(paint, bounds);
			button->OnPaintForeground(paint, bounds);
			button->OnPaintBorder(paint, bounds);
		}
	}
	int countAm = (int)m_yearButtons_am.size();
	for (int j = 0; j < countAm; j++)
	{
		YearButton *buttonAm = m_yearButtons_am[j];
		if (buttonAm->IsVisible())
		{
			RECT rectAm = buttonAm->GetBounds();
			buttonAm->OnPaintBackground(paint, rectAm);
			buttonAm->OnPaintForeground(paint, rectAm);
			buttonAm->OnPaintBorder(paint, rectAm);
		}
	}
}

void YearDiv::OnResetDiv(int state)
{
	if (m_calendar)
	{
		int startYear = m_startYear;
		int pre12Year = m_startYear - 12;
		int next12Year = m_startYear + 12;
		int x = 0;
		int height = m_calendar->GetHeadDiv()->GetHeight();
		int width = m_calendar->GetWidth();
		int noTimeHeight = m_calendar->GetHeight() - m_calendar->GetTimeDiv()->GetHeight();
		int noHeadHeight = noTimeHeight - height;
		if (noHeadHeight < 1)
		{
			noHeadHeight = 1;
		}
		int num10 = 0;
		vector<YearButton*> yearButtons;
		if (m_am_Direction == 1)
		{
			num10 = (noHeadHeight * m_am_Tick) / m_am_TotalTick;
			if (state == 1)
			{
				startYear = next12Year;
				pre12Year = startYear - 12;
				next12Year = startYear + 12;
			}
		}
		else if (m_am_Direction == 2)
		{
			num10 = (-noHeadHeight * m_am_Tick) / m_am_TotalTick;
			if (state == 1)
			{
				startYear = pre12Year;
				pre12Year = startYear - 12;
				next12Year = startYear + 12;
			}
		}
		if (state == 0)
		{
			yearButtons = m_yearButtons;
		}
		else if (state == 1)
		{
			yearButtons = m_yearButtons_am;
		}
		int cy = noHeadHeight / 3;
		int count = (int)yearButtons.size();
		for (int i = 0; i < count; i++)
		{
			if (i == 8)
			{
				cy = noTimeHeight - height;
			}
			YearButton *button = yearButtons[i];
			button->SetYear(startYear + i);
			int num14 = 0;
			if (state == 1)
			{
				if (m_am_Tick <= 0)
				{
					button->SetVisible(FALSE);
					continue;
				}
				if (m_am_Tick > 0)
				{
					button->SetVisible(TRUE);
					if (m_am_Direction == 1)
					{
						num14 = num10 - noHeadHeight;
					}
					else if (m_am_Direction == 2)
					{
						num14 = num10 + noHeadHeight;
					}
				}
			}
			else
			{
				num14 = num10;
			}
			if ((i + 1) % 4 == 0)
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
				SIZE size2 = {width / 4 + ((i + 1) % 4 % 2), cy};
				RECT rect = {point2.x, point2.y, point2.x + size2.cx, point2.y + size2.cy};
				button->SetBounds(rect);
				x += size2.cx;
			}
		}
	}
}

void YearDiv::OnTimer()
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

void YearDiv::SelectStartYear(int startYear)
{
	if (m_calendar && m_startYear != startYear)
	{
		if (startYear > m_startYear)
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
		m_startYear = startYear;
	}
}

void YearDiv::Show()
{
	int count = (int)m_yearButtons.size();
	for (int i = 0; i < count; i++)
	{
		YearButton *button = m_yearButtons[i];
		button->SetVisible(true);
	}
}

void YearDiv::Update()
{
	OnResetDiv(0);
	OnResetDiv(1);
}