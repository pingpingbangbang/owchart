#include "..\\stdafx.h"
#include "..\\include\\Base\\WinHost.h"
#include "..\\include\\TextBox\\DateTimePicker.h"
#include "..\\include\\Layout\\SplitLayoutDiv.h"
#include "..\\include\\TabControl\\TabPage.h"
#include "..\\include\\TextBox\\ComboBox.h"
#include "..\\include\\Grid\\Grid.h"
using namespace OwLib;

SIZE WinHost::GetClientSize()
{
	int cx = 0;
	int cy = 0;
	if (m_native)
	{
		RECT rc;
		::GetClientRect(m_hWnd, &rc);
		cx = rc.right - rc.left;
		cy = rc.bottom - rc.top;
	}
	SIZE sz = {cx, cy};
	return sz;
}

WinHost::WinHost()
{
	m_allowOperate = true;
	m_allowPartialPaint = true;
	m_hImc = 0;
	m_hWnd = 0;
	m_invokeSerialID = 0;
	m_native = 0;
	m_pInvokeMsgID = 1025;
	m_toolTip = 0;
	::InitializeCriticalSection(&_csLock);
}

WinHost::~WinHost()
{
	if (m_toolTip)
	{
		m_native->RemoveControl(m_toolTip);
		delete m_toolTip;
	}
	m_toolTip = 0;
	m_hImc = 0;
	m_hWnd = 0;
	m_native = 0;
	::DeleteCriticalSection(&_csLock);
}

HWND WinHost::GetHWnd()
{
	return m_hWnd;
}

void WinHost::SetHWnd( HWND hWnd )
{
	m_hWnd = hWnd;
	m_hImc = ImmGetContext(m_hWnd);
	if(m_native){
		m_native->OnResize();
	}
}

NativeBase* WinHost::GetNative()
{
	return m_native;
}

void WinHost::SetNative( NativeBase *native )
{
	m_native = native;
}

int WinHost::GetPInvokeMsgID()
{
	return m_pInvokeMsgID;
}

void WinHost::SetPInvokeMsgID( int pInvokeMsgID )
{
	m_pInvokeMsgID = pInvokeMsgID;
}

ControlA* WinHost::GetToolTip()
{
	return m_toolTip;
}

void WinHost::SetToolTip( ControlA *toolTip )
{
	m_toolTip = toolTip;
}

void WinHost::ActiveMirror()
{
	if (m_native->GetMirrorMode() != MirrorMode_None)
	{
		vector<ControlA*> controls = m_native->GetControls();
		int count = (int)controls.size();
		for (int i = 0; i < count; i++)
		{
			ControlA *control = controls[i];
			if (control->GetNative() != m_native)
			{
				control->SetNative(m_native);
			}
		}
	}
}

bool WinHost::AllowOperate()
{
	return m_allowOperate;
}

bool WinHost::AllowPartialPaint()
{
	return m_allowPartialPaint;
}

void WinHost::BeginInvoke( ControlA *control, void *args )
{
	Lock();
	m_invokeArgs[m_invokeSerialID] = args;
	m_invokeControls[m_invokeSerialID] = control;
	UnLock();
	HWND hWnd = m_hWnd;
	if (m_native->GetMirrorMode() != MirrorMode_None)
	{
		WinHost *host = dynamic_cast<WinHost*>(m_native->GetMirrorHost()->GetHost());
		hWnd = host->GetHWnd();
	}
	SendMessage(hWnd, m_pInvokeMsgID, m_invokeSerialID, 0);
	m_invokeSerialID++;
}

void WinHost::Copy( string text )
{
    if (::OpenClipboard(m_hWnd))
    {
		if((int)text.length() > 0)
		{
			::EmptyClipboard();
			size_t cbStr = (text.length() + 1) * sizeof(wchar_t);

			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, cbStr); 

			if (hMem == NULL) 
			{
				CloseClipboard();
				return; 
			}

			char * lpDest = (char *)GlobalLock(hMem);
			strcpy_s(lpDest, cbStr, text.c_str());

			GlobalUnlock(hMem); 

			UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR))?CF_UNICODETEXT:CF_TEXT;

			if(SetClipboardData(uiFormat, hMem) == NULL)
			{
				CloseClipboard();
				return;
			}
			CloseClipboard();
		}
    }
}

ControlA* WinHost::CreateInternalControl( ControlA *parent, const String& clsid )
{
	CalendarA *calendar = dynamic_cast<CalendarA*>(parent);
	if (calendar)
	{
		if (clsid == L"datetitle")
		{
			return new DateTitle(calendar);
		}
		if (clsid == L"headdiv")
		{
			HeadDiv *div = new HeadDiv(calendar);
			div->SetWidth(parent->GetWidth());
			div->SetDock(DockStyleA_Top);
			return div;
		}
		if (clsid == L"lastbutton")
		{
			return new ArrowButton(calendar);
		}
		if (clsid == L"nextbutton")
		{
			ArrowButton *button = new ArrowButton(calendar);
			button->SetToLast(false);
			return button;
		}
	}
	
	if (dynamic_cast<SplitLayoutDivA*>(parent) && (clsid == L"splitter"))
	{
		ButtonA *na = new ButtonA();
		SIZE sz = {5, 5};
		na->SetSize(sz);
		return na;
	}
	if (dynamic_cast<ScrollBarA*>(parent))
	{
		if (clsid == L"addbutton")
		{
			ButtonA *na2 = new ButtonA();
			SIZE sz = {15, 15};
			na2->SetSize(sz);
			return na2;
		}
		if (clsid == L"backbutton")
		{
			return new ButtonA();
		}
		if (clsid == L"scrollbutton")
		{
			ButtonA *na3 = new ButtonA();
			na3->SetAllowDrag(true);
			return na3;
		}
		if (clsid == L"reducebutton")
		{
			ButtonA *na4 = new ButtonA();
			SIZE sz = {15, 15};
			na4->SetSize(sz);
			return na4;
		}
	}
	if (dynamic_cast<TabPageA*>(parent) && (clsid == L"headerbutton"))
	{
		ButtonA *buttonA = new ButtonA();
		buttonA->SetAllowDrag(true);
		SIZE sz = {100, 20};
		buttonA->SetSize(sz);
		return buttonA;
	}
	ComboBoxA *comboBoxA = dynamic_cast<ComboBoxA*>(parent);
	if (comboBoxA)
	{
		if (clsid == L"dropdownbutton")
		{
			ButtonA *buttonA6 = new ButtonA();
			buttonA6->SetDisplayOffset(false);
			int width = comboBoxA->GetWidth();
			int height = comboBoxA->GetHeight();
			POINT point = {width - 16, 0};
			buttonA6->SetLocation(point);
			SIZE size2 = {16, height};
			buttonA6->SetSize(size2);
			return buttonA6;
		}
		if (clsid == L"dropdownmenu")
		{
			ComboBoxMenu *menu = new ComboBoxMenu();
			menu->SetComboBox(comboBoxA);
			menu->SetPopup(true);
			SIZE size3 = {100, 200};
			menu->SetSize(size3);
			return menu;
		}
	}
	DateTimePickerA *ra3 = dynamic_cast<DateTimePickerA*>(parent);
	if (ra3)
	{
		if (clsid == L"dropdownbutton")
		{
			ButtonA *buttonA7 = new ButtonA();
			buttonA7->SetDisplayOffset(false);
			int width = ra3->GetWidth();
			int cy = ra3->GetHeight();
			POINT point2 = {width - 16, 0};
			buttonA7->SetLocation(point2);
			SIZE size4 = {16, cy};
			buttonA7->SetSize(size4);
			return buttonA7;
		}
		if (clsid == L"dropdownmenu")
		{
			MenuA *ua = new MenuA();
			ua->SetPadding(PADDING(1));
			ua->SetPopup(true);
			SIZE size5 = {200, 200};
			ua->SetSize(size5);
			return ua;
		}
	}
	if (dynamic_cast<SpinA*>(parent))
	{
		if (clsid == L"downbutton")
		{
			ButtonA *na9 = new ButtonA();
			na9->SetDisplayOffset(false);
			SIZE size6 = {16, 16};
			na9->SetSize(size6);
			return na9;
		}
		if (clsid == L"upbutton")
		{
			ButtonA *na10 = new ButtonA();
			na10->SetDisplayOffset(false);
			SIZE size7 = {16, 16};
			na10->SetSize(size7);
			return na10;
		}
	}
	if (dynamic_cast<DivA*>(parent))
	{
		if (clsid == L"hscrollbar")
		{
			HScrollBarA *ra4 = new HScrollBarA();
			ra4->SetVisible(false);
			SIZE sz = {15, 15};
			ra4->SetSize(sz);
			return ra4;
		}
		if (clsid == L"vscrollbar")
		{
			VScrollBarA *ra5 = new VScrollBarA();
			ra5->SetVisible(false);
			SIZE sz = {15, 15};
			ra5->SetSize(sz);
			return ra5;
		}
	}
	if (dynamic_cast<GridA*>(parent) && (clsid == L"edittextbox"))
	{
		return new TextBoxA();
	}
	return 0;
}

std::string WinHost::GetAppPath()
{
	char exeFullPath[MAX_PATH]; 
	string strPath = "";
	GetModuleFileNameA(0, exeFullPath, MAX_PATH);
	strPath = (string)exeFullPath; 
	int pos = (int)strPath.rfind('\\', strPath.length());
	return strPath.substr(0, pos);
}

CursorsA WinHost::GetCursor()
{
	if (m_hWnd)
	{
		HCURSOR cursor = ::GetCursor();
		if (!cursor || (cursor == ::LoadCursor(0, IDC_ARROW)))
		{
			return CursorsA_Arrow;
		}
		if (cursor == ::LoadCursor(0, IDC_APPSTARTING))
		{
			return CursorsA_AppStarting;
		}
		if (cursor == ::LoadCursor(0, IDC_CROSS))
		{
			return CursorsA_Cross;
		}
		if (cursor == ::LoadCursor(0, IDC_HAND))
		{
			return CursorsA_Hand;
		}
		if (cursor == ::LoadCursor(0, IDC_HELP))
		{
			return CursorsA_Help;
		}
		if (cursor == ::LoadCursor(0, IDC_IBEAM))
		{
			return CursorsA_IBeam;
		}
		if (cursor == ::LoadCursor(0, IDC_NO))
		{
			return CursorsA_No;
		}
		if (cursor == ::LoadCursor(0, IDC_SIZEALL))
		{
			return CursorsA_SizeAll;
		}
		if (cursor == ::LoadCursor(0, IDC_SIZENESW))
		{
			return CursorsA_SizeNESW;
		}
		if (cursor == ::LoadCursor(0, IDC_SIZENS))
		{
			return CursorsA_SizeNS;
		}
		if (cursor == ::LoadCursor(0, IDC_SIZENWSE))
		{
			return CursorsA_SizeNWSE;
		}
		if (cursor == ::LoadCursor(0, IDC_SIZEWE))
		{
			return CursorsA_SizeWE;
		}
		if (cursor == ::LoadCursor(0, IDC_UPARROW))
		{
			return CursorsA_UpArrow;
		}
		if (cursor == ::LoadCursor(0, IDC_WAIT))
		{
			return CursorsA_WaitCursor;
		}
	}
	return CursorsA_Arrow;
}

int WinHost::GetIntersectRect( LPRECT lpDestRect, const RECT *lpSrc1Rect, const RECT *lpSrc2Rect )
{
	return IntersectRect(lpDestRect, lpSrc1Rect, lpSrc2Rect);
}

POINT WinHost::GetMousePoint()
{
	int x = 0;
	int y = 0;
	if (m_hWnd)
	{
		POINT point = {0, 0};
		GetCursorPos(&point);
		ScreenToClient(m_hWnd, &point);
		x = point.x;
		y = point.y;
		if (m_native->AllowScaleSize())
		{
			SIZE clientSize = GetClientSize();
			if (clientSize.cx > 0 && clientSize.cy > 0)
			{
				SIZE scaleSize = m_native->GetScaleSize();
				x = (x * scaleSize.cx) / clientSize.cx;
				y = (y * scaleSize.cy) / clientSize.cy;
			}
		}
	}
	POINT pt = {x, y};
	return pt;
}

SIZE WinHost::GetSize()
{
	if (m_native->AllowScaleSize())
	{
		return m_native->GetScaleSize();
	}
	return GetClientSize();
}

int WinHost::GetUnionRect( LPRECT lpDestRect, const RECT *lpSrc1Rect, const RECT *lpSrc2Rect )
{
	return UnionRect(lpDestRect, lpSrc1Rect, lpSrc2Rect);
}

void WinHost::Lock()
{
	::EnterCriticalSection(&_csLock);
}

void WinHost::Invalidate()
{
	if (m_hWnd)
	{
		RECT rc;
		SIZE size = GetClientSize();
		rc.left = 0;
		rc.top = 0;
		rc.right = size.cx;
		rc.bottom = size.cy;
		InvalidateRect(m_hWnd, &rc, FALSE);
	}
}

void WinHost::Invalidate( const RECT& rect )
{
	if (m_allowPartialPaint)
	{
		HDC dc = GetDC(m_hWnd);
		OnPaint(dc, rect);
		::ReleaseDC(m_hWnd, dc);
	}
	else
	{
		Invalidate();
	}
}

void WinHost::Invoke( ControlA *control, void *args )
{
	Lock();
	m_invokeArgs[m_invokeSerialID] = args;
	m_invokeControls[m_invokeSerialID] = control;
	UnLock();
	HWND hWnd = m_hWnd;
	if (m_native->GetMirrorMode() != MirrorMode_None)
	{
		WinHost *host = dynamic_cast<WinHost*>(m_native->GetMirrorHost()->GetHost());
		hWnd = host->GetHWnd();
	}
	PostMessage(hWnd, m_pInvokeMsgID, m_invokeSerialID, 0);
	m_invokeSerialID++;
}

bool WinHost::IsKeyPress( char key )
{
	int num = GetKeyState(key) & 0x8000;
	return num != 0;
}

void WinHost::OnInvoke( int invokeSerialID )
{
	void *args = 0;
	ControlA *la = 0;
	Lock();
	if (m_invokeArgs.find(invokeSerialID) != m_invokeArgs.end())
	{
		args = m_invokeArgs[invokeSerialID];
		m_invokeArgs.erase(invokeSerialID);
	}
	if (m_invokeControls.find(invokeSerialID) != m_invokeControls.end())
	{
		la = m_invokeControls[invokeSerialID];
		m_invokeControls.erase(invokeSerialID);
		m_invokeArgs[m_invokeSerialID] = la;
	}
	UnLock();
	if (la != 0)
	{
		la->OnInvoke(args);
	}
}

int WinHost::OnMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_native)
	{
		if (message == WM_IME_SETCONTEXT && (int)wParam == 1)
		{
			ImmAssociateContext(m_hWnd, m_hImc);
		}
		if (message == m_pInvokeMsgID)
		{
			OnInvoke((int)wParam);
		}
		switch (message)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			{
				if(m_allowOperate)
				{
					char keyData = (int)wParam;
					if (m_native->OnPreviewsKeyEvent(EVENTID::KEYDOWN, keyData))
					{
						return 1;
					}
					m_native->OnKeyDown(keyData);
				}
				return 0;
			}
		case WM_KEYUP:
		case WM_SYSKEYUP:
			if (m_allowOperate)
			{
				char keyData = (int)wParam;
				m_native->OnKeyUp(keyData);
			}
			break;
		case 5:
			if((int)wParam != 1)
			{
				m_native->OnResize();
			}
			break;

		case WM_CHAR:
			{
				char keyData = (int)wParam;
				if (m_allowOperate && m_native->OnChar(keyData))
				{
					return 1;
				}
				return 0;
			}
		case WM_ERASEBKGND:
			return 1;

		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				BeginPaint(m_hWnd, &ps);
				SIZE displaySize = m_native->GetDisplaySize();
				RECT clipRect = { 0, 0, displaySize.cx, displaySize.cy };
				HDC hdc = ::GetDC(m_hWnd); 
				OnPaint(hdc, clipRect);

				EndPaint(m_hWnd, &ps);
				return 1;
			}
		case WM_MOUSEMOVE:
			if (m_allowOperate)
			{
				m_native->OnMouseMove(MouseButtonsA_Left, 1, 0);
			}
			break;

		case WM_LBUTTONDOWN:
			if (m_allowOperate)
			{
				ActiveMirror();
				m_native->OnMouseDown(MouseButtonsA_Left, 1, 0);
			}
			break;

		case WM_LBUTTONUP:
			if (m_allowOperate)
			{
				m_native->OnMouseUp(MouseButtonsA_Left, 1, 0);
			}
			break;

		case WM_LBUTTONDBLCLK:
			if (m_allowOperate)
			{
				m_native->OnMouseDown(MouseButtonsA_Left, 2, 0);
				m_native->OnDoubleClick(MouseButtonsA_Left, 2, 0);
			}
			break;

		case WM_RBUTTONDOWN:
			if (m_allowOperate)
			{
				ActiveMirror();
				m_native->OnMouseDown(MouseButtonsA_Right, 1, 0);
			}
			break;

		case WM_RBUTTONUP:
			if (m_allowOperate)
			{
				m_native->OnMouseUp(MouseButtonsA_Right, 1, 0);
			}
			break;

		case WM_RBUTTONDBLCLK:
			if (m_allowOperate)
			{
				m_native->OnMouseDown(MouseButtonsA_Right, 2, 0);
				m_native->OnDoubleClick(MouseButtonsA_Right, 2, 0);
			}
			break;

		case WM_MOUSEWHEEL:
			if (m_allowOperate)
			{
				m_native->OnMouseWheel(MouseButtonsA_None, 0, (int) wParam);
			}
			break;

		case WM_IME_CHAR:
			if ((m_allowOperate && (int)wParam == 1) && m_native->GetFocusedControl())
			{
				int dwBufLen = ImmGetCompositionString(m_hImc, 8, NULL, 0) + 2;
				char *buffer = new char[dwBufLen];
				memset(buffer, 0, dwBufLen);
				ImmGetCompositionString(m_hImc, GCS_RESULTSTR, buffer, dwBufLen);
			}
			break;

		case WM_TIMER:
			if (m_hWnd && hWnd == m_hWnd)
			{
				m_native->OnTimer((int) wParam);
			}
			break;
		}
	}
	return 0;
}

void WinHost::OnPaint( HDC hDC, const RECT& clipRect )
{
	Lock();
	if (m_hWnd != 0)
	{
		SIZE displaySize = m_native->GetDisplaySize();
		double scaleFactorX = 1.0;
		double scaleFactorY = 1.0;
		SIZE clientSize = GetClientSize();
		if (m_native->AllowScaleSize() && clientSize.cx > 0 && clientSize.cy > 0)
		{
			SIZE scaleSize = m_native->GetScaleSize();
			scaleFactorX = ((double) clientSize.cx) / ((double) scaleSize.cx);
			scaleFactorY = ((double) clientSize.cy) / ((double) scaleSize.cy);
		}
		m_native->GetPaint()->SetScaleFactor(scaleFactorX, scaleFactorY);
		RECT rc = {0, 0, clientSize.cx, clientSize.cy};
		m_native->GetPaint()->BeginPaint(hDC, rc, clipRect);
		m_native->OnPaint(clipRect);
		m_native->GetPaint()->EndPaint();
	}
	UnLock();
}

string WinHost::Paste()
{
	string text = "";
	UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;
	if(::OpenClipboard(m_hWnd) && ::IsClipboardFormatAvailable(uiFormat))
    {
        HGLOBAL hMem = GetClipboardData(uiFormat); 
        if (hMem != NULL) 
        { 
            LPCTSTR lpStr = (LPCTSTR)GlobalLock(hMem); 
            if (lpStr != NULL) 
            { 
				CStr::wstringTostring(text, lpStr);
            } 
            GlobalUnlock(hMem);
		} 
		CloseClipboard();
    }
	return text;
}

void WinHost::SetAllowOperate( bool allowOperate )
{
	m_allowOperate = allowOperate;
}

void WinHost::SetAllowPartialPaint( bool allowPartialPaint )
{
	m_allowPartialPaint = allowPartialPaint;
}

void WinHost::SetCursor( CursorsA cursor )
{
	if (m_hWnd != 0)
	{
		switch (cursor)
		{
		case CursorsA_Arrow:
			::SetCursor(::LoadCursorW(NULL, IDC_ARROW));
			return;

		case CursorsA_AppStarting:
			::SetCursor(::LoadCursorW(NULL, IDC_APPSTARTING));
			return;

		case CursorsA_Cross:
			::SetCursor(::LoadCursorW(NULL, IDC_CROSS));
			return;

		case CursorsA_Hand:
			::SetCursor(::LoadCursorW(NULL, IDC_HAND));
			return;

		case CursorsA_Help:
			::SetCursor(::LoadCursorW(NULL, IDC_HELP));
			return;

		case CursorsA_IBeam:
			::SetCursor(::LoadCursorW(NULL, IDC_IBEAM));
			return;

		case CursorsA_No:
			::SetCursor(::LoadCursorW(NULL, IDC_NO));
			return;

		case CursorsA_SizeAll:
			::SetCursor(::LoadCursorW(NULL, IDC_SIZEALL));
			return;

		case CursorsA_SizeNESW:
			::SetCursor(::LoadCursorW(NULL, IDC_SIZENESW));
			return;

		case CursorsA_SizeNS:
			::SetCursor(::LoadCursorW(NULL, IDC_SIZENS));
			return;

		case CursorsA_SizeNWSE:
			::SetCursor(::LoadCursorW(NULL, IDC_SIZENWSE));
			return;

		case CursorsA_SizeWE:
			::SetCursor(::LoadCursorW(NULL, IDC_SIZEWE));
			return;

		case CursorsA_UpArrow:
			::SetCursor(::LoadCursorW(NULL, IDC_UPARROW));
			return;

		case CursorsA_WaitCursor:
			::SetCursor(::LoadCursorW(NULL, IDC_WAIT));
			break;
		}
	}
}

void WinHost::ShowToolTip(void *sender, const wstring& text, const POINT& mp)
{
	if (m_toolTip)
	{
		m_toolTip->SetLocation(mp);
		m_toolTip->SetNative(m_native);
		m_toolTip->SetLocation(mp);
		m_toolTip->SetText(text);
		m_toolTip->Show();
	}
}

void WinHost::StartTimer( int timerID, int interval )
{
	HWND hWnd = m_hWnd;
	if (m_native->GetMirrorMode() != MirrorMode_None)
	{
		WinHost *host = dynamic_cast<WinHost*>(m_native->GetMirrorHost()->GetHost());
		hWnd = host->GetHWnd();
	}
	SetTimer(hWnd, timerID, interval, 0);
}

void WinHost::StopTimer( int timerID )
{
	HWND hWnd = m_hWnd;
	if (m_native->GetMirrorMode() != MirrorMode_None)
	{
		WinHost *host = dynamic_cast<WinHost*>(m_native->GetMirrorHost()->GetHost());
		hWnd = host->GetHWnd();
	}
	KillTimer(hWnd, timerID);
}

void WinHost::UnLock()
{
	::LeaveCriticalSection(&_csLock);
}