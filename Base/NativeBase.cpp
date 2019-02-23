#include "..\\stdafx.h"
#include "..\\include\\Base\\NativeBase.h"
#include "..\\include\\Base\\CMathLib.h"
using namespace OwLib;

ControlA* NativeBase::FindControl( const POINT& mp, vector<ControlA*> *controls )
{
	int count = (int)controls->size();
	for (int i =  count - 1; i >= 0; i--)
	{
		ControlA *parent = (*controls)[i];
		if (parent->IsVisible() && parent->ContainsPoint(mp))
		{
			vector<ControlA*> sortedControls;
			GetSortedControls(parent, &sortedControls);
			ControlA *control = FindControl(mp, &sortedControls);
			if (control)
			{
				return control;
			}
			return parent;
		}
	}
	return 0;
}

ControlA* NativeBase::FindControl( const String& name, vector<ControlA*> *controls )
{
	int count = (int)controls->size();
	for (int i = 0; i < count; i++)
	{
		ControlA *parent = controls->at(i);
		if (parent->GetName() == name)
		{
			return parent;
		}
		vector<ControlA*> list = parent->GetControls();
		if ((int)list.size() > 0)
		{
			ControlA *control = FindControl(name, &list);
			if (control)
			{
				return control;
			}
		}
	}
	return 0;
}

ControlA* NativeBase::FindPreviewsControl( ControlA *control )
{
	if (control && !control->AllowPreviewsEvent())
	{
		ControlA *parent = control->GetParent();
		if (parent)
		{
			return FindPreviewsControl(parent);
		}
	}
	return control;
}

ControlA* NativeBase::FindWindow( ControlA *control )
{
	if (!control->IsWindow())
	{
		ControlA *parent = control->GetParent();
		if (parent)
		{
			return FindWindow(parent);
		}
	}
	return control;
}

float NativeBase::GetPaintingOpacity( ControlA *control )
{
	float opacity = control->GetOpacity();
	ControlA *parent = control->GetParent();
	if (parent)
	{
		return (opacity * GetPaintingOpacity(parent));
	}
	return (opacity * m_opacity);
}

String NativeBase::GetPaintingResourcePath( ControlA *control )
{
	String resourcePath = control->GetResourcePath();
	if ((int)resourcePath.size() > 0)
	{
		return resourcePath;
	}
	ControlA *parent = control->GetParent();
	if (parent)
	{
		return GetPaintingResourcePath(parent);
	}
	return m_resourcePath;
}

bool NativeBase::GetSortedControls( ControlA *parent, vector<ControlA*> *sortedControls )
{
	vector<ControlA*> controls;
	if (parent)
	{
		controls = parent->GetControls();
	}
	else
	{
		controls = m_controls;
	}
	int count = (int)controls.size();
	int index = 0;
	for (int i = 0; i < count; i++)
	{
		ControlA *item = controls[i];
		if (item->IsVisible())
		{
			if (item->IsTopMost())
			{
				sortedControls->push_back(item);
			}
			else
			{
				sortedControls->insert(sortedControls->begin() + index, item);
				index++;
			}
		}
	}
	return (int)sortedControls->size() > 0;
}

void NativeBase::GetTabStopControls( ControlA *control, vector<ControlA*> *tabStopControls )
{
	vector<ControlA*> controls = control->GetControls();
	int count = (int)controls.size();
	for (int i = 0; i < count; i++)
	{
		ControlA *item = controls[i];
		if (!item->IsWindow())
		{
			if (item->IsEnabled() && item->IsTabStop())
			{
				tabStopControls->push_back(item);
			}
			GetTabStopControls(item, tabStopControls);
		}
	}
}

bool NativeBase::IsPaintEnabled( ControlA *control )
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

void NativeBase::RenderControls( const RECT& rect, vector<ControlA*> *controls, String resourcePath, float opacity )
{
	int count = (int)controls->size();
	for (int i = 0; i < count; i++)
	{
		ControlA *control = (*controls)[i];
		control->OnPrePaint(m_paint, control->GetDisplayRect());
		RECT lpDestRect;
		int left = ClientX(control);
		int top = ClientY(control);
		RECT rect3 = {left, top, left + control->GetWidth(), top + control->GetHeight()};
		if (control->UseRegion())
		{
			RECT region = control->GetRegion();
			rect3.left += region.left;
			rect3.top += region.top;
			rect3.right = rect3.left + region.right - region.left;
			rect3.bottom = rect3.top + region.bottom - region.top;
		}
		if (control->IsVisible() && (m_host->GetIntersectRect(&lpDestRect, &rect, &rect3) > 0))
		{
			RECT clipRect = {lpDestRect.left - left, lpDestRect.top - top, lpDestRect.right - left, lpDestRect.bottom - top};
			String str = control->GetResourcePath();
			if ((int)str.size() == 0)
			{
				str = resourcePath;
			}
			float num5 = control->GetOpacity() * opacity;
			SetPaint(left, top, clipRect, str, num5);
			control->OnPaint(m_paint, clipRect);
			vector<ControlA*> sortedControls;
			GetSortedControls(control, &sortedControls);
			if ((int)sortedControls.size() > 0)
			{
				RenderControls(lpDestRect, &sortedControls, str, num5);
				sortedControls.clear();
			}
			SetPaint(left, top, clipRect, str, num5);
			control->OnPaintBorder(m_paint, clipRect);
		}
	}
}

void NativeBase::SetCursor( ControlA *control )
{
	CursorsA cursor = control->GetCursor();
	if (!IsPaintEnabled(control))
	{
		cursor = CursorsA_Arrow;
	}
	if (GetCursor() != cursor)
	{
		SetCursor(cursor);
	}
}

void NativeBase::SetPaint( int offsetX, int offsetY, const RECT& clipRect, String resourcePath, float opacity )
{
	if (m_paint)
	{
		POINT pt = {offsetX, offsetY};
		m_paint->SetOffset(pt);
		m_paint->SetClip(clipRect);
		m_paint->SetResourcePath(resourcePath);
		m_paint->SetOpacity(opacity);
	}
}

NativeBase::NativeBase()
{
	m_allowScaleSize = false;
	m_displaySize.cx = 0;
	m_displaySize.cy = 0;
	m_drawBeginPoint.x = 0;
	m_drawBeginPoint.y = 0;
	m_dragBeginRect.bottom = 0;
	m_dragBeginRect.left = 0;
	m_dragBeginRect.right = 0;
	m_dragBeginRect.top = 0;
	m_dragStartOffset.x = 0;
	m_dragStartOffset.y = 0;
	m_exportingControl = 0;
	m_host = new WinHost();
	m_host->SetNative(this);
	m_mirrorHost = 0;
	m_mirrorMode = MirrorMode_None;
	m_opacity = 1.0f;
	m_paint = new GdiPaint();
	m_mouseDownPoint.x = 0;
	m_mouseDownPoint.y = 0;
	m_resourcePath = L"";
	m_rotateAngle = 0;
	m_scaleSize.cx = 0;
	m_scaleSize.cy = 0;
	m_draggingControl = 0;
	m_focusedControl = 0;
	m_mouseDownControl = 0;
	m_mouseMoveControl = 0;
}

NativeBase::~NativeBase()
{
	if (m_host)
	{
		delete m_host;
		m_host = 0;
	}
	m_mirrorHost = 0;
	if (m_paint)
	{
		delete m_paint;
		m_paint = 0;
	}
	m_rotateAngle = 0;
	m_draggingControl = 0;
	m_exportingControl = 0;
	m_focusedControl = 0;
	m_mouseDownControl = 0;
	m_mouseMoveControl = 0;
	m_timers.clear();
	ClearControls();
}

bool NativeBase::AllowScaleSize()
{
	return m_allowScaleSize;
}

void NativeBase::SetAllowScaleSize( bool allowScaleSize )
{
	m_allowScaleSize = allowScaleSize;
}

CursorsA NativeBase::GetCursor()
{
	if (m_host)
	{
		return m_host->GetCursor();
	}
	return CursorsA_Arrow;
}

void NativeBase::SetCursor( CursorsA cursor )
{
	if (m_host)
	{
		m_host->SetCursor(cursor);
	}
}

SIZE NativeBase::GetDisplaySize()
{
	return m_displaySize;
}

void NativeBase::SetDisplaySize( SIZE displaySize )
{
	m_displaySize = displaySize;
}

ControlA* NativeBase::GetFocusedControl()
{
	return m_focusedControl;
}

void NativeBase::SetFocusedControl( ControlA *focusedControl )
{
	if (m_focusedControl != focusedControl)
	{
		if (m_focusedControl)
		{
			ControlA *la = m_focusedControl;
			m_focusedControl = 0;
			la->OnLostFocus();
		}
		m_focusedControl = focusedControl;
		if (m_focusedControl)
		{
			m_focusedControl->OnGotFocus();
		}
	}
}

ControlHost* NativeBase::GetHost()
{
	return m_host;
}

void NativeBase::SetHost( ControlHost *host )
{
	m_host = host;
}

ControlA* NativeBase::GetHoveredControl()
{
	return m_mouseMoveControl;
}

NativeBase* NativeBase::GetMirrorHost()
{
	return m_mirrorHost;
}

MirrorMode NativeBase::GetMirrorMode()
{
	return m_mirrorMode;
}

void NativeBase::SetMirrorMode( MirrorMode mirrorMode )
{
	m_mirrorMode = mirrorMode;
}

POINT NativeBase::GetMousePoint()
{
	if (m_host)
	{
		return m_host->GetMousePoint();
	}
	POINT pt = {0, 0};
	return pt;
}

float NativeBase::GetOpacity()
{
	return m_opacity;
}

void NativeBase::SetOpacity( float opacity )
{
	m_opacity = opacity;
}

CPaint* NativeBase::GetPaint()
{
	return m_paint;
}

void NativeBase::SetPaint( CPaint *paint )
{
	m_paint = paint;
}

ControlA* NativeBase::GetPushedControl()
{
	return m_mouseDownControl;
}

String NativeBase::GetResourcePath()
{
	return m_resourcePath;
}

void NativeBase::SetResourcePath( const String& resourcePath )
{
	m_resourcePath = resourcePath;
}

int NativeBase::GetRotateAngle()
{
	return m_rotateAngle;
}

void NativeBase::SetRotateAngle( int rotateAngle )
{
	m_rotateAngle = rotateAngle;
}

SIZE NativeBase::GetScaleSize()
{
	return m_scaleSize;
}

void NativeBase::SetScaleSize( SIZE scaleSize )
{
	m_scaleSize = scaleSize;
}

void NativeBase::AddControl( ControlA *control )
{
	control->SetNative(this);
	m_controls.push_back(control);
	control->OnAdd();
}

void NativeBase::AddMirror( NativeBase *mirrorHost, ControlA *control )
{
	m_mirrorHost = mirrorHost;
	m_mirrorHost->m_mirrors.push_back(this);
	control->SetNative(this);
	m_controls.push_back(control);
}

void NativeBase::BringToFront( ControlA *control )
{
	ControlA *parent = control->GetParent();
	if (parent)
	{
		parent->BringChildToFront(control);
	}
	else
	{
		int size = (int)m_controls.size();
		if(size > 0)
		{
			for (vector<ControlA*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
			{
				if (*it == control)
				{
					m_controls.erase(it);
					break;
				}
			}
			m_controls.push_back(control);
		}
	}
}

void NativeBase::CancelDragging()
{
	if (m_draggingControl)
	{
		m_draggingControl->SetBounds(m_dragBeginRect);
		ControlA *la = m_draggingControl;
		m_draggingControl = 0;
		la->OnDragEnd();
		ControlA *parent = la->GetParent();
		if (parent)
		{
			parent->Invalidate();
		}
		else
		{
			Invalidate();
		}
	}
}

void NativeBase::ClearControls()
{
	vector<ControlA*> controls;
	for (vector<ControlA*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		controls.push_back(*it);
	}

	for (vector<ControlA*>::iterator it = controls.begin(); it != controls.end(); it++)
	{
		(*it)->OnRemove();
		delete *it;
		*it = 0;
	}
	controls.clear();
	m_controls.clear();
}

int NativeBase::ClientX( ControlA *control )
{
	if (!control)
	{
		return 0;
	}
	ControlA *parent = control->GetParent();
	int left = control->GetLeft();
	if (control == m_exportingControl)
	{
		left = 0;
	}
	if (!parent)
	{
		return left;
	}
	if (m_mirrorMode != MirrorMode_None)
	{
		int count = (int)m_controls.size();
		for (int i = 0; i < count; i++)
		{
			if (m_controls[i] == control)
			{
				return left;
			}
		}
	}
	return (left - (control->DisplayOffset() ? parent->GetDisplayOffset().x : 0) + ClientX(parent));
}

int NativeBase::ClientY( ControlA *control )
{
	if (!control)
	{
		return 0;
	}
	ControlA *parent = control->GetParent();
	int top = control->GetTop();
	if (control == m_exportingControl)
	{
		top = 0;
	}
	if (!parent)
	{
		return top;
	}
	if (m_mirrorMode != MirrorMode_None)
	{
		int count = (int)m_controls.size();
		for (int i = 0; i < count; i++)
		{
			if (m_controls[i] == control)
			{
				return top;
			}
		}
	}
	return (top - (control->DisplayOffset() ? parent->GetDisplayOffset().y : 0) + ClientY(parent));
}

bool NativeBase::ContainsControl( ControlA *control )
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

void NativeBase::ExportToImage( const String& exportPath )
{
	ExportToImage(exportPath, 0);
}

void NativeBase::ExportToImage( const String& exportPath, ControlA *control )
{
	m_exportingControl = control;
	if (control)
	{
		vector<ControlA*> controls;
		controls.push_back(control);
		RECT rect = {0, 0, control->GetWidth(), control->GetHeight()};
		m_paint->BeginExport(exportPath, rect);
		RenderControls(rect, &controls, GetPaintingResourcePath(control), GetPaintingOpacity(control));
		m_paint->EndExport();
	}
	else
	{
		RECT rect2 = {0, 0, m_displaySize.cx, m_displaySize.cy};
		m_paint->BeginExport(exportPath, rect2);
		vector<ControlA*> sortedControls;
		GetSortedControls(0, &sortedControls);
		RenderControls(rect2, &sortedControls, m_resourcePath, m_opacity);
		sortedControls.clear();
		m_paint->EndExport();
	}
	m_exportingControl = 0;
}

ControlA* NativeBase::FindControl( const POINT& mp )
{
	vector<ControlA*> sortedControls;
	if(GetSortedControls(0, &sortedControls))
	{
		return FindControl(mp, &sortedControls);
	}
	return 0;
}

ControlA* NativeBase::FindControl( const POINT& mp, ControlA *parent )
{
	vector<ControlA*> subControls;
	if(GetSortedControls(parent, &subControls))
	{
		return FindControl(mp, &subControls);
	}
	return 0;
}

ControlA* NativeBase::FindControl( const String& name )
{
	return FindControl(name, &m_controls);
}

vector<ControlA*> NativeBase::GetControls()
{
	return m_controls;
}

void NativeBase::InsertControl( int index, ControlA *control )
{
	m_controls.insert(m_controls.begin() + index, control);
}

void NativeBase::Invalidate()
{
	if (m_host)
	{
		m_host->Invalidate();
	}
}

void NativeBase::Invalidate( ControlA *control )
{
	if (m_host)
	{
		int left = ClientX(control);
		int top = ClientY(control);
		RECT rc = {left, top, left + control->GetWidth(), top + control->GetHeight()};
		m_host->Invalidate(rc);
		vector<NativeBase*> mirrors;
		if (m_mirrorMode == MirrorMode_Shadow)
		{
			left = m_mirrorHost->ClientX(control);
			top = m_mirrorHost->ClientY(control);
			RECT rect = {left, top, left + control->GetWidth(), top + control->GetHeight()};
			m_mirrorHost->GetHost()->Invalidate(rect);
			mirrors = m_mirrorHost->m_mirrors;
		}
		else
		{
			mirrors = m_mirrors;
		}
		int count = (int)mirrors.size();
		for (int i = 0; i < count; i++)
		{
			if (mirrors[i] != this && mirrors[i]->GetMirrorMode() != MirrorMode_BugHole)
			{
				left = mirrors[i]->ClientX(control);
				top = mirrors[i]->ClientY(control);
				RECT rect = {left, top, left + control->GetWidth(), top + control->GetHeight()};
				m_mirrorHost->GetHost()->Invalidate(rect);
			}
		}
	}
}

void NativeBase::Invalidate( const RECT& rect )
{
	if (m_host)
	{
		m_host->Invalidate(rect);
	}
}

bool NativeBase::OnChar( wchar_t key )
{
	ControlA *focusedControl = GetFocusedControl();
	if (focusedControl && IsPaintEnabled(focusedControl))
	{
		if (focusedControl->IsTabStop())
		{
			ControlA *control = FindWindow(focusedControl);
			if (control && !m_host->IsKeyPress(0x10) && !m_host->IsKeyPress(0x11) && key == L'\t')
			{
				vector<ControlA*> tabStopControls;
				GetTabStopControls(control, &tabStopControls);
				int count = (int)tabStopControls.size();
				if (count > 0)
				{
					for (int i = 0; i < (count - 1); i++)
					{
						for (int j = 0; j < (count - 1 - i); j++)
						{
							ControlA *la3 = tabStopControls[j];
							ControlA *la4 = tabStopControls[j + 1];
							if (la3->GetTabIndex() > la4->GetTabIndex())
							{
								ControlA *la5 = tabStopControls[j + 1];
								tabStopControls[j + 1] = tabStopControls[j];
								tabStopControls[j] = la5;
							}
						}
					}
					bool flag = false;
					ControlA *la6 = 0;
					for (int k = 0; k < count; k++)
					{
						ControlA *la7 = tabStopControls[k];
						if (focusedControl == la7)
						{
							if (k < count - 1)
							{
								la6 = tabStopControls[k + 1];
							}
							else
							{
								la6 = tabStopControls[0];
							}
							flag = true;
							break;
						}
					}
					if (!flag)
					{
						la6 = tabStopControls[0];
					}
					if (la6 != focusedControl)
					{
						la6->SetFocused(true);
						focusedControl = la6;
						focusedControl->OnTabStop();
						control->Invalidate();
						return true;
					}
				}
			}
		}
		focusedControl->OnChar(key);
	}
	return false;
}

void NativeBase::OnDoubleClick( MouseButtonsA button, int clicks, int delta )
{
	ControlA *focusedControl = GetFocusedControl();
	if (focusedControl && IsPaintEnabled(focusedControl))
	{
		POINT mousePoint = GetMousePoint();
		int left = ClientX(focusedControl);
		int top = ClientY(focusedControl);
		POINT mp = {mousePoint.x - left, mousePoint.y - top};
		focusedControl->OnDoubleClick(mp, button, clicks, delta);
	}
}

void NativeBase::OnKeyDown( char key )
{
	ControlA *focusedControl = GetFocusedControl();
	if (focusedControl && IsPaintEnabled(focusedControl))
	{
		focusedControl->OnKeyDown(key);
	}
}

void NativeBase::OnKeyUp( char key )
{
	ControlA *focusedControl = GetFocusedControl();
	if (focusedControl && IsPaintEnabled(focusedControl))
	{
		focusedControl->OnKeyUp(key);
	}
}

void NativeBase::OnMouseDown( MouseButtonsA button, int clicks, int delta )
{
	m_draggingControl = 0;
	m_mouseDownControl = 0;
	POINT mousePoint = GetMousePoint();
	m_mouseDownPoint = mousePoint;
	vector<ControlA*> sortedControls;
	GetSortedControls(0, &sortedControls);
	ControlA *control = FindControl(mousePoint, &sortedControls);
	if (control)
	{
		ControlA *la2 = FindWindow(control);
		if (la2 && la2->IsWindow())
		{
			la2->BringToFront();
		}
		if (IsPaintEnabled(control))
		{
			int left = ClientX(control);
			int top = ClientY(control);
			POINT mp = {mousePoint.x - left, mousePoint.y - top};
			ControlA *focusedControl = GetFocusedControl();
			m_mouseDownControl = control;
			if (focusedControl == GetFocusedControl())
			{
				if (control->CanFocus())
				{
					if (button == MouseButtonsA_Left)
					{
						SetFocusedControl(control);
					}
				}
				else
				{
					SetFocusedControl(0);
				}
			}
			if (!OnPreviewsMouseEvent(EVENTID::MOUSEDOWN, m_mouseDownControl, mousePoint, button, clicks, delta))
			{
				if (m_mouseDownControl)
				{
					m_mouseDownControl->OnMouseDown(mp, button, clicks, delta);
					if (m_mouseDownControl)
					{
						m_mouseDownControl->OnDragReady(&m_dragStartOffset);
					}
				}
			}
		}
	}
}

void NativeBase::OnMouseLeave( MouseButtonsA button, int clicks, int delta )
{
	if (m_mouseMoveControl && IsPaintEnabled(m_mouseMoveControl))
	{
		POINT mousePoint = GetMousePoint();
		POINT mp = {mousePoint.x - ClientX(m_mouseMoveControl), mousePoint.y - ClientY(m_mouseMoveControl)};
		ControlA *control = m_mouseMoveControl;
		m_mouseMoveControl = 0;
		if (!OnPreviewsMouseEvent(EVENTID::MOUSELEAVE, m_mouseDownControl, mousePoint, button, clicks, delta))
		{
			control->OnMouseLeave(mp, button, clicks, delta);
		}
	}
}

void NativeBase::OnMouseMove( MouseButtonsA button, int clicks, int delta )
{
	POINT mousePoint = GetMousePoint();
	if (m_mouseDownControl)
	{
		if (!OnPreviewsMouseEvent(EVENTID::MOUSEMOVE, m_mouseDownControl, mousePoint, button, clicks, delta))
		{
			POINT mp = {mousePoint.x - ClientX(m_mouseDownControl), mousePoint.y - ClientY(m_mouseDownControl)};
			m_mouseDownControl->OnMouseMove(mp, button, clicks, delta);
			SetCursor(m_mouseDownControl);
			if (((m_mouseDownControl->AllowDrag() && button == MouseButtonsA_Left && clicks == 1) 
				&& ((abs((int) (mousePoint.x - m_mouseDownPoint.x)) > m_dragStartOffset.x) 
				|| (abs((int) (mousePoint.y - m_mouseDownPoint.y)) > m_dragStartOffset.y))) 
				&& m_mouseDownControl->OnDragBegin())
			{
				m_dragBeginRect = m_mouseDownControl->GetBounds();
				m_drawBeginPoint = m_mouseDownPoint;
				m_draggingControl = m_mouseDownControl;
				m_mouseDownControl = 0;
				ControlA *parent = m_draggingControl->GetParent();
				if (parent)
				{
					parent->Invalidate();
				}
				else
				{
					Invalidate();
				}
			}
		}
	}
	else if (m_draggingControl)
	{
		ControlA *la2 = m_draggingControl;
		int num = mousePoint.x - m_drawBeginPoint.x;
		int num2 = mousePoint.y - m_drawBeginPoint.y;
		RECT rect = m_dragBeginRect;
		rect.left += num;
		rect.top += num2;
		rect.right += num;
		rect.bottom += num2;
		la2->SetBounds(rect);
		la2->OnDragging();
		ControlA *la3 = la2->GetParent();
		if (la3)
		{
			la3->Invalidate();
		}
		else
		{
			Invalidate();
		}
	}
	else
	{
		vector<ControlA*> sortedControls;
		GetSortedControls(0, &sortedControls);
		ControlA *control = FindControl(mousePoint, &sortedControls);
		if(control && OnPreviewsMouseEvent(EVENTID::MOUSEMOVE, control, mousePoint, button, clicks, delta))
		{
			return;
		}
		sortedControls.clear();
		if (m_mouseMoveControl != control)
		{
			if ((m_mouseMoveControl && IsPaintEnabled(m_mouseMoveControl)) && !m_mouseDownControl)
			{
				POINT point3 = {mousePoint.x - ClientX(m_mouseMoveControl), mousePoint.y - ClientY(m_mouseMoveControl)};
				ControlA *la5 = m_mouseMoveControl;
				m_mouseMoveControl = control;
				la5->OnMouseLeave(point3, button, clicks, delta);
			}
			if ((control && IsPaintEnabled(control)) && !m_mouseDownControl)
			{
				POINT point4 = {mousePoint.x - ClientX(control), mousePoint.y - ClientY(control)};
				m_mouseMoveControl = control;
				control->OnMouseEnter(point4, button, clicks, delta);
				control->OnMouseMove(point4, button, clicks, delta);
				SetCursor(control);
			}
		}
		else if (control && IsPaintEnabled(control))
		{
			POINT point5 = {mousePoint.x - ClientX(control), mousePoint.y - ClientY(control)};
			m_mouseMoveControl = control;
			control->OnMouseMove(point5, button, clicks, delta);
			SetCursor(control);
		}
	}
}

void NativeBase::OnMouseUp( MouseButtonsA button, int clicks, int delta )
{
	POINT mousePoint = GetMousePoint();
	vector<ControlA*> sortedControls;
	GetSortedControls(0, &sortedControls);
	if (m_mouseDownControl)
	{
		ControlA *control = m_mouseDownControl;
		if (OnPreviewsMouseEvent(EVENTID::MOUSEUP, control, mousePoint, button, clicks, delta))
		{
			m_mouseDownControl = 0;
			return;
		}
		if (m_mouseDownControl)
		{
			control = m_mouseDownControl;
			ControlA *la2 = FindControl(mousePoint, &sortedControls);
			POINT mp = {mousePoint.x - ClientX(control), mousePoint.y - ClientY(control)};
			if (la2 && la2 == control)
			{
				control->OnClick(mp, button, clicks, delta);
			}
			else
			{
				m_mouseMoveControl = 0;
			}
			if (m_mouseDownControl != 0)
			{
				control = m_mouseDownControl;
				m_mouseDownControl = 0;
				control->OnMouseUp(mp, button, clicks, delta);
			}
		}
	}
	else if (m_draggingControl)
	{
		POINT point3 = {mousePoint.x - ClientX(m_mouseDownControl), mousePoint.y - ClientY(m_mouseDownControl)};
		ControlA *la3 = m_draggingControl;
		m_draggingControl = 0;
		if (OnPreviewsMouseEvent(EVENTID::MOUSEUP, la3, mousePoint, button, clicks, delta))
		{
			return;
		}
		la3->OnMouseUp(point3, button, clicks, delta);
		la3->OnDragEnd();
		ControlA *parent = la3->GetParent();
		if (parent)
		{
			parent->Invalidate();
		}
		else
		{
			Invalidate();
		}
	}
	sortedControls.clear();
}

void NativeBase::OnMouseWheel( MouseButtonsA button, int clicks, int delta )
{
	ControlA *focusedControl = GetFocusedControl();
	if (focusedControl && IsPaintEnabled(focusedControl))
	{
		POINT mousePoint = GetMousePoint();
		if (!OnPreviewsMouseEvent(EVENTID::MOUSEWHEEL, focusedControl, mousePoint, button, clicks, delta))
		{
			mousePoint.x -= ClientX(focusedControl);
			mousePoint.y -= ClientY(focusedControl);
			focusedControl->OnMouseWheel(mousePoint, button, clicks, delta);
		}
	}
}

void NativeBase::OnPaint( const RECT& clipRect )
{
	vector<ControlA*> sortedControls;
	GetSortedControls(0, &sortedControls);
	RenderControls(clipRect, &sortedControls, m_resourcePath, m_opacity);
	sortedControls.clear();
}

bool NativeBase::OnPreviewsKeyEvent( int eventID, char key )
{
	ControlA *focusedControl = GetFocusedControl();
	if (focusedControl && IsPaintEnabled(focusedControl))
	{
		ControlA *la2 = FindWindow(focusedControl);
		if (la2)
		{
			return la2->OnPreviewsKeyEvent(eventID, key);
		}
	}
	return false;
}

bool NativeBase::OnPreviewsMouseEvent( int eventID, ControlA *control, const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	ControlA *la = FindPreviewsControl(control);
	if (la)
	{
		int x = ClientX(la);
		int y = ClientY(la);
		POINT point = {mp.x - x, mp.y - y};
		if (la->OnPreviewsMouseEvent(eventID, point, button, clicks, delta))
		{
			return true;
		}
	}
	return false;
}

void NativeBase::OnResize()
{
	Update();
}

void NativeBase::OnTimer( int timerID )
{
	map<int, ControlA*>::iterator it = m_timers.find(timerID);
	if (it != m_timers.end())
	{
		it->second->OnTimer(timerID);
	}
	for (vector<NativeBase*>::iterator it = m_mirrors.begin(); it != m_mirrors.end(); it++)
	{
		(*it)->OnTimer(timerID);
	}
}

void NativeBase::RemoveControl( ControlA *control )
{
	if (control == m_draggingControl)
	{
		m_draggingControl = 0;
	}
	if (control == m_focusedControl)
	{
		m_focusedControl = 0;
	}
	if (control == m_mouseDownControl)
	{
		m_mouseDownControl = 0;
	}
	if (control == m_mouseMoveControl)
	{
		m_mouseMoveControl = 0;
	}
	for (map<int, ControlA*>::iterator it = m_timers.begin(); it != m_timers.end(); it++)
	{
		if (it->second == control)
		{
			it->second->StopTimer(it->first);
			break;
		}
	}

	if (!control->GetParent())
	{
		for (vector<ControlA*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
		{
			if (*it == control)
			{
				m_controls.erase(it);
				break;
			}
		}
		control->OnRemove();
	}
}

void NativeBase::RemoveMirror( ControlA *control )
{
	for (vector<NativeBase*>::iterator iter = m_mirrorHost->m_mirrors.begin(); iter != m_mirrorHost->m_mirrors.end(); iter++)
	{
		if (*iter == this)
		{
			m_mirrorHost->m_mirrors.erase(iter);
			break;
		}
	}
	for (vector<ControlA*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		if (*it == control)
		{
			m_controls.erase(it);
			break;
		}
	}
	control->SetNative(m_mirrorHost);
}

void NativeBase::SendToBack( ControlA *control )
{
	ControlA *parent = control->GetParent();
	if (parent)
	{
		parent->SendChildToBack(control);
	}
	else
	{
		for (vector<ControlA*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
		{
			if (*it == control)
			{
				m_controls.erase(it);
				break;
			}
		}
		m_controls.insert(m_controls.begin(), control);
	}
}

void NativeBase::SetAlign( vector<ControlA*> *controls )
{
	int count = (int)controls->size();
	for (int i = 0; i < count; i++)
	{
		ControlA *la = (*controls)[i];
		if (la->DisplayOffset())
		{
			SIZE size = m_displaySize;
			ControlA *parent = la->GetParent();
			if (parent && (m_mirrorMode != MirrorMode_BugHole))
			{
				size = parent->GetSize();
			}
			SIZE size2 = la->GetSize();
			PADDING margin = la->GetMargin();
			PADDING padding;
			if (parent)
			{
				padding = parent->GetPadding();
			}
			if (la->GetAlign() == HorizontalAlignA_Center)
			{
				la->SetLeft((size.cx - size2.cx) / 2);
			}
			else if (la->GetAlign() == HorizontalAlignA_Right)
			{
				la->SetLeft(size.cx - size2.cx - margin.right - padding.right);
			}
			if (la->GetVerticalAlign() == VerticalAlignA_Bottom)
			{
				la->SetTop(size.cy - size2.cy - margin.bottom - padding.bottom);
			}
			else if (la->GetVerticalAlign() == VerticalAlignA_Middle)
			{
				la->SetTop((size.cy - size2.cy) / 2);
			}
		}
	}
}

void NativeBase::SetAnchor( vector<ControlA*> *controls, SIZE oldSize )
{
	if ((oldSize.cx != 0) && (oldSize.cy != 0))
	{
		int count = (int)controls->size();
		for (int i = 0; i < count; i++)
		{
			ControlA *la = controls->at(i);
			SIZE displaySize = m_displaySize;
			ControlA *parent = la->GetParent();
			if (parent && m_mirrorMode != MirrorMode_BugHole)
			{
				displaySize = parent->GetSize();
			}
			ANCHOR anchor = la->GetAnchor();
			RECT bounds = la->GetBounds();
			if (anchor.right && !anchor.left)
            {
                bounds.left = bounds.left + displaySize.cx - oldSize.cx;
            }
            if (anchor.bottom && !anchor.top)
            {
                bounds.top = bounds.top + displaySize.cy - oldSize.cy;
            }
            if (anchor.right)
            {
                bounds.right = bounds.right + displaySize.cx - oldSize.cx;
            }
            if (anchor.bottom)
            {
                bounds.bottom = bounds.bottom + displaySize.cy - oldSize.cy;
            }
			la->SetBounds(bounds);
		}
	}
}

void NativeBase::SetDock( vector<ControlA*> *controls )
{
	int count = (int)controls->size();
	for (int i = 0; i < count; i++)
	{
		ControlA *la = (*controls)[i];
		SIZE size = m_displaySize;
		ControlA *parent = la->GetParent();
		if (parent && m_mirrorMode != MirrorMode_BugHole)
		{
			size = parent->GetSize();
		}
		DockStyleA dock = la->GetDock();
		if (dock != DockStyleA_None)
		{
			PADDING padding;
			if (parent)
			{
				padding = parent->GetPadding();
			}
			PADDING margin = la->GetMargin();
			SIZE cSize = la->GetSize();
			RECT spaceRect;
			spaceRect.left = padding.left + margin.left;
			spaceRect.top = padding.top + margin.top;
			spaceRect.right = size.cx - padding.right - margin.right;
			spaceRect.bottom = size.cy - padding.bottom - margin.bottom;
			RECT bounds;
			switch (dock)
            {
                case DockStyleA_Bottom:
                    bounds.left = spaceRect.left;
                    bounds.top = spaceRect.bottom - size.cy;
                    bounds.right = spaceRect.right;
                    bounds.bottom = spaceRect.bottom;
                    break;
                case DockStyleA_Fill:
                    bounds = spaceRect;
                    break;
                case DockStyleA_Left:
                    bounds.left = spaceRect.left;
                    bounds.top = spaceRect.top;
                    bounds.right = bounds.left + size.cx;
                    bounds.bottom = spaceRect.bottom;
                    break;
                case DockStyleA_Right:
                    bounds.left = spaceRect.right - size.cx;
                    bounds.top = spaceRect.top;
                    bounds.right = spaceRect.right;
                    bounds.bottom = spaceRect.bottom;
                    break;
                case DockStyleA_Top:
                    bounds.left = spaceRect.left;
                    bounds.top = spaceRect.top;
                    bounds.right = spaceRect.right;
                    bounds.bottom = bounds.top + size.cy;
                    break;
            }
			la->SetBounds(bounds);
		}
	}
}

void NativeBase::StartTimer( ControlA *control, int timerID, int interval )
{
	m_timers[timerID] = control;
	if (m_host)
	{
		m_host->StartTimer(timerID, interval);
	}
}

void NativeBase::StopTimer( int timerID )
{
	map<int, ControlA*>::iterator it = m_timers.find(timerID);
	if (it != m_timers.end())
	{
		if (m_host)
		{
			m_host->StopTimer(timerID);
		}
		m_timers.erase(it);
	}
}

void NativeBase::Update()
{
	if (m_host)
	{
		SIZE size = m_displaySize;
		m_displaySize = m_host->GetSize();
		if ((m_displaySize.cx != 0) && (m_displaySize.cy != 0))
		{
			SetAlign(&m_controls);
			SetAnchor(&m_controls, size);
			SetDock(&m_controls);
			int size = (int)m_controls.size();
			for (int i = 0; i < size; i++)
			{
				m_controls[i]->Update();
			}
		}
	}
}