#include "..\\stdafx.h"
#include "..\\include\\Grid\\Grid.h"
#include "..\\include\\Base\\CMathLib.h"

namespace OwLib
{
	GridRowCompare::GridRowCompare()
	{
		m_columnIndex = 0;
		m_type = 0;
	}

	GridRowCompare::~GridRowCompare()
	{
	}

	bool GridRowCompare::operator()(GridRow *x, GridRow *y)
	{
		GridCell *cellLeft = x->GetCell(m_columnIndex);
        GridCell *cellRight = y->GetCell(m_columnIndex);
        if (m_type == 0)
        {
			return cellRight->CompareTo(cellLeft) > 0 ? true : false;
        }
        else
        {
			return cellLeft->CompareTo(cellRight) > 0 ? true : false;
        }
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GridSort::GridSort()
	{
	}

	GridSort::~GridSort()
	{
	}

	void GridSort::SortColumn(GridA *grid, GridColumn *column, GridColumnSortMode sortMode)
	{
		if(column->AllowSort())
		{
			int columnIndex = -1;
			int colSize = (int)grid->m_columns.size();
			for (int i = 0; i < colSize; i++)
			{
				if (grid->m_columns[i] != column)
				{
					grid->m_columns[i]->SetSortMode(GridColumnSortMode_None);
				}
				else
				{
					grid->m_columns[i]->SetSortMode(sortMode);
					columnIndex = i;
				}
			}
			if (columnIndex != -1)
			{
				GridRowCompare compare;
				compare.m_columnIndex = columnIndex;
				if (sortMode == GridColumnSortMode_Desc)
				{
					compare.m_type = 1;
				}
				sort(grid->m_rows.begin(), grid->m_rows.end(), compare);
			}
			grid->Update();
			grid->Invalidate();
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GridA::CallCellEvents(int eventID, GridCell *cell)
	{
		if(m_events.size() > 0)
		{
			map<int, vector<void*>*>::iterator sIter = m_events.find(eventID);
			if(sIter != m_events.end())
			{
				map<int, vector<void*>*>::iterator sIter2 = m_invokes.find(eventID);
				vector<void*> *events = sIter->second;
				vector<void*> *invokes = sIter2->second;
				int eventSize = (int)events->size();
				for(int i = 0; i < eventSize; i++)
				{
					GridCellEvent func = (GridCellEvent)(*events)[i];
					if(func)
					{
						func(this, cell, (*invokes)[i]);
					}
				}
			}
		}
	}

	void GridA::CallCellMouseEvents(int eventID, GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		if(m_events.size() > 0)
		{
			map<int, vector<void*>*>::iterator sIter = m_events.find(eventID);
			if(sIter != m_events.end())
			{
				map<int, vector<void*>*>::iterator sIter2 = m_invokes.find(eventID);
				vector<void*> *events = sIter->second;
				vector<void*> *invokes = sIter2->second;
				int eventSize = (int)events->size();
				for(int i = 0; i < eventSize; i++)
				{
					GridCellMouseEvent func = (GridCellMouseEvent)(*events)[i];
					if(func)
					{
						func(this, cell, mp, button, clicks, delta, (*invokes)[i]);
					}
				}
			}
		}
	}

	void GridA::MouseEvent(const POINT& mp, MouseButtonsA button, int clicks, int delta, int state)
	{
		int height = GetHeight();
		int hHeight = m_headerVisible ? m_headerHeight : 0;
		int scrollH = 0, scrollV = 0;
		HScrollBarA *hScrollBar = GetHScrollBar();
		VScrollBarA *vScrollBar = GetVScrollBar();
		ControlHost *host = GetNative()->GetHost();
		if (hScrollBar && hScrollBar->IsVisible())
		{
			scrollH = - hScrollBar->GetPos();
		}
		if (vScrollBar && vScrollBar->IsVisible())
		{
			scrollV = - vScrollBar->GetPos();
		}
		POINT fPoint = {0, hHeight + 1 - scrollV};
		POINT ePoint = {0, height - 10 - scrollV};
		GridRow *fRow = GetRow(fPoint);
		GridRow *eRow = GetRow(ePoint);
		while (!eRow && ePoint.y > 0)
		{
			ePoint.y -= 10;
			eRow = GetRow(ePoint);
		}
		if (fRow && eRow)
		{
			int fIndex = fRow->GetIndex();
            int eIndex = eRow->GetIndex();
            for (int i = fIndex; i <= eIndex; i++)
            {
				GridRow *row = m_rows[i];
				if (row->IsVisible())
				{
					RECT rowRect = row->GetBounds();
					rowRect.top += scrollV;
                    rowRect.bottom += scrollV;
					vector<GridCell*> cells;
					vector<GridCell*> unFrozenCells;
					for (int j = 0; j < 2; j++)
					{
						if (j == 0)
						{
							cells = row->m_cells;
						}
						else
						{
							cells = unFrozenCells;
						}
						int cellSize = (int)cells.size();
						for (int c = 0; c < cellSize; c++)
						{
							GridCell *cell = cells[c];
							GridColumn *column = cell->GetColumn();
							if (column->IsVisible())
							{
								if (j == 0 && !column->IsFrozen())
								{
									unFrozenCells.push_back(cell);
									continue;
								}
								RECT headerRect = column->GetHeaderRect();
								if(!column->IsFrozen())
								{
									headerRect.left += scrollH;
									headerRect.right += scrollH;
								}
								int cellWidth = column->GetWidth();
								int colSpan = cell->GetColSpan();
								if (colSpan > 1)
								{
									for (int n = 1; n < colSpan; n++)
									{
										GridColumn *spanColumn = GetColumn(column->GetIndex() + n);
										if(spanColumn && spanColumn->IsVisible())
										{
											cellWidth += spanColumn->GetWidth();
										}
									}
								}
								int cellHeight = row->GetHeight();
								int rowSpan = cell->GetRowSpan();
								if (rowSpan > 1)
								{
									for (int n = 1; n < rowSpan; n++)
									{
										GridRow *spanRow = GetRow(i + n);
										if (spanRow && spanRow->IsVisible())
										{
											cellHeight += spanRow->GetHeight();
										}
									}
								}
								RECT cellRect = {headerRect.left, rowRect.top + m_verticalOffset,
									headerRect.left + cellWidth, rowRect.top + m_verticalOffset + cellHeight};
								if (mp.x >= cellRect.left && mp.x <= cellRect.right 
									&& mp.y >= cellRect.top && mp.y <= cellRect.bottom)
								{
									if(state == 0)
									{
										bool hoverChanged = false;
										if (m_allowHoveredRow && m_hoveredRow != row)
										{
											m_hoveredRow = row;
											hoverChanged = true;
										}
										if (GetNative()->GetPushedControl() == this)
                                        {
                                            if (m_allowDragRow)
                                            {
                                                if (m_selectionMode == GridSelectionMode_SelectFullRow)
                                                {
                                                    int selectedRowsSize = (int)m_selectedRows.size();
                                                    if (selectedRowsSize == 1)
                                                    {
                                                        if (m_selectedRows[0] != row)
                                                        {
                                                            MoveRow(m_selectedRows[0]->GetIndex(), row->GetIndex());
                                                            hoverChanged = true;
                                                        }
                                                    }
                                                }
                                            }
                                        }
										if (m_hoveredCell != cell)
                                        {
                                            if (m_hoveredCell)
                                            {
                                                OnCellMouseLeave(m_hoveredCell, mp, button, clicks, delta);
                                            }
                                            m_hoveredCell = cell;
                                            OnCellMouseEnter(m_hoveredCell, mp, button, clicks, delta);
                                        }
										OnCellMouseMove(cell, mp, button, clicks, delta);
                                        if (!m_editingRow)
                                        {
                                            if (row->AllowEdit())
                                            {
                                                if (GetNative()->GetPushedControl() == this)
                                                {
                                                    int selectedRowsSize = (int)m_selectedRows.size();
                                                    if (selectedRowsSize == 1)
                                                    {
                                                        if (m_selectedRows[0] == row)
                                                        {
                                                            OnRowEditBegin(row);
                                                            hoverChanged = true;
                                                        }
                                                    }
                                                }
                                            }
                                        }
										if (hoverChanged)
										{
											Invalidate();
										}
									}
									else
									{
										if(state == 1)
										{
											m_mouseDownPoint = mp;
											OnCellMouseDown(cell, mp, button, clicks, delta);
											if(button == MouseButtonsA_Left && clicks == 1)
											{
												int multiSelectMode = 0;
												if (m_multiSelect)
												{
													if (host->IsKeyPress(VK_SHIFT))
													{
														multiSelectMode = 1;
													}
													else if (host->IsKeyPress(VK_CONTROL))
													{
														multiSelectMode = 2;
													}
												}
												if (m_selectionMode == GridSelectionMode_SelectCell)
												{
													bool contains = false;
													bool selectedChanged = false;
													int selectedCellSize = (int)m_selectedCells.size();
													if (multiSelectMode == 0 || multiSelectMode == 2)
													{
														vector<GridCell*>::iterator sIter = m_selectedCells.begin();
														for(; sIter != m_selectedCells.end(); ++sIter)
														{
															if(*sIter == cell)
															{
																contains = true;
																if (multiSelectMode == 2)
																{
																	m_selectedCells.erase(sIter);
																	selectedChanged = true;
																}
																break;
															}
														}
													}
													if (multiSelectMode == 0)
													{
														selectedCellSize = (int)m_selectedCells.size();
														if (!contains || selectedCellSize > 1)
														{
															m_selectedCells.clear();
															m_selectedCells.push_back(cell);
															selectedChanged = true;
														}
													}
													else if (multiSelectMode == 2)
													{
														if (!contains)
														{
															m_selectedCells.push_back(cell);
															selectedChanged = true;
														}
													}
													if (selectedChanged)
													{
														OnSelectedCellsChanged();
													}
												}
												else if (m_selectionMode == GridSelectionMode_SelectFullColumn)
												{
													bool contains = false;
													bool selectedChanged = false;
													int selectedColumnsSize = (int)m_selectedColumns.size();
													if (multiSelectMode == 0 || multiSelectMode == 2)
													{
														vector<GridColumn*>::iterator sIter = m_selectedColumns.begin();
														for(; sIter != m_selectedColumns.end(); ++sIter)
														{
															if(*sIter == column)
															{
																contains = true;
																if (multiSelectMode == 2)
																{
																	m_selectedColumns.erase(sIter);
																	selectedChanged = true;
																}
																break;
															}
														}
													}
													if (multiSelectMode == 0)
													{
														if (!contains || selectedColumnsSize > 1)
														{
															m_selectedColumns.clear();
															m_selectedColumns.push_back(column);
															selectedChanged = true;
														}
													}
													else if (multiSelectMode == 2)
													{
														if (!contains)
														{
															m_selectedColumns.push_back(column);
															selectedChanged = true;
														}
													}
													m_selectedCells.clear();
													m_selectedCells.push_back(cell);
													if (selectedChanged)
													{
														OnSelectedColumnsChanged();
													}
												}
												else if (m_selectionMode == GridSelectionMode_SelectFullRow)
												{
													bool contains = false;
													bool selectedChanged = false;
													int selectedRowsSize = (int)m_selectedRows.size();
													if (multiSelectMode == 0 || multiSelectMode == 2)
													{
														vector<GridRow*>::iterator sIter = m_selectedRows.begin();
														for(; sIter != m_selectedRows.end(); ++sIter)
														{
															if(*sIter == row)
															{
																contains = true;
																if (multiSelectMode == 2)
																{
																	m_selectedRows.erase(sIter);
																	selectedChanged = true;
																}
																break;
															}
														}
													}
													if (multiSelectMode == 0)
													{
														selectedRowsSize = (int)m_selectedRows.size();
														if (!contains || selectedRowsSize > 1)
														{
															m_selectedRows.clear();
															m_selectedRows.push_back(row);
															selectedChanged = true;
														}
													}
													else if (multiSelectMode == 1)
													{
														selectedRowsSize = (int)m_selectedRows.size();
														if (selectedRowsSize > 0)
														{
															int firstIndex = m_selectedRows[0]->GetIndex();
															int newIndex = row->GetIndex();
															int minIndex = min(firstIndex, newIndex);
															int maxIndex = max(firstIndex, newIndex);
															m_selectedRows.clear();
															for (int s = minIndex; s <= maxIndex; s++)
															{
																m_selectedRows.push_back(GetRow(s));
															}
														}
														else
														{
															m_selectedRows.push_back(row);
														}
													}
													else if (multiSelectMode == 2)
													{
														if (!contains)
														{
															m_selectedRows.push_back(row);
															selectedChanged = true;
														}
													}
													m_selectedCells.clear();
													m_selectedCells.push_back(cell);
													if (selectedChanged)
													{
														OnSelectedRowsChanged();
													}
												}
											}
										}
										else if(state == 2)
										{
											OnCellMouseUp(cell, mp, button, clicks, delta);
										}
										if (state == 2 || (clicks == 2 && state == 1))
										{	
											 if ((int)m_selectedCells.size() > 0 && m_selectedCells[0] == cell)
											 {
													OnCellClick(cell, mp, button, clicks, delta);
													if (button == MouseButtonsA_Left && cell->AllowEdit())
													{
														if ((m_cellEditMode == GridCellEditMode_DoubleClick && (clicks == 2 && state == 1))
														|| (m_cellEditMode == GridCellEditMode_SingleClick && state == 2))
														{
															OnCellEditBegin(cell);
														}
													}
											 }
										}
										Invalidate();
									}
									unFrozenCells.clear();
									if (state == 1 && m_editingRow)
                                    {
                                        OnRowEditEnd();
                                    }
									return;
								}
							}
						}
					}
					unFrozenCells.clear();
				}
			}
		}
	    if (state == 1 && m_editingRow)
        {
            OnRowEditEnd();
        }
	}

	void GridA::EditTextBoxLostFocus(void *sender, void *pInvoke)
	{
		GridA *grid = (GridA*)pInvoke;
		if(grid)
		{
			TextBoxA *textBox = grid->GetEditTextBox();
			if (textBox && textBox->GetTag())
			{
				GridCell *cell = (GridCell*)textBox->GetTag();
				grid->OnCellEditEnd(cell);
			}
		}
	}

	void GridA::EditTextBoxKeyDown(void *sender, char key, void *pInvoke)
	{
		GridA *grid = (GridA*)pInvoke;
		if(grid)
		{
			if(key == 13)
			{
				TextBoxA *editTextBox = grid->GetEditTextBox();
				if(editTextBox && !editTextBox->IsMultiline())
				{
					editTextBox->SetFocused(false);
				}
			}
			else if(key == 27)
			{
				if(grid)
				{
					grid->OnCellEditEnd(0);
				}
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int GridA::GetAllVisibleColumnsWidth()
	{
		int allVisibleColumnsWidth = 0;
		int colSize = (int)m_columns.size();
		for (int i = 0; i < colSize; i++)
		{
			GridColumn *column = m_columns[i];
			if (column->IsVisible())
			{
				allVisibleColumnsWidth += column->GetWidth();
			}
		}
		return allVisibleColumnsWidth;
	}

	int GridA::GetAllVisibleRowsHeight()
	{
		int allVisibleRowsHeight = 0;
		int rowSize = (int)m_rows.size();
		for (int i = 0; i < rowSize; i++)
		{
			if (m_rows[i]->IsVisible())
			{
				allVisibleRowsHeight += m_rows[i]->GetHeight();
			}
		}
		return allVisibleRowsHeight;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GridA::GridA()
	{
		m_allowDragRow = false;
		m_allowHoveredRow = true;
		m_alternateRowStyle = 0;
		m_cellEditMode = GridCellEditMode_SingleClick;
		m_editingCell = 0;
		m_editingRow = 0;
		m_editTextBoxLostFocusEvent = EditTextBoxLostFocus;
		m_editTextBoxKeyDownEvent = EditTextBoxKeyDown;
		m_editTextBox = 0;
		m_gridLineColor = COLOR::ARGB(100, 100, 100);
		m_hasUnVisibleRow = false;
		m_headerVisible = true;
		m_headerHeight = 20;
		m_horizontalOffset = 0;
		m_hoveredCell = 0;
		m_hoveredRow = 0;
		m_lockUpdate = false;
		m_mouseDownPoint.x = 0;
		m_mouseDownPoint.y = 0;
		m_multiSelect = false;
		m_rowStyle = new GridRowStyle;
		m_selectionMode = GridSelectionMode_SelectFullRow;
		m_sort = new GridSort;
		m_timerID = GetNewTimerID();
		m_useAnimation = false;
		m_verticalOffset = 0;
		SetShowHScrollBar(true);
		SetShowVScrollBar(true);
	}

	GridA::~GridA()
	{
		StopTimer(m_timerID);
		m_animateAddRows.clear();
		m_animateRemoveRows.clear();
		if(m_alternateRowStyle)
		{
			delete m_alternateRowStyle;
			m_alternateRowStyle = 0;
		}
		if(m_rowStyle)
		{
			delete m_rowStyle;
			m_rowStyle = 0;
		}
		m_editingCell = 0;
		m_editingRow = 0;
		if(m_editTextBox)
		{
			if (m_editTextBoxLostFocusEvent)
			{
				m_editTextBox->UnRegisterEvent(m_editTextBoxLostFocusEvent, EVENTID::LOSTFOCUS);
				m_editTextBoxLostFocusEvent = 0;
			}
			if(m_editTextBoxKeyDownEvent)
			{
				m_editTextBox->UnRegisterEvent(m_editTextBoxKeyDownEvent, EVENTID::KEYDOWN);
				m_editTextBoxKeyDownEvent = 0;
			}
			m_editTextBox = 0;
		}
		m_editTextBox = 0;
		if(m_sort)
		{
			delete m_sort;
			m_sort = 0;
		}
		m_hoveredCell = 0;
		m_hoveredRow = 0;
		Clear();
	}

	bool GridA::AllowDragRow()
	{
		return m_allowDragRow;
	}

	void GridA::SetAllowDragRow(bool allowDragRow)
	{
		m_allowDragRow = allowDragRow;
	}

	bool GridA::AllowHoveredRow()
	{
		return m_allowHoveredRow;
	}

	void GridA::SetAllowHoveredRow(bool allowHoveredRow)
	{
		m_allowHoveredRow = allowHoveredRow;
	}

	GridRowStyle* GridA::GetAlternateRowStyle()
	{
		return m_alternateRowStyle;
	}

	void GridA::SetAlternateRowStyle(GridRowStyle *alternateRowStyle)
	{
		if(alternateRowStyle)
		{
			if(!m_alternateRowStyle)
			{
				m_alternateRowStyle = new GridRowStyle;
			}
			m_alternateRowStyle->Copy(alternateRowStyle);
		}
		else
		{
			if(m_alternateRowStyle)
			{
				delete m_alternateRowStyle;
				m_alternateRowStyle = 0;
			}
		}
	}

	GridCellEditMode GridA::GetCellEditMode()
	{
		return m_cellEditMode;
	}

	void GridA::SetCellEditMode(GridCellEditMode cellEditMode)
	{
		m_cellEditMode = cellEditMode;
	}

	TextBoxA* GridA::GetEditTextBox()
	{
		return m_editTextBox;
	}

	_int64 GridA::GetGridLineColor()
	{
		return m_gridLineColor;
	}

	void GridA::SetGridLineColor(_int64 gridLineColor)
	{
		m_gridLineColor = gridLineColor;
	}

	bool GridA::IsHeaderVisible()
	{
		return m_headerVisible;
	}

	void GridA::SetHeaderVisible(bool headerVisible)
	{
		m_headerVisible = headerVisible;
	}

	int GridA::GetHeaderHeight()
	{
		return m_headerHeight;
	}

	void GridA::SetHeaderHeight(int headerHeight)
	{
		m_headerHeight = headerHeight;
	}

	int GridA::GetHorizontalOffset()
	{
		return m_horizontalOffset;
	}

	void GridA::SetHorizontalOffset(int horizontalOffset)
	{
		m_horizontalOffset = horizontalOffset;
	}

	GridCell* GridA::GetHoveredCell()
	{
		return m_hoveredCell;
	}

	GridRow* GridA::GetHoveredRow()
	{
		return m_hoveredRow;
	}

	bool GridA::IsMultiSelect()
	{
		return m_multiSelect;
	}

	void GridA::SetMultiSelect(bool multiSelect)
	{
		m_multiSelect = multiSelect;
	}

	GridRowStyle* GridA::GetRowStyle()
	{
		return m_rowStyle;
	}

	void GridA::SetRowStyle(GridRowStyle *rowStyle)
	{
		if(rowStyle)
		{
			if(!m_rowStyle)
			{
				m_rowStyle = new GridRowStyle;
			}
			m_rowStyle->Copy(rowStyle);
		}
		else
		{
			if(m_rowStyle)
			{
				delete m_rowStyle;
				m_rowStyle = 0;
			}
		}
	}

	vector<GridCell*> GridA::GetSelectedCells()
	{
		return m_selectedCells;
	}

	void GridA::SetSelectedCells(vector<GridCell*> selectedCells)
	{
        m_selectedCells.clear();
        int selectedCellsSize = (int)selectedCells.size();
        for (int i = 0; i < selectedCellsSize; i++)
        {
			m_selectedCells.push_back(selectedCells[i]);
        }
		OnSelectedCellsChanged();
	}

	vector<GridColumn*> GridA::GetSelectedColumns()
	{
		return m_selectedColumns;
	}

	void GridA::SetSelectedColumns(vector<GridColumn*> selectedColumns)
	{
        m_selectedColumns.clear();
        int selectedColumnsSize = (int)selectedColumns.size();
        for (int i = 0; i < selectedColumnsSize; i++)
        {
            m_selectedColumns.push_back(selectedColumns[i]);
        }
		OnSelectedColumnsChanged();
	}

	vector<GridRow*> GridA::GetSelectedRows()
	{
		return m_selectedRows;
	}

	void GridA::SetSelectedRows(vector<GridRow*> selectedRows)
	{
        m_selectedRows.clear();
        int selectedRowsSize = (int)selectedRows.size();
        for (int i = 0; i < selectedRowsSize; i++)
        {
            m_selectedRows.push_back(selectedRows[i]);
        }
		OnSelectedRowsChanged();
	}

	GridSelectionMode GridA::GetSelectionMode()
	{
		return m_selectionMode;
	}

	void GridA::SetSelectionMode(GridSelectionMode selectionMode)
	{
		m_selectionMode = selectionMode;
	}

	GridSort* GridA::GetSort()
	{
		return m_sort;
	}

	void GridA::SetSort(GridSort *sort)
	{
		if(m_sort)
		{
			delete m_sort;
			m_sort = 0;
		}
		m_sort = sort;
	}

	bool GridA::UseAnimation()
	{
		return m_useAnimation;
	}

	void GridA::SetUseAnimation(bool useAnimation)
	{
		m_useAnimation = useAnimation;
		if(m_useAnimation)
		{
			StartTimer(m_timerID, 20);
		}
		else
		{
			StopTimer(m_timerID);
		}
	}

	int GridA::GetVerticalOffset()
	{
		return m_verticalOffset;
	}

	void GridA::SetVerticalOffset(int verticalOffset)
	{
		m_verticalOffset = verticalOffset;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GridA::AddColumn(GridColumn *column)
	{
		column->SetGrid(this);
		m_columns.push_back(column);
		int columnsSize = (int)m_columns.size();
		for (int i = 0; i < columnsSize; i++)
		{
			m_columns[i]->SetIndex(i);
		}
		AddControl(column);
	}

	void GridA::AddRow(GridRow *row)
	{
		row->SetGrid(this);
		m_rows.push_back(row);
		row->OnAdd();
		if (m_selectionMode == GridSelectionMode_SelectFullRow)
		{
			int selectedRowsSize = (int)m_selectedRows.size();
			if (selectedRowsSize == 0)
			{
				m_selectedRows.push_back(row);
				OnSelectedRowsChanged();
			}
		}
	}

	void GridA::AnimateAddRow(GridRow *row)
	{
		row->SetGrid(this);
		m_rows.push_back(row);
		row->OnAdd();
		if (m_selectionMode == GridSelectionMode_SelectFullRow)
		{
			int selectedRowsSize = (int)m_selectedRows.size();
			if (selectedRowsSize == 0)
			{
				m_selectedRows.push_back(row);
				OnSelectedRowsChanged();
			}
		}
		if (m_useAnimation)
        {
            m_animateAddRows.push_back(row);
        }
	}

	void GridA::AnimateRemoveRow(GridRow *row)
	{
		if (m_useAnimation)
        {
            m_animateRemoveRows.push_back(row);
        }
        else
        {
            RemoveRow(row);
        }
	}

	void GridA::BeginUpdate()
	{
		m_lockUpdate = true;
	}

	void GridA::Clear()
	{
		ClearRows();
		ClearColumns();
	}

	void GridA::ClearColumns()
	{
		m_selectedColumns.clear();
		int colSize = (int)m_columns.size();
		for(int i = 0; i < colSize; i++)
		{
			RemoveControl(m_columns[i]);
			delete m_columns[i];
			m_columns[i] = 0;
		}
		m_columns.clear();
	}

	void GridA::ClearRows()
	{
		m_hasUnVisibleRow = false;
		m_hoveredCell = 0;
		m_hoveredRow = 0;
		m_selectedRows.clear();
		int rowSize = (int)m_rows.size();
		for (int i = 0; i < rowSize; i++)
		{
			m_rows[i]->OnRemove();
			delete m_rows[i];
			m_rows[i] = 0;
		}
		m_rows.clear();
	}

	void GridA::EndUpdate()
	{
        if (m_lockUpdate)
        {
            m_lockUpdate = false;
            Update();
        }
	}

	GridColumn* GridA::GetColumn(int columnIndex)
	{
		if (columnIndex >= 0 && columnIndex < (int)m_columns.size())
		{
			return m_columns[columnIndex];
		}
		return 0;
	}

	GridColumn* GridA::GetColumn(const String& columnName)
	{
		int colSize = (int)m_columns.size();
		for (int i = 0; i < colSize; i++)
		{
			if (m_columns[i]->GetName() == columnName)
			{
				return m_columns[i];
			}
		}
		return 0;
	}

	vector<GridColumn*> GridA::GetColumns()
	{
		return m_columns;
	}

	int GridA::GetContentHeight()
	{
		int allVisibleRowsHeight = GetAllVisibleRowsHeight();
		if(allVisibleRowsHeight > 0)
		{
			if(allVisibleRowsHeight <= GetHeight())
			{
				allVisibleRowsHeight += m_headerVisible ? m_headerHeight : 0;
			}
			return allVisibleRowsHeight;
		}
		else
		{
			return 0;
		}
	}

	int GridA::GetContentWidth()
	{
        return GetAllVisibleColumnsWidth();
	}

	String GridA::GetControlType()
	{
		return L"Grid";
	}

	POINT GridA::GetDisplayOffset()
	{
		POINT offset = {0};
		return offset;
	}

	vector<String> GridA::GetEventNames()
	{
		vector<String> eventNames = ControlA::GetEventNames();
		eventNames.push_back(L"GridCellClick");
		eventNames.push_back(L"GridCellEditBegin");
		eventNames.push_back(L"GridCellEditEnd");
		eventNames.push_back(L"GridCellMouseDown");
		eventNames.push_back(L"GridCellMouseMove");
		eventNames.push_back(L"GridCellMouseUp");
		eventNames.push_back(L"GridSelectedCellsChanged");
		eventNames.push_back(L"GridSelectedColumnsChanged");
		eventNames.push_back(L"GridSelectedRowsChanged");
		return eventNames;
	}

	void GridA::GetProperty(const String& name, String *value, String *type)
	{
		if(name == L"allowdragrow")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(AllowDragRow());
		}
		else if (name == L"allowhoveredrow")
        {
            *type = L"bool";
			*value = CStr::ConvertBoolToStr(AllowHoveredRow());
        }
	    else if (name == L"celleditmode")
        {
            *type = L"enum:GridCellEditMode";
            GridCellEditMode cellEditMode = GetCellEditMode();
            if (cellEditMode == GridCellEditMode_DoubleClick)
            {
                *value = L"DoubleClick";
            }
            else if (cellEditMode == GridCellEditMode_None)
            {
                *value = L"None";
            }
            else
            {
                *value = L"SingleClick";
            }
        }
		if(name == L"gridlinecolor")
		{
			*type = L"color";
			*value = CStr::ConvertColorToStr(GetGridLineColor());
		}
		else if(name == L"headerheight")
		{
			*type = L"int";
			*value = CStr::ConvertIntToStr(GetHeaderHeight());
		}
		else if(name == L"headervisible")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(IsHeaderVisible());
		}
		else if(name == L"horizontaloffset")
		{
			*type = L"int";
			*value = CStr::ConvertIntToStr(GetHorizontalOffset());
		}
		else if(name == L"multiselect")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(IsMultiSelect());
		}
		else if (name == L"selectionmode")
        {
			*type = L"enum:GridSelectionMode";
            GridSelectionMode selectionMode = GetSelectionMode();
            if (selectionMode == GridSelectionMode_SelectCell)
            {
                *value = L"SelectCell";
            }
            else if (selectionMode == GridSelectionMode_SelectFullColumn)
            {
                *value = L"SelectFullColumn";
            }
            else if (selectionMode == GridSelectionMode_SelectFullRow)
            {
                *value = L"SelectFullRow";
            }
            else
            {
                *value = L"none";
            }
        }
		else if(name == L"useanimation")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(UseAnimation());
		}
		else if(name == L"verticaloffset")
		{
			*type = L"int";
			*value = CStr::ConvertIntToStr(GetVerticalOffset());
		}
		else
		{
			DivA::GetProperty(name, value, type);
		}
	}

	vector<String> GridA::GetPropertyNames()
	{
		vector<String> propertyNames = DivA::GetPropertyNames();
		propertyNames.push_back(L"AllowDragRow");
		propertyNames.push_back(L"AllowHoveredRow");
		propertyNames.push_back(L"CellEditMode");
		propertyNames.push_back(L"GridLineColor");
		propertyNames.push_back(L"HeaderHeight");
		propertyNames.push_back(L"HeaderVisible");
		propertyNames.push_back(L"HorizontalOffset");
		propertyNames.push_back(L"MultiSelect");
		propertyNames.push_back(L"SelectionMode");
		propertyNames.push_back(L"UseAnimation");
		propertyNames.push_back(L"VerticalOffset");
		return propertyNames;
	}

	GridRow* GridA::GetRow(const POINT& mp)
	{
		if (m_hasUnVisibleRow)
        {
            int rowsSize = (int)m_rows.size();
            for (int i = 0; i < rowsSize; i++)
            {
                GridRow *row = m_rows[i];
				if (row->IsVisible())
                {
                    RECT bounds = row->GetBounds();
                    if (mp.y >= bounds.top && mp.y <= bounds.bottom)
                    {
                        return row;
                    }
                }
            }
        }
		else
		{
			int begin = 0;
			int end = (int)m_rows.size() - 1;
			int sub = end - begin;
			while (sub >= 0)
			{
				int half = begin + sub / 2;
				GridRow *row = m_rows[half];
				RECT bounds = row->GetBounds();
				if (half == begin || half == end)
				{
					if (mp.y >= m_rows[begin]->GetBounds().top && mp.y <= m_rows[begin]->GetBounds().bottom)
					{
						return m_rows[begin];
					}
					if (mp.y >= m_rows[end]->GetBounds().top && mp.y <= m_rows[end]->GetBounds().bottom)
					{
						return m_rows[end];
					}
					break;
				}
				if (mp.y >= bounds.top && mp.y <= bounds.bottom)
				{
					return row;
				}
				else if (bounds.top > mp.y)
				{
					end = half;
				}
				else if (bounds.bottom < mp.y)
				{
					begin = half;
				}
				sub = end - begin;
			}
		}
        return 0;
	}

	GridRow* GridA::GetRow(int rowIndex)
	{
		if (rowIndex >= 0 && rowIndex < (int)m_rows.size())
		{
			return m_rows[rowIndex];
		}
		return 0;
	}

	vector<GridRow*> GridA::GetRows()
	{
		return m_rows;
	}

	void GridA::GetVisibleRowsIndex(double visiblePercent, int *firstVisibleRowIndex, int *lastVisibleRowIndex)
	{
	    *firstVisibleRowIndex = -1;
        *lastVisibleRowIndex = -1;
        int rowsSize = (int)m_rows.size();
        if (rowsSize > 0)
        {
            for (int i = 0; i < rowsSize; i++)
            {
                GridRow *row = m_rows[i];
                if (IsRowVisible(row, visiblePercent))
                {
                    if (*firstVisibleRowIndex == -1)
                    {
                        *firstVisibleRowIndex = i;
                    }
                }
                else
                {
                    if (*firstVisibleRowIndex != -1)
                    {
                        *lastVisibleRowIndex = i;
                        break;
                    }
                }
            }
            if (*firstVisibleRowIndex != -1 && *lastVisibleRowIndex == -1)
            {
                *lastVisibleRowIndex = *firstVisibleRowIndex;
            }
        }
	}

	void GridA::InsertRow(int index, GridRow *row)
	{
		row->SetGrid(this);
		m_rows.insert(m_rows.begin() + index, row);
		row->OnAdd();
	}

	bool GridA::IsRowVisible(GridRow *row, double visiblePercent)
	{
		int scrollV = 0;
        VScrollBarA *vScrollBar = GetVScrollBar();
        if (vScrollBar && vScrollBar->IsVisible())
        {
            scrollV = -vScrollBar->GetPos();
        }

		int cell = m_headerVisible ? m_headerHeight : 0;
		int floor = GetHeight() - cell;
		RECT bounds = row->GetBounds();
		int top = bounds.top + scrollV;
		int bottom = bounds.bottom + scrollV;
		if (top < cell) 
		{
			top = cell;
		}
		else if (top > floor) 
		{
			top = floor;
		}
		if (bottom < cell) 
		{
			bottom = cell;
		} 
		else if (bottom > floor) 
		{
			bottom = floor;
		}
		if (bottom - top > row->GetHeight() * visiblePercent) {
			return true;
		}
		return false;
	}

	void GridA::MoveRow(int oldIndex, int newIndex)
	{
		int rowsSize = (int)m_rows.size();
        if (rowsSize > 0)
        {
            if (oldIndex >= 0 && oldIndex < rowsSize && newIndex >= 0 && newIndex < rowsSize)
            {
                GridRow *movingRow = m_rows[oldIndex];
                GridRow *targetRow = m_rows[newIndex];
                if (movingRow != targetRow)
                {
                    m_rows[newIndex] = movingRow;
                    m_rows[oldIndex] = targetRow;
                    movingRow->SetIndex(newIndex);
                    targetRow->SetIndex(oldIndex);
                    VScrollBarA *vScrollBar = GetVScrollBar();
                    if (vScrollBar && vScrollBar->IsVisible())
                    {
                        int firstVisibleRowIndex = -1;
						int lastVisibleRowIndex = -1;
                        GetVisibleRowsIndex(0.6, &firstVisibleRowIndex, &lastVisibleRowIndex);
						int th = targetRow->GetHeight();
                        if (newIndex <= firstVisibleRowIndex)
                        {
                            if (newIndex == firstVisibleRowIndex)
                            {
								vScrollBar->SetPos(vScrollBar->GetPos() - th);
                            }
							int count = 0;
                            while (!IsRowVisible(targetRow, 0.6))
                            {
								int newPos = vScrollBar->GetPos() - th;
                                vScrollBar->SetPos(newPos);
								count++;
								if(count > rowsSize || newPos <= vScrollBar->GetPos())
								{
									break;
								}
                            }
                        }
                        else if (newIndex >= lastVisibleRowIndex)
                        {
                            if (newIndex == lastVisibleRowIndex)
                            {
                                vScrollBar->SetPos(vScrollBar->GetPos() + th);
                            }
							int count = 0;
                            while (!IsRowVisible(targetRow, 0.6))
                            {
								int newPos = vScrollBar->GetPos() + th;
                                vScrollBar->SetPos(newPos);
								count++;
								if(count > rowsSize || newPos >= vScrollBar->GetPos())
								{
									break;
								}
                            }
                        }
                        vScrollBar->Update();
                    }
					Update();
                }
            }
        }
	}

	void GridA::OnCellClick(GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		CallCellMouseEvents(EVENTID::GRIDCELLCLICK, cell, mp, button, clicks, delta);
	}

	void GridA::OnCellEditBegin(GridCell *cell)
	{
        m_editingCell = cell;
		if (!m_editTextBox)
        {
			ControlHost *host = GetNative()->GetHost();
            m_editTextBox = dynamic_cast<TextBoxA*>(host->CreateInternalControl(this, L"edittextbox"));
			m_editTextBox->RegisterEvent(m_editTextBoxLostFocusEvent, EVENTID::LOSTFOCUS, this);
			m_editTextBox->RegisterEvent(m_editTextBoxKeyDownEvent, EVENTID::KEYDOWN, this);
            AddControl(m_editTextBox);
        }
		m_editTextBox->SetFocused(true);
		m_editTextBox->SetTag(m_editingCell);
		String text = m_editingCell->GetText();
		m_editTextBox->SetText(text);
		m_editTextBox->ClearRedoUndo();
		m_editTextBox->SetVisible(true);
		if(text.length() > 0)
		{
			m_editTextBox->SetSelectionStart((int)text.length());
		}
		CallCellEvents(EVENTID::GRIDCELLEDITBEGIN, cell);
	}

	void GridA::OnCellEditEnd(GridCell *cell)
	{
		if(cell)
		{
			cell->SetText(m_editTextBox->GetText());
		}
		m_editTextBox->SetTag(0);
		m_editTextBox->SetVisible(false);
		m_editingCell = 0;
		CallCellEvents(EVENTID::GRIDCELLEDITEND, cell);
		Invalidate();
	}

	void GridA::OnCellMouseDown(GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		CallCellMouseEvents(EVENTID::GRIDCELLMOUSEDOWN, cell, mp, button, clicks, delta);
	}

	void GridA::OnCellMouseEnter(GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		CallCellMouseEvents(EVENTID::GRIDCELLMOUSEENTER, cell, mp, button, clicks, delta);
		GridCellStyle* style = cell->GetStyle();
		if (AutoEllipsis() || (style && style->AutoEllipsis()))
        {
            m_native->GetHost()->ShowToolTip(this, cell->GetPaintText(), m_native->GetMousePoint());
        }
	}

	void GridA::OnCellMouseLeave(GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		CallCellMouseEvents(EVENTID::GRIDCELLMOUSELEAVE, cell, mp, button, clicks, delta);
	}

	void GridA::OnCellMouseMove(GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		CallCellMouseEvents(EVENTID::GRIDCELLMOUSEMOVE, cell, mp, button, clicks, delta);
	}

	void GridA::OnCellMouseUp(GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		CallCellMouseEvents(EVENTID::GRIDCELLMOUSEUP, cell, mp, button, clicks, delta);
	}

	void GridA::OnKeyDown(char key)
	{
		ControlHost *host = GetNative()->GetHost();
		if(!host->IsKeyPress(VK_CONTROL)
		&& !host->IsKeyPress(VK_MENU)
		&& !host->IsKeyPress(VK_SHIFT))
		{
			if (key == 38 || key == 40)
			{
				CallKeyEvents(EVENTID::KEYDOWN, key);
				GridRow *row = 0;
				int offset = 0;
				if (key == 38)
				{
					row = SelectFrontRow();
					if(row)
					{
						offset = -row->GetHeight();
					}
				}
				else if (key == 40)
				{
					row = SelectNextRow();
					if(row)
					{
						offset = row->GetHeight();
					}
				}
				if (row && !IsRowVisible(row, 0.6))
				{
					VScrollBarA *vScrollBar = GetVScrollBar();
					if (vScrollBar && vScrollBar->IsVisible())
					{
						vScrollBar->SetPos(vScrollBar->GetPos() + offset);
						vScrollBar->Update();
					}
				}
				Invalidate();   
				return;
			}
		}
		DivA::OnKeyDown(key);
	}

	void GridA::OnLoad()
	{
		DivA::OnLoad();
		if(m_useAnimation)
		{
			StartTimer(m_timerID, 20);
		}
		else
		{
			StopTimer(m_timerID);
		}
	}

	void GridA::OnLostFocus()
	{
		DivA::OnLostFocus();
		m_hoveredCell = 0;
		m_hoveredRow = 0;
	}

	void GridA::OnMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		DivA::OnMouseDown(mp, button, clicks, delta);
		MouseEvent(mp, button, clicks, delta, 1);
	}

	void GridA::OnMouseLeave(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		DivA::OnMouseLeave(mp, button, clicks, delta);
		if (m_hoveredCell)
        {
            OnCellMouseLeave(m_hoveredCell, mp, button, clicks, delta);
            m_hoveredCell = 0;
        }
		m_hoveredRow = 0;
		Invalidate();
	}

	void GridA::OnMouseMove(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		DivA::OnMouseMove(mp, button, clicks, delta);
		MouseEvent(mp, button, clicks, delta, 0);
	}

	void GridA::OnMouseUp(const POINT& mp, MouseButtonsA button, int clicks, int delta)
	{
		DivA::OnMouseUp(mp, button, clicks, delta);
		MouseEvent(mp, button, clicks, delta, 2);
	}

	void GridA::OnPaintForeground(CPaint *paint, const RECT& clipRect)
	{
		ResetHeaderLayout();
		int width = GetWidth();
		int height = GetHeight();
		if (width > 0 && height > 0)
		{
			NativeBase* native = GetNative();
			RECT drawRect;
			drawRect.left = 0;
			drawRect.top = 0;
			drawRect.right = width;
			drawRect.bottom = height;
			int allVisibleColumnsWidth = GetAllVisibleColumnsWidth();
			int hHeight = 0;
			int lHeight = 0;
			if(allVisibleColumnsWidth > 0){
				if(allVisibleColumnsWidth <= width)
				{
					hHeight = allVisibleColumnsWidth;
				}
				else
				{
					hHeight = width;
				}
				lHeight = hHeight;
			}
			hHeight = m_headerVisible ? m_headerHeight : 0;
			int scrollH = 0;
			int scrollV = 0;
			HScrollBarA* hScrollBar = GetHScrollBar();
			VScrollBarA* vScrollBar = GetVScrollBar();
			if (hScrollBar && hScrollBar->IsVisible())
			{
				scrollH = -hScrollBar->GetPos();
			}
			if (vScrollBar && vScrollBar->IsVisible())
			{
				scrollV = -vScrollBar->GetPos();
			}
			OnSetEmptyClipRegion();
			POINT fPoint;
			fPoint.x = 0;
			fPoint.y = hHeight + 1 - scrollV;
			POINT ePoint;
			ePoint.x = 0;
			ePoint.y = height - 10 - scrollV;
			GridRow* fRow = GetRow(fPoint);
			GridRow* eRow = GetRow(ePoint);
			while (!eRow && ePoint.y > 0)
			{
				ePoint.y -= 10;
				eRow = GetRow(ePoint);
			}
			if (fRow && eRow)
			{
				int fIndex = fRow->GetIndex();
				int eIndex = eRow->GetIndex();
				for (int i = fIndex; i <= eIndex; i++)
				{
					GridRow* row3 = m_rows[i];
					if (row3->IsVisible())
					{
						RECT rowRect = row3->GetBounds();
						rowRect.top += scrollV;
						rowRect.bottom += scrollV;
						row3->OnPaint(paint, rowRect, (row3->GetVisibleIndex() % 2) == 1);
						RECT lpDestRect = {0};
						vector<GridCell*> cells;
						vector<GridCell*> frozenCells;
						for (int j = 0; j < 2; j++)
						{
							if (j == 0)
							{
								cells = row3->GetCells();
							}
							else
							{
								cells = frozenCells;
							}
							int right = 0;
							int count = (int)cells.size();
							for (int k = 0; k < count; k++)
							{
								GridCell* item = cells[k];
								GridColumn* column = item->GetColumn();
								if (column->IsVisible())
								{
									RECT headerRect = column->GetHeaderRect();
									if (j == 0 && column->IsFrozen())
									{
										right = headerRect.right;
										frozenCells.push_back(item);
									}
									else
									{
										if (!column->IsFrozen())
										{
											headerRect.left += scrollH;
											headerRect.right += scrollH;
										}
										int cellWidth = column->GetWidth();
										int colSpan = item->GetColSpan();
										if (colSpan > 1)
										{
											for (int m = 1; m < colSpan; m++)
											{
												GridColumn* spanColumn = GetColumn(column->GetIndex() + m);
												if (spanColumn && spanColumn->IsVisible())
												{
													cellWidth += spanColumn->GetWidth();
												}
											}
										}
										int cellHeight = row3->GetHeight();
										int rowSpan = item->GetRowSpan();
										if (rowSpan > 1)
										{
											for (int n = 1; n < rowSpan; n++)
											{
												GridRow* spanRow = GetRow(i + n);
												if (spanRow && spanRow->IsVisible())
												{
													cellHeight += spanRow->GetHeight();
												}
											}
										}
										RECT cellRect;
										cellRect.left = headerRect.left;
										cellRect.top = rowRect.top + m_verticalOffset;
										cellRect.right = headerRect.left + cellWidth;
										cellRect.bottom = rowRect.top + m_verticalOffset + cellHeight;
										if (native->GetHost()->GetIntersectRect(&lpDestRect, &cellRect, & drawRect) > 0 && item)
										{
											RECT cellClipRect = cellRect;
											if (!column->IsFrozen())
											{
												if (cellClipRect.left < right)
												{
													cellClipRect.left = right;
												}
												if (cellClipRect.right < right)
												{
													cellClipRect.right = right;
												}
											}
											item->OnPaint(paint, cellRect, cellClipRect, (row3->GetVisibleIndex() % 2) == 1);
											if (m_editingCell && m_editingCell == item && m_editTextBox)
											{
												RECT editClipRect;
												editClipRect.left = cellClipRect.left - cellRect.left;
												editClipRect.top = cellClipRect.top - cellRect.top;
												editClipRect.right = cellClipRect.right - cellRect.left;
												editClipRect.bottom = cellClipRect.bottom - cellRect.top;
												OnPaintEditTextBox(item, paint, cellRect, editClipRect);
											}
											if (m_gridLineColor != COLOR_EMPTY)
											{
												if (i == fIndex)
												{
													paint->DrawLine(m_gridLineColor, 1, 0, cellClipRect.left, cellClipRect.top, cellClipRect.right - 1, cellClipRect.top);
												}
												if (k == 0)
												{
													paint->DrawLine(m_gridLineColor, 1, 0, cellClipRect.left, cellClipRect.top, cellClipRect.left, cellClipRect.bottom - 1);
												}
												paint->DrawLine(m_gridLineColor, 1, 0, cellClipRect.left, cellClipRect.bottom - 1, cellClipRect.right - 1, cellClipRect.bottom - 1);
												paint->DrawLine(m_gridLineColor, 1, 0, cellClipRect.right - 1, cellClipRect.top, cellClipRect.right - 1, cellClipRect.bottom - 1);
											}
										}
									}
								}
							}
						}
						row3->OnPaintBorder(paint, rowRect, (row3->GetVisibleIndex() % 2) == 1);
						frozenCells.clear();
					}
				}
			}
		}
	}

	void GridA::OnPaintEditTextBox(GridCell *cell, CPaint *paint, const RECT& rect, const RECT& clipRect)
	{
		m_editTextBox->SetRegion(clipRect);
        m_editTextBox->SetBounds(rect);
        m_editTextBox->SetDisplayOffset(false);
        m_editTextBox->BringToFront();
	}

	void GridA::OnRowEditBegin(GridRow *row)
	{
		ControlA *editButton = row->GetEditButton();
        if (editButton && !ContainsControl(editButton))
        {
            POINT mp = GetMousePoint();
            if (mp.x - m_mouseDownPoint.x < -10)
            {
                m_editingRow = row;
                AddControl(editButton);
                if (m_useAnimation)
                {
					POINT location = {-10000, -10000};
					editButton->SetLocation(location);
                    m_editingRow->m_editState = 1;
                }
                else
                {
					m_editingRow->SetHorizontalOffset(-editButton->GetWidth() - ((m_vScrollBar && m_vScrollBar->IsVisible()) ? m_vScrollBar->GetWidth() : 0));
                }
            }
        }
	}

	void GridA::OnRowEditEnd()
	{
	    if (m_useAnimation)
        {
            m_editingRow->m_editState = 2;
        }
        else
        {
            m_editingRow->SetHorizontalOffset(0);
            RemoveControl(m_editingRow->GetEditButton());
            m_editingRow = 0;
        }
	}

	void GridA::OnSelectedCellsChanged()
	{
		CallEvents(EVENTID::GRIDSELECTEDCELLSCHANGED);
	}

	void GridA::OnSelectedColumnsChanged()
	{
		CallEvents(EVENTID::GRIDSELECTEDCOLUMNSSCHANGED);
	}

	void GridA::OnSelectedRowsChanged()
	{
		CallEvents(EVENTID::GRIDSELECTEDROWSCHANGED);
	}

	void GridA::OnSetEmptyClipRegion()
	{
		vector<ControlA*> controls = GetControls();
		vector<ControlA*>::iterator sIter = controls.begin();
		RECT emptyClipRect = {0};
		for(; sIter != controls.end(); ++sIter)
		{
			ControlA *control = *sIter;
			if (m_editingRow && control == m_editingRow->GetEditButton())
            {
                continue;
            }
            ScrollBarA *scrollBar = dynamic_cast<ScrollBarA*>(control);
            GridColumn *gridColumn = dynamic_cast<GridColumn*>(control);
            if (control != m_editTextBox && !scrollBar && !gridColumn)
            {
                control->SetRegion(emptyClipRect);
            }
		}
	}

	void GridA::OnTimer(int timerID)
	{
		DivA::OnTimer(timerID);
		if (m_timerID == timerID)
		{
			if(m_useAnimation)
			{
				bool paint = false;
				if (m_horizontalOffset != 0 || m_verticalOffset != 0)
				{
					if (m_horizontalOffset != 0)
					{
						m_horizontalOffset = m_horizontalOffset * 2 / 3;
						if (m_horizontalOffset >= -1 && m_horizontalOffset <= 1)
						{
							m_horizontalOffset = 0;
						}
					}
					if (m_verticalOffset != 0)
					{
						m_verticalOffset = m_verticalOffset * 2 / 3;
						if (m_verticalOffset >= -1 && m_verticalOffset <= 1)
						{
							m_verticalOffset = 0;
						}
					}
					paint = true;
				}
				int animateAddRowsSize = (int)m_animateAddRows.size();
                if (animateAddRowsSize > 0)
                {
                    int width = GetAllVisibleColumnsWidth();
                    int step = width / 10;
                    if (step < 10)
                    {
                        step = 10;
                    }
                    for (int i = 0; i < animateAddRowsSize; i++)
                    {
                        GridRow *row = m_animateAddRows[i];
                        int horizontalOffset = row->GetHorizontalOffset();
                        if (horizontalOffset > step)
                        {
                            horizontalOffset -= step;
                        }
                        else
                        {
                            horizontalOffset = 0;
                        }
                        row->SetHorizontalOffset(horizontalOffset);
                        if (horizontalOffset == 0)
                        {
                            m_animateAddRows.erase(m_animateAddRows.begin() + i);
                            animateAddRowsSize--;
                            i--;
                        }
                    }
                    paint = true;
                }
                int animateRemoveRowsSize = (int)m_animateRemoveRows.size();
                if (animateRemoveRowsSize > 0)
                {
                    int width = GetAllVisibleColumnsWidth();
                    int step = width / 10;
                    if (step < 10)
                    {
                        step = 10;
                    }
                    for (int i = 0; i < animateRemoveRowsSize; i++)
                    {
                        GridRow *row = m_animateRemoveRows[i];
                        int horizontalOffset = row->GetHorizontalOffset();
                        if (horizontalOffset <= width)
                        {
                            horizontalOffset += step;
                        }
                        row->SetHorizontalOffset(horizontalOffset);
                        if (horizontalOffset > width)
                        {
                            m_animateRemoveRows.erase(m_animateRemoveRows.begin() + i);
                            RemoveRow(row);
                            Update();
                            animateRemoveRowsSize--;
                            i--;
                        }
                    }
                    paint = true;
                }
				if (m_editingRow)
                {
                    int scrollH = 0, scrollV = 0;
                    HScrollBarA *hScrollBar = GetHScrollBar();
                    VScrollBarA *vScrollBar = GetVScrollBar();
                    int vScrollBarW = 0;
                    if (hScrollBar && hScrollBar->IsVisible())
                    {
                        scrollH = -hScrollBar->GetPos();
                    }
                    if (vScrollBar && vScrollBar->IsVisible())
                    {
                        scrollV = -vScrollBar->GetPos();
                        vScrollBarW = vScrollBar->GetWidth();
                    }
                    if (m_editingRow->m_editState == 1)
                    {
                        ControlA *editButton = m_editingRow->GetEditButton();
                        bool isOver = false;
                        int sub = editButton->GetWidth() + vScrollBarW + m_editingRow->GetHorizontalOffset();
                        if (sub < 2)
                        {
                            isOver = true;
                            m_editingRow->SetHorizontalOffset(-editButton->GetWidth() - vScrollBarW);
                        }
                        else
                        {
                            m_editingRow->SetHorizontalOffset(m_editingRow->GetHorizontalOffset() - 10);
                        }
						POINT newLocation = {GetAllVisibleColumnsWidth() + scrollH + m_editingRow->GetHorizontalOffset(),
							m_editingRow->GetBounds().top + scrollV};
                        editButton->SetLocation(newLocation);
                        if (isOver)
                        {
                            m_editingRow->m_editState = 0;
                        }
                    }
                    if (m_editingRow->m_editState == 2)
                    {
                        ControlA *editButton = m_editingRow->GetEditButton();
                        bool isOver = false;
                        if (m_editingRow->GetHorizontalOffset() < 0)
                        {
                            m_editingRow->SetHorizontalOffset(m_editingRow->GetHorizontalOffset() + 10);
                            if (m_editingRow->GetHorizontalOffset() >= 0)
                            {
                                m_editingRow->SetHorizontalOffset(0);
                                isOver = true;
                            }
                        }
						POINT newLocation = {GetAllVisibleColumnsWidth() + scrollH + m_editingRow->GetHorizontalOffset(),
                        m_editingRow->GetBounds().top + scrollV};
						editButton->SetLocation(newLocation);
                        if (isOver)
                        {
                            RemoveControl(editButton);
                            m_editingRow->m_editState = 0;
                            m_editingRow = 0;
                        }
                    }
                    paint = true;
                }
                if (paint)
                {
                    Invalidate();
                }
			}
		}
	}


	void GridA::OnVisibleChanged()
	{
		DivA::OnVisibleChanged();
		m_hoveredCell = 0;
		m_hoveredRow = 0;
	}

	void GridA::RemoveColumn(GridColumn *column)
	{
		bool selectedChanged = false;
		vector<GridColumn*>::iterator sIter = m_selectedColumns.begin();
		for(; sIter != m_selectedColumns.end(); ++sIter)
		{
			if(*sIter != column)
			{
				m_selectedColumns.erase(sIter);
				selectedChanged = true;
				break;
			}
		}
		vector<GridColumn*>::iterator sIter2 = m_columns.begin();
		for(; sIter2 != m_columns.end(); ++sIter2)
		{
			if(*sIter2 == column)
			{
				m_columns.erase(sIter2);
				int columnsSize = (int)m_columns.size();
				for (int i = 0; i < columnsSize; i++)
				{
					m_columns[i]->SetIndex(i);
				}
				RemoveControl(column);
				break;
			}
		}
		int rowSize = (int)m_rows.size();
		for (int i = 0; i < rowSize; i++)
		{
			GridRow *row = m_rows[i];
			row->RemoveCell(column->GetIndex());
		}
		if(selectedChanged)
		{
			OnSelectedColumnsChanged();
		}
	}

	void GridA::RemoveRow(GridRow *row)
	{
		if (m_editingRow)
        {
            if (ContainsControl(m_editingRow->GetEditButton()))
            {
                RemoveControl(m_editingRow->GetEditButton());
            }
            m_editingRow->m_editState = 0;
            m_editingRow = 0;
        }
		int animateAddRowsSize = (int)m_animateAddRows.size();
		for(int i = 0; i < animateAddRowsSize; i++)
		{
			if(m_animateAddRows[i] ==  row)
			{
				m_animateAddRows.erase(m_animateAddRows.begin() + i);
				break;
			}
		}
		bool selectedChanged = false;
        bool selected = false;
        int selectedRowsSize = (int)m_selectedRows.size();
        for (int i = 0; i < selectedRowsSize; i++)
        {
            GridRow *selectedRow = m_selectedRows[i];
            if (selectedRow == row)
            {
                selected = true;
                break;
            }
        }
        if (selected)
        {
            GridRow *otherRow = SelectFrontRow();
            if (otherRow)
            {
                selectedChanged = true;
            }
            else
            {
                otherRow = SelectNextRow();
				if(otherRow)
				{
					selectedChanged = true;
				}
            }
        }
        if (m_hoveredRow == row)
        {
			m_hoveredCell = 0;
            m_hoveredRow = 0;
        }
		vector<GridRow*>::iterator sIter = m_rows.begin();
		for(; sIter != m_rows.end(); ++sIter)
		{
			if(*sIter == row)
			{
				row->OnRemove();
				m_rows.erase(sIter);
				break;
			}
		}
		int rowSize = (int)m_rows.size();
		if(rowSize == 0)
		{
			m_selectedCells.clear();
			m_selectedRows.clear();
		}
		int visibleIndex = 0;
		for (int i = 0; i < rowSize; i++)
		{
			GridRow *gridRow = m_rows[i];
			gridRow->SetIndex(i);
			if(gridRow->IsVisible())
			{
				gridRow->SetVisibleIndex(visibleIndex);
				visibleIndex++;
			}
		}
		if(selected)
		{
			if(selectedChanged)
			{
				OnSelectedRowsChanged();
			}
			else
			{
				m_selectedCells.clear();
				m_selectedRows.clear();
			}
		}
	}

	void GridA::ResetHeaderLayout()
	{
		if (!m_lockUpdate)
		{
			int left = 0, top =0;
			int scrollH = 0, scrollV = 0;
            HScrollBarA *hScrollBar = GetHScrollBar();
            VScrollBarA *vScrollBar = GetVScrollBar();
            int vScrollBarW = 0;
            if (hScrollBar && hScrollBar->IsVisible())
            {
                scrollH = -hScrollBar->GetPos();
            }
            if (vScrollBar && vScrollBar->IsVisible())
            {
                scrollV = -vScrollBar->GetPos();
                vScrollBarW = vScrollBar->GetWidth();
            }
			int headerHeight = m_headerVisible ? m_headerHeight : 0;
			GridColumn *draggingColumn = 0;
			int colSize = (int)m_columns.size();
			for (int i = 0; i < colSize; i++)
			{
				GridColumn *column = m_columns[i];
				if (column->IsVisible())
				{
					RECT cellRect = {left + m_horizontalOffset, top + m_verticalOffset,
						left + m_horizontalOffset + column->GetWidth(), top + headerHeight + m_verticalOffset};
					column->SetHeaderRect(cellRect);
					if (column->IsDragging())
					{
						draggingColumn = column;
						RECT newRect = {column->GetLeft(), cellRect.top, column->GetRight(), cellRect.bottom};
						column->SetBounds(newRect);
					}
					else
					{
						if (!column->IsFrozen())
						{
							cellRect.left += scrollH;
							cellRect.right += scrollH;
						}
						column->SetBounds(cellRect);
					}
					left += column->GetWidth();
				}
			}
			for (int i = colSize - 1; i >= 0; i--)
			{
				m_columns[i]->BringToFront();
			}
			if(draggingColumn)
			{
				draggingColumn->BringToFront();
			}
		    if (m_editingRow && m_editingRow->m_editState == 0 && m_editingRow->GetEditButton())
            {
                ControlA *editButton = m_editingRow->GetEditButton();
				POINT newLocation = {GetAllVisibleColumnsWidth() - editButton->GetWidth() + scrollH - vScrollBarW, m_editingRow->GetBounds().top + scrollV};
                editButton->SetLocation(newLocation);
            }
		}
	}

	GridRow* GridA::SelectFrontRow()
	{
		int rowsSize = (int)m_rows.size();
	    if (rowsSize == 0)
        {
			m_selectedCells.clear();
            m_selectedRows.clear();
            return 0;
        }
		GridRow *frontRow = 0;
		vector<GridRow*> selectedRows = GetSelectedRows();
		if ((int)selectedRows.size() == 1)
		{
            GridRow *selectedRow = selectedRows[0];
            int selectedIndex = selectedRow->GetIndex();
            for (int i = selectedIndex - 1; i >= 0; --i)
            {
                if (i < rowsSize && m_rows[i]->IsVisible())
                {
                    frontRow = m_rows[i];
                    break;
                }
            }
			if(m_selectionMode == GridSelectionMode_SelectFullRow)
			{
				if (frontRow)
                {
                    m_selectedRows.clear();
					m_selectedRows.push_back(frontRow);
                }
                else
                {
                    m_selectedRows.clear();
                    m_selectedRows.push_back(m_rows[(int)m_rows.size() - 1]);
                    VScrollBarA *vScrollBar = GetVScrollBar();
                    if (vScrollBar && vScrollBar->IsVisible())
                    {
                        vScrollBar->ScrollToEnd();
					}
                }
			}
		}
		return frontRow;
	}

	GridRow* GridA::SelectNextRow()
	{
		int rowsSize = (int)m_rows.size();
		if (rowsSize == 0)
        {
			m_selectedCells.clear();
            m_selectedRows.clear();
            return 0;
        }
		GridRow *nextRow = 0;
		vector<GridRow*> selectedRows = GetSelectedRows();
		if ((int)selectedRows.size() == 1)
		{
			GridRow *selectedRow = selectedRows[0];
            int selectedIndex = selectedRow->GetIndex();
            for (int i = selectedIndex + 1; i < rowsSize; ++i)
            {
                if (i >= 0 && m_rows[i]->IsVisible())
                {
                    nextRow = m_rows[i];
                    break;
                }
            }
			if(m_selectionMode == GridSelectionMode_SelectFullRow)
			{
				if (nextRow)
                {
                    m_selectedRows.clear();
                    m_selectedRows.push_back(nextRow);
                }
                else
                {
                    m_selectedRows.clear();
                    m_selectedRows.push_back(m_rows[0]);
					VScrollBarA *vScrollBar = GetVScrollBar();
					if (vScrollBar && vScrollBar->IsVisible())
					{
						vScrollBar->ScrollToBegin();
					}
                }
			}
		}
		return nextRow;
	}

	void GridA::SetProperty(const String& name, const String& value)
	{
		if(name == L"allowdragrow")
		{
			SetAllowDragRow(CStr::ConvertStrToBool(value));
		}
		else if (name == L"allowhoveredrow")
        {
			SetAllowHoveredRow(CStr::ConvertStrToBool(value));
        }
	    else if (name == L"celleditmode")
        {
			String lowerStr = CStr::ToLower(value);
            if (lowerStr == L"doubleclick")
            {
                SetCellEditMode(GridCellEditMode_DoubleClick);
            }
            else if (lowerStr == L"none")
            {
                SetCellEditMode(GridCellEditMode_None);
            }
            else if (lowerStr == L"singleclick")
            {
                SetCellEditMode(GridCellEditMode_SingleClick);
            }
        }
		else if(name == L"gridlinecolor")
		{
			SetGridLineColor(CStr::ConvertStrToColor(value));
		}
		else if(name == L"headerheight")
		{
			SetHeaderHeight(CStr::ConvertStrToInt(value));
		}
		else if(name == L"headervisible")
		{
			SetHeaderVisible(CStr::ConvertStrToBool(value));
		}
		else if(name == L"horizontaloffset")
		{
			SetHorizontalOffset(CStr::ConvertStrToInt(value));
		}
		else if(name == L"multiselect")
		{
			SetMultiSelect(CStr::ConvertStrToBool(value));
		}
	    else if (name == L"selectionmode")
        {
			String lowerStr = CStr::ToLower(value);
            if (lowerStr == L"selectcell")
            {
                SetSelectionMode(GridSelectionMode_SelectCell);
            }
            else if (lowerStr == L"selectfullcolumn")
            {
                SetSelectionMode(GridSelectionMode_SelectFullColumn);
            }
            else if (lowerStr == L"selectfullrow")
            {
                SetSelectionMode(GridSelectionMode_SelectFullRow);
            }
            else
            {
                SetSelectionMode(GridSelectionMode_SelectNone);
            }
        }
		else if(name == L"useanimation")
		{
			SetUseAnimation(CStr::ConvertStrToBool(value));
		}
		else if(name == L"verticaloffset")
		{
			SetVerticalOffset(CStr::ConvertStrToInt(value));
		}
		else
		{
			DivA::SetProperty(name, value);
		}
	}
	
	void GridA::SortColumn(GridA *grid, GridColumn *column, GridColumnSortMode sortMode)
	{
		if(column && column->AllowSort()){

			int columnIndex = -1;
			int colSize = (int)grid->m_columns.size();
			for (int i = 0; i < colSize; ++i)
			{
				if (grid->m_columns[i] != column)
				{
					grid->m_columns[i]->SetSortMode(GridColumnSortMode_None);
				}
				else
				{
					grid->m_columns[i]->SetSortMode(sortMode);
					columnIndex = i;
				}
			}
			if (columnIndex != -1)
			{
				GridRowCompare compare;
				compare.m_columnIndex = columnIndex;
				if (sortMode == GridColumnSortMode_Desc)
				{
					compare.m_type = 1;
				}
				sort(grid->m_rows.begin(), grid->m_rows.end(), compare);
			}
			grid->Update();
			grid->Invalidate();
		}
	}

	void GridA::Update()
	{
		if(GetNative())
		{
			if (!m_lockUpdate)
			{
				DivA::Update();
				if(IsVisible())
				{
					int colSize = (int)m_columns.size();
					for (int i = 0; i < colSize; i++)
					{
						m_columns[i]->SetIndex(i);
					}
					int rowSize = (int)m_rows.size();
					int visibleIndex = 0;
					int rowTop = m_headerVisible ? m_headerHeight : 0;
					int allVisibleColumnsWidth = GetAllVisibleColumnsWidth();
					m_hasUnVisibleRow = false;
					for (int i = 0; i < rowSize; ++i)
					{
						GridRow *gridRow = m_rows[i];
						gridRow->SetIndex(i);
                        if (gridRow->IsVisible())
                        {
                            gridRow->SetVisibleIndex(i);
							int rowHeight = gridRow->GetHeight();
							RECT rowRect = {0, rowTop, allVisibleColumnsWidth, rowTop + rowHeight};
                            gridRow->SetBounds(rowRect);
                            rowTop += rowHeight;
                            visibleIndex++;
                        }
					    else
                        {
                            m_hasUnVisibleRow = true;
                            gridRow->SetVisibleIndex(-1);
							RECT rowRect = {0, rowTop, allVisibleColumnsWidth, rowTop};
                            gridRow->SetBounds(rowRect);
                        }
					}
					HScrollBarA *hScrollBar = GetHScrollBar();
					VScrollBarA *vScrollBar = GetVScrollBar();
					if (vScrollBar && vScrollBar->IsVisible())
                    {
                        int top = m_headerVisible ? m_headerHeight : 0;
                        vScrollBar->SetTop(top);
                        int height = GetHeight() - top - ((hScrollBar && hScrollBar->IsVisible()) ? hScrollBar->GetHeight() : 0);
                        vScrollBar->SetHeight(height);
						vScrollBar->SetPageSize(height);
						if (rowSize > 0)
                        {
                            vScrollBar->SetLineSize(GetAllVisibleRowsHeight() / rowSize);
                        }
                    }
				}
			}
		}
	}

	void GridA::UpdateSortColumn()
	{
		int colSize = (int)m_columns.size();
		for (int i = 0; i < colSize; ++i)
		{
			if (m_columns[i]->GetSortMode() != GridColumnSortMode_None)
			{
				m_sort->SortColumn(this, m_columns[i], m_columns[i]->GetSortMode());
				break;
			}
		}
	}
}