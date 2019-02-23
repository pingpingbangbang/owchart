#include "..\\stdafx.h"
#include "..\\include\\Grid\\BandedGridColumn.h"

namespace OwLib
{
	BandedGridColumn::BandedGridColumn()
	{
		m_band = 0;
	}
	
	BandedGridColumn::~BandedGridColumn()
	{
		m_band = 0;
	}
	
	GridBand* BandedGridColumn::GetBand()
	{
		return m_band;
	}

	void BandedGridColumn::SetBand(GridBand *band)
	{
		m_band = band;
	}

	String BandedGridColumn::GetControlType()
	{
		return L"BandedGridColumn";
	}
	
	bool BandedGridColumn::OnDragBegin()
	{
		return GridColumn::m_resizeState == 0;
	}

	void BandedGridColumn::OnMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		ControlA::CallMouseEvents(EVENTID::MOUSEDOWN, mp, button, clicks, delta);
		if (m_band && button == MouseButtonsA_Left && clicks == 1 && AllowResize())
		{
			vector<BandedGridColumn*> columns = m_band->GetColumns();
			int columnsSize = (int)columns.size();
			int index = -1;
			for (int i = 0; i < columnsSize; i++)
			{
				if (this == columns[i])
				{
					index = i;
					break;
				}
			}
			if (index > 0 && mp.x < 5)
			{
				GridColumn::m_resizeState = 1;
				GridColumn::m_beginWidth = columns[index - 1]->GetWidth();
			}
			else if (index < columnsSize - 1 && mp.x > GetWidth() - 5)
			{
				GridColumn::m_resizeState = 2;
				GridColumn::m_beginWidth = GetWidth();
			}
			GridColumn::m_mouseDownPoint = GetNative()->GetMousePoint();
		}
		Invalidate();		
	}

	void BandedGridColumn::OnMouseMove(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		ControlA::CallMouseEvents(EVENTID::MOUSEMOVE, mp, button, clicks, delta);
		GridA* grid = GetGrid();
		if (m_band && grid && AllowResize())
		{
			vector<BandedGridColumn*> columns = m_band->GetColumns();
			int count = (int)columns.size();
			int index = -1;
			int width = GetWidth();
			for (int i = 0; i < count; i++)
			{
				if (this == columns[i])
				{
					index = i;
					break;
				}
			}
			if (GridColumn::m_resizeState > 0)
			{
				POINT curPoint = GetNative()->GetMousePoint();
				int newWidth = GridColumn::m_beginWidth + (curPoint.x - m_mouseDownPoint.x);
				if (newWidth > 0)
				{
					if (GridColumn::m_resizeState == 1)
					{
						BandedGridColumn* leftColumn = columns[index - 1];
						int leftWidth = leftColumn->GetWidth();
						leftColumn->SetWidth(newWidth);
						width += leftWidth - newWidth;
						SetWidth(width);
					}
					else if (GridColumn::m_resizeState == 2)
					{
						BandedGridColumn* rightColumn = columns[index + 1];
						int rightWidth = rightColumn->GetWidth() + width - newWidth;
						SetWidth(newWidth);
						rightColumn->SetWidth(rightWidth);
					}
				}
				grid->Invalidate();
			}
			else
			{
				CursorsA cursor = GetCursor();
				CursorsA sizeWE = cursor;
				if ((index > 0 && mp.x < 5) || (index < count - 1 && mp.x > width - 5))
				{
					sizeWE = CursorsA_SizeWE;
				}
				else
				{
					sizeWE = CursorsA_Arrow;
				}
				if (cursor != sizeWE)
				{
					SetCursor(sizeWE);
					Invalidate();
				}
				if (!IsDragging())
				{
					SetCursor(CursorsA_Arrow);
				}
			}
		}		
	}
}