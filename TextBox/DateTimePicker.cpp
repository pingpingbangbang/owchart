#include "..\\stdafx.h"
#include "..\\include\\TextBox\\DateTimePicker.h"
using namespace OwLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DateTimePickerA::DropDownButtonMouseDown( void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke )
{
	DateTimePickerA *pThis = (DateTimePickerA*)sender;
	if(pThis)
	{
		pThis->OnDropDownOpening();
	}
}

void DateTimePickerA::SelectedTimeChanged( void *sender, void *pInvoke )
{
	DateTimePickerA *pThis = (DateTimePickerA*)sender;
	if(pThis)
	{
		pThis->OnSelectedTimeChanged();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DateTimePickerA::DateTimePickerA()
{
	m_calendar = 0;
	m_dropDownButton = 0;
	m_dropDownMenu = 0;
	m_customFormat = L"yyyy-MM-dd";
	m_dropDownButtonMouseDownEvent = &DropDownButtonMouseDown;
	m_selectedTimeChangedEvent = &SelectedTimeChanged;
}

DateTimePickerA::~DateTimePickerA()
{
	if (m_calendar)
	{
		if(m_selectedTimeChangedEvent)
		{
			m_calendar->UnRegisterEvent(m_selectedTimeChangedEvent, EVENTID::SELECTEDTIMECHANGED);
			m_selectedTimeChangedEvent = 0;
		}
		m_calendar = 0;
	}
	if (m_dropDownButton)
	{
		if(m_dropDownButtonMouseDownEvent)
		{
			m_dropDownButton->UnRegisterEvent(m_dropDownButtonMouseDownEvent, EVENTID::MOUSEDOWN);
			m_dropDownButtonMouseDownEvent = 0;
		}
		m_dropDownButton = 0;
	}
	if (m_dropDownMenu)
	{
		GetNative()->RemoveControl(m_dropDownMenu);
		delete m_dropDownMenu;
		m_dropDownMenu = 0;
	}
}

CalendarA* DateTimePickerA::GetCalendar()
{
	return m_calendar;
}

String DateTimePickerA::GetCustomFormat()
{
	return m_customFormat;
}

void DateTimePickerA::SetCustomFormat( const String& customFormat )
{
	m_customFormat = customFormat;
}

ButtonA* DateTimePickerA::GetDropDownButton()
{
	return m_dropDownButton;
}

MenuA* DateTimePickerA::GetDropDownMenu()
{
	return m_dropDownMenu;
}

bool DateTimePickerA::ShowTime()
{
	return m_showTime;
}

void DateTimePickerA::SetShowTime(bool showTime)
{
	m_showTime = showTime;
}

String DateTimePickerA::GetControlType()
{
	return L"DateTimePicker";
}

void DateTimePickerA::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"customformat")
	{
		*type = L"string";
		*value = GetCustomFormat();
	}
	else if (name == L"showtime")
	{
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(m_showTime);
	}
	else
	{
		TextBoxA::GetProperty(name, value, type);
	}
}

vector<String> DateTimePickerA::GetPropertyNames()
{
	vector<String> propertyNames = TextBoxA::GetPropertyNames();
	propertyNames.push_back(L"CustomFormat");
	propertyNames.push_back(L"ShowTime");
	return propertyNames;
}

void DateTimePickerA::OnDropDownOpening()
{
	if (!m_dropDownMenu)
	{
		ControlHost *host = GetNative()->GetHost();
		m_dropDownMenu = (MenuA*)host->CreateInternalControl(this, L"dropdownmenu");
		GetNative()->AddControl(m_dropDownMenu);
		if (!m_calendar)
		{
			m_calendar = new CalendarA();
			m_calendar->SetDock(DockStyleA_Fill);
			m_dropDownMenu->AddControl(m_calendar);
			m_calendar->SetSize(m_dropDownMenu->GetSize());
			m_calendar->RegisterEvent(m_selectedTimeChangedEvent, EVENTID::SELECTEDTIMECHANGED, this);
		}
	}
	m_dropDownMenu->SetNative(GetNative());
	POINT pt = {0, GetHeight()};
	POINT point = PointToNative(pt);
	m_dropDownMenu->SetLocation(point);
	m_dropDownMenu->SetVisible(true);
	if (m_calendar)
	{
		m_calendar->SetMode(CalendarMode_Day);
	}
	m_dropDownMenu->BringToFront();
	m_dropDownMenu->Invalidate();
}

void DateTimePickerA::OnLoad()
{
	ControlA::OnLoad();
	if (!m_dropDownButton)
	{
		ControlHost *host = GetNative()->GetHost();
		m_dropDownButton = (ButtonA*)host->CreateInternalControl(this, L"dropdownbutton");
		AddControl(m_dropDownButton);
		m_dropDownButton->RegisterEvent(m_dropDownButtonMouseDownEvent, EVENTID::MOUSEDOWN, this);
	}
	if (m_dropDownMenu)
	{
		m_dropDownMenu->SetNative(GetNative());
	}
}

void DateTimePickerA::OnSelectedTimeChanged()
{
	CallEvents(EVENTID::VALUECHANGED);
	if (m_calendar)
	{
		CDay *selectedDay = m_calendar->GetSelectedDay();
		if (selectedDay)
		{
			TimeDiv *dir = m_calendar->GetTimeDiv();
			String buff = CStr::GetFormatDate(m_customFormat.c_str(), selectedDay->GetYear(), 
				selectedDay->GetMonth(), selectedDay->GetDay(), dir->GetHour(), dir->GetMinute(), dir->GetSecond());
			SetText(buff);
			Invalidate();
		}
	}
}

void DateTimePickerA::SetProperty( const String& name, const String& value )
{
	if (name == L"customformat")
	{
		SetCustomFormat(value);
	}
	else if (name == L"showtime")
	{
		m_showTime = CStr::ConvertStrToBool(value);
	}
	else
	{
		TextBoxA::SetProperty(name, value);
	}
}

void DateTimePickerA::Update()
{
	TextBoxA::Update();
	int width = GetWidth();
	int height = GetHeight();
	if (m_dropDownButton)
	{
		int right = m_dropDownButton->GetWidth();
		POINT pt = {width - right, 0};
		m_dropDownButton->SetLocation(pt);
		SIZE sz = {right, height};
		m_dropDownButton->SetSize(sz);
		PADDING pd(0, 0, right, 0);
		SetPadding(pd);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////