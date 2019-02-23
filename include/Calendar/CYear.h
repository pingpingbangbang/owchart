/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __CYEAR_H__
#define __CYEAR_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CMonth.h"

namespace OwLib
{
	class  CYear
	{
	protected:
		int m_year;
		void CreateMonths();
	public:
		CYear(int year);
		virtual ~CYear();
		map<int,CMonth*> Months;
	};
}

#endif