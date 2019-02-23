/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __BANDEDGRIDCOLUMN_H__
#define __BANDEDGRIDCOLUMN_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "GridEnums.h"
#include "BandedGrid.h"
#include "GridColumn.h"
#include "GridBand.h"

namespace OwLib
{
	class  BandedGridA;
	class  GridColumn;
	class  GridBand;

	class  BandedGridColumn : public GridColumn
	{
	protected:
		GridBand *m_band;
	public:
		BandedGridColumn();
		virtual ~BandedGridColumn();
		virtual GridBand* GetBand();
		virtual void SetBand(GridBand *band);
	public:
		virtual wstring GetControlType();
		virtual bool OnDragBegin();
		virtual void OnMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnMouseMove(const POINT& mp, MouseButtonsA button, int clicks, int delta);
	};
}

#endif