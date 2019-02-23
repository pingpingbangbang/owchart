#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CYears.h"
using namespace OwLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CYears::CYears()
{

}

CYears::~CYears()
{
	map<int,CYear*>::iterator sIter = Years.begin();
	for(; sIter != Years.end(); ++sIter)
	{
		delete sIter->second;
		sIter->second = 0;
	}
	Years.clear();
}

CYear* CYears::GetYear(int year)
{
	map<int, CYear*>::iterator sIter = Years.find(year);
	if(sIter != Years.end())
	{
		return sIter->second;
	}
	else
	{
		CYear* cYear = new CYear(year);
		Years.insert(make_pair(year, cYear));
		return cYear;
	}
}