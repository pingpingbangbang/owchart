#include "..\\stdafx.h"
#include "..\\include\\Base\\Control.h"
using namespace OwLib;

void ControlA::CallEvents( int eventID )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlEvent func = (ControlEvent)(*list)[i];
			if (func != 0)
			{
				func(this, (*listInvoke)[i]);
			}
		}
	}
}

void ControlA::CallInvokeEvents( int eventID, void *args )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlInvokeEvent func = (ControlInvokeEvent)(*list)[i];
			if (func != 0)
			{
				func(this, args, (*listInvoke)[i]);
			}
		}
	}
}

void ControlA::CallKeyEvents( int eventID, char key )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlKeyEvent func = (ControlKeyEvent)(*list)[i];
			if (func != 0)
			{
				func(this, key, (*listInvoke)[i]);
			}
		}
	}
}

void ControlA::CallMouseEvents( int eventID, const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlMouseEvent func = (ControlMouseEvent)(*list)[i];
			if (func != 0)
			{
				func(this, mp, button, clicks, delta, (*listInvoke)[i]);
			}
		}
	}
}

void ControlA::CallPaintEvents( int eventID, CPaint *paint, const RECT& clipRect )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlPaintEvent func = (ControlPaintEvent)(*list)[i];
			if (func != 0)
			{
				func(this, paint, clipRect, (*listInvoke)[i]);
			}
		}
	}
}

void ControlA::CallTimerEvents( int eventID, int timerID )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlTimerEvent func = (ControlTimerEvent)(*list)[i];
			if (func != 0)
			{
				func(this, timerID, (*listInvoke)[i]);
			}
		}
	}
}

void ControlA::CallTouchEvents( int eventID, vector<CTouch> *touches )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlTouchEvent func = (ControlTouchEvent)(*list)[i];
			if (func != 0)
			{
				func(this, touches, (*listInvoke)[i]);
			}
		}
	}
}

_int64 ControlA::GetPaintingBackColor()
{
	if ((m_backColor == COLOR_EMPTY) || COLOR_DISABLEDCONTROL != COLOR_EMPTY || !IsPaintEnabled(this))
	{
		return m_backColor;
	}
	else
	{
		return COLOR_DISABLEDCONTROL;
	}
}

String ControlA::GetPaintingBackImage()
{
	return m_backImage;
}

_int64 ControlA::GetPaintingBorderColor()
{
	return m_borderColor;
}

_int64 ControlA::GetPaintingForeColor()
{
	if (m_foreColor == COLOR_CONTROLTEXT || COLOR_DISABLEDCONTROLTEXT == COLOR_EMPTY || IsPaintEnabled(this))
	{
		return m_foreColor;
	}
	else
	{
		return COLOR_DISABLEDCONTROLTEXT;
	}
}

static int m_timerID = 10000;
ControlA::ControlA()
{
	m_align = HorizontalAlignA_Left;
	m_allowDrag = false;
	m_allowPreviewsEvent = false;
	m_autoEllipsis = false;
	m_autoShowToolTip = false;
	m_autoSize = false;
	m_anchor = ANCHOR(true, true, false, false);
	m_backColor = COLOR_CONTROL;
	m_backImage = L"";
	m_borderColor = COLOR_CONTROLBORDER;
	m_canFocus = true;
	m_canRaiseEvents = true;
	m_cursor = CursorsA_Arrow;
	m_displayOffset = true;
	m_dock = DockStyleA_None;
	m_enabled = true;
	m_focused = 0;
	m_font = new FONT(L"Î¢ÈíÑÅºÚ", 14, false, false, false);
	m_foreColor = COLOR_CONTROLTEXT;
	m_hasPopupMenu = false;
	m_isDragging = false;
	m_isWindow = false;
	m_location.x = 0;
	m_location.y = 0;
	m_maximumSize.cx = 100000;
	m_maximumSize.cy = 100000;
	m_minimumSize.cx = 0;
	m_minimumSize.cy = 0;
	m_margin.left = 0;
	m_margin.top = 0;
	m_margin.right = 0;
	m_margin.bottom = 0;
	m_name = L"";
	m_native = 0;
	m_oldLocation.x = 0;
	m_oldLocation.y = 0;
	m_oldSize.cx = 0;
	m_oldSize.cy = 0;
	m_opacity = 1.0f;
	m_padding = PADDING(0);
	m_parent = 0;
	m_percentLocation = 0;
	m_percentSize = 0;
	m_region.bottom = 0;
	m_region.left = 0;
	m_region.right = 0;
	m_region.top = 0;
	m_resourcePath = L"";
	m_size.cx = 0;
	m_size.cy = 0;
	m_tabIndex = 0;
	m_tabStop = false;
	m_tag = 0;
	m_text = L"";
	m_topMost = false;
	m_useRegion = false;
	m_verticalAlign = VerticalAlignA_Top;
	m_visible = true;
}

ControlA::~ControlA()
{	
	if(m_font)
	{
		delete m_font;
		m_font = 0;
	}
	map<int, vector<void*>*>::iterator sIterEvents = m_events.begin();
	for(; sIterEvents != m_events.end(); ++sIterEvents)
	{
		vector<void*>::iterator sIterInner = sIterEvents->second->begin();
		for(; sIterInner !=  sIterEvents->second->end(); ++sIterInner)
		{
			*sIterInner = 0;
		}
		sIterEvents->second->clear();
		delete sIterEvents->second;
		sIterEvents->second = 0;
	}
	m_events.clear();

	map<int, vector<void*>*>::iterator sIterInvokes = m_invokes.begin();
	for(; sIterInvokes != m_invokes.end(); ++sIterInvokes)
	{
		sIterInvokes->second->clear();
		delete sIterInvokes->second;
		sIterInvokes->second = 0;
	}
	m_invokes.clear();

	if(m_parent)
	{
		delete m_parent;
		m_parent = 0;
	}
	if(m_percentLocation)
	{
		delete m_percentLocation;
		m_percentLocation = 0;
	}
	ClearControls();
	m_native = 0;
	m_parent = 0;
}

HorizontalAlignA ControlA::GetAlign()
{
	return m_align;
}

void ControlA::SetAlign( HorizontalAlignA align )
{
	m_align = align;
}

bool ControlA::AllowDrag()
{
	return m_allowDrag;
}

void ControlA::SetAllowDrag( bool allowDrag )
{
	m_allowDrag = allowDrag;
}

bool ControlA::AllowPreviewsEvent()
{
	return m_allowPreviewsEvent;
}

void ControlA::SetAllowPreviewsEvent( bool allowPreviewsEvent )
{
	m_allowPreviewsEvent = allowPreviewsEvent;
}

ANCHOR ControlA::GetAnchor()
{
	return m_anchor;
}

void ControlA::SetAnchor( const ANCHOR& anchor )
{
	m_anchor = anchor;
}

bool ControlA::AutoEllipsis()
{
	return m_autoEllipsis;
}

void ControlA::SetAutoEllipsis( bool autoEllipsis )
{
	m_autoEllipsis = autoEllipsis;
}

bool ControlA::AutoSize()
{
	return m_autoSize;
}

void ControlA::SetAutoSize( bool autoSize )
{
	if (m_autoSize != autoSize)
	{
		m_autoSize = autoSize;
		OnAutoSizeChanged();
	}
}

_int64 ControlA::GetBackColor()
{
	return m_backColor;
}

void ControlA::SetBackColor( _int64 backColor )
{
	if (m_backColor != backColor)
	{
		m_backColor = backColor;
		OnBackColorChanged();
	}
}

String ControlA::GetBackImage()
{
	return m_backImage;
}

void ControlA::SetBackImage( const String& backImage )
{
	if (m_backImage != backImage)
	{
		m_backImage = backImage;
		OnBackImageChanged();
	}
}

_int64 ControlA::GetBorderColor()
{
	return m_borderColor;
}

void ControlA::SetBorderColor( _int64 borderColor )
{
	m_borderColor = borderColor;
}

int ControlA::GetBottom()
{
	return GetTop() + GetHeight();
}

RECT ControlA::GetBounds()
{
	RECT rect = {GetLeft(), GetTop(), GetRight(), GetBottom()};
	return rect;
}

void ControlA::SetBounds( const RECT& rect )
{
	POINT pt = {rect.left, rect.top};
	SetLocation(pt);
	SIZE sz = {rect.right - rect.left, rect.bottom - rect.top};
	SetSize(sz);
}

bool ControlA::CanFocus()
{
	return m_canFocus;
}

void ControlA::SetCanFocus( bool canFocus )
{
	m_canFocus = canFocus;
}

bool ControlA::CanRaiseEvents()
{
	return m_canRaiseEvents;
}

void ControlA::SetCanRaiseEvents( bool canRaiseEvents )
{
	m_canRaiseEvents = canRaiseEvents;
}

bool ControlA::IsCapture()
{
	if (m_native)
	{
		if ((m_native->GetHoveredControl() == this) || (m_native->GetPushedControl() == this))
		{
			return true;
		}
	}
	return false;
}

CursorsA ControlA::GetCursor()
{
	return m_cursor;
}

void ControlA::SetCursor( CursorsA cursor )
{
	m_cursor = cursor;
}

bool ControlA::DisplayOffset()
{
	return m_displayOffset;
}

void ControlA::SetDisplayOffset( bool displayOffset )
{
	m_displayOffset = displayOffset;
}

RECT ControlA::GetDisplayRect()
{
	if (m_useRegion)
	{
		return m_region;
	}
	RECT rc = {0, 0, GetWidth(), GetHeight()};
	return rc;
}

DockStyleA ControlA::GetDock()
{
	return m_dock;
}

void ControlA::SetDock( DockStyleA dock )
{
	if (m_dock != dock)
	{
		m_dock = dock;
		OnDockChanged();
	}
}

bool ControlA::IsEnabled()
{
	return m_enabled;
}

void ControlA::SetEnabled( bool enabled )
{
	if (m_enabled != enabled)
	{
		m_enabled = enabled;
		OnEnableChanged();
	}
}

bool ControlA::AutoShowToolTip()
{
	return m_autoShowToolTip;
}

void ControlA::SetAutoShowToolTip(bool autoShowToolTip)
{
	m_autoShowToolTip = autoShowToolTip;
}

bool ControlA::IsFocused()
{
	return m_native != 0 && m_native->GetFocusedControl() == this;
}

void ControlA::SetFocused( bool focused )
{
	if (m_native)
	{
		if (focused)
		{
			m_native->SetFocusedControl(this);
		}
		else
		{
			if(m_native->GetFocusedControl() == this)
			{
				m_native->SetFocusedControl(0);
			}
		}
	}
}

FONT* ControlA::GetFont()
{
	return m_font;
}

void ControlA::SetFont( FONT *font )
{
	if(m_font)
	{
		m_font->Copy(font);
	}
	OnFontChanged();
}

_int64 ControlA::GetForeColor()
{
	return m_foreColor;
}

void ControlA::SetForeColor( _int64 foreColor )
{
	if (m_foreColor != foreColor)
	{
		m_foreColor = foreColor;
		OnForeColorChanged();
	}
}

bool ControlA::HasPopupMenu()
{
	return m_hasPopupMenu;
}

void ControlA::SetHasPopupMenu( bool hasPopupMenu )
{
	m_hasPopupMenu = hasPopupMenu;
}

int ControlA::GetHeight()
{
	if (m_percentSize && m_percentSize->cy != -1.0f)
	{
		SIZE size = m_parent != 0 ? m_parent->GetSize() : m_native->GetDisplaySize();
		return (int) (size.cy * m_percentSize->cy);
	}
	return m_size.cy;
}

void ControlA::SetHeight( int height )
{
	if (m_percentSize && m_percentSize->cy != -1.0f)
	{
		return;
	}
	SIZE sz = {m_size.cx, height};
	SetSize(sz);
}

bool ControlA::IsDragging()
{
	return m_isDragging;
}

bool ControlA::IsWindow()
{
	return m_isWindow;
}

void ControlA::SetWindow( bool isWindow )
{
	m_isWindow = isWindow;
}

int ControlA::GetLeft()
{
	if (m_percentLocation && m_percentLocation->x != -1.0f)
	{
		SIZE size = m_parent != 0 ? m_parent->GetSize() : m_native->GetDisplaySize();
		return (int) (size.cx * m_percentLocation->x);
	}
	return m_location.x;
}

void ControlA::SetLeft( int left )
{
	if (m_percentLocation == 0 || m_percentLocation->x == -1.0f)
	{
		POINT pt = {left, m_location.y};
		SetLocation(pt);
	}
}

POINT ControlA::GetLocation()
{
	if (m_percentLocation)
	{
		POINT pt = {GetLeft(), GetTop()};
		return pt;
	}
	return m_location;
}

void ControlA::SetLocation( const POINT& location )
{
	if (m_location.x != location.x || m_location.y != location.y)
	{
		if (m_percentLocation)
		{
			m_oldLocation = GetLocation();
			if (m_percentLocation->x == -1.0f)
			{
				m_location.x = location.x;
			}
			if (m_percentLocation->y == -1.0f)
			{
				m_location.y = location.y;
			}
		}
		else
		{
			m_oldLocation.x = m_location.x;
			m_oldLocation.y = m_location.y;
			m_location.x = location.x;
			m_location.y = location.y;
		}
		OnLocationChanged();
	}
}

PADDING ControlA::GetMargin()
{
	return m_margin;
}

void ControlA::SetMargin( const PADDING& margin )
{
	m_margin = margin;
	OnMarginChanged();
}

SIZE ControlA::GetMaximumSize()
{
	return m_maximumSize;
}

void ControlA::SetMaximumSize( SIZE maxinumSize )
{
	m_maximumSize = maxinumSize;
}

SIZE ControlA::GetMinimumSize()
{
	return m_minimumSize;
}

void ControlA::SetMinimumSize( SIZE minimumSize )
{
	m_minimumSize = minimumSize;
}

POINT ControlA::GetMousePoint()
{
	if(m_native)
	{
		POINT mousePoint = m_native->GetMousePoint();
		return PointToControl(mousePoint);
	}
	else
	{
		POINT mousePoint;
		mousePoint.x = 0;
		mousePoint.y = 0;
		return mousePoint;
	}
}

String ControlA::GetName()
{
	return m_name;
}

void ControlA::SetName( const String& name )
{
	m_name = name;
}

NativeBase* ControlA::GetNative()
{
	return m_native;
}

void ControlA::SetNative( NativeBase *native )
{
	m_native = native;
	int count = (int)m_controls.size();
	for (int i = 0; i < count; i++)
	{
		m_controls[i]->SetNative(native);
	}
	OnLoad();
}

float ControlA::GetOpacity()
{
	return m_opacity;
}

void ControlA::SetOpacity( float opacity )
{
	m_opacity = opacity;
}

PADDING ControlA::GetPadding()
{
	return m_padding;
}

void ControlA::SetPadding( const PADDING& padding )
{
	m_padding = padding;
	OnPaddingChanged();
}

ControlA* ControlA::GetParent()
{
	return m_parent;
}

void ControlA::SetParent( ControlA *control )
{
	if (m_parent != control)
	{
		m_parent = control;
		OnParentChanged();
	}
}

RECT ControlA::GetRegion()
{
	return m_region;
}

void ControlA::SetRegion( const RECT& region )
{
	m_useRegion = true;
	m_region = region;
	OnRegionChanged();
}

String ControlA::GetResourcePath()
{
	return m_resourcePath;
}

void ControlA::SetResourcePath( const String& resourcePath )
{
	m_resourcePath = resourcePath;
}

int ControlA::GetRight()
{
	return GetLeft() + GetWidth();
}

SIZE ControlA::GetSize()
{
	if (m_percentSize)
	{
		SIZE sz = {GetWidth(), GetHeight()};
		return sz;
	}
	return m_size;
}

void ControlA::SetSize( const SIZE& sz )
{
	SIZE size = sz;
	if (size.cx > m_maximumSize.cx)
	{
		size.cx = m_maximumSize.cx;
	}
	if (size.cy > m_maximumSize.cy)
	{
		size.cy = m_maximumSize.cy;
	}
	if (size.cx < m_minimumSize.cx)
	{
		size.cx = m_minimumSize.cx;
	}
	if (size.cy < m_minimumSize.cy)
	{
		size.cy = m_minimumSize.cy;
	}
	if (m_size.cx != size.cx || m_size.cy != size.cy)
	{
		if (m_percentSize)
		{
			m_oldSize = GetSize();
			if (m_percentSize->cx == -1.0f)
			{
				m_size.cx = size.cx;
			}
			if (m_percentSize->cy == -1.0f)
			{
				m_size.cy = size.cy;
			}
		}
		else
		{
			m_oldSize = m_size;
			m_size = size;
		}
		OnSizeChanged();
		Update();
	}
}

int ControlA::GetTabIndex()
{
	return m_tabIndex;
}

void ControlA::SetTabIndex( int tabIndex )
{
	if (m_tabIndex != tabIndex)
	{
		m_tabIndex = tabIndex;
		OnTabIndexChanged();
	}
}

bool ControlA::IsTabStop()
{
	return m_tabStop;
}

void ControlA::SetTabStop( bool tabStop )
{
	if (m_tabStop != tabStop)
	{
		m_tabStop = tabStop;
		OnTabStopChanged();
	}
}

void* ControlA::GetTag()
{
	return m_tag;
}

void ControlA::SetTag( void *tag )
{
	m_tag = tag;
}

String ControlA::GetText()
{
	return m_text;
}

void ControlA::SetText( const String& text )
{
	if (m_text != text)
	{
		m_text = text;
		OnTextChanged();
	}
}

int ControlA::GetTop()
{
	if (m_percentLocation && m_percentLocation->y != -1.0f)
	{
		SIZE size = m_parent != 0 ? m_parent->GetSize() : m_native->GetDisplaySize();
		return (int) (size.cy * m_percentLocation->y);
	}
	return m_location.y;
}

void ControlA::SetTop( int top )
{
	if (m_percentLocation == 0 || m_percentLocation->y == -1.0f)
	{
		POINT pt = {m_location.x, top};
		SetLocation(pt);
	}
}

bool ControlA::IsTopMost()
{
	return m_topMost;
}

void ControlA::SetTopMost( bool topMost )
{
	m_topMost = topMost;
}

bool ControlA::UseRegion()
{
	return m_useRegion;
}

VerticalAlignA ControlA::GetVerticalAlign()
{
	return m_verticalAlign;
}

void ControlA::SetVerticalAlign( VerticalAlignA verticalAlign )
{
	m_verticalAlign = verticalAlign;
}

bool ControlA::IsVisible()
{
	return m_visible;
}

void ControlA::SetVisible( bool visible )
{
	if (m_visible != visible)
	{
		m_visible = visible;
		OnVisibleChanged();
	}
}

int ControlA::GetWidth()
{
	if (m_percentSize && m_percentSize->cx != -1.0f)
	{
		SIZE size = m_parent != 0 ? m_parent->GetSize() : m_native->GetDisplaySize();
		return (int) (size.cx * m_percentSize->cx);
	}
	return m_size.cx;
}

void ControlA::SetWidth( int width )
{
	if (!m_percentSize || m_percentSize->cx == -1.0f)
	{
		SIZE sz = {width, m_size.cy};
		SetSize(sz);
	}
}

void ControlA::AddControl( ControlA *control )
{
	control->SetParent(this);
	control->SetNative(m_native);
	m_controls.push_back(control);
	control->OnAdd();
}

void ControlA::BeginInvoke( void *args )
{
	if (m_native)
	{
		m_native->GetHost()->BeginInvoke(this, args);
	}
}

void ControlA::BringChildToFront( ControlA *childControl )
{
	for (vector<ControlA*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		if (*it == childControl)
		{
			m_controls.erase(it);
			break;
		}
	}
	m_controls.push_back(childControl);
}

void ControlA::BringToFront()
{
	if (m_native)
	{
		m_native->BringToFront(this);
	}
}

void ControlA::ClearControls()
{
	vector<ControlA*> controlsTemp;
	String name = GetName();
	for (vector<ControlA*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		ControlA* control = (*it);
		controlsTemp.push_back(control);
	}

	for (vector<ControlA*>::iterator it = controlsTemp.begin(); it != controlsTemp.end(); it++)
	{
		ControlA* control = (*it);
		control->OnRemove();
	}
	controlsTemp.clear();
	m_controls.clear();
}

bool ControlA::ContainsControl( ControlA *control )
{
	for (vector<ControlA*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		if (*it == control)
		{
			return true;
		}
	}
	return false;
}

bool ControlA::ContainsPoint( const POINT& mp )
{
	POINT point2 = PointToControl(mp);
	SIZE size = GetSize();
	if (point2.x >= 0 && point2.x <= size.cx && point2.y >= 0 && point2.y <= size.cy)
	{
		if (!m_useRegion)
		{
			return true;
		}
		if (point2.x >= m_region.left 
			&& point2.x <= m_region.right 
			&& point2.y >= m_region.top 
			&& point2.y <= m_region.bottom)
		{
			return true;
		}
	}
	return false;
}

void ControlA::Focus()
{
	SetFocused(true);
}

vector<ControlA*> ControlA::GetControls()
{
	return m_controls;
}

String ControlA::GetControlType()
{
	return L"ControlA";
}

POINT ControlA::GetDisplayOffset()
{
	POINT pt = {0, 0};
	return pt;
}

vector<wstring> ControlA::GetEventNames()
{
	vector<wstring> ws;
	ws.push_back(L"Add");
	ws.push_back(L"BackColorChanged");
	ws.push_back(L"BackImageChanged");
	ws.push_back(L"Char");
	ws.push_back(L"Click");
	ws.push_back(L"Copy");
	ws.push_back(L"Cut");
	ws.push_back(L"DockChanged");
	ws.push_back(L"DoubleClick");
	ws.push_back(L"DragBegin");
	ws.push_back(L"DragEnd");
	ws.push_back(L"Dragging");
	ws.push_back(L"EnabledChanged");
	ws.push_back(L"FontChanged");
	ws.push_back(L"ForeColorChanged");
	ws.push_back(L"GotFocus");
	ws.push_back(L"Invoke");
	ws.push_back(L"KeyDown");
	ws.push_back(L"KeyUp");
	ws.push_back(L"Load");
	ws.push_back(L"LocationChanged");
	ws.push_back(L"LostFocus");
	ws.push_back(L"MarginChanged");
	ws.push_back(L"MouseDown");
	ws.push_back(L"MouseEnter");
	ws.push_back(L"MouseLeave");
	ws.push_back(L"MouseMove");
	ws.push_back(L"MouseUp");
	ws.push_back(L"MouseWheel");
	ws.push_back(L"PaddingChanged");
	ws.push_back(L"ParentChanged");
	ws.push_back(L"Paint");
	ws.push_back(L"PaintBorder");
	ws.push_back(L"Paste");
	ws.push_back(L"RegionChanged");
	ws.push_back(L"Remove");
	ws.push_back(L"SizeChanged");
	ws.push_back(L"TabIndexChanged");
	ws.push_back(L"TabStop");
	ws.push_back(L"TabStopChanged");
	ws.push_back(L"TextChanged");
	ws.push_back(L"Timer");
	ws.push_back(L"VisibleChanged");
	return ws;
}

int ControlA::GetNewTimerID()
{
	return m_timerID++;
}

ControlA* ControlA::GetPopupMenuContext( ControlA *control )
{
	if (m_hasPopupMenu)
	{
		return this;
	}
	if (m_parent)
	{
		return GetPopupMenuContext(m_parent);
	}
	return 0;
}

void ControlA::GetProperty( const String& name, String *value, String *type )
{
	int len = (int)name.length();
	switch (len)
	{
	case 3:
		if (name != L"top")
		{
			break;
		}
		*type = L"float";
		if (m_percentLocation == 0 || m_percentLocation->y == -1.0f)
		{
			*value = CStr::ConvertIntToStr(GetTop());
			return;
		}
		*value = L"%" + CStr::ConvertFloatToStr(100.0f * m_percentLocation->y);
		return;

	case 4:
		if (name != L"dock")
		{
			if (name == L"font")
			{
				*type = L"font";
				*value = CStr::ConvertFontToStr(GetFont());
				return;
			}
			if (name == L"left")
			{
				*type = L"float";
				if ((m_percentLocation != 0) && (m_percentLocation->x != -1.0f))
				{
					*value = L"%" + CStr::ConvertFloatToStr(100.0f * m_percentLocation->x);
					return;
				}
				*value = CStr::ConvertIntToStr(GetLeft());
				return;
			}
			if (name == L"name")
			{
				*type = L"text";
				*value = GetName();
				return;
			}
			if (name == L"size")
			{
				*type = L"size";
				if (m_percentSize != 0)
				{
					String str;
					String str2;
					String str3;
					GetProperty(L"width", &str, &str3);
					GetProperty(L"height", &str2, &str3);
					*value = str + L"," + str2;
					return;
				}
				*value = CStr::ConvertSizeToStr(GetSize());
				return;
			}
			if (name != L"text")
			{
				break;
			}
			*type = L"text";
			*value = GetText();
			return;
		}
		*type = L"enum:DockStyleA";
		*value = CStr::ConvertDockToStr(GetDock());
		return;

	case 5:
		if (name != L"align")
		{
			if (name != L"width")
			{
				break;
			}
			*type = L"float";
			if ((m_percentSize != 0) && (m_percentSize->cx != -1.0f))
			{
				*value = L"%" + CStr::ConvertFloatToStr(100.0f * m_percentSize->cx);
				return;
			}
			*value = CStr::ConvertIntToStr(GetWidth());
			return;
		}
		*type = L"enum:HorizontalAlignA";
		*value = CStr::ConvertHorizontalAlignToStr(GetAlign());
		return;

	case 6:
		if (name != L"anchor")
		{
			if (name == L"bounds")
			{
				*type = L"rect";
				*value = CStr::ConvertRectToStr(GetBounds());
				return;
			}
			if (name == L"cursor")
			{
				*type = L"enum:CursorsA";
				*value = CStr::ConvertCursorToStr(GetCursor());
				return;
			}
			if (name == L"height")
			{
				*type = L"float";
				if ((m_percentSize != 0) && (m_percentSize->cy != -1.0f))
				{
					*value = L"%" + CStr::ConvertFloatToStr(100.0f * m_percentSize->cy);
					return;
				}
				*value = CStr::ConvertIntToStr(GetHeight());
				return;
			}
			if (name == L"margin")
			{
				*type = L"margin";
				*value = CStr::ConvertPaddingToStr(GetMargin());
				return;
			}
			if (name != L"region")
			{
				break;
			}
			*type = L"rect";
			*value = CStr::ConvertRectToStr(GetRegion());
			return;
		}
		*type = L"anchor";
		*value = CStr::ConvertAnchorToStr(GetAnchor());
		return;

	case 7:
		if (name != L"enabled")
		{
			if (name == L"focused")
			{
				*type = L"bool";
				*value = CStr::ConvertBoolToStr(IsFocused());
				return;
			}
			if (name == L"opacity")
			{
				*type = L"float";
				*value = CStr::ConvertFloatToStr(GetOpacity());
				return;
			}
			if (name == L"padding")
			{
				*type = L"padding";
				*value = CStr::ConvertPaddingToStr(GetPadding());
				return;
			}
			if (name == L"tabstop")
			{
				*type = L"bool";
				*value = CStr::ConvertBoolToStr(IsTabStop());
				return;
			}
			if (name == L"topmost")
			{
				*type = L"bool";
				*value = CStr::ConvertBoolToStr(IsTopMost());
				return;
			}
			if (name != L"visible")
			{
				break;
			}
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(IsVisible());
			return;
		}
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(IsEnabled());
		return;

	case 8:
		if (name != L"autosize")
		{
			if (name == L"canfocus")
			{
				*type = L"bool";
				*value = CStr::ConvertBoolToStr(CanFocus());
				return;
			}
			if (name == L"iswindow")
			{
				*type = L"bool";
				*value = CStr::ConvertBoolToStr(IsWindow());
				return;
			}
			if (name == L"location")
			{
				*type = L"point";
				if (m_percentLocation != 0)
				{
					String str4;
					String str5;
					String str6;
					GetProperty(L"left", &str4, &str6);
					GetProperty(L"top", &str5, &str6);
					*value = str4 + L"," + str5;
					return;
				}
				*value = CStr::ConvertPointToStr(GetLocation());
				return;
			}
			if (name != L"tabindex")
			{
				break;
			}
			*type = L"int";
			*value = CStr::ConvertIntToStr(GetTabIndex());
			return;
		}
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(AutoSize());
		return;

	case 9:
		if (name != L"allowdrag")
		{
			if (name == L"backcolor")
			{
				*type = L"color";
				*value = CStr::ConvertColorToStr(GetBackColor());
				return;
			}
			if (name == L"backimage")
			{
				*type = L"text";
				*value = GetBackImage();
				return;
			}
			if (name != L"forecolor")
			{
				break;
			}
			*type = L"color";
			*value = CStr::ConvertColorToStr(GetForeColor());
			return;
		}
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(AllowDrag());
		return;

	default:
		if (name == L"allowpreviewsevent")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(AllowPreviewsEvent());
			return;
		}
		if (name == L"autoellipsis")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(AutoEllipsis());
			return;
		}
		if (name == L"bordercolor")
		{
			*type = L"color";
			*value = CStr::ConvertColorToStr(GetBorderColor());
			return;
		}
		if (name == L"canraiseevents")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(CanRaiseEvents());
			return;
		}
		if (name == L"displayoffset")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(DisplayOffset());
			return;
		}
		if (name == L"haspopupmenu")
		{
			*type = L"bool";
			*value = CStr::ConvertBoolToStr(HasPopupMenu());
			return;
		}
		if (name == L"maximumsize")
		{
			*type = L"size";
			*value = CStr::ConvertSizeToStr(GetMaximumSize());
			return;
		}
		if (name == L"minimumsize")
		{
			*type = L"size";
			*value = CStr::ConvertSizeToStr(GetMinimumSize());
			return;
		}
		if (name == L"resourcepath")
		{
			*type = L"text";
			*value = GetResourcePath();
			return;
		}
		if (name == L"vertical-align")
		{
			*type = L"enum:VerticalAlignA";
			*value = CStr::ConvertVerticalAlignToStr(GetVerticalAlign());
		}
		break;
	}
}

vector<String> ControlA::GetPropertyNames()
{
	static String arry[] = {L"Align", L"AllowDrag", L"AllowPreviewsEvent", L"Anchor", L"AutoEllipsis", L"AutoSize", 
		L"BackColor", L"BackImage", L"BorderColor", L"Bounds", 
		L"CanFocus", L"CanRaiseEvents", L"Cursor", L"DisplayOffset", L"Dock", L"Enabled",
		L"Focused", L"Font", L"ForeColor", L"HasPopupMenu", L"Height", L"IsWindow", L"Left", L"Location"
		, L"Margin", L"MaximumSize", L"MinimumSize", L"Name", L"Opacity", L"Padding", L"Region", L"ResourcePath",
		L"Size", L"TabIndex", L"TabStop", L"Text", L"Top", L"TopMost", L"Vertical-Align", L"Visible", L"Width"};
	vector<String> propertyNames(arry, arry + _countof(arry));
	return propertyNames;
}

bool ControlA::HasChildren()
{
	return !m_controls.empty();
}

void ControlA::Hide()
{
	SetVisible(false);
}

void ControlA::InsertControl( int index, ControlA *control )
{
	m_controls.insert(m_controls.begin() + index, control);
}

void ControlA::Invalidate()
{
	if (m_native)
	{
		m_native->Invalidate(this);
	}
}

void ControlA::Invoke( void *args )
{
	if (m_native)
	{
		m_native->GetHost()->Invoke(this, args);
	}
}

bool ControlA::IsPaintEnabled( ControlA *control )
{
	if (!control->IsEnabled())
	{
		return false;
	}
	ControlA *parent = control->GetParent();
	if (parent)
	{
		return IsPaintEnabled(parent);
	}
	return true;
}

bool ControlA::IsPaintVisible( ControlA *control )
{
	if (!control->IsVisible())
	{
		return false;
	}
	ControlA *parent = control->GetParent();
	if (parent != 0)
	{
		return IsPaintVisible(parent);
	}
	return true;
}

void ControlA::OnAdd()
{
	CallEvents(EVENTID::ADD);
}

void ControlA::OnAutoSizeChanged()
{
	CallEvents(EVENTID::AUTOSIZECHANGED);
}

void ControlA::OnBackColorChanged()
{
	CallEvents(EVENTID::BACKCOLORCHANGED);
}

void ControlA::OnBackImageChanged()
{
	CallEvents(EVENTID::BACKIMAGECHANGED);
}

void ControlA::OnChar( wchar_t ch )
{
	CallKeyEvents(EVENTID::CHAR, ch);
}

void ControlA::OnClick( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::CLICK, mp, button, clicks, delta);
}

void ControlA::OnCopy()
{
	CallEvents(EVENTID::COPY);
}

void ControlA::OnCut()
{
	CallEvents(EVENTID::CUT);
}

void ControlA::OnDockChanged()
{
	CallEvents(EVENTID::DOCKCHANGED);
}

void ControlA::OnDoubleClick( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::DOUBLECLICK, mp, button, clicks, delta);
}

bool ControlA::OnDragBegin()
{
	CallEvents(EVENTID::DRAGBEGIN);
	return true;
}

void ControlA::OnDragEnd()
{
	m_isDragging = false;
	CallEvents(EVENTID::DRAGEND);
}

void ControlA::OnDragging()
{
	m_isDragging = true;
	CallEvents(EVENTID::DRAGGING);
}

void ControlA::OnDragReady( POINT *startOffset )
{
	startOffset->x = 5;
	startOffset->y = 5;
}

void ControlA::OnEnableChanged()
{
	CallEvents(EVENTID::ENABLECHANGED);
}

void ControlA::OnFontChanged()
{
	CallEvents(EVENTID::FONTCHANGED);
}

void ControlA::OnForeColorChanged()
{
	CallEvents(EVENTID::FORECOLORCHANGED);
}

void ControlA::OnGotFocus()
{
	CallEvents(EVENTID::GOTFOCUS);
}

void ControlA::OnInvoke( void *args )
{
	CallInvokeEvents(EVENTID::INVOKE, args);
}

void ControlA::OnLoad()
{
	CallEvents(EVENTID::LOAD);
}

void ControlA::OnLocationChanged()
{
	CallEvents(EVENTID::LOCATIONCHANGED);
}

void ControlA::OnLostFocus()
{
	CallEvents(EVENTID::LOSTFOCUS);
}

void ControlA::OnKeyDown( char key )
{
	CallKeyEvents(EVENTID::KEYDOWN, key);
	if (GetNative()->GetHost()->IsKeyPress(0x11))
	{
		if (key == 'C')
		{
			OnCopy();
		}
		else if (key == 'V')
		{
			OnPaste();
		}
		else if (key == 'X')
		{
			OnCut();
		}
	}
}

void ControlA::OnKeyUp( char key )
{
	CallKeyEvents(EVENTID::KEYUP, key);
}

void ControlA::OnMarginChanged()
{
	CallEvents(EVENTID::MARGINCHANGED);
}

void ControlA::OnMouseDown( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::MOUSEDOWN, mp, button, clicks, delta);
}

void ControlA::OnMouseEnter( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::MOUSEENTER, mp, button, clicks, delta);
	if (m_autoShowToolTip && !m_text.empty())
	{
		m_native->GetHost()->ShowToolTip(this, m_text, m_native->GetMousePoint());
	}
}

void ControlA::OnMouseLeave( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::MOUSELEAVE, mp, button, clicks, delta);
}

void ControlA::OnMouseMove( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::MOUSEMOVE, mp, button, clicks, delta);
}

void ControlA::OnMouseUp( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::MOUSEUP, mp, button, clicks, delta);
}

void ControlA::OnMouseWheel( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::MOUSEWHEEL, mp, button, clicks, delta);
}

void ControlA::OnPaddingChanged()
{
	CallEvents(EVENTID::PADDINGCHANGED);
}

void ControlA::OnPaint( CPaint *paint, const RECT& clipRect )
{
	OnPaintBackground(paint, clipRect);
	OnPaintForeground(paint, clipRect);
	CallPaintEvents(EVENTID::PAINT, paint, clipRect);
}

void ControlA::OnPaintBackground( CPaint *paint, const RECT& clipRect )
{
	RECT rect = {0, 0, GetWidth(), GetHeight()};
	paint->FillRect(GetPaintingBackColor(), rect);
	String paintingBackImage = GetPaintingBackImage();
	if ((int)paintingBackImage.size() > 0)
	{
		paint->DrawImage(paintingBackImage.c_str(), rect);
	}
}

void ControlA::OnPaintBorder( CPaint *paint, const RECT& clipRect )
{
	RECT rect = {0, 0, GetWidth(), GetHeight()};
	paint->DrawRect(GetPaintingBorderColor(), 1.0f, 0, rect);
	CallPaintEvents(EVENTID::PAINTBORDER, paint, clipRect);
}

void ControlA::OnPaintForeground( CPaint *paint, const RECT& clipRect )
{

}

void ControlA::OnParentChanged()
{
	CallEvents(EVENTID::PARENTCHANGED);
}

void ControlA::OnPaste()
{
	CallEvents(EVENTID::PASTE);
}

void ControlA::OnPrePaint( CPaint *paint, const RECT& clipRect )
{

}

bool ControlA::OnPreviewsKeyEvent( int eventID, char key )
{
	return false;
}

bool ControlA::OnPreviewsMouseEvent( int eventID, const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	return false;
}

void ControlA::OnRegionChanged()
{
	CallEvents(EVENTID::REGIONCHANGED);
}

void ControlA::OnRemove()
{
	CallEvents(EVENTID::REMOVE);
}

void ControlA::OnSizeChanged()
{
	CallEvents(EVENTID::SIZECHANGED);
}

void ControlA::OnTabIndexChanged()
{
	CallEvents(EVENTID::TABINDEXCHANGED);
}

void ControlA::OnTabStop()
{
	CallEvents(EVENTID::TABSTOP);
}

void ControlA::OnTabStopChanged()
{
	CallEvents(EVENTID::TABSTOPCHANGED);
}

void ControlA::OnTextChanged()
{
	CallEvents(EVENTID::TEXTCHANGED);
}

void ControlA::OnTimer( int timerID )
{
	CallTimerEvents(EVENTID::TIMER, timerID);
}

void ControlA::OnTouchBegin( vector<CTouch> *touches )
{
	CallTouchEvents(EVENTID::TOUCHBEGIN, touches);
}

void ControlA::OnTouchCancel( vector<CTouch> *touches )
{
	CallTouchEvents(EVENTID::TOUCHCANCEL, touches);
}

void ControlA::OnTouchEnd( vector<CTouch> *touches )
{
	CallTouchEvents(EVENTID::TOUCHEND, touches);
}

void ControlA::OnTouchMove( vector<CTouch> *touches )
{
	CallTouchEvents(EVENTID::TOUCHMOVE, touches);
}

void ControlA::OnVisibleChanged()
{
	CallEvents(EVENTID::VISIBLECHANGED);
}

POINT ControlA::PointToControl( const POINT& mp )
{
	if (m_native)
	{
		int clientX = m_native->ClientX(this);
		int clientY = m_native->ClientY(this);
		POINT pt = {mp.x - clientX, mp.y - clientY};
		return pt;
	}
	return mp;
}

POINT ControlA::PointToNative( const POINT& mp )
{
	if (m_native)
	{
		int clientX = m_native->ClientX(this);
		int clientY = m_native->ClientY(this);
		POINT pt = {mp.x + clientX, mp.y + clientY};
		return pt;
	}
	return mp;
}

void ControlA::RegisterEvent( void *func, int eventID, void *pInvoke )
{
	vector<void*> *list = 0;
	if (m_events.find(eventID) != m_events.end())
	{
		list = m_events[eventID];
	}
	else
	{
		list = new vector<void*>();
		m_events[eventID] = list;
	}
	list->push_back(func);
	
	vector<void*> *listInvoke = 0;
	if (m_invokes.find(eventID) != m_invokes.end())
	{
		listInvoke = m_invokes[eventID];
	}
	else
	{
		listInvoke = new vector<void*>();
		m_invokes[eventID] = listInvoke;
	}
	listInvoke->push_back(pInvoke);
}

void ControlA::RemoveControl( ControlA *control )
{
	if (m_native)
	{
		m_native->RemoveControl(control);
	}
	for (vector<ControlA*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		if (*it == control)
		{
			m_controls.erase(it);
			break;
		}
	}
	control->OnRemove();
	control->SetParent(0);
}

void ControlA::SendChildToBack( ControlA *childControl )
{
	for (vector<ControlA*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		if (*it == childControl)
		{
			m_controls.erase(it);
			break;
		}
	}
	m_controls.insert(m_controls.begin(), childControl);
}

void ControlA::SendToBack()
{
	if (m_native)
	{
		m_native->SendToBack(this);
	}
}

void ControlA::SetProperty( const String& name, const String& value )
{
	int len = (int)name.length();
	switch (len)
	{
	case 3:
		{
			if (name != L"top")
			{
				break;
			}
			if (value.find(L"%") == -1)
			{
				if (m_percentLocation)
				{
					m_percentLocation->y = -1.0f;
				}
				SetTop(CStr::ConvertStrToInt(value));
				return;
			}
			float num2 = CStr::ConvertStrToFloat(value) / 100.0f;
			if (m_percentLocation == 0)
			{
				m_percentLocation = new POINTF();
				m_percentLocation->x = -1.0f;
			}
			m_percentLocation->y = num2;
			return;
		}
	case 4:
		if (name != L"dock")
		{
			if (name == L"font")
			{
				SetFont(CStr::ConvertStrToFont(value));
				return;
			}
			if (name == L"left")
			{
				if (value.find(L"%") != -1)
				{
					float num3 = CStr::ConvertStrToFloat(value) / 100.0f;
					if (m_percentLocation == 0)
					{
						m_percentLocation = new POINTF();
						m_percentLocation->y = -1.0f;
					}
					m_percentLocation->x = num3;
					return;
				}
				if (m_percentLocation != 0)
				{
					m_percentLocation->x = -1.0f;
				}
				SetLeft(CStr::ConvertStrToInt(value));
				return;
			}
			if (name == L"name")
			{
				SetName(value);
				return;
			}
			if (name == L"size")
			{
				if (value.find(L"%") == -1)
				{
					SetSize(CStr::ConvertStrToSize(value));
					return;
				}
				vector<String> strArray = CStr::Split(value, L",");
				SetProperty(L"width", strArray[0]);
				SetProperty(L"height", strArray[1]);
				return;
			}
			if (name != L"text")
			{
				break;
			}
			SetText(value);
			return;
		}
		SetDock(CStr::ConvertStrToDock(value));
		return;

	case 5:
		if (name != L"align")
		{
			if (name != L"width")
			{
				break;
			}
			if (value.find(L"%") != -1)
			{
				float num4 = CStr::ConvertStrToFloat(value) / 100.0f;
				if (m_percentSize == 0)
				{
					m_percentSize = new SIZEF();
					m_percentSize->cy = -1.0f;
				}
				m_percentSize->cx = num4;
				return;
			}
			if (m_percentSize != 0)
			{
				m_percentSize->cx = -1.0f;
			}
			SetWidth(CStr::ConvertStrToInt(value));
			return;
		}
		SetAlign(CStr::ConvertStrToHorizontalAlign(value));
		return;

	case 6:
		if (name != L"anchor")
		{
			if (name == L"bounds")
			{
				SetBounds(CStr::ConvertStrToRect(value));
				return;
			}
			if (name == L"cursor")
			{
				SetCursor(CStr::ConvertStrToCursor(value));
				return;
			}
			if (name == L"height")
			{
				if (value.find(L"%") != -1)
				{
					float num5 = CStr::ConvertStrToFloat(value) / 100.0f;
					if (m_percentSize == 0)
					{
						m_percentSize = new SIZEF();
						m_percentSize->cx = -1.0f;
					}
					m_percentSize->cy = num5;
					return;
				}
				if (m_percentSize != 0)
				{
					m_percentSize->cy = -1.0f;
				}
				SetHeight(CStr::ConvertStrToInt(value));
				return;
			}
			if (name == L"margin")
			{
				SetMargin(CStr::ConvertStrToPadding(value));
				return;
			}
			if (name != L"region")
			{
				break;
			}
			SetRegion(CStr::ConvertStrToRect(value));
			return;
		}
		SetAnchor(CStr::ConvertStrToAnchor(value));
		return;

	case 7:
		if (name != L"enabled")
		{
			if (name == L"focused")
			{
				SetFocused(CStr::ConvertStrToBool(value));
				return;
			}
			if (name == L"opacity")
			{
				SetOpacity(CStr::ConvertStrToFloat(value));
				return;
			}
			if (name == L"padding")
			{
				SetPadding(CStr::ConvertStrToPadding(value));
				return;
			}
			if (name == L"tabstop")
			{
				SetTabStop(CStr::ConvertStrToBool(value));
				return;
			}
			if (name == L"topmost")
			{
				SetTopMost(CStr::ConvertStrToBool(value));
				return;
			}
			if (name != L"visible")
			{
				break;
			}
			SetVisible(CStr::ConvertStrToBool(value));
			return;
		}
		SetEnabled(CStr::ConvertStrToBool(value));
		return;

	case 8:
		if (name != L"autosize")
		{
			if (name == L"canfocus")
			{
				SetCanFocus(CStr::ConvertStrToBool(value));
				return;
			}
			if (name == L"iswindow")
			{
				SetWindow(CStr::ConvertStrToBool(value));
				return;
			}
			if (name == L"location")
			{
				if (value.find(L"%") == -1)
				{
					SetLocation(CStr::ConvertStrToPoint(value));
					return;
				}
				vector<String> strArray2 = CStr::Split(value, L",");
				SetProperty(L"left", strArray2[0]);
				SetProperty(L"top", strArray2[1]);
				return;
			}
			if (name != L"tabindex")
			{
				break;
			}
			SetTabIndex(CStr::ConvertStrToInt(value));
			return;
		}
		SetAutoSize(CStr::ConvertStrToBool(value));
		return;

	case 9:
		if (name != L"allowdrag")
		{
			if (name == L"backcolor")
			{
				SetBackColor(CStr::ConvertStrToColor(value));
				return;
			}
			if (name == L"backimage")
			{
				SetBackImage(value);
				return;
			}
			if (name != L"forecolor")
			{
				break;
			}
			SetForeColor(CStr::ConvertStrToColor(value));
			return;
		}
		SetAllowDrag(CStr::ConvertStrToBool(value));
		return;

	default:
		if (name == L"allowpreviewsevent")
		{
			SetAllowPreviewsEvent(CStr::ConvertStrToBool(value));
			return;
		}
		if (name == L"autoellipsis")
		{
			SetAutoEllipsis(CStr::ConvertStrToBool(value));
			return;
		}
		if (name == L"bordercolor")
		{
			SetBorderColor(CStr::ConvertStrToColor(value));
			return;
		}
		if (name == L"canraiseevents")
		{
			SetCanRaiseEvents(CStr::ConvertStrToBool(value));
			return;
		}
		if (name == L"displayoffset")
		{
			SetDisplayOffset(CStr::ConvertStrToBool(value));
			return;
		}
		if (name == L"haspopupmenu")
		{
			SetHasPopupMenu(CStr::ConvertStrToBool(value));
			return;
		}
		if (name == L"maximumsize")
		{
			SetMaximumSize(CStr::ConvertStrToSize(value));
			return;
		}
		if (name == L"minimumsize")
		{
			SetMinimumSize(CStr::ConvertStrToSize(value));
			return;
		}
		if (name == L"resourcepath")
		{
			SetResourcePath(value);
			return;
		}
		if (name == L"vertical-align")
		{
			SetVerticalAlign(CStr::ConvertStrToVerticalAlign(value));
		}
		break;
	}
}

void ControlA::Show()
{
	SetVisible(true);
}

void ControlA::StartTimer( int timerID, int interval )
{
	if (m_native)
	{
		m_native->StartTimer(this, timerID, interval);
	}
}

void ControlA::StopTimer( int timerID )
{
	if (m_native)
	{
		m_native->StopTimer(timerID);
	}
}

void ControlA::UnRegisterEvent( void *func, int eventID )
{
	map<int, vector<void*>*>::iterator it = m_events.find(eventID);
	if (it != m_events.end())
	{
		vector<void*> *vec = it->second;
		int size = (int)vec->size();
		int index = -1;
		if(size > 0)
		{
			for(int i = 0; i < size; i++)
			{
				if((*vec)[i] = func)
				{
					index = i;
					break;
				}
			}
		}
		if(index > 0)
		{
			int count = 0;
			for (vector<void*>::iterator iter = vec->begin(); iter != vec->end(); iter++)
			{
				if (count == index)
				{
					vec->erase(iter);
					break;
				}
				++count;
			}
			map<int, vector<void*>*>::iterator itInvokes = m_invokes.find(eventID);
			count = 0;
			for (vector<void*>::iterator iter = itInvokes->second->begin(); iter != itInvokes->second->end(); iter++)
			{
				if (count == index)
				{
					itInvokes->second->erase(iter);
					break;
				}
				++count;
			}
		}
	}
}

void ControlA::Update()
{
	if (m_native)
	{
		m_native->SetAlign(&m_controls);
		if (m_oldSize.cx > 0 && m_oldSize.cy > 0)
		{
			m_native->SetAnchor(&m_controls, m_oldSize);
		}
		m_native->SetDock(&m_controls);
		m_oldLocation = GetLocation();
		m_oldSize = GetSize();
		int count = (int)m_controls.size();
		for (int i = 0; i < count; i++)
		{
			m_controls[i]->Update();
		}
	}
}