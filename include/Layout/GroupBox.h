/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __GROUPBOX_H__
#define __GROUPBOX_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "Div.h"

namespace OwLib
{
	class  GroupBoxA : public DivA
	{
	public:
		GroupBoxA();
		virtual ~GroupBoxA();
	public:
		virtual wstring GetControlType();
		virtual void OnPaintBorder(CPaint *paint, const RECT& clipRect);
		virtual void OnPaintForeground(CPaint *paint, const RECT& clipRect);
	};
}
#endif