#include "..\\stdafx.h"
#include "..\\include\\TextBox\\DatePicker.h"
using namespace OwLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DatePickerA::DropDownButtonMouseDown( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{

}

void DatePickerA::SelectedDayChanged( void *sender, void *pInvoke )
{

}

DatePickerA::DatePickerA()
{
	m_dropDownButtonMouseDownEvent = &DropDownButtonMouseDown;
	m_selectedDayChangedEvent = &SelectedDayChanged;
}

DatePickerA::~DatePickerA()
{
	if ((m_calendar) && (m_selectedDayChangedEvent))
	{
		m_calendar->UnRegisterEvent(m_selectedDayChangedEvent, 0x2e);
		m_selectedDayChangedEvent = 0;
	}
	if ((m_dropDownButton) && (m_dropDownButtonMouseDownEvent))
	{
		m_dropDownButton->UnRegisterEvent(m_dropDownButtonMouseDownEvent, 0x18);
		m_dropDownButtonMouseDownEvent = 0;
	}
	if (m_dropDownMenu)
	{
		GetNative()->RemoveControl(m_dropDownMenu);
		delete m_dropDownMenu;
		m_dropDownMenu = 0;
	}
}

CalendarA* DatePickerA::GetCalendar()
{
	return m_calendar;
}

ButtonA* DatePickerA::GetDropDownButton()
{
	return  m_dropDownButton;
}

MenuA* DatePickerA::GetDropDownMenu()
{
	return m_dropDownMenu;
}

String DatePickerA::GetControlType()
{
	return L"DateTimePicker";
}

void DatePickerA::OnDropDownOpening()
{

}

void DatePickerA::OnLoad()
{
	TextBoxA::OnLoad();
	if (m_dropDownButton == 0)
	{
		ControlHost *host = GetNative()->GetHost();
		m_dropDownButton = (ButtonA*)host->CreateInternalControl(this, L"dropdownbutton");
		AddControl(m_dropDownButton);
		m_dropDownButton->RegisterEvent(m_dropDownButtonMouseDownEvent, 0x18, this);
	}
	if (m_dropDownMenu != 0)
	{
		m_dropDownMenu->SetNative(GetNative());
	}
}

void DatePickerA::OnValueChanged()
{
	CallEvents(0x2e);
	if (m_calendar != 0)
	{
		CDay *selectedDay = m_calendar->GetSelectedDay();
		if (selectedDay != 0)
		{
			TimeDiv *dir = m_calendar->GetTimeDiv();
			wchar_t buff[128] = {0};
			SetText(buff);
			Invalidate();
		}
	}
}

void DatePickerA::Update()
{
	TextBoxA::Update();
	int width = GetWidth();
	int height = GetHeight();
	if (m_dropDownButton != 0)
	{
		int right = m_dropDownButton->GetWidth();
		PADDING pd(0, 0, right, 0);
		SetPadding(pd);
		POINT pt = {width - right, 0};
		m_dropDownButton->SetLocation(pt);
		SIZE sz = {right, height};
		m_dropDownButton->SetSize(sz);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
