#include "..\\stdafx.h"
#include "..\\include\\Tree\\Tree.h"
using namespace OwLib;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TreeA::TreeA()
{
	m_checkBoxes = false;
	m_checkBoxSize.cx = 14;
	m_checkBoxSize.cy = 14;
	GridA::SetGridLineColor(COLOR_EMPTY);
	m_movingNode = 0;
	m_nodeSize.cx = 14;
	m_nodeSize.cy = 14;
}

TreeA::~TreeA()
{
	m_movingNode = 0;
}

bool TreeA::HasCheckBoxes()
{
	return m_checkBoxes;
}

void TreeA::SetCheckBoxes( bool checkBoxes )
{
	m_checkBoxes = checkBoxes;
}

SIZE TreeA::GetCheckBoxSize()
{
	return m_checkBoxSize;
}

void TreeA::SetCheckBoxSize( SIZE checkBoxSize )
{
	m_checkBoxSize = checkBoxSize;
}

String TreeA::GetCheckedImage()
{
	return m_checkedImage;
}

void TreeA::SetCheckedImage( const String& checkedImage )
{
	m_checkedImage = checkedImage;
}

String TreeA::GetCollapsedNodeImage()
{
	return m_collapsedNodeImage;
}

void TreeA::SetCollapsedNodeImage( const String& collapsedNodeImage )
{
	m_collapsedNodeImage = collapsedNodeImage;
}

String TreeA::GetExpendedNodeImage()
{
	return m_expendedNodeImage;
}

void TreeA::SetExpendedNodeImage( const String& expendedNodeImage )
{
	m_expendedNodeImage = expendedNodeImage;
}

SIZE TreeA::GetNodeSize()
{
	return m_nodeSize;
}

void TreeA::SetNodeSize( SIZE nodeSize )
{
	m_nodeSize = nodeSize;
}

vector<TreeNodeA*> TreeA::GetSelectedNodes()
{
	vector<TreeNodeA*> list;
	vector<GridRow*> selectedRows = GetSelectedRows();
	int count = (int)selectedRows.size();
	for (int i = 0; i < count; i++)
	{
		vector<GridCell*> cells = selectedRows[i]->m_cells;
		int num3 = (int)cells.size();
		for (int j = 0; j < num3; j++)
		{
			TreeNodeA *item = (TreeNodeA*)cells[j];
			if (item)
			{
				list.push_back(item);
				break;
			}
		}
	}
	return list;
}

void TreeA::SetSelectedNodes( vector<TreeNodeA*> selectedNodes )
{
	int count = (int)selectedNodes.size();
	vector<GridRow*> list;
	for (int i = 0; i < count; i++)
	{
		list.push_back(selectedNodes[i]->GetRow());
	}
	SetSelectedRows(list);
}

String TreeA::GetUnCheckedImage()
{
	return m_unCheckedImage;
}

void TreeA::SetUnCheckedImage( const String& unCheckedImage )
{
	m_unCheckedImage = unCheckedImage;
}

void TreeA::AppendNode( TreeNodeA *node )
{
	node->SetTree(this);
	node->OnAddingNode(-1);
	m_nodes.push_back(node);
}

void TreeA::ClearNodes()
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		RemoveNode(m_nodes[i]);
	}
	m_nodes.clear();
}

void TreeA::Collapse()
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		m_nodes[i]->Collapse();
	}
}

void TreeA::CollapseAll()
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		m_nodes[i]->CollapseAll();
	}
}

void TreeA::Expend()
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		m_nodes[i]->Expend();
	}
}

void TreeA::ExpendAll()
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		m_nodes[i]->ExpendAll();
	}
}

vector<TreeNodeA*> TreeA::GetChildNodes()
{
	return m_nodes;
}

String TreeA::GetControlType()
{
	return L"Tree";
}

int TreeA::GetNodeIndex( TreeNodeA *node )
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		if (m_nodes[i] == node)
		{
			return i;
		}
	}
	return -1;
}

void TreeA::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"checkboxes")
	{
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(HasCheckBoxes());
	}
	else if (name == L"checkboxsize")
	{
		*type = L"size";
		*value = CStr::ConvertSizeToStr(GetCheckBoxSize());
	}
	else if (name == L"checkedimage")
	{
		*type = L"String";
		*value = GetCheckedImage();
	}
	else if (name == L"collapsednodeimage")
	{
		*type = L"String";
		*value = GetCollapsedNodeImage();
	}
	else if (name == L"expendednodeimage")
	{
		*type = L"String";
		*value = GetExpendedNodeImage();
	}
	else if (name == L"uncheckedimage")
	{
		*type = L"String";
		*value = GetUnCheckedImage();
	}
	else if (name == L"nodesize")
	{
		*type = L"size";
		*value = CStr::ConvertSizeToStr(GetNodeSize());
	}
	else
	{
		GridA::GetProperty(name, value, type);
	}
}

vector<String> TreeA::GetPropertyNames()
{
	vector<String> propertyNames = GridA::GetPropertyNames();
	propertyNames.push_back(L"CheckBoxes");
	propertyNames.push_back(L"CheckBoxSize");
	propertyNames.push_back(L"CheckedImage");
	propertyNames.push_back(L"CollapsedNodeImage");
	propertyNames.push_back(L"ExpendedNodeImage");
	propertyNames.push_back(L"UnCheckedImage");
	propertyNames.push_back(L"NodeSize");
	return propertyNames;
}

void TreeA::InsertNode( int index, TreeNodeA *node )
{
	int num = -1;
	if (index == 0)
	{
		if (node->GetParent())
		{
			num = node->GetParent()->GetRow()->GetIndex() + 1;
		}
		else
		{
			num = 0;
		}
	}
	else if (!m_nodes.empty())
	{
		num = m_nodes[index]->GetRow()->GetIndex();
	}
	node->SetTree(this);
	node->OnAddingNode(num);
	m_nodes.insert(m_nodes.begin() + index, node);
}

void TreeA::OnCellMouseDown( GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	GridA::OnCellMouseDown(cell, mp, button, clicks, delta);
	TreeNodeA *ea = (TreeNodeA*)cell;
	if (ea)
	{
		int pos = 0;
		HScrollBarA *hScrollBar = GetHScrollBar();
		if (hScrollBar && hScrollBar->IsVisible())
		{
			pos = hScrollBar->GetPos();
		}
		RECT bounds = ea->GetTargetColumn()->GetBounds();
		bounds.left += GetHorizontalOffset() - pos;
		bounds.top += GetVerticalOffset() - pos;
		int left = bounds.left;
		if (m_checkBoxes)
		{
			int cx = m_checkBoxSize.cx;
			if ((mp.x >= left) && (mp.x <= (left + cx)))
			{
				ea->SetChecked(!ea->IsChecked());
				return;
			}
			left += cx + 10;
		}
		vector<TreeNodeA*> childNodes = ea->GetChildNodes();
		if (!childNodes.empty())
		{
			int num4 = m_nodeSize.cx;
			if ((mp.x >= left) && (mp.x <= (left + num4)))
			{
				if (ea->IsExpended())
				{
					ea->Collapse();
				}
				else
				{
					ea->Expend();
				}
				Update();
				return;
			}
		}
		if (ea->AllowDragOut())
		{
			m_movingNode = ea;
		}
	}
}

void TreeA::OnCellMouseMove( GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	GridA::OnCellMouseMove(cell, mp, button, clicks, delta);
	if (m_movingNode)
	{
		Invalidate();
	}
}

void TreeA::OnCellMouseUp( GridCell *cell, const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	GridA::OnCellMouseUp(cell, mp, button, clicks, delta);
	if (m_movingNode)
	{
		GridRow *row = GetRow(mp);
		if (row)
		{
			TreeNodeA *node = (TreeNodeA*)(row->GetCell(0));
			if (node->AllowDragIn() && (m_movingNode != node))
			{
				TreeNodeA *parent = node->GetParent();
				TreeNodeA *ea3 = m_movingNode->GetParent();
				if (ea3)
				{
					ea3->RemoveNode(m_movingNode);
				}
				else
				{
					RemoveNode(m_movingNode);
				}
				if (parent)
				{
					if (ea3 == parent)
					{
						parent->InsertNode(parent->GetNodeIndex(node), m_movingNode);
					}
					else
					{
						node->AppendNode(m_movingNode);
					}
				}
				else if (ea3 == parent)
				{
					InsertNode(GetNodeIndex(node), m_movingNode);
				}
				else
				{
					node->AppendNode(m_movingNode);
				}
				node->Expend();
			}
		}
		m_movingNode = 0;
		Update();
	}
}

void TreeA::OnPaintForeground( CPaint *paint, const RECT& clipRect )
{
	GridA::OnPaintForeground(paint, clipRect);
	if (m_movingNode)
	{
		FONT *font = GetFont();
		POINT mousePoint = GetMousePoint();
		SIZE size = paint->TextSize(m_movingNode->GetText().c_str(), font);
		RECT rect = {mousePoint.x, mousePoint.y, mousePoint.x + size.cx, mousePoint.y + size.cy};
		paint->DrawText(m_movingNode->GetText().c_str(), GetForeColor(), font, rect);
	}
}

void TreeA::OnPaintEditTextBox( GridCell *cell, CPaint *paint, const RECT& rc, const RECT& clipRect )
{
	RECT rect = rc;
	TextBoxA *editTextBox = GetEditTextBox();
	if (editTextBox)
	{
		TreeNodeA *ea = (TreeNodeA*)cell;
		if (ea)
		{
			int indent = ea->GetIndent();
			rect.left += indent;
			if (rect.right < rect.left)
			{
				rect.right = rect.left;
			}
			editTextBox->SetBounds(rect);
			editTextBox->SetDisplayOffset(false);
			editTextBox->BringToFront();
		}
		else
		{
			GridA::OnPaintEditTextBox(cell, paint, rect, clipRect);
		}
	}
}

void TreeA::RemoveNode( TreeNodeA *node )
{
	node->OnRemovingNode();
	for (vector<TreeNodeA*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		if (*it == node)
		{
			m_nodes.erase(it);
			break;
		}
	}
}

void TreeA::SetProperty( const String& name, const String& value )
{
	if (name == L"checkboxes")
	{
		SetCheckBoxes(CStr::ConvertStrToBool(value));
	}
	else if (name == L"checkboxsize")
	{
		SetCheckBoxSize(CStr::ConvertStrToSize(value));
	}
	else if (name == L"checkedimage")
	{
		SetCheckedImage(value);
	}
	else if (name == L"collapsednodeimage")
	{
		SetCollapsedNodeImage(value);
	}
	else if (name == L"expendednodeimage")
	{
		SetExpendedNodeImage(value);
	}
	else if (name == L"uncheckedimage")
	{
		SetUnCheckedImage(value);
	}
	else if (name == L"nodesize")
	{
		SetNodeSize(CStr::ConvertStrToSize(value));
	}
	else
	{
		GridA::SetProperty(name, value);
	}
}
