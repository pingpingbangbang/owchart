/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __DATETITLE_H__
#define __DATETITLE_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\Button.h"
#include "Calendar.h"

namespace OwLib
{
	class  CalendarA;

	class  DateTitle : public ButtonA
	{
	protected:
		CalendarA *m_calendar;
	public:
		DateTitle(CalendarA *calendar);
		virtual ~DateTitle();
		virtual CalendarA* GetCalendar();
		virtual void SetCalendar(CalendarA *calendar);
	public:
		virtual wstring GetControlType();
		virtual void OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
	};
}
#endif