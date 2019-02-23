#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CDay.h"
using namespace OwLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CDay::CDay(int year, int month, int day)
{
	m_year = year;
	m_month = month;
	m_day = day;
}

CDay::~CDay()
{
}

int CDay::GetDay()
{
	return m_day;
}

int CDay::GetMonth()
{
	return m_month;
}

int CDay::GetYear()
{
	return m_year;
}