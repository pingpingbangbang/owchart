#include "..\\stdafx.h"
#include "..\\include\\Grid\\GridCellExtends.h"
#include "..\\include\\Button\\CheckBox.h"
#include "..\\include\\Button\\RadioButton.h"
#include "..\\include\\TextBox\\ComboBox.h"
#include "..\\include\\TextBox\\DateTimePicker.h"
#include "..\\include\\Label\\Label.h"

namespace OwLib
{
	GridBoolCell::GridBoolCell()
	{
		m_value = false;		
	}

	GridBoolCell::GridBoolCell(bool value)
	{
		m_value = value;
	}

	GridBoolCell::~GridBoolCell()
	{
		
	}
		
	int GridBoolCell::CompareTo(GridCell *cell)
	{
		bool value = this->GetBool();
		bool target = cell->GetBool();
		if(value && !target)
		{
			return 1;
		}
		if(!value && target)
		{
			return -1;
		}
		return 0;
	}
	
	bool GridBoolCell::GetBool()
	{
		return m_value;
	}
	
	double GridBoolCell::GetDouble()
	{
		return (double)(m_value ? 1 : 0);
	}
	
	float GridBoolCell::GetFloat()
	{
		return (float)(m_value ? 1 : 0);
	}
	
	int GridBoolCell::GetInt()
	{
		return m_value ? 1 : 0;
	}
	
	_int64 GridBoolCell::GetLong()
	{
		return m_value ? 1 : 0;
	}
	
	String GridBoolCell::GetString()
	{
		return m_value ? L"true" : L"false";
	}
	
	void GridBoolCell::SetBool(bool value)
	{
		m_value = value;
	}
	
	void GridBoolCell::SetDouble(double value)
	{
		m_value = value > 0.0;
	}
	
	void GridBoolCell::SetFloat(float value)
	{
		m_value = value > 0.0;
	}
	
	void GridBoolCell::SetInt(int value)
	{
		m_value = value > 0;
	}
	
	void GridBoolCell::SetLong(_int64 value)
	{
		m_value = value > 0;
	}
	
	void GridBoolCell::SetString(const String& value)
	{
		m_value = value == L"true";
	}
	////////////////////////////////////////////////////////////////////////////

	GridButtonCell::GridButtonCell()
	{
		ButtonA* buttonA = new ButtonA();
		buttonA->SetBorderColor(COLOR_EMPTY);
		buttonA->SetDisplayOffset(false);
		SetControl(buttonA);
	}

	GridButtonCell:: ~GridButtonCell()
	{
	}

	ButtonA* GridButtonCell::GetButton()
	{
		ControlA *control = GetControl();
		if (control)
		{
			return dynamic_cast<ButtonA*>(control);
		}
        return 0;
	}
	//////////////////////////////////////////////////////////////////////////////////////////

	GridCheckBoxCell::GridCheckBoxCell()
	{
		CheckBoxA* checkBoxA = new CheckBoxA();
		checkBoxA->SetDisplayOffset(false);
		checkBoxA->SetButtonAlign(HorizontalAlignA_Center);
		SetControl(checkBoxA);
	}
	
	GridCheckBoxCell:: ~GridCheckBoxCell()
	{
	 
	}
	
	CheckBoxA* GridCheckBoxCell::GetCheckBox()
	{
		ControlA *control = GetControl();
		if (control)
		{
			return dynamic_cast<CheckBoxA*>(control);
		}
		return NULL;
	}

	 bool GridCheckBoxCell::GetBool()
	 {
		 CheckBoxA* checkBox = GetCheckBox();
		 if(checkBox)
		 {
			 return checkBox->IsChecked();
		 }
		 else
		 {
			 return false;
		 }
	 }

	 double GridCheckBoxCell::GetDouble()
	 {
		 CheckBoxA* checkBox = GetCheckBox();
		 if(checkBox)
		 {
			 return (double)(checkBox->IsChecked() ? 1 : 0);
		 }
		 return 0;
	 }
	 
	 float GridCheckBoxCell::GetFloat()
	 {
		CheckBoxA* checkBox = GetCheckBox();
		if (checkBox)
		{
			return (float)(checkBox->IsChecked() ? 1 : 0);
		}
		return 0;
	 }

	 int GridCheckBoxCell::GetInt()
	 {
		CheckBoxA* checkBox = GetCheckBox();
		if (checkBox)
		{
			return (checkBox->IsChecked()) ? 1 : 0;
		}
		return 0;		 
	 }
	 
	 _int64 GridCheckBoxCell::GetLong()
	 {
		CheckBoxA* checkBox = GetCheckBox();
		if (checkBox)
		{
			return (checkBox->IsChecked()) ? 1 : 0;
		}
		return 0;			 
	 }
	 
	 String GridCheckBoxCell::GetString()
	 {
		CheckBoxA* checkBox = GetCheckBox();
		if (!checkBox)
		{
			return L"false";
		}
		if (!checkBox->IsChecked())
		{
			return L"false";
		}
		return L"true";		 
	 }
	 
	 void GridCheckBoxCell::SetBool(bool value)
	 {
		CheckBoxA* checkBox = GetCheckBox();
		if (checkBox)
		{
			checkBox->SetChecked(value);
		}		 
	 }
	 
	 void GridCheckBoxCell::SetDouble(double value)
	 {
		CheckBoxA* checkBox = GetCheckBox();
		if (checkBox)
		{
			checkBox->SetChecked(value > 0);
		}		 
	 }
	 
	 void GridCheckBoxCell::SetFloat(float value)
	 {
		CheckBoxA* checkBox = GetCheckBox();
		if (checkBox)
		{
			checkBox->SetChecked(value > 0);
		}		 
	 }
	 
	 void GridCheckBoxCell::SetInt(int value)
	 {
		CheckBoxA* checkBox = GetCheckBox();
		if (checkBox)
		{
			checkBox->SetChecked(value > 0);
		}		 
	 }
	 
	 void GridCheckBoxCell::SetLong(_int64 value)
	 {
		CheckBoxA* checkBox = GetCheckBox();
		if (checkBox)
		{
			checkBox->SetChecked(value > 0);
		}		 
	 }

	 void GridCheckBoxCell::SetString(const String& value)
	 {
		CheckBoxA* checkBox = GetCheckBox();
		if (checkBox)
		{
			checkBox->SetChecked(value == L"true");
		}		 
	 }
	 ///////////////////////////////////////////////////////////////////////////////////////////
	 

	GridComboBoxCell::GridComboBoxCell()
	{
        ComboBoxA* comboBoxA = new ComboBoxA();
		comboBoxA->SetBorderColor(COLOR_EMPTY);
		comboBoxA->SetDisplayOffset(false);
		SetControl(comboBoxA);		
	}
	 
	GridComboBoxCell::~GridComboBoxCell()
	{
		
	}

	ComboBoxA* GridComboBoxCell::GetComboBox()
	{
		ControlA *control = GetControl();
		if (control)
		{
			return dynamic_cast<ComboBoxA*>(control);
		}
		return 0;		
	}
	
	bool GridComboBoxCell::GetBool()
	{
		ComboBoxA* comboBox = GetComboBox();
		return (comboBox && (comboBox->GetSelectedIndex() > 0));		
	}

	double GridComboBoxCell::GetDouble()
	{
		ComboBoxA* comboBox = GetComboBox();
		if(comboBox)
		{
			return comboBox->GetSelectedIndex();
		}
		return 0.0;
	}
	
	float GridComboBoxCell::GetFloat()
	{
		ComboBoxA* comboBox = GetComboBox();
		if(comboBox)
		{
			return comboBox->GetSelectedIndex();
		}
		return 0.0;		
	}
	
	int GridComboBoxCell::GetInt()
	{
		ComboBoxA* comboBox = GetComboBox();
		if(comboBox)
		{
			return comboBox->GetSelectedIndex();
		}
		return 0;		
	}
	
	_int64 GridComboBoxCell::GetLong()
	{
		ComboBoxA* comboBox = GetComboBox();
		if(comboBox)
		{
			return comboBox->GetSelectedIndex();
		}
		return 0;		
	}
	
	String GridComboBoxCell::GetString()
	{
		ComboBoxA* comboBox = GetComboBox();
		if(comboBox)
		{
			return comboBox->GetSelectedValue();
		}
		return L"";			
	}

	void GridComboBoxCell::OnAdd()
	{
		ComboBoxA* comboBox = GetComboBox();
		if(comboBox  && comboBox->GetDropDownButton())
		{
			comboBox->RegisterEvent(m_mouseDownEvent, EVENTID::MOUSEDOWN, this);
			comboBox->RegisterEvent(m_mouseMoveEvent, EVENTID::MOUSEMOVE, this);
			comboBox->RegisterEvent(m_mouseUpEvent,  EVENTID::MOUSEUP, this);
			comboBox->RegisterEvent(m_mouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		}
		GridControlCell::OnAdd();
	}

	void GridComboBoxCell::OnRemove()
	{
		ComboBoxA* comboBox = GetComboBox();
		if(comboBox  && comboBox->GetDropDownButton())
		{
			comboBox->UnRegisterEvent(m_mouseDownEvent, EVENTID::MOUSEDOWN);
			comboBox->UnRegisterEvent(m_mouseMoveEvent, EVENTID::MOUSEMOVE);
			comboBox->UnRegisterEvent(m_mouseUpEvent,  EVENTID::MOUSEUP);
			comboBox->UnRegisterEvent(m_mouseWheelEvent, EVENTID::MOUSEWHEEL);
		}
		GridControlCell::OnRemove();
	}

	void GridComboBoxCell::SetBool(bool value)
	{
		ComboBoxA* comboBox = GetComboBox();
		if (comboBox)
		{
			comboBox->SetSelectedIndex(value ? 1 : 0);
		}
	}
	
	void GridComboBoxCell::SetDouble(double value)
	{
		ComboBoxA* comboBox = GetComboBox();
		if (comboBox)
		{
			comboBox->SetSelectedIndex((int)value);
		}		
	}
	
	void GridComboBoxCell::SetFloat(float value)
	{
		ComboBoxA* comboBox = GetComboBox();
		if (comboBox)
		{
			comboBox->SetSelectedIndex((int)value);
		}	
	}
	
	void GridComboBoxCell::SetInt(int value)
	{
		ComboBoxA* comboBox = GetComboBox();
		if (comboBox)
		{
			comboBox->SetSelectedIndex((int)value);
		}			
	}
	
	void GridComboBoxCell::SetLong(_int64 value)
	{
		ComboBoxA* comboBox = GetComboBox();
		if (comboBox)
		{
			comboBox->SetSelectedIndex((int)value);
		}			
	}
	
	void GridComboBoxCell::SetString(const String& value)
	{
		ComboBoxA* comboBox = GetComboBox();
		if (comboBox)
		{
			comboBox->SetSelectedValue(value);
		}		
	}
	///////////////////////////////////////////////////////////////////////////////

	GridDateTimePickerCell::GridDateTimePickerCell()
	{
		DateTimePickerA* dateTimePickerA = new DateTimePickerA();
		dateTimePickerA->SetBorderColor(COLOR_EMPTY);
		dateTimePickerA->SetDisplayOffset(false);
		SetControl(dateTimePickerA);
	}
	
	GridDateTimePickerCell::~GridDateTimePickerCell()
	{
	}
	
	DateTimePickerA* GridDateTimePickerCell::GetDatePicker()
	{
		ControlA *control = GetControl();
		if (control)
		{
			return dynamic_cast<DateTimePickerA*>(control);
		}
		return 0;		
	}
	/////////////////////////////////////////////////////////////////////////////
	
	GridDivCell::GridDivCell()
	{
		DivA* divA = new DivA();
		divA->SetBorderColor(COLOR_EMPTY);
		divA->SetDisplayOffset(false);
		SetControl(divA);		
	}
	
	GridDivCell::~GridDivCell()
	{
		
	}
	
	DivA* GridDivCell::GetDiv()
	{
		ControlA *control = GetControl();
		if (control)
		{
			return dynamic_cast<DivA*>(control);
		}
		return 0;		
	}
	/////////////////////////////////////////////////////////////////////////////

	GridDoubleCell::GridDoubleCell()
	{
		m_value = 0;
	}
	
	GridDoubleCell::GridDoubleCell(double value)
	{
		m_value = value;
	}
	
	GridDoubleCell::~GridDoubleCell()
	{

	}

	int GridDoubleCell::CompareTo(GridCell *cell)
	{
		double value = GetDouble();
		double target = cell->GetDouble();
		if(value > target)
		{
			return 1;
		}
		if(value < target)
		{
			return -1;
		}
		return 0;
	}
	
	bool GridDoubleCell::GetBool()
	{
		return m_value != 0;
	}
	
	double GridDoubleCell::GetDouble()
	{
		return m_value;
	}
	
	float GridDoubleCell::GetFloat()
	{
		return (float)m_value;
	}

	int GridDoubleCell::GetInt()
	{
		return (int)m_value;
	}

	_int64 GridDoubleCell::GetLong()
	{
		return (_int64)m_value;
	}

	String GridDoubleCell::GetString()
	{
		return CStr::ConvertDoubleToStr(m_value);
	}
	
	void GridDoubleCell::SetBool(bool value)
	{
		m_value = value ? ((double) 1) : ((double) 0);
	}
	
	void GridDoubleCell::SetDouble(double value)
	{
		m_value = value;
	}
	
	void GridDoubleCell::SetFloat(float value)
	{
		m_value = value;
	}
	
	void GridDoubleCell::SetInt(int value)
	{
		m_value = (double)value;
	}
	
	void GridDoubleCell::SetLong(_int64 value)
	{
		m_value = (double)value;
	}
	
	void GridDoubleCell::SetString(const String& value)
	{
		m_value = CStr::ConvertStrToDouble(value);
	}
	///////////////////////////////////////////////////////////////////////////
	
	GridFloatCell::GridFloatCell()
	{
		m_value = 0;
	}

	GridFloatCell::GridFloatCell(float value)
	{
		m_value = value;
	}
	
	GridFloatCell::~GridFloatCell()
	{
		
	}
	
	int GridFloatCell::CompareTo(GridCell *cell)
	{
		float value = GetFloat();
		float target = cell->GetFloat();
		if (value > target)
		{
			return 1;
		}
		if (value < target)
		{
			return -1;
		}
		return 0;		
	}
	
	bool GridFloatCell::GetBool()
	{
		return m_value != 0;
	}
	
	double GridFloatCell::GetDouble()
	{
		return (double)m_value;
	}
	
	float GridFloatCell::GetFloat()
	{
		return m_value;
	}
	
	int GridFloatCell::GetInt()
	{
		return (int)m_value;
	}
	
	_int64 GridFloatCell::GetLong()
	{
		return(_int64)m_value;
	}
	
	String GridFloatCell::GetString()
	{
		return CStr::ConvertFloatToStr(m_value);
	}

	void GridFloatCell::SetBool(bool value)
	{
		m_value = value ? 1 : 0;
	}
	
	void GridFloatCell::SetDouble(double value)
	{
		m_value = (float)value;
	}
	
	void GridFloatCell::SetFloat(float value)
	{
		m_value = value;
	}
	
	void GridFloatCell::SetInt(int value)
	{
		m_value = (float)value;
	}
	
	void GridFloatCell::SetLong(_int64 value)
	{
		m_value = (float)value;
	}
	
	void GridFloatCell::SetString(const String& value)
	{
		m_value = CStr::ConvertStrToFloat(value);
	}

	////////////////////////////////////////////////////////////////////////////////////
	GridIntCell::GridIntCell()
	{
		m_value = 0;
	}
	GridIntCell::GridIntCell(int value)
	{
		m_value = value;
	}
	
	GridIntCell::~GridIntCell()
	{
		
	}

	int GridIntCell::CompareTo(GridCell *cell)
	{
		int value = GetInt();
		int target = cell->GetInt();
		if(value > target)
		{
			return 1;
		}
		if(value < target)
		{
			return -1;
		}
		return 0;
	}
	
	bool GridIntCell::GetBool()
	{
		return m_value != 0;
	}
	
	double GridIntCell::GetDouble()
	{
		return (double)m_value;
	}
	
	float GridIntCell::GetFloat()
	{
		return (float)m_value;
	}
	
	int GridIntCell::GetInt()
	{
		return m_value;
	}
	
	_int64 GridIntCell::GetLong()
	{
		return (_int64)m_value;
	}
	
	String GridIntCell::GetString()
	{
		return CStr::ConvertIntToStr(m_value);
	}

	void GridIntCell::SetBool(bool value)
	{
		m_value = value ? 1 : 0;
	}

	void GridIntCell::SetDouble(double value)
	{
		m_value = (int)value;
	}

	void GridIntCell::SetFloat(float value)
	{
		m_value = (int)value;
	}
	void GridIntCell::SetInt(int value)
	{
		m_value = (int)value;
	}
	void GridIntCell::SetLong(_int64 value)
	{
		m_value = (int)value;
	}
	void GridIntCell::SetString(const String& value)
	{
		m_value = CStr::ConvertStrToInt(value);
	}
	////////////////////////////////////////////////////////////////////////////////////

	GridLabelCell::GridLabelCell()
	{
		LabelA* labelA = new LabelA();
		labelA->SetBorderColor(COLOR_EMPTY);
		labelA->SetDisplayOffset(false);
		SetControl(labelA);
	}

	GridLabelCell:: ~GridLabelCell()
	{
	}

	LabelA* GridLabelCell::GetLabel()
	{
		ControlA *control = GetControl();
		if (control)
		{
			return dynamic_cast<LabelA*>(control);
		}
		return 0;
	}
	
	////////////////////////////////////////////////////////////////////////////////////

	GridLongCell::GridLongCell()
	{
		m_value = 0;
	}
	
	GridLongCell::GridLongCell(_int64 value)
	{
		m_value = value;
	}

	GridLongCell::~GridLongCell()
	{
	}

	int GridLongCell::CompareTo(GridCell *cell)
	{
	    _int64 value = GetLong();
        _int64 target = cell->GetLong();
        if (value > target)
        {
            return 1;
        }
        if (value < target)
        {
            return -1;
        }
        return 0;
	}
	
	bool GridLongCell::GetBool()
	{
		return m_value != 0;
	}
	
	double GridLongCell::GetDouble()
	{
		return (double)m_value;
	}
	
	float GridLongCell::GetFloat()
	{
		return (float)m_value;
	}
	
	int GridLongCell::GetInt()
	{
		return (int)m_value;
	}
	
	_int64 GridLongCell::GetLong()
	{
		return m_value;
	}

	String GridLongCell::GetString()
	{
		return CStr::ConvertLongToStr(m_value);
	}
	
	void GridLongCell::SetBool(bool value)
	{
		m_value = value ? 1 : 0;
	}
	
	void GridLongCell::SetDouble(double value)
	{
		m_value = (_int64)value;
	}
	
	void GridLongCell::SetFloat(float value)
	{
		m_value = (_int64)value;
	}
	
	void GridLongCell::SetInt(int value)
	{
		m_value = (_int64)value;
	}
	
	void GridLongCell::SetLong(_int64 value)
	{
		m_value = (_int64)value;
	}
	
	void GridLongCell::SetString(const String& value)
	{
		m_value = CStr::ConvertStrToLong(value);
	}
	///////////////////////////////////////////////////////////////////////////////////

	GridRadioButtonCell::GridRadioButtonCell()
	{
		RadioButtonA* radioButtonA = new RadioButtonA();
		radioButtonA->SetBorderColor(COLOR_EMPTY);
		radioButtonA->SetDisplayOffset(false);
		SetControl(radioButtonA);		
	}
	
	GridRadioButtonCell::~GridRadioButtonCell()
	{
		
	}
	
	RadioButtonA* GridRadioButtonCell::GetRadioButton()
	{
		ControlA *control = GetControl();
		if (control)
		{
			return dynamic_cast<RadioButtonA*>(control);
		}
		return NULL;		
	}

	bool GridRadioButtonCell::GetBool()
	{
		RadioButtonA* radioButton = GetRadioButton();
		return (radioButton && radioButton->IsChecked());
	}
	
	double GridRadioButtonCell::GetDouble()
	{
		RadioButtonA* radioButton = GetRadioButton();
		if(radioButton)
		{
			return radioButton->IsChecked() ? 1 : 0;
		}
		return 0;
	}
	
	float GridRadioButtonCell::GetFloat()
	{
		RadioButtonA* radioButton = GetRadioButton();
		if(radioButton)
		{
			return radioButton->IsChecked() ? 1 : 0;
		}
		return 0;
	}
	
	int GridRadioButtonCell::GetInt()
	{
		RadioButtonA* radioButton = GetRadioButton();
		if(radioButton)
		{
			return radioButton->IsChecked() ? 1 : 0;
		}
		return 0;
	}
	
	_int64 GridRadioButtonCell::GetLong()
	{
		RadioButtonA* radioButton = GetRadioButton();
		if(radioButton)
		{
			return radioButton->IsChecked() ? 1 : 0;
		}
		return 0;		
	}
	
	String GridRadioButtonCell::GetString()
	{
		RadioButtonA* radioButton = GetRadioButton();
		if (!radioButton)
		{
			return L"false";
		}
		if (!radioButton->IsChecked())
		{
			return L"false";
		}
		return L"true";		
	}
	
	void GridRadioButtonCell::SetBool(bool value)
	{
		RadioButtonA* radioButton = GetRadioButton();
		if(radioButton)
		{
			radioButton->SetChecked(value);
		}
	}

	void GridRadioButtonCell::SetDouble(double value)
	{
		RadioButtonA* radioButton = GetRadioButton();
		if(radioButton)
		{
			radioButton->SetChecked(value > 0);
		}
	}

	void GridRadioButtonCell::SetFloat(float value)
	{
		RadioButtonA* radioButton = GetRadioButton();
		if(radioButton)
		{
			radioButton->SetChecked(value > 0);
		}
	}

	void GridRadioButtonCell::SetInt(int value)
	{
		RadioButtonA* radioButton = GetRadioButton();
		if(radioButton)
		{
			radioButton->SetChecked(value > 0);
		}
	}

	void GridRadioButtonCell::SetLong(_int64 value)
	{
		RadioButtonA* radioButton = GetRadioButton();
		if(radioButton)
		{
			radioButton->SetChecked(value > 0);
		}
	}

	void GridRadioButtonCell::SetString(const String& value)
	{
		RadioButtonA* radioButton = GetRadioButton();
		if(radioButton)
		{
			radioButton->SetChecked(value == L"true");
		}
	}
	////////////////////////////////////////////////////////////////////

	GridSpinCell::GridSpinCell()
	{
		SpinA* spinA = new SpinA();
		spinA->SetBorderColor(COLOR_EMPTY);
		spinA->SetDisplayOffset(false);
		SetControl(spinA);
	}
	
	GridSpinCell::~GridSpinCell()
	{
	
	}
	
	SpinA* GridSpinCell::GetSpin()
	{
		ControlA* control = GetControl();
		if (control)
        {
			return dynamic_cast<SpinA*>(control);
        }
        return 0;	
	}
	
	bool GridSpinCell::GetBool()
	{
		SpinA* spin = GetSpin();
		if(spin)
		{
			return spin->GetValue() > 0;
		}
		return false;
	}
	
	double GridSpinCell::GetDouble()
	{
		SpinA* spin = GetSpin();
		if(spin)
		{
			return spin->GetValue();
		}		
		return 0;
	}
	
	float GridSpinCell::GetFloat()
	{
		SpinA* spin = GetSpin();
		if(spin)
		{
			return (float)spin->GetValue();
		}		
		return 0;		
	}
	
	int GridSpinCell::GetInt()
	{
		SpinA* spin = GetSpin();
		if(spin)
		{
			return (int)spin->GetValue();
		}		
		return 0;		
	}
	
	_int64 GridSpinCell::GetLong()
	{
		SpinA* spin = GetSpin();
		if(spin)
		{
			return (_int64)spin->GetValue();
		}		
		return 0;			
	}
	
	void GridSpinCell::SetBool(bool value)
	{
		SpinA* spin = GetSpin();
		if(spin)
		{
			spin->SetValue(value ? 1 : 0);
		}			
	}
	
	void GridSpinCell::SetDouble(double value)
	{
		SpinA* spin = GetSpin();
		if(spin)
		{
			spin->SetValue(value);
		}			
	}
	
	void GridSpinCell::SetFloat(float value)
	{
		SpinA* spin = GetSpin();
		if(spin)
		{
			spin->SetValue(value);
		}
	}
	
	void GridSpinCell::SetInt(int value)
	{
		SpinA* spin = GetSpin();
		if(spin)
		{
			spin->SetValue(value);
		}
	}
	
	void GridSpinCell::SetLong(_int64 value)
	{
		SpinA* spin = GetSpin();
		if(spin)
		{
			spin->SetValue(value);
		}
	}
	///////////////////////////////////////////////////////////////

	GridStringCell::GridStringCell()
	{
		m_value = L"";
	}
	
	GridStringCell::GridStringCell(const String& value)
	{
		m_value = value;
	}
	
	GridStringCell::~GridStringCell()
	{

	}

	int GridStringCell::CompareTo(GridCell *cell)
	{
		String value = cell->GetString();
		String target = GetString();
		if (target.size() > 0)
		{
			return target.compare(value);
		}
		return -1;
	}

	bool GridStringCell::GetBool()
	{
		return false;
	}

	double GridStringCell::GetDouble()
	{
		return 0;
	}

	float GridStringCell::GetFloat()
	{
		return 0;
	}

	int GridStringCell::GetInt()
	{
		return 0;
	}

	_int64 GridStringCell::GetLong()
	{
		return 0;
	}

	String GridStringCell::GetString()
	{
		return m_value;
	}

	void GridStringCell::SetString(const String& value)
	{
		m_value = value;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GridPasswordCell::GridPasswordCell()
	{
	}

	GridPasswordCell:: ~GridPasswordCell()
	{
	}

	String GridPasswordCell::GetPaintText()
	{
		return L"******";
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GridTextBoxCell::GridTextBoxCell()
	{
        TextBoxA* textBoxA = new TextBoxA();
        textBoxA->SetBorderColor(COLOR_EMPTY);
        textBoxA->SetDisplayOffset(false);
        SetControl(textBoxA);		
	}
	
	GridTextBoxCell:: ~GridTextBoxCell()
	{
		
	}
	
	TextBoxA* GridTextBoxCell::GetTextBox()
	{
		ControlA *control = GetControl();
		if (control)
		{
			return dynamic_cast<TextBoxA*>(control);
		}
		return 0;	
	}
}