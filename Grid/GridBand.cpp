#include "..\\stdafx.h"
#include "..\\include\\Grid\\GridBand.h"

namespace OwLib
{
	GridBand::GridBand()
	{
		m_beginWidth = 0;
		m_allowResize = 0;
		m_grid = 0;
		m_index = -1;
		m_mouseDownPoint.x = 0;
		m_mouseDownPoint.y = 0;
		m_parentBand = 0;
		m_resizeState = 0;
		SetWidth(100);
	}
	
	GridBand::~GridBand()
	{
		ClearBands();
		ClearColumns();
		m_grid = 0;
		m_parentBand = 0;		
	}

	bool GridBand::AllowResize()
	{
		return m_allowResize;
	}
	
	void GridBand::SetAllowResize(bool allowResize)
	{
		m_allowResize = allowResize;
	}
	
	BandedGridA* GridBand::GetGrid()
	{
		return m_grid;
	}
	
	void GridBand::SetGrid(BandedGridA *grid)
	{
		m_grid = grid;
	}
	
	int GridBand::GetIndex()
	{
		return m_index;
	}
	void GridBand::SetIndex(int index)
	{
		m_index = index;
	}
	
	GridBand* GridBand::GetParentBand()
	{
		return m_parentBand;
	}

	void GridBand::SetParentBand(GridBand *parentBand)
	{
		m_parentBand = parentBand;
	}

	void GridBand::AddBand(GridBand *band)
	{
		band->SetGrid(m_grid);
		band->SetParentBand(this);
		m_bands.push_back(band);
		int count = (int)m_bands.size();
		for (int i = 0; i < count; i++)
		{
			m_bands[i]->SetIndex(i);
		}
		m_grid->AddControl(band);
	}

	void GridBand::AddColumn(BandedGridColumn *column)
	{
		column->SetBand(this);
		m_columns.push_back(column);
		m_grid->AddColumn(column);		
	}
	
	void GridBand::ClearBands()
	{
		int count = (int)m_bands.size();
		for (int i = 0; i < count; i++)
		{
			GridBand* control = m_bands[i];
			m_grid->RemoveControl(control);
			delete control;
			control = 0;
		}
		m_bands.clear();
	}
	
	void GridBand::ClearColumns()
	{
		int count = (int)m_columns.size();
		for (int i = 0; i < count; i++)
		{
			BandedGridColumn* column = m_columns[i];
			m_grid->RemoveColumn(column);
			delete column;
			column = 0;
		}
		m_columns.clear();
	}
	
	vector<BandedGridColumn*> GridBand::GetAllChildColumns()
	{
		vector<BandedGridColumn*> list;
		int count = (int)m_columns.size();
		for (int i = 0; i < count; i++)
		{
			BandedGridColumn* item = m_columns[i];
			list.push_back(item);
		}
		int bandCount = (int)m_bands.size();
		for (int j = 0; j < bandCount; j++)
		{
			vector<BandedGridColumn*> allChildColumns = m_bands[j]->GetAllChildColumns();
			int childColumnsCount = (int)allChildColumns.size();
			for (int k = 0; k < childColumnsCount; k++)
			{
				BandedGridColumn* column2 = allChildColumns[k];
				list.push_back(column2);
			}
		}
		return list;		
		
	}
	
	vector<GridBand*> GridBand::GetBands()
	{
		return m_bands;
	}
	
	vector<BandedGridColumn*> GridBand::GetColumns()
	{
		return m_columns;
	}
	
	String GridBand::GetControlType()
	{
		return L"GridBand";
	}

	void GridBand::GetProperty(const String& name, String *value, String *type)
	{
		if (name == L"allowresize")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(AllowResize());
		}
		else
		{
			ButtonA::GetProperty(name, value, type);
		}
	}
	vector<String> GridBand::GetPropertyNames()
	{
		vector<String> propertyNames = ButtonA::GetPropertyNames();
		propertyNames.push_back(L"AllowResize" );
		return propertyNames;
	}
	
	void GridBand::InsertBand(int index, GridBand *band)
	{
		band->SetGrid(m_grid);
		band->SetParentBand(this);
		m_bands.insert(m_bands.begin() + index, band);
		int count = (int)m_bands.size();
		for (int i = 0; i < count; i++)
		{
			m_bands[i]->SetIndex(i);
		}
		m_grid->AddControl(band);
	}
	
	void GridBand::InsertColumn(int index, BandedGridColumn *column)
	{
        column->SetBand(this);
		m_columns.insert(m_columns.begin() + index, column);
        m_grid->AddColumn(column);		
	}

	void GridBand::OnMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		ButtonA::OnMouseDown(mp, button, clicks, delta);
        if ((button == MouseButtonsA_Left && clicks == 1) && m_allowResize)
        {
            vector<GridBand*> bands;
            if (m_parentBand)
            {
                bands = m_parentBand->GetBands();
            }
            else
            {
                bands = m_grid->GetBands();
            }
            int count = (int)bands.size();
            if (m_index > 0 && mp.x < 5)
            {
                m_resizeState = 1;
                m_beginWidth = bands[m_index - 1]->GetWidth();
            }
            else if ((!m_parentBand || m_index < count - 1) && mp.x > GetWidth() - 5)
            {
                m_resizeState = 2;
                m_beginWidth = GetWidth();
            }
            m_mouseDownPoint = GetNative()->GetMousePoint();
        }
	}

	void GridBand::OnMouseMove(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		ButtonA::OnMouseMove(mp, button, clicks, delta);
        if (m_allowResize)
        {
            vector<GridBand*> bands;
            if (m_parentBand)
            {
                bands = m_parentBand->GetBands();
            }
            else
            {
                bands = m_grid->GetBands();
            }
            int count = (int)bands.size();
            int width = GetWidth();
            if (m_resizeState > 0)
            {
                POINT curPoint = GetNative()->GetMousePoint();
                int newWidth = m_beginWidth + curPoint.x - m_mouseDownPoint.x;
                if (newWidth > 0)
                {
                    if (m_resizeState == 1)
                    {
                        GridBand* leftBand = bands[m_index - 1];
                        int leftWidth = leftBand->GetWidth();
                        leftBand->SetWidth(newWidth);
                        width += leftWidth - newWidth;
                        SetWidth(width);
                    }
                    else if (m_resizeState == 2)
                    {
                        SetWidth(newWidth);
                        if (m_index < count - 1)
                        {
                            GridBand* rightBand = bands[m_index + 1];
                            int rightWidth = rightBand->GetWidth() + width - newWidth;
                            rightBand->SetWidth(rightWidth);
                        }
                        else if (m_grid)
                        {
                            m_grid->ResetHeaderLayout();
                            m_grid->Update();
                        }
                    }
                }
                if (m_grid)
                {
                    m_grid->Invalidate();
                }
            }
            else if ((m_index <= 0 || mp.x >= 5) && m_parentBand && (m_index >= count - 1 || mp.x <= width - 5))
            {
				SetCursor(CursorsA_Arrow);
            }
            else
			{
				SetCursor(CursorsA_SizeWE);
            }
        }
	}
	void GridBand::OnMouseUp(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		if (m_resizeState != 0)
		{
			ButtonA::OnMouseUp(mp, button, clicks, delta);
			SetCursor(CursorsA_Arrow);
			m_resizeState = 0;
			if (m_grid)
			{
				m_grid->Invalidate();
			}
		}
	}
	
	void GridBand::RemoveBand(GridBand *band)
	{
		int size = (int)m_bands.size();
		bool flag = false;
		for(int i = 0; i < size; i++)
		{
			GridBand* item = m_bands[i];
			if(item == band)
			{
				m_bands.erase(m_bands.begin() + i);
				flag = true;
				break;
			}
		}
		if(flag)
		{
			int count = (int)m_bands.size();
			for (int i = 0; i < count; i++)
			{
				m_bands[i]->SetIndex(i);
			}
			m_grid->RemoveControl(band);
		}
	}

	void GridBand::RemoveColumn(BandedGridColumn *column)
	{
		int size = (int)m_columns.size();
		for(int i = 0; i < size; i++)
		{
			BandedGridColumn* item = m_columns[i];
			if(item == column)
			{
				m_columns.erase(m_columns.begin() + i);
				m_grid->RemoveColumn(column);
				break;
			}			
		}	
	}
	
	void GridBand::ResetHeaderLayout()
	{
		int bandsSize = (int)m_bands.size();
		RECT bounds = GetBounds();
		int left = bounds.left;
		int width = GetWidth();
		if (bandsSize == 0)
		{
			int scrollH = 0;
			HScrollBarA* hScrollBar = GetGrid()->GetHScrollBar();
			if (hScrollBar && hScrollBar->IsVisible())
			{
				scrollH = -hScrollBar->GetPos();
			}
			int columnsSize = (int)m_columns.size();
			for (int i = 0; i < columnsSize; i++)
			{
				BandedGridColumn* column = m_columns[i];
				if (column->IsVisible())
				{
					int columnWidth = column->GetWidth();
					if (i == columnsSize - 1 || left + columnWidth > width + bounds.left)
					{
						columnWidth = width + bounds.left - left;
					}
					RECT cellRect;
					cellRect.left = left;
					cellRect.top = bounds.bottom;
					cellRect.right = left + columnWidth;
					cellRect.bottom = bounds.bottom + column->GetHeight();
					column->SetBounds(cellRect);
					cellRect.left -= scrollH;
					cellRect.right -= scrollH;
					column->SetHeaderRect(cellRect);
					left += columnWidth;
				}
			}
		}
		else
		{
			for (int j = 0; j < bandsSize; j++)
			{
				GridBand *band = m_bands[j];
				if (band->IsVisible())
				{
					int bandWidth = band->GetWidth();
					if (j == bandsSize - 1 || left + bandWidth > width + bounds.left)
					{
						bandWidth = width + bounds.left - left;
					}
					RECT cellRect ;
					cellRect.left = left;
					cellRect.top = bounds.bottom;
					cellRect.right = left + bandWidth;
					cellRect.bottom = bounds.bottom + band->GetHeight();
					band->SetBounds(cellRect);
					band->ResetHeaderLayout();
					left += bandWidth;
				}
			}
		}	
	}

	void GridBand::SetProperty(const String& name, const String& value)
	{
		if (name == L"allowresize")
		{
			SetAllowResize(CStr::ConvertStrToBool(value));
		}
		else
		{
			ButtonA::SetProperty(name, value);
		}		
	}
}