#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CYear.h"
using namespace OwLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CYear::CreateMonths()
{
	for (int i = 1; i <= 12; i++)
	{
		Months.insert(make_pair(i, new CMonth(m_year, i)));
	}
}

CYear::CYear(int year)
{
	m_year = year;
	CreateMonths();
}

CYear::~CYear()
{
	map<int,CMonth*>::iterator sIter = Months.begin();
	for(; sIter != Months.end(); ++sIter)
	{
		delete sIter->second;
		sIter->second = 0;
	}
	Months.clear();
}