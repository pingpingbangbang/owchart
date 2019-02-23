/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __CYEARS_H__
#define __CYEARS_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CYear.h"

namespace OwLib
{
	class  CYears
	{
	public:
		CYears();
		virtual ~CYears();
		map<int,CYear*> Years;
		CYear* GetYear(int year);
	};
}

#endif