/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __RADIOBUTTON_H__
#define __RADIOBUTTON_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CStr.h"
#include "CheckBox.h"

namespace OwLib
{
	class  RadioButtonA:public CheckBoxA
	{
	protected:
		wstring m_groupName;
	public:
		RadioButtonA();
		virtual ~RadioButtonA();
		virtual wstring GetGroupName();
		virtual void SetGroupName(const wstring& groupName);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaintCheckButton(CPaint *paint, const RECT& clipRect);
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}

#endif