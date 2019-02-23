/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __ARROWBUTTON_H__
#define __ARROWBUTTON_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\Button.h"
#include "Calendar.h"
#include "YearDiv.h"

namespace OwLib
{
	class  CalendarA;

	class  ArrowButton:public ButtonA
	{
	protected:
		CalendarA *m_calendar;
		bool m_toLast;
	public:
		ArrowButton(CalendarA *calendar);
		virtual ~ArrowButton();
		virtual CalendarA* GetCalendar();
		virtual void SetCalendar(CalendarA *calendar);
		virtual bool IsToLast();
		virtual void SetToLast(bool toLast);
	public:
		virtual wstring GetControlType();
		virtual void OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
	};
}
#endif