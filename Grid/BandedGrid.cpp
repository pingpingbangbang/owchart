#include "..\\stdafx.h"
#include "..\\include\\Grid\\BandedGrid.h"

namespace OwLib
{
	int BandedGridA::GetAllVisibleBandsWidth()
	{
		int num = 0;
        int count = (int)m_bands.size();
        for (int i = 0; i < count; i++)
        {
            GridBand* band = m_bands[i];
			if (band->IsVisible())
            {
                num += band->GetWidth();
            }
        }
        return num;
	}

	BandedGridA::BandedGridA()
	{
	
	}
	
	BandedGridA:: ~BandedGridA()
	{
		
	}
	
	void BandedGridA::AddBand(GridBand *band)
	{
		band->SetGrid(this);
		m_bands.push_back(band);
		int count = (int)m_bands.size();
		for (int i = 0; i < count; i++)
		{
			m_bands[i]->SetIndex(i);
		}
		AddControl(band);	
	}
	
	void BandedGridA::AddColumn(GridColumn *column)
	{
		BandedGridColumn* bandedGridColumn = dynamic_cast<BandedGridColumn*>(column);
		if(bandedGridColumn)
		{
			column->SetGrid(this);
			GridA::m_columns.push_back(column);
			AddControl(column);
		}	
	}
	
	void BandedGridA::ClearBands()
	{
		int count = (int)m_bands.size();
		for (int i = 0; i < count; i++)
		{
			GridBand* control = m_bands[i];
			RemoveControl(control);
			delete control;
			control = 0;
		}
		m_bands.clear();
	}
	
	void BandedGridA::ClearColumns()
	{
		
	}
	vector<GridBand*> BandedGridA::GetBands()
	{
		return m_bands;
	}

	int BandedGridA::GetContentWidth()
	{
        HScrollBarA* hScrollBar = GetHScrollBar();
        VScrollBarA* vScrollBar = GetVScrollBar();
        int wmax = 0;
        vector<ControlA*> controls = GetControls();
        int count = (int)controls.size();
        for (int i = 0; i < count; i++)
        {
            ControlA* la = controls[i];
            if (la->IsVisible() && la != hScrollBar && la != vScrollBar)
            {
                int right = la->GetRight();
                if (right > wmax)
                {
                    wmax = right;
                }
            }
        }
        int allVisibleBandsWidth = GetAllVisibleBandsWidth();
        if (wmax <= allVisibleBandsWidth)
        {
            return allVisibleBandsWidth;
        }
        return wmax;
	}
	
	String BandedGridA::GetControlType()
	{
		return L"BandedGrid";
	}
	
	void BandedGridA::InsertBand(int index, GridBand *band)
	{
        band->SetGrid(this);
		m_bands.insert(m_bands.begin() + index, band);
        int count = (int)m_bands.size();
        for (int i = 0; i < count; i++)
        {
            m_bands[i]->SetIndex(i);
        }
        AddControl(band);		
	}

	void BandedGridA::OnSetEmptyClipRegion()
	{
		vector<ControlA*> controls = GetControls();
		int count = (int)controls.size();
		RECT rect = {0} ;
		for (int i = 0; i < count; i++)
		{
			ControlA* control = controls[i];
			ScrollBarA* scrollBar = dynamic_cast<ScrollBarA*>(control);
			GridColumn* gridColumn = dynamic_cast<GridColumn*>(control);
			GridBand* gridBand = dynamic_cast<GridBand*>(control);
			if (control != GetEditTextBox() && !scrollBar && !gridColumn && !gridBand)
			{
				control->SetRegion(rect);
			}
		}		
	}
	
	void BandedGridA::RemoveBand(GridBand *band)
	{
		int count = (int)m_bands.size();
		bool isRemove = false;
		for(int i = 0; i < count; i++)
		{
			GridBand* bItem = m_bands[i];
			if(bItem == band)
			{
				m_bands.erase(m_bands.begin() + i);
				isRemove = true;
				break;
			}
		}
		if(isRemove)
		{
			count = (int)m_bands.size();
			for (int i = 0; i < count; i++)
			{
				m_bands[i]->SetIndex(i);
			}
			RemoveControl(band);
		}
	}
	
	void BandedGridA::RemoveColumn(GridColumn *column)
	{
		BandedGridColumn* bandedGridColumn = dynamic_cast<BandedGridColumn*>(column);
		if(bandedGridColumn)
		{
			int size = (int)GridA::m_columns.size();
			for(int i = 0; i < size; i++)
			{
				if(GridA::m_columns[i] == column)
				{
					GridA::m_columns.erase(GridA::m_columns.begin() + i);
					RemoveControl(column);
					break;
				}
			}
        }		
	}
	
	void BandedGridA::ResetHeaderLayout()
	{
		int left = 0;
		int top = 0;
		int scrollH = 0;
		HScrollBarA* hScrollBar = GetHScrollBar();
		if (hScrollBar && hScrollBar->IsVisible())
		{
			scrollH = -hScrollBar->GetPos();
		}
		int headerHeight = IsHeaderVisible() ? GridA::GetHeaderHeight() : 0;
		int horizontalOffset = GetHorizontalOffset();
		int verticalOffset = GetVerticalOffset();
		int count = (int)m_bands.size();
		for (int i = 0; i < count; i++)
		{
			GridBand* band = m_bands[i];
			if (band->IsVisible())
			{
				int bandHeight = (headerHeight < band->GetHeight()) ? headerHeight : band->GetHeight();
				RECT rect;
				rect.left = left + horizontalOffset;
				rect.top = top + verticalOffset;
				rect.right = left + horizontalOffset + band->GetWidth();
				rect.bottom = top + bandHeight + verticalOffset;
				bool hasFrozenColumn = false;
				vector<BandedGridColumn*> allChildColumns = band->GetAllChildColumns();
				int childColumnsCount = (int)allChildColumns.size();
				for (int j = 0; j < childColumnsCount; j++)
				{
					if (allChildColumns[j]->IsFrozen())
					{
						hasFrozenColumn = true;
						break;
					}
				}
				if (!hasFrozenColumn)
				{
					rect.left += scrollH;
					rect.right += scrollH;
				}
				band->SetBounds(rect);
				band->ResetHeaderLayout();
				left += band->GetWidth();
			}
		}		
	}
	
	void BandedGridA::Update()
	{
        if (!GridA::m_lockUpdate)
        {
            int count = (int)m_bands.size();
            int col = 0;
            for (int i = 0; i < count; i++)
            {
                vector<BandedGridColumn*> allChildColumns = m_bands[i]->GetAllChildColumns();
                int childColumnsCount = (int)allChildColumns.size();
                for (int j = 0; j < childColumnsCount; j++)
                {
                    BandedGridColumn* column = allChildColumns[j];
                    column->SetIndex(col);
                    col++;
                }
            }
        }
        GridA::Update();		
	}
}