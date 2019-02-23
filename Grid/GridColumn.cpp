#include "..\\stdafx.h"
#include "..\\include\\Grid\\GridColumn.h"

namespace OwLib
{
	GridColumn::GridColumn()
	{
		m_allowResize = false;
		m_allowSort = true;
		m_beginWidth = 0;
		m_cellAlign = HorizontalAlignA_Left;
		m_columnType = L"";
		m_frozen = false;
		m_grid = 0;
		m_headerRect.bottom = 0;
		m_headerRect.top = 0;
		m_headerRect.left = 0;
		m_headerRect.right = 0;
		m_index = -1;
		m_mouseDownPoint.x = 0;
		m_mouseDownPoint.y = 0;
		m_resizeState = 0;
		m_sortMode = GridColumnSortMode_None;
		SetWidth(100);
	}
	
	GridColumn::GridColumn(const String& text)
	{
		m_allowResize = false;
		m_allowSort = true;
		m_beginWidth = 0;
		m_cellAlign = HorizontalAlignA_Left;
		m_columnType = L"";
		m_frozen = false;
		m_grid = 0;
		m_headerRect.bottom = 0;
		m_headerRect.top = 0;
		m_headerRect.left = 0;
		m_headerRect.right = 0;
		m_index = -1;
		m_mouseDownPoint.x = 0;
		m_mouseDownPoint.y = 0;
		m_resizeState = 0;
		m_sortMode = GridColumnSortMode_None;
		SetText(text);
		SetWidth(100);
	}
	
	GridColumn::~GridColumn()
	{
		m_grid = 0;		
	}
	
	bool GridColumn::AllowResize()
	{
		return m_allowResize;
	}
	
	void GridColumn::SetAllowResize(bool allowResize)
	{
		m_allowResize = allowResize;
	}
	
	bool GridColumn::AllowSort()
	{
		return m_allowSort;
	}
	
	void GridColumn::SetAllowSort(bool allowSort)
	{
		m_allowSort = allowSort;
	}
	
	HorizontalAlignA GridColumn::GetCellAlign()
	{
		return m_cellAlign;
	}
	
	void GridColumn::SetCellAlign(HorizontalAlignA cellAlign)
	{
		m_cellAlign = cellAlign;
	}
	
	String GridColumn::GetColumnType()
	{
		return m_columnType;
	}
	
	void GridColumn::SetColumnType(String columnType)
	{
		m_columnType = columnType;
	}
	
	bool GridColumn::IsFrozen()
	{
		return m_frozen;
	}
	
	void GridColumn::SetFrozen(bool frozen)
	{
		m_frozen = frozen;
	}
	
	GridA* GridColumn::GetGrid()
	{
		return m_grid;
	}
	
	void GridColumn::SetGrid(GridA *grid)
	{
		m_grid = grid;
	}
	
	RECT GridColumn::GetHeaderRect()
	{
		return m_headerRect;
	}
	
	void GridColumn::SetHeaderRect(RECT headerRect)
	{
		m_headerRect = headerRect;
	}
	
	int GridColumn::GetIndex()
	{
		return m_index;
	}
	
	void GridColumn::SetIndex(int index)
	{
		m_index = index;
	}
	
	GridColumnSortMode GridColumn::GetSortMode()
	{
		return m_sortMode;
	}
	
	void GridColumn::SetSortMode(GridColumnSortMode sortMode)
	{
		m_sortMode = sortMode;
	}
	
	String GridColumn::GetControlType()
	{
		return L"GridColumn";
	}
	
	void GridColumn::GetProperty(const String& name, String *value, String *type)
	{
		
		if (name == L"allowresize")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(AllowResize());
		}
		else if (name == L"allowsort")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(AllowSort());
		}
		else if (name == L"cellalign")
		{
			*type = L"enum:HorizontalAlignA";
			*value = CStr::ConvertHorizontalAlignToStr(GetCellAlign());
		}
		else if (name == L"columntype")
		{
			*type = L"text";
			*value = GetColumnType();
		}
		else if (name == L"frozen")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(IsFrozen());
		}
		else
		{
			ButtonA::GetProperty(name, value, type);
		}
	}
	
	vector<String> GridColumn::GetPropertyNames()
	{
		vector<String> propertyNames;
		propertyNames.push_back(L"AllowResize");
		propertyNames.push_back(L"AllowSort");
		propertyNames.push_back(L"CellAlign");
		propertyNames.push_back(L"ColumnType");
		propertyNames.push_back(L"Frozen");
		return propertyNames;
	}
	
	void GridColumn::OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		ControlA::OnClick(mp, button, clicks, delta);
		if (m_resizeState == 0)
		{
			switch (m_sortMode)
			{
				case GridColumnSortMode_Asc:
					m_grid->GetSort()->SortColumn(m_grid, this, GridColumnSortMode_Desc);
					break;

				case GridColumnSortMode_Desc:
				case GridColumnSortMode_None:
					m_grid->GetSort()->SortColumn(m_grid, this, GridColumnSortMode_Asc);
					return;

				default:
					return;
			}
		}
	}
	
	bool GridColumn::OnDragBegin()
	{
		return m_resizeState == 0;
	}
	
	void GridColumn::OnDragging()
	{
		ControlA::OnDragging();
		if (m_grid)
		{
			int count = (int)m_grid->m_columns.size();
			for (int i = 0; i < count; i++)
			{
				GridColumn* column = m_grid->m_columns[i];
				if (column == this)
				{
					GridColumn* lastColumn = 0;
					GridColumn* nextColumn = 0;
					if (i > 0)
					{
						lastColumn = m_grid->m_columns[i - 1];
					}
					if (i < count - 1)
					{
						nextColumn = m_grid->m_columns[i + 1];
					}
					NativeBase* native = GetNative();
					int clientX = native->ClientX(this);
					if (lastColumn)
					{
						int lastClientX = native->ClientX(lastColumn);
						if (clientX < lastClientX + (lastColumn->GetWidth() / 2))
						{
							m_grid->m_columns[i - 1] = this;
							m_grid->m_columns[i] = lastColumn;
							m_grid->Update();
							return;
						}
					}
					if (nextColumn)
					{
						int nextClientX = native->ClientX(nextColumn);
						if (clientX + column->GetWidth() > nextClientX + (nextColumn->GetWidth() / 2))
						{
							m_grid->m_columns[i + 1] = this;
							m_grid->m_columns[i] = nextColumn;
							m_grid->Update();
							return;
						}
					}
					break;
				}
			}
		}
	}
	
	void GridColumn::OnMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		ControlA::OnMouseDown(mp, button, clicks, delta);
		if ((button == MouseButtonsA_Left && clicks == 1) && m_allowResize)
		{
			if (m_index > 0 && mp.x < 5)
			{
				m_resizeState = 1;
				m_beginWidth = GetGrid()->GetColumn(m_index - 1)->GetWidth();
			}
			else if (mp.x > GetWidth() - 5)
			{
				m_resizeState = 2;
				m_beginWidth = GetWidth();
			}
			m_mouseDownPoint = GetNative()->GetMousePoint();
		}
	}
	
	void GridColumn::OnMouseMove(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		ControlA::OnMouseMove(mp, button, clicks, delta);
		if (m_allowResize)
		{
			if (m_resizeState > 0)
			{
				POINT curPoint = GetNative()->GetMousePoint();
				int newWidth = m_beginWidth + curPoint.x - m_mouseDownPoint.x;
				if (newWidth > 0)
				{
					if (m_resizeState == 1)
					{
						GetGrid()->GetColumn(m_index - 1)->SetWidth(newWidth);
					}
					else if (m_resizeState == 2)
					{
						SetWidth(newWidth);
					}
				}
				if (m_grid)
				{
					m_grid->Update();
					m_grid->Invalidate();
				}
			}
			else if ((m_index > 0 && mp.x < 5) || (mp.x > GetWidth() - 5))
			{
				SetCursor(CursorsA_SizeWE);
			}
			else
			{
				SetCursor(CursorsA_Arrow);
			}
			if (IsDragging())
			{
				SetCursor(CursorsA_Arrow);
			}
		}
	}
	
	void GridColumn::OnMouseUp(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		ControlA::OnMouseUp(mp, button, clicks, delta);
		SetCursor(CursorsA_Arrow);
		m_resizeState = 0;
		if (m_grid)
		{
			m_grid->Invalidate();
		}
	}
	
	void GridColumn::OnPaintForeground(CPaint *paint, const RECT& clipRect)
	{
		ControlA::OnPaintForeground(paint, clipRect);
		if (GetNative() && m_grid)
		{
			RECT rect;
			rect.left = 0;
			rect.top = 0;
			rect.right = GetWidth();
			rect.bottom = GetHeight();
			int tLeft = rect.right - 15;
			int midTop = rect.top + (rect.bottom - rect.top) / 2;
			_int64 paintingForeColor = GetPaintingForeColor();
			if (m_sortMode == GridColumnSortMode_Asc)
			{
				POINT*  points = new POINT[3];
				POINT point1;
				point1.x = tLeft + 5;
				point1.y = midTop - 5;
				POINT point2;
				point2.x = tLeft;
				point2.y = midTop + 5;
				POINT point3;
				point3.x = tLeft + 10;
				point3.y = midTop + 5;
				points[0] = point1;
				points[1] = point2;
				points[2] = point3;
				paint->FillPolygon(paintingForeColor, points, 3);
				delete[] points;
			}
			else if (m_sortMode == GridColumnSortMode_Desc)
			{								
				POINT*  pointArray2 = new POINT[3];
				POINT point1;
				point1.x = tLeft + 5;
				point1.y = midTop + 5;
				POINT point2;
				point2.x = tLeft;
				point2.y = midTop - 5;
				POINT point3;
				point3.x = tLeft + 10;
				point3.y = midTop - 5;
				pointArray2[0] = point1;
				pointArray2[1] = point2;
				pointArray2[2] = point3;
				paint->FillPolygon(paintingForeColor, pointArray2, 3);
				delete[] pointArray2;
			}
		}
	}

	void GridColumn::SetProperty(const String& name, const String& value)
	{
		if (name == L"allowresize")
		{
			SetAllowResize(CStr::ConvertStrToBool(value));
		}
		else if (name == L"allowsort")
		{
			SetAllowSort(CStr::ConvertStrToBool(value));
		}
		else if (name == L"cellalign")
		{
			SetCellAlign(CStr::ConvertStrToHorizontalAlign(value));
		}
		else if (name == L"columntype")
		{
			SetColumnType(value);
		}
		else if (name == L"frozen")
		{
			SetFrozen(CStr::ConvertStrToBool(value));
		}
		else
		{
			ButtonA::SetProperty(name, value);
		}
	}
}