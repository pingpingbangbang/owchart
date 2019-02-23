/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __CMONTH_H__
#define __CMONTH_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CDay.h"

namespace OwLib
{
	class  CMonth
	{
	protected:
		int m_month;
		int m_year;
		void CreateDays();
	public:
		CMonth(int year, int month);
		virtual ~CMonth();
		map<int,CDay*> Days;
		int GetDaysInMonth();
		CDay* GetFirstDay();
		CDay* GetLastDay();
		int GetMonth();
		int GetYear();
	};
}
#endif