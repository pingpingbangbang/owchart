/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __VSCROLLBAR_H__
#define __VSCROLLBAR_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "ScrollBar.h"

namespace OwLib
{
	class  VScrollBarA:public ScrollBarA
	{
	protected:
        ControlMouseEvent m_backButtonMouseDownEvent;
		ControlMouseEvent m_backButtonMouseUpEvent;
		static void BackButtonMouseDown(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
		static void BackButtonMouseUp(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
	public:
		VScrollBarA();
		virtual ~VScrollBarA();
		virtual wstring GetControlType();
		void OnBackButtonMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		void OnBackButtonMouseUp(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnDragScroll();
		virtual void OnLoad();
		virtual void Update();
	};
}

#endif