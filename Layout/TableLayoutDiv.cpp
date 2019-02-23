#include "..\\stdafx.h"
#include "..\\include\\Layout\\TableLayoutDiv.h"
using namespace OwLib;

ColumnStyleA::ColumnStyleA( SizeTypeA sizeType, float width )
{
	m_sizeType = sizeType;
	m_width = width;
}

ColumnStyleA::~ColumnStyleA()
{

}

SizeTypeA ColumnStyleA::GetSizeType()
{
	return m_sizeType;
}

void ColumnStyleA::SetSizeTypeA( SizeTypeA sizeType )
{
	m_sizeType = sizeType;
}

float ColumnStyleA::GetWidth()
{
	return m_width;
}

void ColumnStyleA::SetWidth( float width )
{
	m_width = width;
}

void ColumnStyleA::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"sizetype")
	{
		*type = L"enum:SizeType";
		if (m_sizeType == SizeTypeA_AbsoluteSize)
		{
			*value = L"absolutesize";
		}
		else if (m_sizeType == SizeTypeA_AutoFill)
		{
			*value = L"autofill";
		}
		else if (m_sizeType == SizeTypeA_PercentSize)
		{
			*value = L"percentsize";
		}
	}
	else if (name == L"width")
	{
		*type = L"float";
		*value = CStr::ConvertFloatToStr(GetWidth());
	}
}

vector<String> ColumnStyleA::GetPropertyNames()
{
	vector<String> propertyNames;
	propertyNames.push_back(L"SizeType");
	propertyNames.push_back(L"Width");
	return propertyNames;
}

void ColumnStyleA::SetProperty( const String& name, const String& value )
{
	if (name == L"sizetype")
	{
		String temp = CStr::ToLower(value);
		if (temp == L"absolutesize")
		{
			m_sizeType = SizeTypeA_AbsoluteSize;
		}
		else if (temp == L"autofill")
		{
			m_sizeType = SizeTypeA_AutoFill;
		}
		else if (temp == L"percentsize")
		{
			m_sizeType = SizeTypeA_PercentSize;
		}
	}
	else if (name == L"width")
	{
		SetWidth(CStr::ConvertStrToFloat(value));
	}
}

RowStyleA::RowStyleA( SizeTypeA sizeType, float height )
{
	m_sizeType = sizeType;
	m_height = height;
}

RowStyleA::~RowStyleA()
{

}

float RowStyleA::GetHeight()
{
	return m_height;
}

void RowStyleA::SetHeight( float height )
{
	m_height = height;
}

SizeTypeA RowStyleA::GetSizeType()
{
	return m_sizeType;
}

void RowStyleA::SetSizeTypeA( SizeTypeA sizeType )
{
	m_sizeType = sizeType;
}

void RowStyleA::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"sizetype")
	{
		*type = L"enum:SizeType";
		if (m_sizeType == SizeTypeA_AbsoluteSize)
		{
			*value = L"absolutesize";
		}
		else if (m_sizeType == SizeTypeA_AutoFill)
		{
			*value = L"autofill";
		}
		else if (m_sizeType == SizeTypeA_PercentSize)
		{
			*value = L"percentsize";
		}
	}
	else if (name == L"height")
	{
		*type = L"float";
		*value = CStr::ConvertFloatToStr(GetHeight());
	}
}

vector<String> RowStyleA::GetPropertyNames()
{
	vector<String> propertyNames;
	propertyNames.push_back(L"SizeType");
	propertyNames.push_back(L"Height");
	return propertyNames;
}

void RowStyleA::SetProperty( const String& name, const String& value )
{
	if (name == L"sizetype")
	{
		String temp = CStr::ToLower(value);
		if (value == L"absolutesize")
		{
			m_sizeType = SizeTypeA_AbsoluteSize;
		}
		else if (value == L"autofill")
		{
			m_sizeType = SizeTypeA_AutoFill;
		}
		else if (value == L"percentsize")
		{
			m_sizeType = SizeTypeA_PercentSize;
		}
	}
	else if (name == L"height")
	{
		SetHeight(CStr::ConvertStrToFloat(value));
	}
}

TableLayoutDivA::TableLayoutDivA()
{
	m_columnsCount = 0;
	m_rowsCount = 0;
}

TableLayoutDivA::~TableLayoutDivA()
{
	m_columns.clear();
	m_columnsCount = 0;
	m_rows.clear();
	m_rowsCount = 0;
	m_tableControls.clear();
	m_columnStyles.clear();
	m_rowStyles.clear();
}

int TableLayoutDivA::GetColumnsCount()
{
	return m_columnsCount;
}

void TableLayoutDivA::SetColumnsCount( int columnsCount )
{
	m_columnsCount = columnsCount;
}

int TableLayoutDivA::GetRowsCount()
{
	return m_rowsCount;
}

void TableLayoutDivA::SetRowsCount( int rowsCount )
{
	m_rowsCount = rowsCount;
}

void TableLayoutDivA::AddControl( ControlA *control )
{
	int count = (int)GetControls().size();
	ControlA::AddControl(control);
	int column = count % m_columnsCount;
	int row = count / m_columnsCount;
	m_columns.push_back(column);
	m_rows.push_back(row);
	m_tableControls.push_back(control);
}

void TableLayoutDivA::AddControl( ControlA *control, int column, int row )
{
	ControlA::AddControl(control);
	m_columns.push_back(column);
	m_rows.push_back(row);
	m_tableControls.push_back(control);
}

String TableLayoutDivA::GetControlType()
{
	return L"TableLayoutDiv";
}

void TableLayoutDivA::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"columnscount")
	{
		*type = L"int";
		*value = CStr::ConvertIntToStr(GetColumnsCount());
	}
	else if (name == L"rowscount")
	{
		*type = L"int";
		*value = CStr::ConvertIntToStr(GetRowsCount());
	}
	else
	{
		ControlA::GetProperty(name, value, type);
	}
}

vector<String> TableLayoutDivA::GetPropertyNames()
{
	vector<String> propertyNames;
	propertyNames.push_back(L"ColumnsCount");
	propertyNames.push_back(L"RowsCount");
	return propertyNames;
}

bool TableLayoutDivA::OnResetLayout()
{
	if (GetNative() && m_columnsCount > 0 && m_rowsCount > 0 && !m_columnStyles.empty() && !m_rowStyles.empty())
	{
		int width = GetWidth();
		int height = GetHeight();
		int count = (int)m_tableControls.size();
		int *columnWidths = new int[m_columnsCount];
		int *rowHeights = new int[m_rowsCount];
		int allWidth = 0;
		int allHeight = 0;
		for (int i = 0; i < m_columnsCount; i++)
		{
			ColumnStyleA columnStyleA = m_columnStyles[i];
			int cWidth = 0;
			SizeTypeA sizeType = columnStyleA.GetSizeType();
			float sWidth = columnStyleA.GetWidth();
			switch (sizeType)
			{
			case SizeTypeA_AbsoluteSize:
				cWidth = (int) sWidth;
				break;

			case SizeTypeA_AutoFill:
				cWidth = width - allWidth;
				break;

			case SizeTypeA_PercentSize:
				cWidth = (int) (width * sWidth);
				break;
			}
			columnWidths[i] = cWidth;
			allWidth += cWidth;
		}
		for (int j = 0; j < m_rowsCount; j++)
		{
			RowStyleA rowStyle = m_rowStyles[j];
			int rHeight = 0;
			SizeTypeA sizeType = rowStyle.GetSizeType();
			float sHeight = rowStyle.GetHeight();
			switch (sizeType)
			{
			case SizeTypeA_AbsoluteSize:
				rHeight = (int) sHeight;
				break;

			case SizeTypeA_AutoFill:
				rHeight = height - allHeight;
				break;

			case SizeTypeA_PercentSize:
				rHeight = (int) (height * sHeight);
				break;
			}
			rowHeights[j] = rHeight;
			allHeight += rHeight;
		}
		for (int k = 0; k < count; k++)
		{
			ControlA *control = m_tableControls[k];
			int column = m_columns[k];
			int row = m_rows[k];
			PADDING margin = control->GetMargin();
			int cLeft = 0;
			int cTop = 0;
			for (int m = 0; m < column; m++)
			{
				cLeft += columnWidths[m];
			}
			for (int n = 0; n < row; n++)
			{
				cTop += rowHeights[n];
			}
			int cRight = cLeft + columnWidths[column] - margin.right;
			int cBottom = cTop + rowHeights[row] - margin.bottom;
			cLeft += margin.left;
			cTop += margin.top;
			if (cRight < cLeft)
			{
				cRight = cLeft;
			}
			if (cBottom < cTop)
			{
				cBottom = cTop;
			}
			RECT rc = {cLeft, cTop, cRight, cBottom};
			control->SetBounds(rc);
		}

		delete []columnWidths;
		columnWidths = 0;
		delete []rowHeights;
		rowHeights = 0;
	}
	return true;
}

void TableLayoutDivA::RemoveControl( ControlA *control )
{
	int count = (int)m_tableControls.size();
	int index = -1;
	for (int i = 0; i < count; i++)
	{
		if (control == m_tableControls[i])
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		m_columns.erase(m_columns.begin() + index);
		m_rows.erase(m_rows.begin() + index);
		m_tableControls.erase(m_tableControls.begin() + index);
	}
	ControlA::RemoveControl(control);
}

void TableLayoutDivA::SetProperty( const String& name, const String& value )
{
	if (name == L"columnscount")
	{
		SetColumnsCount(CStr::ConvertStrToInt(value));
	}
	else if (name == L"rowscount")
	{
		SetRowsCount(CStr::ConvertStrToInt(value));
	}
	else
	{
		ControlA::SetProperty(name, value);
	}
}

void TableLayoutDivA::Update()
{
	OnResetLayout();
	int count = (int)m_controls.size();
	for (int i = 0; i < count; i++)
	{
		m_controls[i]->Update();
	}
	UpdateScrollBar();
}