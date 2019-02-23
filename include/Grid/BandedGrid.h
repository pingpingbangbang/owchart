/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __BANDEDGRID_H__
#define __BANDEDGRID_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "GridEnums.h"
#include "BandedGridColumn.h"
#include "GridBand.h"
#include "Grid.h"

namespace OwLib
{
	class  BandedGridColumn;
	class  GridBand;

	class  BandedGridA : public GridA
	{
	protected:
		int GetAllVisibleBandsWidth();
	public:
		vector<GridBand*> m_bands;
		BandedGridA();
		virtual ~BandedGridA();
	public:
		void AddBand(GridBand *band);
		virtual void AddColumn(GridColumn *column);
		void ClearBands();
		virtual void ClearColumns();
		vector<GridBand*> GetBands();
		virtual int GetContentWidth();
		virtual wstring GetControlType();
		void InsertBand(int index, GridBand *band);
		virtual void OnSetEmptyClipRegion();
		void RemoveBand(GridBand *band);
		virtual void RemoveColumn(GridColumn *column);
		virtual void ResetHeaderLayout();
		virtual void Update();
	};
}

#endif