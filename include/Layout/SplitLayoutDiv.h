/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __SPLITLAYOUTDIV_H__
#define __SPLITLAYOUTDIV_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\Button.h"
#include "Div.h"
#include "LayoutDiv.h"
#include "TableLayoutDiv.h"

namespace OwLib
{
	class  SplitLayoutDivA : public LayoutDivA
	{
	protected:
		ControlA *m_firstControl;
		ControlA *m_secondControl;
		SizeTypeA m_splitMode;
		float m_splitPercent;
		ButtonA *m_splitter;
		ControlEvent m_splitterDraggingEvent;
		static void SplitterDragging(void *sender, void *pInvoke);
	public:
		SplitLayoutDivA();
		virtual ~SplitLayoutDivA();
		virtual ControlA* GetFirstControl();
		virtual void SetFirstControl(ControlA *firstControl);
		virtual ControlA* GetSecondControl();
		virtual void SetSecondControl(ControlA *secondControl);
		virtual SizeTypeA GetSplitMode();
		virtual void SetSplitMode(SizeTypeA splitMode);
		virtual ButtonA* GetSplitter();
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		void SplitLayoutDivA::OnSplitterDragging();
		virtual void OnLoad();
		virtual bool OnResetLayout();
		virtual void Update();
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif