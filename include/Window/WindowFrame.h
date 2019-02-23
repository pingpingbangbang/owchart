/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __WINDOWFRAME_H__
#define __WINDOWFRAME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "Window.h"

namespace OwLib
{
	class  WindowFrameA : public ControlA
	{
	public:
		WindowFrameA();
		virtual ~WindowFrameA();
	public:
		virtual bool ContainsPoint(const POINT& point);
		virtual wstring GetControlType();
		virtual void Invalidate();
		virtual void OnPaintBackground(CPaint *paint, const RECT& clipRect);
	};
}
#endif