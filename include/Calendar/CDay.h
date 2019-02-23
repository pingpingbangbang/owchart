/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __CDAY_H__
#define __CDAY_H__
#pragma once

#include "..\\..\\stdafx.h"

namespace OwLib
{
	class  CDay
	{
	protected:
		int m_day;
		int m_month;
		int m_year;
	public:
		CDay(int year, int month, int day);
		virtual ~CDay();
		int GetDay();
		int GetMonth();
		int GetYear();
	};
}
#endif