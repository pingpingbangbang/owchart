/**
*  @file
*  @copyright defined in owchart/LICENSE
*/

#ifndef __COMBOBOX_H__
#define __COMBOBOX_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "TextBox.h"
#include "..\\Button\\Button.h"
#include "..\\Menu\\Menu.h"
#include "..\\Menu\\MenuItem.h"

namespace OwLib
{
	class  ComboBoxA;

	class  ComboBoxMenu : public MenuA
	{
	protected:
		ComboBoxA *m_comboBox;
	public:
		ComboBoxMenu();
		virtual ~ComboBoxMenu();
		ComboBoxA* GetComboBox();
		void SetComboBox(ComboBoxA *comboBox);
		virtual bool OnAutoHide();
	};

	class  ComboBoxA : public TextBoxA
	{
	protected:
		ButtonA* m_dropDownButton;
		ControlMouseEvent m_dropDownButtonMouseDownEvent;
		MenuItemMouseEvent m_menuItemClickEvent;
		ControlKeyEvent m_menuKeyDownEvent;
		ComboBoxMenu* m_dropDownMenu;
		static void DropDownButtonMouseDown(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
		static void MenuItemClick(void *sender, MenuItemA *item, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
		static void MenuKeyDown(void *sender, char key, void *pInvoke);
	public:
		ComboBoxA();
		virtual ~ComboBoxA();
		virtual ButtonA* GetDropDownButton();
		virtual ComboBoxMenu* GetDropDownMenu();
		virtual int GetSelectedIndex();
		virtual void SetSelectedIndex(int selectedIndex);
		virtual wstring GetSelectedText();
		virtual void SetSelectedText(const wstring& selectedText);
		virtual wstring GetSelectedValue();
		virtual void SetSelectedValue(const wstring& selectedValue);
	public:
		void AddItem(MenuItemA *item);
		void ClearItems();
		virtual wstring GetControlType();
		virtual vector<wstring> GetEventNames();
		vector<MenuItemA*> GetItems();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		void InsertItem(int index, MenuItemA *item);
		virtual void OnDropDownOpening();
		virtual void OnKeyDown(char key);
		virtual void OnLoad();
		virtual void OnSelectedIndexChanged();
		virtual void OnMouseWheel(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		void RemoveItem(MenuItemA *item);
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}

#endif