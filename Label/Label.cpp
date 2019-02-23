#include "..\\stdafx.h"
#include "..\\include\\Label\\Label.h"
using namespace OwLib;

LabelA::LabelA()
{
	SetAutoSize(true);
	SetBackColor(COLOR_EMPTY);
	SetBorderColor(COLOR_EMPTY);
	SetCanFocus(false);
	SIZE sz = {100, 20};
	SetSize(sz);
}

LabelA::~LabelA()
{

}

ContentAlignmentA LabelA::GetTextAlign()
{
	return m_textAlign;
}

void LabelA::SetTextAlign( ContentAlignmentA textAlign )
{
	m_textAlign = textAlign;
}

String LabelA::GetControlType()
{
	return L"Label";
}

void LabelA::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"textalign")
	{
		*type = L"enum:ContentAlignmentA";
		*value = CStr::ConvertContentAlignmentToStr(m_textAlign);
	}
	else
	{
		ControlA::GetProperty(name, value, type);
	}
}

vector<String> LabelA::GetPropertyNames()
{
	vector<String> names = ControlA::GetPropertyNames();
	names.push_back(L"TextAlign");
	return names;
}

void LabelA::OnPaintForeground( CPaint *paint, const RECT& clipRect )
{
	String text = GetText();
	if ((int)text.length() > 0)
	{
		int width = GetWidth();
		int height = GetHeight();
		if (width > 0 && height > 0)
		{
			FONT *font = GetFont();
			SIZE size = paint->TextSize(text.c_str(), font);
			POINT point = {(width - size.cx) / 2, (height - size.cy) / 2};
			PADDING padding = GetPadding();
			switch (m_textAlign)
			{
			case ContentAlignmentA_BottomCenter:
				point.y = height - size.cy;
				break;

			case ContentAlignmentA_BottomLeft:
				point.x = padding.left;
				point.y = height - size.cy - padding.bottom;
				break;

			case ContentAlignmentA_BottomRight:
				point.x = width - size.cx - padding.right;
				point.y = height - size.cy - padding.bottom;
				break;

			case ContentAlignmentA_MiddleLeft:
				point.x = padding.left;
				break;

			case ContentAlignmentA_MiddleRight:
				point.x = width - size.cx - padding.right;
				break;

			case ContentAlignmentA_TopCenter:
				point.y = padding.top;
				break;

			case ContentAlignmentA_TopLeft:
				point.x = padding.left;
				point.y = padding.top;
				break;

			case ContentAlignmentA_TopRight:
				point.x = width - size.cx - padding.right;
				point.y = padding.top;
				break;
			}
			RECT rect = {point.x, point.y, point.x + size.cx, point.y + size.cy};
			_int64 paintingForeColor = GetPaintingForeColor();
			if (AutoEllipsis() && (rect.right < clipRect.right || rect.bottom < clipRect.bottom))
			{
				if (rect.right < clipRect.right)
				{
					rect.right = clipRect.right;
				}
				if (rect.bottom < clipRect.bottom)
				{
					rect.bottom = clipRect.bottom;
				}
				paint->DrawTextAutoEllipsis(text.c_str(), paintingForeColor, font, rect);
			}
			else
			{
				paint->DrawText(text.c_str(), paintingForeColor, font, rect);
			}
		}
	}
}

void LabelA::OnPrePaint( CPaint *paint, const RECT& clipRect )
{
	ControlA::OnPrePaint(paint, clipRect);
	if (AutoSize())
	{
		int width = GetWidth();
		int height = GetHeight();
		if (width > 0 && height > 0)
		{
			String text = GetText();
			FONT *font = GetFont();
			SIZE size = paint->TextSize(text.c_str(), font);
			if (AutoSize())
			{
				int cx = size.cx + 4;
				int cy = size.cy + 4;
				if (cx != width || cy != height)
				{
					SIZE sz = {cx, cy};
					SetSize(sz);
				}
			}
		}
	}
}

void LabelA::SetProperty( const String& name, const String& value )
{
	if (name == L"textalign")
	{
		SetTextAlign(CStr::ConvertStrToContentAlignment(value));
	}
	else
	{
		ControlA::SetProperty(name, value);
	}
}
