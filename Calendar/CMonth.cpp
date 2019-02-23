#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CMonth.h"
using namespace OwLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMonth::CreateDays()
{
	int daysInMonth = GetDaysInMonth();
	for (int i = 1; i <= daysInMonth; i++)
	{
		Days.insert(make_pair(i, new CDay(m_year, m_month, i)));
	}
}

CMonth::CMonth(int year, int month)
{
	m_year = year;
	m_month = month;
	CreateDays();
}

CMonth::~CMonth()
{
	map<int,CDay*>::iterator sIter = Days.begin();
	for(; sIter != Days.end(); ++sIter)
	{
		delete sIter->second;
		sIter->second = 0;
	}
	Days.clear();
}

int CMonth::GetDaysInMonth()
{
	int days = 0;
	int dayArray[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (2 == m_month)
	{
		days = (((0 == m_year % 4) && (0 != m_year % 100) || (0 == m_year % 400)) ? 29 : 28);
	}
	else
	{
		days = dayArray[m_month - 1];
	}
	return days;
}

CDay* CMonth:: GetFirstDay()
{
	map<int,CDay*>::iterator sIter = Days.find(1);
	if(sIter != Days.end())
	{
		return sIter->second;
	}
	return 0;
}

CDay* CMonth::GetLastDay()
{
	int size = (int)Days.size();
	map<int,CDay*>::iterator sIter = Days.find(size);
	if(sIter != Days.end())
	{
		return sIter->second;
	}
	return 0;
}

int CMonth::GetMonth()
{
	return m_month;
}

int CMonth::GetYear()
{
	return m_year;
}