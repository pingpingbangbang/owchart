/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __CPROPERTY_H__
#define __CPROPERTY_H__
#pragma once

#include "..\\..\\stdafx.h"

namespace OwLib
{
	class  CProperty
	{
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type)
		{
		}
		virtual vector<wstring> GetPropertyNames()
		{
			vector<wstring> propertyNames;
			return propertyNames;
		}
		virtual void SetProperty(const wstring& name, const wstring& value)
		{
		}
	};
}
#endif