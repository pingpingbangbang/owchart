#include "..\\stdafx.h"
#include "..\\include\\Button\\CheckBox.h"
using namespace OwLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_int64 CheckBoxA::GetPaintingBackColor()
{
    _int64 backColor = GetBackColor();
    if (backColor != COLOR_EMPTY  && COLOR_DISABLEDCONTROL != COLOR_EMPTY && !IsPaintEnabled(this))
    {
        return COLOR_DISABLEDCONTROL;
    }
    return backColor;
}

_int64 CheckBoxA::GetPaintingButtonBackColor()
{	
    _int64 buttonBackColor = m_buttonBackColor;
    if (buttonBackColor != COLOR_EMPTY
        && COLOR_DISABLEDCONTROL != COLOR_EMPTY 
        && !IsPaintEnabled(this))
    {
        return COLOR_DISABLEDCONTROL;
    }
    return buttonBackColor;
}

_int64 CheckBoxA::GetPaintingButtonBorderColor()
{
	return m_buttonBorderColor;
}

String CheckBoxA::GetPaintingBackImage()
{
    String checkPushedBackImage = L"";
    if (m_checked)
    {
        if (IsEnabled())
        {
            if (this == m_native->GetPushedControl())
            {
                checkPushedBackImage = m_checkPushedBackImage;
            }
            else if (this == m_native->GetHoveredControl())
            {
                checkPushedBackImage = m_checkHoveredBackImage;
            }
            else
            {
                checkPushedBackImage = m_checkedBackImage;
            }
        }
        else
        {
            checkPushedBackImage = m_disableCheckedBackImage;
        }
    }
    if (checkPushedBackImage != L"")
    {
        return checkPushedBackImage;
    }
	return ButtonA::GetPaintingBackImage();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CheckBoxA::CheckBoxA()
{
	SetBackColor(COLOR_EMPTY);
	SetBorderColor(COLOR_EMPTY);
	m_buttonAlign = HorizontalAlignA_Left;
	m_buttonBackColor = COLOR_CONTROLBORDER;
	m_buttonBorderColor = COLOR_CONTROLBORDER;
	SIZE size = {16,16};
	m_buttonSize = size;
	m_checked = false;
	m_checkedBackImage = L"";
	m_checkHoveredBackImage = L"";
	m_checkPushedBackImage = L"";
	m_disableCheckedBackImage = L"";
}

CheckBoxA::~CheckBoxA()
{
}

HorizontalAlignA CheckBoxA::GetButtonAlign()
{
	return m_buttonAlign;
}

void CheckBoxA::SetButtonAlign(HorizontalAlignA buttonAlign)
{
	m_buttonAlign = buttonAlign;
}

_int64 CheckBoxA::GetButtonBackColor()
{
	return m_buttonBackColor;
}

void CheckBoxA::SetButtonBackColor(_int64 buttonBackColor)
{
	m_buttonBackColor = buttonBackColor;
}

_int64 CheckBoxA::GetButtonBorderColor()
{
	return m_buttonBorderColor;
}

void CheckBoxA::SetButtonBorderColor(_int64 buttonBorderColor)
{
	m_buttonBorderColor = buttonBorderColor;
}

SIZE CheckBoxA::GetButtonSize()
{
	return m_buttonSize;
}

void CheckBoxA::SetButtonSize(SIZE buttonSize)
{
	m_buttonSize = buttonSize;
}

bool CheckBoxA::IsChecked()
{
	return m_checked;
}

void CheckBoxA::SetChecked(bool checked)
{
    if (m_checked != checked)
    {
        m_checked = checked;
        OnCheckedChanged();
    }
}

String CheckBoxA::GetCheckedBackImage()
{
	return m_checkedBackImage;
}

void CheckBoxA::SetCheckedBackImage(const String& checkedBackImage)
{
	m_checkedBackImage = checkedBackImage;
}

String CheckBoxA::GetCheckHoveredBackImage()
{
	return m_checkHoveredBackImage;
}

void CheckBoxA::SetCheckHoveredBackImage(const String& checkHoveredBackImage)
{
	m_checkHoveredBackImage = checkHoveredBackImage;
}

String CheckBoxA::GetCheckPushedBackImage()
{
	return m_checkPushedBackImage;
}

void CheckBoxA::SetCheckPushedBackImage(const String& checkPushedBackImage)
{
	m_checkPushedBackImage = checkPushedBackImage;
}

String CheckBoxA::GetDisableCheckedBackImage()
{
	return m_disableCheckedBackImage;
}

void CheckBoxA::SetDisableCheckedBackImage(const String& disableCheckedBackImage)
{
	m_disableCheckedBackImage = disableCheckedBackImage;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

String CheckBoxA::GetControlType()
{
    return L"CheckBox";
}

vector<wstring> CheckBoxA::GetEventNames()
{
	vector<wstring> ws;
	ws.push_back(L"CheckedChanged");
	return ws;
}

void CheckBoxA::GetProperty(const String& name, String *value, String *type)
{	
    if (name == L"buttonalign")
    {
        *type = L"enum:HorizontalAlignA";
		*value = CStr::ConvertHorizontalAlignToStr(GetButtonAlign());
    }
    else if (name == L"buttonbackcolor")
    {
        *type = L"color";
        *value  = CStr::ConvertColorToStr(GetButtonBackColor());
    }
    else if (name == L"buttonbordercolor")
    {
        *type = L"color";
        *value  = CStr::ConvertColorToStr(GetButtonBorderColor());
    }
    else if (name == L"buttonsize")
    {
        *type = L"size";
        *value  = CStr::ConvertSizeToStr(GetButtonSize());
    }
    else if (name == L"checked")
    {
        *type = L"bool";
        *value  = CStr::ConvertBoolToStr(IsChecked());
    }
    else if (name == L"checkedbackimage")
    {
        *type = L"text";
        *value  = GetCheckedBackImage();
    }
    else if (name == L"checkhoveredbackimage")
    {
        *type = L"text";
        *value  = GetCheckHoveredBackImage();
    }
    else if (name == L"checkpushedbackimage")
    {
        *type = L"text";
        *value  = GetCheckPushedBackImage();
    }
    else if (name == L"disablecheckedbackimage")
    {
        *type = L"text";
        *value  = GetDisableCheckedBackImage();
    }
    else
    {
		ControlA::GetProperty(name, value, type);
    }
}

vector<String> CheckBoxA::GetPropertyNames()
{
    vector<String> propertyNames;
	propertyNames.push_back(L"ButtonAlign");
	propertyNames.push_back(L"ButtonBackColor");
	propertyNames.push_back(L"ButtonBorderColor");
	propertyNames.push_back(L"ButtonSize");
	propertyNames.push_back(L"Checked");
	propertyNames.push_back(L"CheckedBackImage");
	propertyNames.push_back(L"CheckHoveredBackimage");
	propertyNames.push_back(L"CheckPushedBackImage");
	propertyNames.push_back(L"DisableCheckedBackImage");
    return propertyNames;
}

void CheckBoxA::OnCheckedChanged()
{
	ControlA::CallEvents(EVENTID::CHECKEDCHANGED);
    Update();
}

void CheckBoxA::OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
    SetChecked(!IsChecked());
	ControlA::CallMouseEvents(EVENTID::CLICK, mp, button, clicks, delta);
    Invalidate();
}

void CheckBoxA::OnPaintBackground(CPaint *paint, const RECT& clipRect)
{
	RECT rect = {0, 0, GetWidth(), GetHeight()};
    paint->FillRect(GetPaintingBackColor(), rect);
}

void CheckBoxA::OnPaintCheckButton(CPaint *paint, const RECT& clipRect)
{
    String paintingBackImage = GetPaintingBackImage();
    if (paintingBackImage != L"" 
        && (int)paintingBackImage.size() > 0)
    {
        paint->DrawImage(paintingBackImage.c_str(), clipRect);
    }
    else
    {
        if (m_checked)
        {
			RECT rect = {clipRect.left + 2, clipRect.top + 2, clipRect.right - 2, clipRect.bottom - 2};
            if (clipRect.right - clipRect.left < 4 || clipRect.bottom - clipRect.top < 4)
            {
                rect = clipRect;
            }
            paint->FillRect(GetPaintingButtonBackColor(), rect);
        }
        paint->DrawRect(GetPaintingButtonBorderColor(), 1, 0, clipRect);
    }
}

void CheckBoxA::OnPaintForeground(CPaint *paint, const RECT& clipRect)
{
    String text = GetText();
    int width = GetWidth();
    int height = GetHeight();
    if (width > 0 && height > 0)
    {
		RECT buttonRect = {5, (height - m_buttonSize.cy) / 2, 5 + m_buttonSize.cx, (height + m_buttonSize.cy) / 2};
		POINT tLocation = {0, 0};
		SIZE size = {0, 0};
        FONT *font = GetFont();
        if ((int)text.size() > 0)
        {
            size = paint->TextSize(text.c_str(), font);
            tLocation.x = buttonRect.right + 5;
            tLocation.y = (height - size.cy) / 2;
        }
        if (m_buttonAlign == HorizontalAlignA_Center)
        {
            buttonRect.left = (width - m_buttonSize.cx) / 2;
            buttonRect.right = (width + m_buttonSize.cx) / 2;
            tLocation.x = buttonRect.right + 5;
        }
        else if (m_buttonAlign == HorizontalAlignA_Right)
        {
            buttonRect.left = width - m_buttonSize.cx - 5;
            buttonRect.right = width - 5;
            tLocation.x = buttonRect.left - size.cx - 5;
        }
        OnPaintCheckButton(paint, buttonRect);
        if ((int)text.size() > 0)
        {
			RECT tRect = { tLocation.x, tLocation.y, tLocation.x + size.cx + 1, tLocation.y + size.cy };
            _int64 paintingForeColor = GetPaintingForeColor();
            if (AutoEllipsis() && (tRect.right < clipRect.right || tRect.bottom < clipRect.bottom))
			{
                if (tRect.right < clipRect.right)
                {
                    tRect.right = clipRect.right;
                }
                if (tRect.bottom < clipRect.bottom)
                {
                    tRect.bottom = clipRect.bottom;
                }
                paint->DrawTextAutoEllipsis(text.c_str(), paintingForeColor, font, tRect);
            }
            else
            {
                paint->DrawText(text.c_str(), paintingForeColor, font, tRect);
            }
        }
    }
}

void CheckBoxA::SetProperty(const String& name, const String& value)
{	
    if (name == L"buttonalign")
    {
        SetButtonAlign(CStr::ConvertStrToHorizontalAlign(value));
    }
    else if (name == L"buttonbackcolor")
    {
        SetButtonBackColor(CStr::ConvertStrToColor(value));
    }
    else if (name == L"buttonbordercolor")
    {
        SetButtonBorderColor(CStr::ConvertStrToColor(value));
    }
    else if (name == L"buttonsize")
    {
        SetButtonSize(CStr::ConvertStrToSize(value));
    }
    else if (name == L"checked")
    {
        SetChecked(CStr::ConvertStrToBool(value));
    }
    else if (name == L"checkedbackimage")
    {
        SetCheckedBackImage(value);
    }
    else if (name == L"checkhoveredbackimage")
    {
        SetCheckHoveredBackImage(value);
    }
    else if (name == L"checkpushedbackimage")
    {
        SetCheckPushedBackImage(value);
    }
    else if (name == L"disablecheckedbackimage")
    {
        SetDisableCheckedBackImage(value);
    }
    else
    {
        ControlA::SetProperty(name, value);
    }
}