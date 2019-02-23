#include "..\\stdafx.h"
#include "..\\include\\TextBox\\Spin.h"
using namespace OwLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpinA::DownButtonMouseDown( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	SpinA *pThis = (SpinA *)pInvoke;
	if(pThis)
	{
		pThis->Reduce();
		pThis->SetIsReducing(true);
		pThis->Invalidate();
	}
}

void SpinA::DownButtonMouseUp( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	SpinA *pThis = (SpinA *)pInvoke;
	if(pThis)
	{
		pThis->SetIsReducing(false);
	}
}

void SpinA::UpButtonMouseDown( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	SpinA *pThis = (SpinA *)pInvoke;
	if(pThis)
	{
		pThis->Add();
		pThis->SetIsAdding(true);
		pThis->Invalidate();
	}
}

void SpinA::UpButtonMouseUp( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	SpinA *pThis = (SpinA *)pInvoke;
	if(pThis)
	{
		pThis->SetIsAdding(false);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpinA::SpinA()
{
	m_autoFormat = true;
	m_digit = 0;
	m_downButton = 0;
	m_downButtonMouseDownEvent = &DownButtonMouseDown;
	m_downButtonMouseUpEvent = &DownButtonMouseUp;
	m_isAdding = false;
	m_isReducing = false;
	m_maximum = 100.0;
	m_minimum = 0.0;
	m_showThousands = false;
	m_step = 1.0;
	m_tick = 0;
	m_timerID = GetNewTimerID();
	m_upButton = 0;
	m_upButtonMouseDownEvent = &UpButtonMouseDown;
	m_upButtonMouseUpEvent = &UpButtonMouseUp;
}

SpinA::~SpinA()
{
	if (m_downButton)
	{
		if (m_downButtonMouseDownEvent)
		{
			m_downButton->UnRegisterEvent(m_downButtonMouseDownEvent, EVENTID::MOUSEDOWN);
			m_downButtonMouseDownEvent = 0;
		}
		if (m_downButtonMouseUpEvent)
		{
			m_downButton->UnRegisterEvent(m_downButtonMouseUpEvent, EVENTID::MOUSEUP);
			m_downButtonMouseUpEvent = 0;
		}
		m_downButton = 0;
	}
	if (m_upButton)
	{
		if (m_upButtonMouseDownEvent)
		{
			m_upButton->UnRegisterEvent(m_upButtonMouseDownEvent, EVENTID::MOUSEDOWN);
			m_upButtonMouseDownEvent = 0;
		}
		if (m_upButtonMouseUpEvent)
		{
			m_upButton->UnRegisterEvent(m_upButtonMouseUpEvent, EVENTID::MOUSEUP);
			m_upButtonMouseUpEvent = 0;
		}
		m_upButton = 0;
	}
}

bool SpinA::AutoFormat()
{
	return m_autoFormat;
}

void SpinA::SetAutoFormat( bool autoFormat )
{
	m_autoFormat = autoFormat;
}

int SpinA::GetDigit()
{
	return m_digit;
}

void SpinA::SetDigit( int digit )
{
	m_digit = digit;
	if (m_autoFormat)
	{
		if (m_text == L"")
		{
			m_text = L"0";
		}
		CStr::ConvertStrToDouble(m_text);
		SetText(GetValueByDigit(GetValue(), m_digit));
	}
}

ButtonA* SpinA::GetDownButton()
{
	return m_downButton;
}

bool SpinA::IsAdding()
{
	return m_isAdding;
}

void SpinA::SetIsAdding( bool isAdding )
{
	if(m_isAdding != isAdding)
	{
		m_isAdding = isAdding;
		m_tick = 0;
		if (m_isAdding)
		{
			StartTimer(m_timerID, 10);
		}
		else
		{
			StopTimer(m_timerID);
		}
	}
}

bool SpinA::IsReducing()
{
	return m_isReducing;
}

void SpinA::SetIsReducing( bool isReducing )
{
	if(m_isReducing != isReducing)
	{
		m_isReducing = isReducing;
		m_tick = 0;
		if (m_isReducing)
		{
			StartTimer(m_timerID, 10);
		}
		else
		{
			StopTimer(m_timerID);
		}
	}
}

double SpinA::GetMaximum()
{
	return m_maximum;
}

void SpinA::SetMaximum( double maximum )
{
	m_maximum = maximum;
	if (GetValue() > maximum)
	{
		SetValue(maximum);
	}
}

double SpinA::GetMinimum()
{
	return m_minimum;
}

void SpinA::SetMinimum( double minimum )
{
	m_minimum = minimum;
	if (GetValue() < minimum)
	{
		SetValue(minimum);
	}
}

bool SpinA::ShowThousands()
{
	return m_showThousands;
}

void SpinA::SetShowThousands( bool showThousands )
{
	m_showThousands = showThousands;
}

double SpinA::GetStep()
{
	return m_step;
}

void SpinA::SetStep( double step )
{
	m_step = step;
}

void SpinA::SetText( const String& text )
{
	String str = CStr::Replace(text, L",", L"");
	ControlA::SetText(FormatNum(str));
}

ButtonA* SpinA::GetUpButton()
{
	return m_upButton;
}

double SpinA::GetValue()
{
	String str = GetText();
	str = CStr::Replace(str, L",", L"");
	return CStr::ConvertStrToDouble(str.c_str());
}

void SpinA::SetValue( double value )
{
	if (value > m_maximum)
	{
		value = m_maximum;
	}
	if (value < m_minimum)
	{
		value = m_minimum;
	}
	double num1 = GetValue();
	SetText(FormatNum(GetValueByDigit(value, m_digit)));
	OnValueChanged();
}

void SpinA::Add()
{
	double value = GetValue();
	value += m_step;
	SetValue(value);
}

String SpinA::FormatNum( String inputText )
{
	if (!m_showThousands)
	{
		return inputText;
	}
	inputText = CStr::Replace(inputText, L",", L"");
	String theNewText;
	int startIndex = 0;
	bool hasMinusSign = false;
	if (inputText.find(L"-") == 0)
	{
		hasMinusSign = true;
		inputText = inputText.substr(1);
	}
	String textAfterDot;
	bool hasDot = false;
	if (inputText.find(L".") != -1)
	{
		hasDot = true;
		textAfterDot = inputText.substr(inputText.find(L".") + 1);
		inputText = inputText.erase(inputText.find(L"."));
	}
	int length = (int)inputText.length();
	for (startIndex = length; startIndex >= 0; startIndex--)
	{
		int logicPos = (int)inputText.length() - startIndex;
		if (((logicPos % 3) == 0) && (logicPos > 1))
		{
			if (theNewText.empty())
			{
				theNewText = inputText.substr(startIndex, 3);
			}
			else
			{
				theNewText = inputText.substr(startIndex, 3) + L"," + theNewText;
			}
		}
		else if (startIndex == 0)
		{
			if (theNewText.empty())
			{
				theNewText = inputText.substr(startIndex, logicPos % 3);
			}
			else
			{
				theNewText = inputText.substr(startIndex, logicPos % 3) + L"," + theNewText;
			}
		}
	}
	if (hasMinusSign)
	{
		theNewText = L"-" + theNewText;
	}
	if (hasDot)
	{
		theNewText = theNewText + L"." + textAfterDot;
	}
	if (theNewText.find(L".") == 0)
	{
		theNewText = L"0" + theNewText;
	}
	if (theNewText.find(L"-.") == 0)
	{
		theNewText = theNewText.insert(1, L"0");
	}
	return theNewText;
}

String SpinA::GetControlType()
{
	return L"Spin";
}

vector<wstring> SpinA::GetEventNames()
{
	vector<wstring> ws;
	ws.push_back(L"ValueChanged");
	return ws;
}

void SpinA::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"autoformat")
	{
		*type = L"int";
		*value = CStr::ConvertBoolToStr(AutoFormat());
	}
	else if (name == L"digit")
	{
		*type = L"int";
		*value = CStr::ConvertDoubleToStr((double) GetDigit());
	}
	else if (name == L"maximum")
	{
		*type = L"double";
		*value = CStr::ConvertDoubleToStr(GetMaximum());
	}
	else if (name == L"minimum")
	{
		*type = L"double";
		*value = CStr::ConvertDoubleToStr(GetMinimum());
	}
	else if (name == L"showthousands")
	{
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(ShowThousands());
	}
	else if (name == L"step")
	{
		*type = L"double";
		*value = CStr::ConvertDoubleToStr(GetStep());
	}
	else if (name == L"value")
	{
		*type = L"double";
		*value = CStr::ConvertDoubleToStr(GetValue());
	}
	else
	{
		TextBoxA::GetProperty(name, value, type);
	}
}

vector<String> SpinA::GetPropertyNames()
{
	vector<String> propertyNames = TextBoxA::GetPropertyNames();
	propertyNames.push_back(L"AutoFormat");
	propertyNames.push_back(L"Digit");
	propertyNames.push_back(L"Maximum");
	propertyNames.push_back(L"Minimum");
	propertyNames.push_back(L"ShowThousands");
	propertyNames.push_back(L"Step");
	propertyNames.push_back(L"Value");
	return propertyNames;
}

String SpinA::GetValueByDigit( double value, int digit )
{
	wchar_t buff[128] = {0};
	CStr::GetValueByDigit(value, digit, buff);
	return buff;
}

void SpinA::OnChar( wchar_t ch )
{
	if (m_autoFormat)
	{
		ControlA::CallEvents(EVENTID::CHAR);
		if (!GetNative()->GetHost()->IsKeyPress(0x11))
		{
			bool flag = false;
			if (GetSelectionLength() > 0)
			{
				flag = true;
			}
			wchar_t ch2 = ch;
			int selectionStart = GetSelectionStart();
			bool flag2 = false;
			if (selectionStart == m_text.length())
			{
				flag2 = true;
			}
			int num2 = 0;
			if (ch2 == L'\b')
			{
				int arg1 = GetSelectionStart();
				if (GetSelectionLength() > 0)
				{
					if (GetSelectionStart() > 0 && m_text[GetSelectionStart() - 1] == L',')
					{
						SetSelectionStart(GetSelectionStart() - 1);
						SetSelectionLength(GetSelectionLength() + 1);
						selectionStart = GetSelectionStart();
					}
					SetText(FormatNum(GetText()));
					SetSelectionStart(selectionStart);
				}
				else
				{
					if (GetSelectionStart() > 0 && m_text[GetSelectionStart() - 1] == L',')
					{
						SetSelectionStart(GetSelectionStart() - 1);
						selectionStart = GetSelectionStart();
					}
					if (GetSelectionStart() > 0 && m_text[GetSelectionStart() - 1] == L'.')
					{
						num2 = (int)m_text.substr(GetSelectionStart()).length() / 3;
					}
					int num3 = (int)m_text.length() - selectionStart;
					String text = GetText();
					int num4 = 0;
					if (text.find(L",") == 0)
					{
						text = text.substr(1);
						num4 = 1;
					}
					m_text = FormatNum(GetText());
					if (((((int)GetText().length() + num4) - num2) - num3) > 0)
					{
						SetSelectionStart((((int)m_text.length() + num4) - num2) - num3);
					}
				}
				Invalidate();
			}
			else if ((ch2 == L'.') && (int)m_text.find(L".") != -1)
			{
				if ((int)m_text.find(L".") != ((int)m_text.length() - 1))
				{
					SetSelectionStart((int)m_text.find(L".") + 1);
				}
				Invalidate();
			}
			else
			{
				int num5 = (int)m_text.length() - selectionStart;
				if (ch2 == L'.')
				{
					String str3 = m_text.substr(GetSelectionStart());
					String temp = CStr::Replace(str3, L",", L"");
					num2 = (int)str3.length() - (int)temp.length();
					String word(1, ch);
					TextBoxA::InsertWord(word);
					OnTextChanged();
					OnValueChanged();
					Invalidate();
				}
				else
				{
					bool flag3 = false;
					if (m_text.find(L"0.") == 0 && (GetSelectionStart() == 0))
					{
						flag3 = true;
						m_text = m_text.substr(1);
						SetSelectionLength(0);
					}
					String text1 = GetText();
					int index = (int)m_text.find(L".");
					if ((m_selectionLength == 0) && (index < GetSelectionStart()))
					{
						m_selectionLength = 1;
					}
					String word(1, ch);
					InsertWord(word);
					int num7 = GetSelectionStart();
					SetRegion();
					m_selectionLength = 0;
					String str4 = GetText();
					if (str4.length() > 0 && num7 > (int)str4.length())
					{
						SetSelectionStart((int)str4.length());
					}
					if (((int)m_text.find(L".") != -1 && (int)m_text.find(L".") < num7) || flag)
					{
						SetSelectionStart(num7);
					}
					else if (flag2)
					{
						SetSelectionStart((int)m_text.length());
					}
					else if (((m_text.length() + num2) - num5) >= 0)
					{
						SetSelectionStart(((int)m_text.length() + num2) - num5);
					}
					if (flag3)
					{
						SetSelectionStart(GetSelectionStart() + 1);
					}
					m_showCursor = true;
					OnTextChanged();
					OnValueChanged();
					Invalidate();
				}
			}
		}
	}
	else
	{
		TextBoxA::OnChar(ch);
	}
}

void SpinA::OnKeyDown( char key )
{
	if (m_autoFormat && ((key == '\b') || (key == '.')))
	{
		String text = GetText();
		if (text.length() > 0)
		{
			int selectionStart = GetSelectionStart();
			if (((text.find(L".") != -1) && (text.find(L".") == (selectionStart - 1))) && (GetSelectionLength() <= 1))
			{
				SetSelectionStart(selectionStart - 1);
				selectionStart = GetSelectionStart();
			}
			if (GetSelectionStart() == 0)
			{
				int startIndex = GetSelectionLength() + 1;
				if (startIndex > (int)text.length())
				{
					startIndex = (int)text.length();
				}
				m_text = text.substr(startIndex);
			}
			else
			{
				TextBoxA::DeleteWord();
			}
			bool flag = m_text.length() == 0;
			SetRegion();
			if (selectionStart > 0)
			{
				SetSelectionStart(selectionStart - 1);
			}
			else
			{
				SetSelectionStart(selectionStart);
			}
			if (flag)
			{
				SetSelectionStart((int)m_text.length());
				SetSelectionLength(0);
			}
			else if ((selectionStart == 0) && (m_text.find(L"0.") == 0))
			{
				SetSelectionStart((int)m_text.length());
			}
			m_showCursor = true;
			OnTextChanged();
			OnValueChanged();
			Invalidate();
			return;
		}
	}
	TextBoxA::OnKeyDown(key);
	ControlHost *host = GetNative()->GetHost();
	if ((!host->IsKeyPress(0x10) && !host->IsKeyPress(0x11)) && !host->IsKeyPress(0x12))
	{
		if (key == '&')
		{
			Add();
			Invalidate();
		}
		else if (key == '(')
		{
			Reduce();
			Invalidate();
		}
	}
}

void SpinA::OnLoad()
{
	TextBoxA::OnLoad();
	ControlHost *host = GetNative()->GetHost();
	if (!m_downButton)
	{
		m_downButton = (ButtonA*)host->CreateInternalControl(this, L"downbutton");
		m_downButton->RegisterEvent(m_downButtonMouseDownEvent, EVENTID::MOUSEDOWN, this);
		m_downButton->RegisterEvent(m_downButtonMouseUpEvent, EVENTID::MOUSEUP, this);
		AddControl(m_downButton);
	}
	if (!m_upButton)
	{
		m_upButton = (ButtonA*)host->CreateInternalControl(this, L"upbutton");
		m_upButton->RegisterEvent(m_upButtonMouseDownEvent, EVENTID::MOUSEDOWN, this);
		m_upButton->RegisterEvent(m_upButtonMouseUpEvent, EVENTID::MOUSEUP, this);
		AddControl(m_upButton);
	}
	Update();
}

void SpinA::OnMouseWheel( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	TextBoxA::OnMouseMove(mp, button, clicks, delta);
	if (delta > 0)
	{
		Add();
	}
	else
	{
		Reduce();
	}
	Invalidate();
}

void SpinA::OnPaste()
{
	if (m_autoFormat)
	{
		TextBoxA::CallEvents(EVENTID::PASTE);
		string str = GetNative()->GetHost()->Paste();
		if (!str.empty())
		{
			String wstr;
			CStr::stringTowstring(wstr, str);
			TextBoxA::InsertWord(wstr);
			SetText(FormatNum(GetValueByDigit(GetValue(), m_digit)));
			OnTextChanged();
			OnValueChanged();
			Invalidate();
		}
	}
	else
	{
		TextBoxA::OnPaste();
	}
}

void SpinA::OnTimer( int timerID )
{
	TextBoxA::OnTimer(timerID);
	if (timerID == m_timerID)
	{
		if (m_tick > 20 && (m_tick > 50 || m_tick % 3 == 1))
		{
			if (m_isAdding)
			{
				Add();
				Invalidate();
			}
			else if (m_isReducing)
			{
				Reduce();
				Invalidate();
			}
		}
		m_tick++;
	}
}

void SpinA::OnValueChanged()
{
	TextBoxA::CallEvents(EVENTID::VALUECHANGED);
}

void SpinA::Reduce()
{
	SetValue(GetValue() - m_step);
}

void SpinA::SetProperty( const String& name, const String& value )
{
	if (name == L"autoformat")
	{
		SetAutoFormat(CStr::ConvertStrToBool(value));
	}
	else if (name == L"digit")
	{
		SetDigit(CStr::ConvertStrToInt(value));
	}
	else if (name == L"maximum")
	{
		SetMaximum(CStr::ConvertStrToDouble(value));
	}
	else if (name == L"minimum")
	{
		SetMinimum(CStr::ConvertStrToDouble(value));
	}
	else if (name == L"showthousands")
	{
		SetShowThousands(CStr::ConvertStrToBool(value));
	}
	else if (name == L"step")
	{
		SetStep(CStr::ConvertStrToDouble(value));
	}
	else if (name == L"value")
	{
		SetValue(CStr::ConvertStrToDouble(value));
	}
	else
	{
		TextBoxA::SetProperty(name, value);
	}
}

void SpinA::SetRegion()
{	
	String textValue = CStr::Replace(m_text, L",", L"");
    if (textValue == L"")
	{
      textValue = L"0";
    }
	
    if (textValue.find(L".") != -1 && textValue.find(L".") == 0) 
	{
      textValue = L"0" + textValue;
    }
    double value = CStr::ConvertStrToDouble(textValue);
    if (value > GetMaximum()) 
	{
      value = GetMaximum();
    }
    if (value < GetMinimum()) 
	{
      value = GetMinimum();
    }
    SetText(FormatNum(GetValueByDigit(value, m_digit)));
}

void SpinA::Update()
{
	TextBoxA::Update();
	int width = GetWidth();
	int height = GetHeight();
	int uBottom = 0;
	if (m_upButton)
	{
		int uWidth = m_upButton->GetWidth();
		POINT point = {width - uWidth, 0};
		m_upButton->SetLocation(point);
		SIZE size = {uWidth, height / 2};
		m_upButton->SetSize(size);
		uBottom = m_upButton->GetBottom();
		PADDING padding = GetPadding();
		PADDING padding2(padding.left, padding.top, uWidth + 3, padding.bottom);
		SetPadding(padding2);
	}
	if (m_downButton)
	{
		int dWidth = m_downButton->GetWidth();
		POINT point2 = {width - dWidth, uBottom};
		m_downButton->SetLocation(point2);
		SIZE size2 = {dWidth, height - uBottom};
		m_downButton->SetSize(size2);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////