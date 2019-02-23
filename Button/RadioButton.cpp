#include "..\\stdafx.h"
#include "..\\include\\Button\\RadioButton.h"
using namespace OwLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RadioButtonA::RadioButtonA()
{
	 m_groupName = L"";
}

RadioButtonA::~RadioButtonA()
{
}

String RadioButtonA::GetGroupName()
{
	return m_groupName;
}

void RadioButtonA::SetGroupName(const String& groupName)
{
	m_groupName = groupName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String RadioButtonA::GetControlType()
{
	return L"RadioButton";
}

void RadioButtonA::GetProperty(const String& name, String *value, String *type)
{
	if (name == L"groupname")
	{
		*type = L"text";
		*value = GetGroupName();
	}
	else
	{
		CheckBoxA::GetProperty(name, value, type);
	}
}

vector<String> RadioButtonA::GetPropertyNames()
{
	vector<String> propertyNames = ButtonA::GetPropertyNames();
	propertyNames.push_back(L"GroupName");
	return propertyNames;
}

void RadioButtonA::OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
	if (!IsChecked())
	{
		SetChecked(!IsChecked());
	}
	CheckBoxA::CallMouseEvents(EVENTID::CLICK, mp, button, clicks, delta);
	Invalidate();
}

void RadioButtonA::OnPaintCheckButton(CPaint *paint, const RECT& clipRect)
{
	String paintingBackImage = GetPaintingBackImage();
	if ((int)paintingBackImage.length() > 0)
	{
		paint->DrawImage(paintingBackImage.c_str(), clipRect);
	}
	else
	{
		if (IsChecked())
		{
			RECT rect = { clipRect.left + 2, clipRect.top + 2, clipRect.right - 3, clipRect.bottom - 3};
			if (clipRect.right - clipRect.left < 4 || clipRect.bottom - clipRect.top < 4)
			{
				rect = clipRect;
			}
			paint->FillEllipse(GetPaintingButtonBackColor(), rect);
		}
		paint->DrawEllipse(GetPaintingButtonBorderColor(), 1, 0, clipRect);
	}
}

void RadioButtonA::SetProperty(const String& name, const String& value)
{
	if (name == L"groupname")
	{
		SetGroupName(value);
	}
	else
	{
		CheckBoxA::SetProperty(name, value);
	}
}

void RadioButtonA::Update()
{
	if (IsChecked())
	{
		vector<ControlA*> controls;
		if (GetParent())
		{
			controls = GetParent()->GetControls();
		}
		else
		{
			controls = GetNative()->GetControls();
		}
		int count = (int)controls.size();
		for (int i = 0; i < count; i++)
		{
			RadioButtonA *radioButton = dynamic_cast<RadioButtonA*>(controls[i]);
			if ((radioButton && radioButton != this) 
				&& (radioButton->GetGroupName() == GetGroupName() && radioButton->IsChecked()))
			{
				radioButton->SetChecked(false);
				radioButton->Invalidate();
			}
		}
	}
}