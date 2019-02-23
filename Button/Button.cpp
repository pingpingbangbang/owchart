#include "..\\stdafx.h"
#include "..\\include\\Button\\Button.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_int64 ButtonA::GetPaintingBackColor()
{
	_int64 paintingBackColor = ControlA::GetPaintingBackColor();
	if (paintingBackColor != COLOR_EMPTY && ControlA::IsPaintEnabled(this))
    {
		NativeBase* native = ControlA::GetNative();
        if (this == native->GetPushedControl())
        {
            return COLOR_PUSHEDCONTROL;
        }
        if (this == native->GetHoveredControl())
        {
            paintingBackColor = COLOR_HOVEREDCONTROL;
        }
    }
    return paintingBackColor;
}

String ButtonA::GetPaintingBackImage()
{           
	String pushedBackImage = L"";
	if (ControlA::IsPaintEnabled(this))
    {
		NativeBase* native = ControlA::GetNative();
        if (this == native->GetPushedControl())
        {
            pushedBackImage = m_pushedBackImage;
        }
        else if (this == native->GetHoveredControl())
        {
            pushedBackImage = m_hoveredBackImage;
        }
    }
    else
    {
        pushedBackImage = m_disabledBackImage;
    }
    if (pushedBackImage != L"")
    {
        return pushedBackImage;
    }
	return ControlA::GetPaintingBackImage();
}
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonA::ButtonA()
{
	m_disabledBackImage = L"";
	m_hoveredBackImage = L"";
	m_pushedBackImage = L"";
	m_textAlign = ContentAlignmentA_MiddleCenter; 
	SIZE size = {60, 20};
	SetSize(size);
}

ButtonA::~ButtonA()	
{
	m_textAlign = ContentAlignmentA_MiddleCenter; 
}

String ButtonA::GetDisabledBackImage()
{
	return m_disabledBackImage;
}

void ButtonA::SetDisabledBackImage(const String& disabledBackImage)
{
	m_disabledBackImage = disabledBackImage;
}

String ButtonA::GetHoveredBackImage()
{
	return m_hoveredBackImage;
}

void ButtonA::SetHoveredBackImage(const String& hoveredBackImage)
{
	m_hoveredBackImage = hoveredBackImage;
}

String ButtonA::GetPushedBackImage()
{
	return m_pushedBackImage;
}

void ButtonA::SetPushedBackImage(const String& pushedBackImage)
{
	m_pushedBackImage = pushedBackImage;
}

ContentAlignmentA ButtonA::GetTextAlign()
{
	return m_textAlign;
}

void ButtonA::SetTextAlign(ContentAlignmentA textAlign)
{
	m_textAlign = textAlign;
}
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String ButtonA::GetControlType()
{
	return L"Button";
}

void ButtonA::GetProperty(const String& name, String *value, String *type)
{
    if (name == L"disabledbackimage")
    {
        *type = L"text";
        *value = GetDisabledBackImage();
    }
    else if (name == L"hoveredbackimage")
    {
        *type = L"text";
        *value = GetHoveredBackImage();
    }
    else if (name == L"pushedbackimage")
    {
        *type = L"text";
        *value = GetPushedBackImage();
    }
    else if (name == L"textalign")
    {
        *type = L"enum:ContentAlignmentA";
		*value = CStr::ConvertContentAlignmentToStr(GetTextAlign());
    }
    else
    {
		ControlA::GetProperty(name, value, type);
    }
}

vector<String> ButtonA::GetPropertyNames()
{
	vector<String> propertyNames;
	propertyNames.push_back(L"DisabledBackImage");
	propertyNames.push_back(L"HoveredBackImage");
	propertyNames.push_back(L"PushedBackImage");
	propertyNames.push_back(L"TextAlign");
	return propertyNames;
}

void ButtonA::OnMouseDown(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	ControlA::OnMouseDown(mp, button, clicks, delta);
	Invalidate();
}

void ButtonA::OnMouseEnter(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	ControlA::OnMouseEnter(mp, button, clicks, delta);
	Invalidate();
}

void ButtonA::OnMouseLeave(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	ControlA::OnMouseLeave(mp, button, clicks, delta);
	Invalidate();
}

void ButtonA::OnMouseUp(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	ControlA::OnMouseUp(mp, button, clicks, delta);
	Invalidate();
}

void ButtonA::OnPaintForeground(CPaint *paint, const RECT& clipRect)
{
    String text = GetText();
	if ((int)text.size() > 0)
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
			if (AutoEllipsis() && (rect.right > clipRect.right || rect.bottom > clipRect.bottom))
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

void ButtonA::SetProperty(const String& name, const String& value)
{
    if (name == L"disabledbackimage")
    {
        SetDisabledBackImage(value);
    }
    else if (name == L"hoveredbackimage")
    {
        SetHoveredBackImage(value);
    }
    else if (name == L"pushedbackimage")
    {
        SetPushedBackImage(value);
    }
    else if (name == L"textalign")
    {
		SetTextAlign(CStr::ConvertStrToContentAlignment(value));
    }
    else
    {
		ControlA::SetProperty(name, value);
    }
}		