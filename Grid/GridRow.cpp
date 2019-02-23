#include "..\\stdafx.h"
#include "..\\include\\Grid\\GridRow.h"

namespace OwLib
{
	GridRowStyle::GridRowStyle()
	{
		m_backColor = COLOR_CONTROL;
		m_font = new FONT(L"Simsun", 14, false, false, false);
		m_foreColor = COLOR_CONTROLTEXT;
		m_hoveredBackColor = COLOR::ARGB(150, 150, 150);
		m_hoveredForeColor = COLOR_CONTROLTEXT;
		m_selectedBackColor = COLOR::ARGB(100, 100, 100);
		m_selectedForeColor = COLOR_CONTROLTEXT;
	}
	
	GridRowStyle::~GridRowStyle()
	{
		if(m_font)
		{
			delete m_font;
		}
		m_font = 0;
	
	}
	
	_int64 GridRowStyle::GetBackColor()
	{
		return m_backColor;
	}

	void GridRowStyle::SetBackColor(_int64 backColor)
	{
		m_backColor = backColor;
	}

	FONT* GridRowStyle::GetFont()
	{
		return m_font;
	}

	void GridRowStyle::SetFont(FONT *font)
	{
		if(font)
		{
			if(!m_font)
			{
				m_font = new FONT();
			}
			m_font->Copy(font);
		}
		else
		{
			if(m_font)
			{
				delete m_font;
				m_font = 0;
			}
		}
	}
	
	_int64 GridRowStyle::GetForeColor()
	{
		return m_foreColor;
	}

	void GridRowStyle::SetForeColor(_int64 foreColor)
	{
		m_foreColor = foreColor;
	}

	_int64 GridRowStyle::GetHoveredBackColor()
	{
		return m_hoveredBackColor;
	}

	void GridRowStyle::SetHoveredBackColor(_int64 hoveredBackColor)
	{
		m_hoveredBackColor = hoveredBackColor;
	}

	_int64 GridRowStyle::GetHoveredForeColor()
	{
		return m_hoveredForeColor;
	}

	void GridRowStyle::SetHoveredForeColor(_int64 hoveredForeColor)
	{
		m_hoveredForeColor = hoveredForeColor;
	}
	
	_int64 GridRowStyle::GetSelectedBackColor()
	{
		return m_selectedBackColor;
	}
	
	void GridRowStyle::SetSelectedBackColor(_int64 selectedBackColor)
	{
		m_selectedBackColor = selectedBackColor;
	}
	
	_int64 GridRowStyle::GetSelectedForeColor()
	{
		return m_selectedForeColor;
	}
	
	void GridRowStyle::SetSelectedForeColor(_int64 selectedForeColor)
	{
		m_selectedForeColor = selectedForeColor;
	}

	void GridRowStyle::Copy(GridRowStyle *style)
	{
		m_backColor = style->m_backColor;
		m_font->Copy(style->m_font);
		m_foreColor = style->m_foreColor;
		m_hoveredBackColor = style->m_hoveredBackColor;
		m_hoveredForeColor = style->m_hoveredForeColor;
		m_selectedBackColor = style->m_selectedBackColor;
		m_selectedForeColor = style->m_selectedForeColor;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	GridRow::GridRow()
	{
		m_allowEdit = false;
		m_bounds.bottom = 0;
		m_bounds.left = 0;
		m_bounds.right = 0;
		m_bounds.top = 0;
		m_editButton = 0;
		m_grid = 0;
		m_height = 20;
		m_horizontalOffset = 0;
		m_index = -1;
		m_tag = 0;
		m_visible = true;
		m_visibleIndex = -1;
	}

	GridRow::~GridRow()
	{
		ClearCells();
	}
	
	bool GridRow::AllowEdit()
	{
		return m_allowEdit;
	}
	
	void GridRow::SetAllowEdit(bool allowEdit)
	{
		m_allowEdit = allowEdit;
	}
	
	RECT GridRow::GetBounds()
	{
		return m_bounds;
	}
	
	void GridRow::SetBounds(RECT bounds)
	{
		m_bounds = bounds;
	}
	
	ControlA* GridRow::GetEditButton()
	{
		return m_editButton;
	}
	
	void GridRow::SetEditButton(ControlA *editButton)
	{
		m_editButton = editButton;
	}

	GridA* GridRow::GetGrid()
	{
		return m_grid;
	}
	
	void GridRow::SetGrid(GridA *grid)
	{
		m_grid = grid;
	}
	
	int GridRow::GetHeight()
	{
		return m_height;
	}
	
	void GridRow::SetHeight(int height)
	{
		m_height = height;
	}
	
	int GridRow::GetHorizontalOffset()
	{
		return m_horizontalOffset;
	}
	
	void GridRow::SetHorizontalOffset(int horizontalOffset)
	{
		m_horizontalOffset = horizontalOffset;
	}
	
	int GridRow::GetIndex()
	{
		return m_index;
	}
	
	void GridRow::SetIndex(int index)
	{
		m_index = index;
	}
	
	void* GridRow::GetTag()
	{
		return m_tag;
	}
	
	void GridRow::SetTag(void *tag)
	{
		m_tag = tag;
	}
	
	bool GridRow::IsVisible()
	{
		return m_visible;
	}
	
	void GridRow::SetVisible(bool visible)
	{
		m_visible = visible;
	}
	
	int GridRow::GetVisibleIndex()
	{
		return m_visibleIndex;
	}
	
	void GridRow::SetVisibleIndex(int visibleIndex)
	{
		m_visibleIndex = visibleIndex;
	}

	void GridRow::AddCell(int columnIndex, GridCell *cell)
	{
		cell->SetGrid(m_grid);
		cell->SetColumn(m_grid->GetColumn(columnIndex));
		cell->SetRow(this);
		m_cells.push_back(cell);
		cell->OnAdd();		
	}
	
	void GridRow::AddCell(const String& columnName, GridCell *cell)
	{
		cell->SetGrid(m_grid);
		cell->SetColumn(m_grid->GetColumn(columnName));
		cell->SetRow(this);
		m_cells.push_back(cell);
		cell->OnAdd();		
	}
	
	void GridRow::ClearCells()
	{
		int count = (int)m_cells.size();
		for (int i = 0; i < count; i++)
		{
			m_cells[i]->OnRemove();
			delete m_cells[i];
			m_cells[i] = 0;
		}
		m_cells.clear();
	}
	
	GridCell* GridRow::GetCell(int columnIndex)
	{
		int count = (int)m_cells.size();
		if (count > 0)
		{
			if (columnIndex >= 0 && columnIndex < count && m_cells[columnIndex]->GetColumn()->GetIndex() == columnIndex)
			{
				return m_cells[columnIndex];
			}
			for (int i = 0; i < count; i++)
			{
				if (m_cells[i]->GetColumn()->GetIndex() == columnIndex)
				{
					return m_cells[i];
				}
			}
		}
		return 0;	
	}
	
	GridCell* GridRow::GetCell(String columnName)
	{
		int count = (int)m_cells.size();
		for (int i = 0; i < count; i++)
		{
			if (m_cells[i]->GetColumn()->GetName() == columnName)
			{
				return m_cells[i];
			}
		}
		return NULL;
	}

	vector<GridCell*> GridRow::GetCells()
	{
		return m_cells;
	}
	
	void GridRow::GetProperty(const String& name, String *value, String *type)
	{
		if (name == L"allowedit")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(AllowEdit());
		}
		else if (name == L"height")
		{
			*type = L"int";
			*value = CStr::ConvertIntToStr(GetHeight());
		}
		else if (name == L"visible")
		{
			*type = L"int";
			*value = CStr::ConvertBoolToStr(IsVisible());
		}
		else
		{
			*type = L"undefined";
			*value = L"";
		}
	}
	
	vector<String> GridRow::GetPropertyNames()
	{
		vector<String> list;
		list.push_back(L"AllowEdit");
		list.push_back(L"Height");
		list.push_back(L"Visible");
		return list;			
	}
	
	void GridRow::OnAdd()
	{
		int count = (int)m_cells.size();
		for (int i = 0; i < count; i++)
		{
			m_cells[i]->OnAdd();
		}		
	}
	
	void GridRow::OnPaint(CPaint *paint, const RECT& clipRect, bool isAlternate)
	{
		
	}
	
	void GridRow::OnPaintBorder(CPaint *paint, const RECT& clipRect, bool isAlternate)
	{
		
	}
	
	void GridRow::OnRemove()
	{
		int count = (int)m_cells.size();
		for (int i = 0; i < count; i++)
		{
			m_cells[i]->OnRemove();
		}
	}
	
	void GridRow::RemoveCell(int columnIndex)
	{
		int count = (int)m_cells.size();
		if (columnIndex >= 0 && columnIndex < count)
		{
			GridCell* item = m_cells[columnIndex];
			if (item->GetColumn()->GetIndex() == columnIndex)
			{
				m_cells.erase(m_cells.begin() + columnIndex);
				item->OnRemove();
				return;
			}
			else
			{
				for (int i = 0; i < count; i++)
				{
					item = m_cells[i];
					if (item->GetColumn()->GetIndex() == columnIndex)
					{
						m_cells.erase(m_cells.begin() + columnIndex);
						item->OnRemove();
						return;
					}
				}
			}
		}
	}
	
	void GridRow::SetProperty(const String& name, const String& value)
	{
		if (name == L"allowedit")
		{
			SetAllowEdit(CStr::ConvertStrToBool(value));
		}
		else if (name == L"height")
		{
			SetHeight(CStr::ConvertStrToInt(value));
		}
		else if (name == L"visible")
		{
			SetVisible(CStr::ConvertStrToBool(value));
		}
	}
}