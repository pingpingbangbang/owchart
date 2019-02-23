#include "..\\stdafx.h"
#include "..\\include\\Grid\\GridCell.h"

namespace OwLib
{
	GridCellStyle::GridCellStyle()
	{
		m_align = HorizontalAlignA_Inherit;
		m_autoEllipsis = false;
		m_backColor = COLOR_EMPTY;
		m_foreColor = COLOR_EMPTY;
		m_font = 0;
	}
	
	GridCellStyle::~GridCellStyle()
	{
		if(m_font)
		{
			delete m_font;
			m_font = 0;
		}
	}
	
	HorizontalAlignA GridCellStyle::GetAlign()
	{
		return m_align;
	}
	
	void GridCellStyle::SetAlign(HorizontalAlignA align)
	{
		m_align = align;
	}
	
	bool GridCellStyle::AutoEllipsis()
	{
		return m_autoEllipsis;
	}
	
	void GridCellStyle::SetAutoEllipsis(bool autoEllipsis)
	{
		m_autoEllipsis = autoEllipsis;
	}
	
	_int64 GridCellStyle::GetBackColor()
	{
		return m_backColor;
	}
	
	void GridCellStyle::SetBackColor(_int64 backColor)
	{
		m_backColor = backColor;
	}

	FONT* GridCellStyle::GetFont()
	{
		return m_font;
	}
	
	void GridCellStyle::SetFont(FONT *font)
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
	
	_int64 GridCellStyle::GetForeColor()
	{
		return m_foreColor;
	}
	
	void GridCellStyle::SetForeColor(_int64 foreColor)
	{
		m_foreColor = foreColor;
	}

	void GridCellStyle::Copy(GridCellStyle *style)
	{
		this->m_align = style->m_align;
		this->m_autoEllipsis = style->m_autoEllipsis;
		if(!m_font)
		{
			m_font = new FONT();
		}
		m_font->Copy(style->m_font);
		this->m_foreColor = style->m_foreColor;
		this->m_backColor = style->m_backColor;
	}
	////////////////////////////////////////////////////////////////////////

	GridCell::GridCell()
	{
		m_allowEdit = false;
		m_colSpan = 1;
		m_column = 0;
		m_grid = 0;
		m_row = 0;
		m_rowSpan = 1;
		m_style = 0;
		m_tag = 0;
	}
	
	GridCell::~GridCell()
	{
		m_column = 0;
		m_grid = 0;
		m_row = 0;
		if(m_style)
		{
			delete m_style;
			m_style = 0;
		}
		m_tag = 0;
	}
	
	bool GridCell::AllowEdit()
	{
		return m_allowEdit;
	}
	
	void GridCell::SetAllowEdit(bool allowEdit)
	{
		m_allowEdit = allowEdit;
	}
	
	int GridCell::GetColSpan()
	{
		return m_colSpan;
	}
	
	void GridCell::SetColSpan(int colSpan)
	{
		m_colSpan = colSpan;
	}
	
	GridColumn* GridCell::GetColumn()
	{
		return m_column;
	}
	
	void GridCell::SetColumn(GridColumn *column)
	{
		m_column = column;
	}
	
	GridA* GridCell::GetGrid()
	{
		return m_grid;
	}
	
	void GridCell::SetGrid(GridA *grid)
	{
		m_grid = grid;
	}

	String GridCell::GetName()
	{
		return m_name;
	}
	
	void GridCell::SetName(const String& name)
	{
		m_name = name;
	}
	
	GridRow* GridCell::GetRow()
	{
		return m_row;
	}

	void GridCell::SetRow(GridRow *row)
	{
		m_row = row;
	}

	int GridCell::GetRowSpan()
	{
		return m_rowSpan;
	}

	void GridCell::SetRowSpan(int rowSpan)
	{
		m_rowSpan = rowSpan;
	}

	GridCellStyle* GridCell::GetStyle()
	{
		return m_style;
	}

	void GridCell::SetStyle(GridCellStyle *style)
	{		
		if(style)
		{
			if(!m_style)
			{
				m_style = new GridCellStyle();
			}
			m_style->Copy(style);
		}
		else if(m_style)
		{
			delete m_style;
			m_style = 0;
		}
	}

	void* GridCell::GetTag()
	{
		return m_tag;
	}
	
	void GridCell::SetTag(void *tag)
	{
		m_tag = tag;
	}

	String GridCell::GetText()
	{
		return GetString();
	}
	
	void GridCell::SetText(const String& text)
	{
		SetString(text);
	}

	int GridCell::CompareTo(GridCell *cell)
	{
		return 0;
	}
	
	bool GridCell::GetBool()
	{
		return false;
	}
	
	double GridCell::GetDouble()
	{
		return 0;
	}
	
	float GridCell::GetFloat()
	{
		return 0;
	}
	
	int GridCell::GetInt()
	{
		return 0;
	}
	
	_int64 GridCell::GetLong()
	{
		return 0;
	}
	
	String GridCell::GetPaintText()
	{
		return GetText();
	}
	
	void GridCell::GetProperty(const String& name, String *value, String *type)
	{
		if (name == L"align")
		{
			*type = L"enum:HorizontalAlignA";
			GridCellStyle* style = GetStyle();
			if (style != NULL)
			{
				*value = CStr::ConvertHorizontalAlignToStr(style->GetAlign());
			}
		}
		else if (name == L"allowedit")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(AllowEdit());
		}
		else if (name == L"autoellipsis")
		{
			*type = L"bool";
			GridCellStyle* style2 = GetStyle();
			if (style2 != NULL)
			{
				*value = CStr::ConvertBoolToStr(style2->AutoEllipsis());
			}
		}
		else if (name == L"backcolor")
		{
			*type = L"color";
			GridCellStyle* style3 = GetStyle();
			if (style3 != NULL)
			{
				*value = CStr::ConvertColorToStr(style3->GetBackColor());
			}
		}
		else if (name == L"colspan")
		{
			*type = L"int";
			*value = CStr::ConvertIntToStr(GetColSpan());
		}
		else if (name == L"font")
		{
			*type = L"font";
			GridCellStyle* style4 = GetStyle();
			if ((style4 != NULL) && (style4->GetFont() != NULL))
			{
				*value = CStr::ConvertFontToStr(style4->GetFont());
			}
		}
		else if (name == L"forecolor")
		{
			*type = L"color";
			GridCellStyle* style5 = GetStyle();
			if (style5 != NULL)
			{
				*value = CStr::ConvertColorToStr(style5->GetForeColor());
			}
		}
		else if (name == L"name")
		{
			*type = L"String";
			*value = GetName();
		}
		else if (name == L"rowspan")
		{
			*type = L"int";
			*value = CStr::ConvertIntToStr(GetRowSpan());
		}
		else if (name == L"text")
		{
			*type = L"String";
			*value = GetText();
		}
		else
		{
			*type = L"undefined";
			*value = L"";
		}
	}
	
	vector<String> GridCell::GetPropertyNames()
	{
		vector<String> list;
		list.push_back(L"Align");
		list.push_back(L"AllowEdit");
		list.push_back(L"AutoEllipsis");
		list.push_back(L"BackColor");
		list.push_back(L"ColSpan");
		list.push_back(L"Font");
		list.push_back(L"ForeColor");
		list.push_back(L"Name");
		list.push_back(L"RowSpan");
		list.push_back(L"Text");
		return list;
	}
	
	String GridCell::GetString()
	{
		return L"";
	}
	
	void GridCell::OnAdd()
	{
		
	}
	
	void GridCell::OnPaint(CPaint *paint, const RECT& rect, const RECT& clipRect, bool isAlternate)
	{
		int clipW = clipRect.right - clipRect.left;
		int clipH = clipRect.bottom - clipRect.top;
		if (clipW > 0 && clipH > 0 && m_grid && m_row && m_column)
		{
			String paintText = GetPaintText();
			bool selected = false;
			if (m_grid->GetSelectionMode() == GridSelectionMode_SelectCell)
			{
				vector<GridCell*> selectedCells = m_grid->GetSelectedCells();
				int selectedCellSize = (int)selectedCells.size();
				for (int i = 0; i < selectedCellSize; i++)
				{
					if (selectedCells[i] == this)
					{
						selected = true;
						break;
					}
				}
			}
			else if (m_grid->GetSelectionMode() == GridSelectionMode_SelectFullColumn)
			{
				vector<GridColumn*> selectedColumns = m_grid->GetSelectedColumns();
				int selectedColumnsSize = (int)selectedColumns.size();
				for (int j = 0; j < selectedColumnsSize; j++)
				{
					if (selectedColumns[j] == m_column)
					{
						selected = true;
						break;
					}
				}
			}
			else if (m_grid->GetSelectionMode() == GridSelectionMode_SelectFullRow)
			{
				vector<GridRow*> selectedRows = m_grid->GetSelectedRows();
				int selectedRowsSize = (int)selectedRows.size();
				for (int k = 0; k < selectedRowsSize; k++)
				{
					if (selectedRows[k] == m_row)
					{
						selected = true;
						break;
					}
				}
			}
			FONT* font = 0;
			_int64 backColor = COLOR_EMPTY;
			_int64 foreColor = COLOR_EMPTY;
			bool autoEllipsis = m_grid->AutoEllipsis();
			HorizontalAlignA cellAlign = m_column->GetCellAlign();
			if (m_style)
			{
				if (m_style->AutoEllipsis())
				{
					autoEllipsis = m_style->AutoEllipsis();
				}
				backColor = m_style->GetBackColor();
				if (m_style->GetFont())
				{
					font = m_style->GetFont();
				}
				foreColor = m_style->GetForeColor();
				if (m_style->GetAlign() != HorizontalAlignA_Inherit)
				{
					cellAlign = m_style->GetAlign();
				}
			}
			GridRowStyle* rowStyle = m_grid->GetRowStyle();
			if (isAlternate)
			{
				GridRowStyle* alternateRowStyle = m_grid->GetAlternateRowStyle();
				if (alternateRowStyle)
				{
					rowStyle = alternateRowStyle;
				}
			}
			if (rowStyle)
			{
				if (backColor == COLOR_EMPTY)
				{
					if (selected)
					{
						backColor = rowStyle->GetSelectedBackColor();
					}
					else if (m_row == m_grid->GetHoveredRow())
					{
						backColor = rowStyle->GetHoveredBackColor();
					}
					else
					{
						backColor = rowStyle->GetBackColor();
					}
				}
				if (!font)
				{
					font = rowStyle->GetFont();
				}
				if (foreColor == COLOR_EMPTY)
				{
					if (selected)
					{
						foreColor = rowStyle->GetSelectedForeColor();
					}
					else if (m_row == m_grid->GetHoveredRow())
					{
						foreColor = rowStyle->GetHoveredForeColor();
					}
					else
					{
						foreColor = rowStyle->GetForeColor();
					}
				}
			}
			paint->FillRect(backColor, rect);
			SIZE tSize = paint->TextSize(paintText.c_str(), font);
			POINT tPoint = {0, 0};
			tPoint.x = rect.left + 1;
			tPoint.y = rect.top + (clipH / 2) - (tSize.cy / 2);
			if( tSize.cx < rect.right - rect.left)
			{
				switch (cellAlign)
				{
					case HorizontalAlignA_Center:
						tPoint.x = rect.left + (rect.right - rect.left - tSize.cx) / 2;
						break;

					case HorizontalAlignA_Right:
						tPoint.x = rect.right - tSize.cx - 2;
						break;
				}
			}
			RECT tRect;
			tRect.left = tPoint.x;
			tRect.top = tPoint.y;
			tRect.right = tPoint.x + tSize.cx;
			tRect.bottom = tPoint.y + tSize.cy;
			if (autoEllipsis && (tRect.right < clipRect.right || tRect.bottom < clipRect.bottom))
			{
				if (tRect.right < clipRect.right)
				{
					tRect.right = clipRect.right;
				}
				if (tRect.bottom < clipRect.bottom)
				{
					tRect.bottom = clipRect.bottom;
				}
				paint->DrawTextAutoEllipsis(paintText.c_str(), foreColor, font, tRect);
			}
			else
			{
				paint->DrawText(paintText.c_str(), foreColor, font, tRect);
			}
		}
	}

	void GridCell::OnRemove()
	{

	}
    
	void GridCell::SetBool(bool value)
	{
		
	}
    
	void GridCell::SetDouble(double value)
	{
		
	}
    
	void GridCell::SetFloat(float value)
	{
		
	}
    
	void GridCell::SetInt(int value)
	{
		
	}
    
	void GridCell::SetLong(_int64 value)
	{
		
	}
		
	void GridCell::SetProperty(const String& name, const String& value)
	{
		if (name == L"align")
		{
			if (!m_style)
			{
				m_style = new GridCellStyle();
			}
			m_style->SetAlign(CStr::ConvertStrToHorizontalAlign(value));
		}
		else if (name == L"allowedit")
		{
			SetAllowEdit(CStr::ConvertStrToBool(value));
		}
		else if (name == L"autoellipsis")
		{
			if (!m_style)
			{
				m_style = new GridCellStyle();
			}
			m_style->SetAutoEllipsis(CStr::ConvertStrToBool(value));
		}
		else if (name == L"backcolor")
		{
			if (!m_style)
			{
				m_style = new GridCellStyle();
			}
			m_style->SetBackColor(CStr::ConvertStrToColor(value));
		}
		else if (name == L"colspan")
		{
			SetColSpan(CStr::ConvertStrToInt(value));
		}
		else if (name == L"font")
		{
			if (!m_style)
			{
				m_style = new GridCellStyle();
			}
			m_style->SetFont(CStr::ConvertStrToFont(value));
		}
		else if (name == L"forecolor")
		{
			if (!m_style)
			{
				m_style = new GridCellStyle();
			}
			m_style->SetForeColor(CStr::ConvertStrToColor(value));
		}
		else if (name == L"name")
		{
			SetName(value);
		}
		else if (name == L"rowspan")
		{
			SetRowSpan(CStr::ConvertStrToInt(value));
		}
		else if (name == L"text")
		{
			SetText(value);
		}		
	}
        
	void GridCell::SetString(const String& value)
	{
		
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	void GridControlCell::ControlMouseDown(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke)
	{
		GridControlCell* gridControlCell = (GridControlCell*)pInvoke;
		gridControlCell->OnControlMouseDown(mp, button, clicks, delta);
	}

	void GridControlCell::ControlMouseMove(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke)
	{
		GridControlCell* gridControlCell = (GridControlCell*)pInvoke;
		gridControlCell->OnControlMouseMove( mp, button, clicks, delta);
	}

	void GridControlCell::ControlMouseUp(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke)
	{
		GridControlCell* gridControlCell = (GridControlCell*)pInvoke;
		gridControlCell->OnControlMouseUp( mp, button, clicks, delta);
	}

	void GridControlCell::ControlMouseWheel(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke)
	{
		GridControlCell* gridControlCell = (GridControlCell*)pInvoke;
		gridControlCell->OnControlMouseWheel( mp, button, clicks, delta);
	}

	GridControlCell::GridControlCell()
	{
		m_control = 0;
        m_mouseDownEvent = &ControlMouseDown;
        m_mouseMoveEvent = &ControlMouseMove;
        m_mouseUpEvent = &ControlMouseUp;
        m_mouseWheelEvent = &ControlMouseWheel;
	}
	
	GridControlCell::~GridControlCell()
	{
		if(m_control)
		{
			delete m_control;
			m_control = 0;
		}
		m_mouseDownEvent = 0;
		m_mouseMoveEvent = 0;
		m_mouseUpEvent = 0;
		m_mouseWheelEvent = 0;
	}
	
	ControlA* GridControlCell::GetControl()
	{
		return m_control;
	}
	
	void GridControlCell::SetControl(ControlA *control)
	{
		m_control = control;
	}
	
	String GridControlCell::GetString()
	{
		if (m_control)
		{
			m_control->GetText();
		}
		return L"";
	}
	
	String GridControlCell::GetPaintText()
	{
		return L"";
	}
	
	void GridControlCell::OnAdd()
	{
		 GridA* grid = GetGrid();
		if (m_control && grid)
		{
			grid->AddControl(m_control);
			m_control->RegisterEvent(m_mouseDownEvent, EVENTID::MOUSEDOWN, this);
			m_control->RegisterEvent(m_mouseMoveEvent, EVENTID::MOUSEMOVE, this);
			m_control->RegisterEvent(m_mouseUpEvent, EVENTID::MOUSEUP, this);
			m_control->RegisterEvent(m_mouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		}
	}
	
	void GridControlCell::OnControlMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		GridA* grid = GetGrid();
		if (m_control && grid)
		{
			grid->OnMouseDown(grid->PointToControl(m_control->PointToNative(mp)), button, clicks, delta);
		}
	}
	
	void GridControlCell::OnControlMouseMove(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		GridA* grid = GetGrid();
		if (m_control && grid)
		{
			grid->OnMouseMove(grid->PointToControl(m_control->PointToNative(mp)), button, clicks, delta);
		}
	}
	
	void GridControlCell::OnControlMouseUp(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		GridA* grid = GetGrid();
		if (m_control && grid)
		{
			grid->OnMouseUp(grid->PointToControl(m_control->PointToNative(mp)), button, clicks, delta);
		}
	}
	
	void GridControlCell::OnControlMouseWheel(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		GridA* grid = GetGrid();
		if (m_control && grid)
		{
			grid->OnMouseWheel(grid->PointToControl(m_control->PointToNative(mp)), button, clicks, delta);
		}
	}
	
	void GridControlCell::OnPaint(CPaint *paint, const RECT& rect, const RECT& clipRect, bool isAlternate)
	{
		GridCell::OnPaint(paint, rect, clipRect, isAlternate);
        OnPaintControl(paint, rect, clipRect);
	}

	void GridControlCell::OnPaintControl(CPaint *paint, const RECT& rect, const RECT& clipRect)
	{
		if (m_control)
		{
			RECT rect2;
			rect2.left = rect.left + 1;
			rect2.top = rect.top + 1;
			rect2.right = rect.right - 1;
			rect2.bottom = rect.bottom - 1;
			m_control->SetBounds(rect2);
			RECT clipR;
			clipR.left = clipRect.left - rect.left;
			clipR.top = clipRect.top - rect.top;
			clipR.right = clipRect.right - rect.left;
			clipR.bottom = clipRect.bottom - rect.top;
			m_control->SetRegion(clipR);
		}
	}
	
	void GridControlCell::OnRemove()
	{
		GridA* grid = GetGrid();
		if (m_control && grid)
		{
			m_control->UnRegisterEvent(m_mouseDownEvent, EVENTID::MOUSEDOWN);
			m_control->UnRegisterEvent(m_mouseMoveEvent, EVENTID::MOUSEMOVE);
			m_control->UnRegisterEvent(m_mouseUpEvent, EVENTID::MOUSEUP);
			m_control->UnRegisterEvent(m_mouseWheelEvent, EVENTID::MOUSEWHEEL);
			grid->RemoveControl(m_control);
		}
	}
	
	void GridControlCell::SetString(const String& value)
	{
		if (m_control)
		{
			m_control->SetText(value);
		}
	}
}