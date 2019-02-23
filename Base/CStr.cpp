#include "..\\stdafx.h"
#include "..\\include\\Base\\CStr.h"
#include "..\\include\\Base\\CMathLib.h"
using namespace OwLib;

double CStr::round( double x )
{
	int sa = 0, si = 0;  
	if(x == 0.0)   
	{
		return 0.0; 
	}
	else    
	{
		if(x > 0.0)  
		{
			sa = (int)x;   
			si = (int)(x + 0.5);        
			if(sa == floor((double)si))   
			{
				return sa;    
			}
			else     
			{
				return sa + 1; 
			}
		}       
		else    
		{
			sa = (int)x;   
			si = (int)(x - 0.5);      
			if(sa == ceil((double)si))  
			{
				return sa;       
			}
			else         
			{
				return sa - 1;      
			}
		}
	}
}

void CStr::Contact( wchar_t *str, const wchar_t *str1, const wchar_t *str2, const wchar_t *str3 )
{
	*str = 0;
	lstrcatW(str, str1);
	if(lstrlenW(str2) > 0){
		lstrcatW(str, str2);
	}
	if(lstrlenW(str3) > 0){
		lstrcatW(str, str3);
	}
} 

String CStr::ConvertAnchorToStr( const ANCHOR& anchor )
{
	vector<String> list;
	if (anchor.left)
	{
		list.push_back(L"Left");
	}
	if (anchor.top)
	{
		list.push_back(L"Top");
	}
	if (anchor.right)
	{
		list.push_back(L"Right");
	}
	if (anchor.bottom)
	{
		list.push_back(L"Bottom");
	}
	String str;
	int count = (int)list.size();
	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			str = str + list[i];
			if (i != count - 1)
			{
				str = str + L",";
			}
		}
		return str;
	}
	return L"None";
}

String CStr::ConvertBoolToStr( bool value )
{
	if (!value)
	{
		return L"False";
	}
	return L"True";
}

String CStr::ConvertColorToStr( _int64 color )
{
	if (color == COLOR_EMPTY)
	{
		return L"Empty";
	}
	if (color == COLOR_CONTROL)
	{
		return L"Control";
	}
	if (color == COLOR_CONTROLBORDER)
	{
		return L"ControlBorder";
	}
	if (color == COLOR_CONTROLTEXT)
	{
		return L"ControlText";
	}
	if (color == COLOR_DISABLEDCONTROL)
	{
		return L"DisabledControl";
	}
	if (color == COLOR_DISABLEDCONTROLTEXT)
	{
		return L"DisabledControlText";
	}
	int a = 0;
	int r = 0;
	int g = 0;
	int b = 0;
	COLOR::ToARGB(0, color, &a, &r, &g, &b);
	if (a == 0xff)
	{
		wchar_t buff[64] = {0};
		swprintf_s(buff, L"%d,%d,%d", r, g, b);
		return buff;
	}
	wchar_t buff[64] = {0};
	swprintf_s(buff, L"%d,%d,%d,%d", a, r, g, b);
	return buff;
}

String CStr::ConvertContentAlignmentToStr( ContentAlignmentA contentAlignment )
{
	String str;
	if (contentAlignment == ContentAlignmentA_BottomCenter)
	{
		return L"BottomCenter";
	}
	if (contentAlignment == ContentAlignmentA_BottomLeft)
	{
		return L"BottomLeft";
	}
	if (contentAlignment == ContentAlignmentA_BottomRight)
	{
		return L"BottomRight";
	}
	if (contentAlignment == ContentAlignmentA_MiddleCenter)
	{
		return L"MiddleCenter";
	}
	if (contentAlignment == ContentAlignmentA_MiddleLeft)
	{
		return L"MiddleLeft";
	}
	if (contentAlignment == ContentAlignmentA_MiddleRight)
	{
		return L"MiddleRight";
	}
	if (contentAlignment == ContentAlignmentA_TopCenter)
	{
		return L"TopCenter";
	}
	if (contentAlignment == ContentAlignmentA_TopLeft)
	{
		return L"TopLeft";
	}
	if (contentAlignment == ContentAlignmentA_TopRight)
	{
		str = L"TopRight";
	}
	return str;
}

String CStr::ConvertCursorToStr( CursorsA cursor )
{
	String str;
	if (cursor == CursorsA_AppStarting)
	{
		return L"AppStarting";
	}
	if (cursor == CursorsA_Arrow)
	{
		return L"Arrow";
	}
	if (cursor == CursorsA_Cross)
	{
		return L"Cross";
	}
	if (cursor == CursorsA_Hand)
	{
		return L"Hand";
	}
	if (cursor == CursorsA_Help)
	{
		return L"Help";
	}
	if (cursor == CursorsA_IBeam)
	{
		return L"IBeam";
	}
	if (cursor == CursorsA_No)
	{
		return L"NO";
	}
	if (cursor == CursorsA_SizeAll)
	{
		return L"SizeAll";
	}
	if (cursor == CursorsA_SizeNESW)
	{
		return L"SizeNESW";
	}
	if (cursor == CursorsA_SizeNS)
	{
		return L"SizeNS";
	}
	if (cursor == CursorsA_SizeNWSE)
	{
		return L"SizeNWSE";
	}
	if (cursor == CursorsA_SizeWE)
	{
		return L"SizeWE";
	}
	if (cursor == CursorsA_UpArrow)
	{
		return L"UpArrow";
	}
	if (cursor == CursorsA_WaitCursor)
	{
		str = L"WaitCursor";
	}
	return str;
}

String CStr::ConvertDockToStr( DockStyleA dock )
{
	String str;
	if (dock == DockStyleA_Bottom)
	{
		return L"Bottom";
	}
	if (dock == DockStyleA_Fill)
	{
		return L"Fill";
	}
	if (dock == DockStyleA_Left)
	{
		return L"Left";
	}
	if (dock == DockStyleA_None)
	{
		return L"None";
	}
	if (dock == DockStyleA_Right)
	{
		return L"Right";
	}
	if (dock == DockStyleA_Top)
	{
		str = L"Top";
	}
	return str;
}

String CStr::ConvertDoubleToStr( double value )
{
	wchar_t buff[256] = {0};
	swprintf_s(buff, 255, L"%f", value);
	return buff;
}

String CStr::ConvertFloatToStr( float value )
{
	wchar_t buff[256] = {0};
	swprintf_s(buff, 255, L"%f", value);
	return buff;
}

String CStr::ConvertFontToStr( FONT *font )
{
	vector<String> list;
	list.push_back(font->m_fontFamily);
	list.push_back(ConvertFloatToStr(font->m_fontSize));
	if (font->m_bold)
	{
		list.push_back(L"Bold");
	}
	if (font->m_underline)
	{
		list.push_back(L"UnderLine");
	}
	if (font->m_italic)
	{
		list.push_back(L"Italic");
	}
	if (font->m_strikeout)
	{
		list.push_back(L"Strikeout");
	}
	String str;
	int count = (int)list.size();
	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			str = str + list[i];
			if (i != count - 1)
			{
				str = str + L",";
			}
		}
	}
	return str;
}

String CStr::ConvertHorizontalAlignToStr( HorizontalAlignA horizontalAlign )
{
	if (horizontalAlign == HorizontalAlignA_Center)
	{
		return L"Center";
	}
	if (horizontalAlign == HorizontalAlignA_Right)
	{
		return L"Right";
	}
	if (horizontalAlign == HorizontalAlignA_Inherit)
	{
		return L"Inherit";
	}
	if (horizontalAlign == HorizontalAlignA_Left)
	{
		return L"Left";
	}
	return L"";
}

String CStr::ConvertIntToStr( int value )
{
	wchar_t buff[32] = {0};
	swprintf_s(buff, 31, L"%d", value);
	return buff;
}

String CStr::ConvertLongToStr( _int64 value )
{
	wchar_t buff[32] = {0};
	swprintf_s(buff, 31, L"%I64d", value);
	return buff;
}

String CStr::ConvertLayoutStyleToStr( LayoutStyleA layoutStyle )
{
	if (layoutStyle == LayoutStyleA_BottomToTop)
	{
		return L"BottomToTop";
	}
	if (layoutStyle == LayoutStyleA_LeftToRight)
	{
		return L"LeftToRight";
	}
	if (layoutStyle == LayoutStyleA_None)
	{
		return L"None";
	}
	if (layoutStyle == LayoutStyleA_RightToLeft)
	{
		return L"RightToLeft";
	}
	if (layoutStyle == LayoutStyleA_TopToBottom)
	{
		return L"TopToBottom";
	}
	return L"";
}

String CStr::ConvertPaddingToStr( const PADDING& padding )
{
	wchar_t buff[128] = {0};
	swprintf_s(buff, 127, L"%d,%d,%d,%d", padding.left, padding.top, padding.right, padding.bottom);
	return buff;
}

String CStr::ConvertPointToStr( const POINT& mp )
{
	wchar_t buff[128] = {0};
	swprintf_s(buff, 127, L"%d,%d", mp.x, mp.y);
	return buff;
}

String CStr::ConvertRectToStr( const RECT& rect )
{
	wchar_t buff[128] = {0};
	swprintf_s(buff, 127, L"%d,%d,%d,%d", rect.left, rect.top, rect.right, rect.bottom);
	return buff;
}

String CStr::ConvertSizeToStr( const SIZE& size )
{
	wchar_t buff[128] = {0};
	swprintf_s(buff, 127, L"%d,%d", size.cx, size.cy);
	return buff;
}

ANCHOR CStr::ConvertStrToAnchor( const String& str )
{
	String str1 = CStr::ToLower(str);
	bool left = false;
	bool top = false;
	bool right = false;
	bool bottom = false;
	vector<String> vec = CStr::Split(str1, L",");
	for(vector<String>::iterator iter = vec.begin(); iter != vec.end(); iter++)
	{
		String str2 = *iter;
		if(str2 == L"left")
		{
			left = true;
		}
		else if(str2 == L"top")
		{
			top = true;
		}
		else if(str2 == L"right")
		{
			right = true;
		}
		else if(str2 == L"bottom")
		{
			bottom = true;
		}
	}
	ANCHOR anchor(left, top, right, bottom);
	return anchor;
}

bool CStr::ConvertStrToBool( const String& str )
{
	String str1 = CStr::ToLower(str);
	if (str1 != L"true")
	{
		return false;
	}
	return true;
}

_int64 CStr::ConvertStrToColor( const String& str )
{
	String str1 = CStr::ToLower(str);
	if (str1 != L"empty")
	{
		if (str1 == L"control")
		{
			return COLOR_CONTROL;
		}
		if (str1 == L"controlborder")
		{
			return COLOR_CONTROLBORDER;
		}
		if (str1 == L"controltext")
		{
			return COLOR_CONTROLTEXT;
		}
		if (str1 == L"disabledcontrol")
		{
			return COLOR_DISABLEDCONTROL;
		}
		if (str1 == L"disabledcontroltext")
		{
			return COLOR_DISABLEDCONTROLTEXT;
		}

		vector<String> strArray = CStr::Split(str1, L",");
		int result = 255;
		int r = 255;
		int g = 255;
		int b = 255;
		if (strArray.size() == 3)
		{
			r = _wtoi(strArray[0].c_str());
			g = _wtoi(strArray[1].c_str());
			b = _wtoi(strArray[2].c_str());
			return (_int64)COLOR::ARGB(r, g, b);
		}
		if (strArray.size() == 4)
		{
			result = _wtoi(strArray[0].c_str());
			r = _wtoi(strArray[1].c_str());
			g = _wtoi(strArray[2].c_str());
			b = _wtoi(strArray[3].c_str());
			return (_int64)COLOR::ARGB(result, r, g, b);
		}
	}
	return COLOR_EMPTY;
}

ContentAlignmentA CStr::ConvertStrToContentAlignment( const String& str )
{
	String str1 = CStr::ToLower(str);
	ContentAlignmentA middleCenter = ContentAlignmentA_MiddleCenter;
	if (str1 == L"bottomcenter")
	{
		return ContentAlignmentA_BottomCenter;
	}
	if (str1 == L"bottomleft")
	{
		return ContentAlignmentA_BottomLeft;
	}
	if (str1 == L"bottomright")
	{
		return ContentAlignmentA_BottomRight;
	}
	if (str1 == L"middlecenter")
	{
		return ContentAlignmentA_MiddleCenter;
	}
	if (str1 == L"middleleft")
	{
		return ContentAlignmentA_MiddleLeft;
	}
	if (str1 == L"middleright")
	{
		return ContentAlignmentA_MiddleRight;
	}
	if (str1 == L"topcenter")
	{
		return ContentAlignmentA_TopCenter;
	}
	if (str1 == L"topleft")
	{
		return ContentAlignmentA_TopLeft;
	}
	if (str1 == L"topright")
	{
		middleCenter = ContentAlignmentA_TopRight;
	}
	return middleCenter;
}

CursorsA CStr::ConvertStrToCursor( const String& str )
{
	String str1 = CStr::ToLower(str);
	CursorsA arrow = CursorsA_Arrow;
	if (str1 == L"appstarting")
	{
		return CursorsA_AppStarting;
	}
	if (str1 == L"cross")
	{
		return CursorsA_Cross;
	}
	if (str1 == L"hand")
	{
		return CursorsA_Hand;
	}
	if (str1 == L"help")
	{
		return CursorsA_Help;
	}
	if (str1 == L"ibeam")
	{
		return CursorsA_IBeam;
	}
	if (str1 == L"no")
	{
		return CursorsA_No;
	}
	if (str1 == L"sizeall")
	{
		return CursorsA_SizeAll;
	}
	if (str1 == L"sizenesw")
	{
		return CursorsA_SizeNESW;
	}
	if (str1 == L"sizens")
	{
		return CursorsA_SizeNS;
	}
	if (str1 == L"sizenwse")
	{
		return CursorsA_SizeNWSE;
	}
	if (str1 == L"sizewe")
	{
		return CursorsA_SizeWE;
	}
	if (str1 == L"uparrow")
	{
		return CursorsA_UpArrow;
	}
	if (str1 == L"waitcursor")
	{
		arrow = CursorsA_WaitCursor;
	}
	return arrow;
}

DockStyleA CStr::ConvertStrToDock( const String& str )
{
	String str1 = CStr::ToLower(str);
	DockStyleA none = DockStyleA_None;
	if (str1 == L"bottom")
	{
		return DockStyleA_Bottom;
	}
	if (str1 == L"fill")
	{
		return DockStyleA_Fill;
	}
	if (str1 == L"left")
	{
		return DockStyleA_Left;
	}
	if (str1 == L"right")
	{
		return DockStyleA_Right;
	}
	if (str1 == L"top")
	{
		none = DockStyleA_Top;
	}
	return none;
}

double CStr::ConvertStrToDouble( const String& str )
{
	return _wtof(str.c_str());
}

double CStr::ConvertStrToDouble( const wchar_t *str )
{
	return _wtof(str);
}

float CStr::ConvertStrToFloat( const String& str )
{
	return (float)_wtof(str.c_str());
}

FONT* CStr::ConvertStrToFont( const String& str )
{
	vector<String> strArray = CStr::Split(str, L",");
	int length = (int)strArray.size();
	String fontFamily = L"SimSun";
	float fontSize = 12;
	bool bold = false;
	bool underline = false;
	bool italic = false;
	bool strikeout = false;
	if (length >= 1)
	{
		fontFamily = strArray[0];
	}
	if (length >= 2)
	{
		fontSize = CStr::ConvertStrToFloat(strArray[1]);
	}
	for (int i = 2; i < length; i++)
	{
		String str2 = CStr::ToLower(strArray[i]);
		if(str2 == L"bold")
		{
			bold = true;
		}
		else if(str2 == L"underline")
		{
			underline = true;
		}
		else if(str2 == L"italic")
		{
			italic = true;
		}
		else if(str2 == L"strikeout")
		{
			strikeout = true;
		}
	}
	FONT* font = new FONT(fontFamily, fontSize, bold, underline, italic, strikeout);
	return font;
}

HorizontalAlignA CStr::ConvertStrToHorizontalAlign( const String& str )
{
	String str1 = CStr::ToLower(str);
	HorizontalAlignA center = HorizontalAlignA_Center;
	if (str1 == L"right")
	{
		return HorizontalAlignA_Right;
	}
	if (str1 == L"inherit")
	{
		return HorizontalAlignA_Inherit;
	}
	if (str1 == L"left")
	{
		center = HorizontalAlignA_Left;
	}
	return center;
}

int CStr::ConvertStrToInt( const String& str )
{
	return _wtoi(str.c_str());
}

int CStr::ConvertStrToInt( const wchar_t *str )
{
	return _wtoi(str);
}

LayoutStyleA CStr::ConvertStrToLayoutStyle( const String& str )
{
	String str1 = CStr::ToLower(str);
	LayoutStyleA none = LayoutStyleA_None;
	if (str1 == L"bottomtotop")
	{
		return LayoutStyleA_BottomToTop;
	}
	if (str1 == L"lefttoright")
	{
		return LayoutStyleA_LeftToRight;
	}
	if (str1 == L"righttoleft")
	{
		return LayoutStyleA_RightToLeft;
	}
	if (str1 == L"toptobottom")
	{
		none = LayoutStyleA_TopToBottom;
	}
	return none;
}

_int64 CStr::ConvertStrToLong( const String& str )
{
	return _wtol(str.c_str());
}

_int64 CStr::ConvertStrToLong( const wchar_t *str )
{
	return _wtol(str);
}

PADDING CStr::ConvertStrToPadding( const String& str )
{
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;
	vector<String> strArray = CStr::Split(str, L",");
	if (strArray.size() == 4)
	{
		left = _wtoi(strArray[0].c_str());
		top = _wtoi(strArray[1].c_str());
		right = _wtoi(strArray[2].c_str());
		bottom = _wtoi(strArray[3].c_str());
	}
	PADDING padding(left, top, right, bottom);
	return padding; 
}

POINT CStr::ConvertStrToPoint( const String& str )
{
	int x = 0;
	int y = 0;
	vector<String> strArray = CStr::Split(str, L",");
	if (strArray.size() == 2)
	{
		x = _wtoi(strArray[0].c_str());
		y = _wtoi(strArray[1].c_str());
	}
	POINT point = {x, y};
	return point;
}

RECT CStr::ConvertStrToRect( const String& str )
{
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;
	vector<String> strArray = CStr::Split(str, L",");
	if (strArray.size() == 4)
	{
		left = _wtoi(strArray[0].c_str());
		top = _wtoi(strArray[1].c_str());
		right = _wtoi(strArray[2].c_str());
		bottom = _wtoi(strArray[3].c_str());
	}
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
	return rect;
}

SIZE CStr::ConvertStrToSize( const String& str )
{
	int cx = 0;
	int cy = 0;
	vector<String> strArray = CStr::Split(str, L",");
	if (strArray.size() == 2)
	{
		cx = _wtoi(strArray[0].c_str());
		cy = _wtoi(strArray[1].c_str());
	}
	SIZE size;
	size.cx = cx;
	size.cy = cy;
	return size;
}

VerticalAlignA CStr::ConvertStrToVerticalAlign( const String& str )
{
	String str1 = CStr::ToLower(str);
	VerticalAlignA middle = VerticalAlignA_Middle;
	if (str1 == L"bottom")
	{
		return VerticalAlignA_Bottom;
	}
	if (str1 == L"inherit")
	{
		return VerticalAlignA_Inherit;
	}
	if (str1 == L"top")
	{
		middle = VerticalAlignA_Top;
	}
	return middle;
}

String CStr::ConvertVerticalAlignToStr( VerticalAlignA verticalAlign )
{
	String str = L"";
	if (verticalAlign == VerticalAlignA_Bottom)
	{
		return L"Bottom";
	}
	if (verticalAlign == VerticalAlignA_Inherit)
	{
		return L"Inherit";
	}
	if (verticalAlign == VerticalAlignA_Middle)
	{
		return L"Middle";
	}
	if (verticalAlign == VerticalAlignA_Top)
	{
		str = L"Top";
	}
	return str;
}

std::string CStr::GetGuid()
{
	char buffer[64] = {0};
	GUID guid;

	if (S_OK == ::CoCreateGuid(&guid))
	{
		_snprintf(buffer, sizeof(buffer),
		"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	}
	return buffer;
}

void CStr::GetValueByDigit( double value, int digit, wchar_t *str )
{
	if(!_isnan(value))
	{
		if(digit == 0)
		{
			double newValue = round(value);
			if(abs(newValue - value) < 1.0)
			{
				value = newValue;
			}
		}
		switch(digit)
		{
		case 0:
			swprintf_s(str, 99, L"%d", (int)value);
			break;
		case 1:
			swprintf_s(str, 99, L"%.f", value);
			break;
		case 2:
			swprintf_s(str, 99, L"%.2f", value);
			break;
		case 3:
			swprintf_s(str, 99, L"%.3f", value);
			break;
		case 4:
			swprintf_s(str, 99, L"%.4f", value);
			break;
		case 5:
			swprintf_s(str, 99, L"%.5f", value);
			break;
		case 6:
			swprintf_s(str, 99, L"%.6f", value);
			break;
		case 7:
			swprintf_s(str, 99, L"%.7f", value);
			break;
		case 8:
			swprintf_s(str, 99, L"%.8f", value);
			break;
		case 9:
			swprintf_s(str, 99, L"%.9f", value);
			break;
		}
		str = 0;
	}
}

void CStr::GetFormatDate( double date, wchar_t *str )
{
	int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, msecond = 0;
	CMathLib::M130(date, &year, &month, &day, &hour, &minute, &second, &msecond);
	if(hour > 0)
	{
		swprintf_s(str, 99, L"%02d:%02d:", hour, minute);
	}
	else
	{
		swprintf_s(str, 99, L"%04d-%02d-%02d", year, month, day);
	}
}

String CStr::GetFormatDate( const String& format, int year, int month, int day, int hour, int minute, int second )
{
	String result = format;
	static wchar_t strYear[100] = {0};
	static wchar_t strMonth[100] = {0};
	static wchar_t strDay[100] = {0};
	static wchar_t strHour[100] = {0};
	static wchar_t strMinute[100] = {0};
	static wchar_t strSecond[100] = {0};
	swprintf_s(strYear, L"%d", year);
	swprintf_s(strMonth, L"%02d", month);
	swprintf_s(strDay, L"%02d", day);
	swprintf_s(strHour, L"%d", hour);
	swprintf_s(strMinute, L"%02d", minute);
	swprintf_s(strSecond, L"%02d", second);
	if((int)format.find(L"yyyy") != -1)
	{
		result = Replace(result, L"yyyy", strYear);
	}
	if((int)format.find(L"MM") != -1)
	{
		result = Replace(result, L"MM", strMonth);
	}
	if((int)format.find(L"dd") != -1)
	{
		result = Replace(result, L"dd", strDay);
	}
	if((int)format.find(L"HH") != -1)
	{
		result = Replace(result, L"HH", strHour);
	}
	if((int)format.find(L"mm") != -1)
	{
		result = Replace(result, L"mm", strMinute);
	}
	if((int)format.find(L"ss") != -1)
	{
		result = Replace(result, L"ss", strSecond);
	}
	return result;
}

int CStr::HexToDec(const char *str, int length)
{
	int rslt = 0;  
	for (int i = 0; i < length; i++)  
	{  
		rslt += (str[i]) << (8 * (length - 1 - i));  

	}  
	return rslt;  
}

bool CStr::IsBlank(int c)
{
	if((c == ' ') || (c == '\t'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int CStr::IsNumeric(const string& str)
{
	if (str == "") 
	{
		return 0;  
	}
	int size = (int)str.size();
	int count = 0;
	int base = 10;  
	char *ptr = new char[size + 1];
	strcpy(ptr, str.c_str());
	
	int type = 0;
	while (IsBlank(*ptr)) 
	{  
		ptr++;  
	}  

	if (*ptr == '-' || *ptr == '+') 
	{
		ptr++;  
	}  
	if (isdigit(*ptr) || ptr[0]=='.') 
	{  
		if (ptr[0]!='.') 
		{
			if (ptr[0] == '0' && ptr[1] && (ptr[1] == 'x' || ptr[1] == 'X')) 
			{
				type = 2;  
				base = 16;  
				ptr += 2;  
			}
			while (*ptr == '0')
			{  
				ptr++;  
			}
			while (isdigit(*ptr) || (base == 16 && isxdigit(*ptr)))
			{  
				ptr++;  
			}  
		}  

		if (base == 10 && *ptr && ptr[0] == '.')
		{  
			type = 3;  
			ptr++;  
		}  
		while (type == 3 && base == 10 && isdigit(*ptr)) 
		{  
			ptr++;  
		}  

		if (*ptr == 0)
		{
			type = (type >0 ) ? type : 1;
		}
		else 
		{
			type = 0;
		}
	}
	return type;
}

String CStr::Replace( const String& str, const String& src, const String& dest )
{
	String newStr = str;
	String::size_type pos = 0;
	while( (pos = newStr.find(src, pos)) != string::npos )
	{
		newStr.replace(pos, src.length(), dest);
		pos += dest.length();
	}
	return newStr;
}

vector<String> CStr::Split( const String& str, const String& pattern )
{
	int pos = -1;
	vector<String> result;
	String newStr = str;
	newStr += pattern;
	int size = (int)str.size();
	for(int i = 0; i < size; i++)
	{
		pos = (int)newStr.find(pattern, i);
		if((int)pos <= size)
		{
			String s = newStr.substr(i, pos - i);
			if(s.length() > 0)
			{
				result.push_back(s);
			}
			i = pos + (int)pattern.size() - 1;
		}
	}
	return result;
}

vector<wstring> CStr::Split(const wstring& str, const vector<wstring>& patterns)
{
	int pos = -1;
	vector<String> result;
	int pattenSize = (int)patterns.size();
	if (pattenSize == 0)
	{
		result.push_back(str);
		return result;
	}
	int i = 0;
	int strSize = (int)str.size();
	while (i != strSize)
	{
		int flag = 0;
		while (i != strSize && flag == 0)
		{
			flag = 1;
			for (int x = 0; x < pattenSize; ++x)
			{
				String patten = patterns[x];
				if (str[i] == patten[0])
				{
					++i;
					flag = 0;
					break;
				}
			}
		}
		flag = 0;
		int j = i;
		while (j != strSize && flag == 0)
		{
			for (int x = 0; x < pattenSize; ++x)
			{
				String patten = patterns[x];
				if (str[j] == patten[0])
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				++j;
			}
		}
		if (i != j)
		{
			result.push_back(str.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

void CStr::stringTowstring( String &strDest, const string& strSrc )
{
	int  unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, strSrc.c_str(), -1, 0, 0);
	wchar_t *pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode,0,(unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, strSrc.c_str(), - 1, (LPWSTR)pUnicode, unicodeLen);
	strDest = ( wchar_t* )pUnicode;
	delete[] pUnicode;
}

String CStr::ToLower( const String& str )
{
	String lowerStr = str;
	transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), tolower);
	return lowerStr;
}

String CStr::ToUpper( const String& str )
{
	String upperStr = str;
	transform(upperStr.begin(), upperStr.end(), upperStr.begin(), toupper);
	return upperStr;
}

void CStr::wstringTostring( string &strDest, const String& strSrc )
{
	int iTextLen = WideCharToMultiByte(CP_ACP, 0, strSrc.c_str(), -1, NULL, 0, NULL, NULL);
	char *pElementText = new char[iTextLen + 1];
	memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	::WideCharToMultiByte(CP_ACP, 0, strSrc.c_str(), - 1, pElementText, iTextLen, 0, 0);
	strDest = pElementText;
	delete[] pElementText;
}

bool CStr::ValueEqual( const float &lhs, const float &rhs )
{
	return lhs - rhs >= -0.000001 && lhs - rhs <= 0.000001;
}

bool CStr::ValueEqual( const double &lhs, const double &rhs )
{
	return lhs - rhs >= -0.000001 && lhs - rhs <= 0.000001;
}


bool CStr::startswith(const string& str, const string& start)
{
	int srclen = (int)str.size();
	int startlen = (int)start.size();
	if(srclen >= startlen)
	{
		string temp = str.substr(0, startlen);
		if(temp == start)
		{
			return true;
		}
	}
	return false;
}

bool CStr::startswith(const wstring& wstr, const wstring& wstart)
{
	if((int)wstr.find(wstart) == 0)
	{
		return true;
	}
	return false;
}

bool CStr::endswith(const string& str, const string& end)
{
	int srclen = (int)str.size();
	int endlen = (int)end.size();
	if(srclen >= endlen)
	{
		string temp = str.substr(srclen - endlen, endlen);
		if(temp == end)
		{
			return true;
		}
	}
	return false;
}

bool CStr::endswith(const wstring& wstr, const wstring& wend)
{	
	int srclen = (int)wstr.size();
	int endlen = (int)wend.size();
	if(srclen >= endlen)
	{
		String temp = wstr.substr(srclen - endlen, endlen);
		if(temp == wend)
		{
			return true;
		}
	}
	return false;
}

string CStr::trim(const string& str)
{    
	string ret;
	string::size_type pos_begin = str.find_first_not_of(" \t");
	if(pos_begin == string::npos)
	{
		return str;
	}
	string::size_type pos_end = str.find_last_not_of(" \t");
	if(pos_end == string::npos)
	{
		return str;
	}
	ret = str.substr(pos_begin, pos_end-pos_begin);
	return ret;
}

wstring CStr::trim(const wstring& wstr)
{
	string str = "";
	CStr::wstringTostring(str, wstr);
	string result = CStr::trim(str);
	String wResult = L"";
	CStr::stringTowstring(wResult, result);
	return wResult;
}