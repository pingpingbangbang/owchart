/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __LABEL_H__
#define __LABEL_H__
#pragma once

#include "..\\..\\stdafx.h"

namespace OwLib
{
	class  LabelA : public ControlA
	{
	protected:
		ContentAlignmentA m_textAlign;
	public:
		LabelA();
		virtual ~LabelA();
		virtual ContentAlignmentA GetTextAlign();
		virtual void SetTextAlign(ContentAlignmentA textAlign);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
		virtual void OnPrePaint(CPaint *paint, const RECT& clipRect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}
#endif