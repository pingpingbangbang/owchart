#include "..\\stdafx.h"
#include "..\\include\\Label\\LinkLabel.h"
using namespace OwLib;

_int64 LinkLabelA::GetPaintingLinkColor()
{
	if (!IsEnabled())
	{
		return m_disabledLinkColor;
	}
	NativeBase *native = GetNative();
	if (this == native->GetHoveredControl())
	{
		return m_activeLinkColor;
	}
	if (this == native->GetPushedControl())
	{
		return m_activeLinkColor;
	}
	if (m_linkVisited && m_visited)
	{
		return m_visitedLinkColor;
	}
	return m_linkColor;
}

LinkLabelA::LinkLabelA()
{
	m_activeLinkColor = COLOR::ARGB(255, 0, 0);
	m_disabledLinkColor = COLOR::ARGB(133, 133, 133);
	m_linkColor = COLOR::ARGB(0, 0, 255);
	m_linkVisited = false;
	m_visited = false;
	m_visitedLinkColor = COLOR::ARGB(128, 0, 128);
	SetCursor(CursorsA_Hand);
}

LinkLabelA::~LinkLabelA()
{

}

_int64 LinkLabelA::GetActiveLinkColor()
{
	return m_activeLinkColor;
}

void LinkLabelA::SetActiveLinkColor( _int64 activeLinkColor )
{
	m_activeLinkColor = activeLinkColor;
}

_int64 LinkLabelA::GetDisabledLinkColor()
{
	return m_disabledLinkColor;
}

void LinkLabelA::SetDisabledLinkColor( _int64 disabledLinkColor )
{
	m_disabledLinkColor = disabledLinkColor;
}

LinkBehaviorA LinkLabelA::GetLinkBehavior()
{
	return m_linkBehavior;
}

void LinkLabelA::SetLinkBehavior( LinkBehaviorA linkBehavior )
{
	m_linkBehavior = linkBehavior;
}

_int64 LinkLabelA::GetLinkColor()
{
	return m_linkColor;
}

void LinkLabelA::SetLinkColor( _int64 linkColor )
{
	m_linkColor = linkColor;
}

bool LinkLabelA::IsLinkVisited()
{
	return m_linkVisited;
}

void LinkLabelA::SetLinkVisited( bool linkVisited )
{
	m_linkVisited = linkVisited;
}

_int64 LinkLabelA::GetVisitedLinkColor()
{
	return m_visitedLinkColor;
}

void LinkLabelA::SetVisitedLinkColor( _int64 visitedLinkColor )
{
	m_visitedLinkColor = visitedLinkColor;
}

String LinkLabelA::GetControlType()
{
	return L"LinkLabel";
}

void LinkLabelA::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"activelinkcolor")
	{
		*type = L"color";
		*value = CStr::ConvertColorToStr(GetActiveLinkColor());
	}
	else if (name == L"disabledlinkcolor")
	{
		*type = L"color";
		*value = CStr::ConvertColorToStr(GetDisabledLinkColor());
	}
	else if (name == L"linkbehavior")
	{
		*type = L"enum:LinkBehaviorA";
		switch (GetLinkBehavior())
		{
		case LinkBehaviorA_AlwaysUnderLine:
			*value = L"AlwaysUnderLine";
			return;
		case LinkBehaviorA_HoverUnderLine:
			*value = L"HoverUnderLine";
			return;
		}
		*value = L"NeverUnderLine";
	}
	else if (name == L"linkcolor")
	{
		*type = L"color";
		*value = CStr::ConvertColorToStr(GetLinkColor());
	}
	else if (name == L"linkvisited")
	{
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(IsLinkVisited());
	}
	else if (name == L"visitedlinkcolor")
	{
		*type = L"color";
		*value = CStr::ConvertColorToStr(GetVisitedLinkColor());
	}
	else
	{
		LabelA::GetProperty(name, value, type);
	}
}

vector<String> LinkLabelA::GetPropertyNames()
{
	vector<wstring> propertyNames = ControlA::GetEventNames();
	propertyNames.push_back(L"ActiveLinkColor");
	propertyNames.push_back(L"DisabledLinkColor");
	propertyNames.push_back(L"LinkBehavior");
	propertyNames.push_back(L"LinkColor");
	propertyNames.push_back(L"LinkVisited");
	propertyNames.push_back(L"VisitedLinkColor");
	return propertyNames;
}

void LinkLabelA::OnClick( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	ControlA::OnClick(mp, button, clicks, delta);
	if (m_linkVisited)
	{
		m_visited = true;
	}
}

void LinkLabelA::OnMouseDown( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	ControlA::OnMouseDown(mp, button, clicks, delta);
	Invalidate();
}

void LinkLabelA::OnMouseEnter( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	ControlA::OnMouseEnter(mp, button, clicks, delta);
	Invalidate();
}

void LinkLabelA::OnMouseLeave( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	ControlA::OnMouseLeave(mp, button, clicks, delta);
	Invalidate();
}

void LinkLabelA::OnMouseUp( const POINT& mp, MouseButtonsA button, int clicks, int delta )
{
	ControlA::OnMouseUp(mp, button, clicks, delta);
	Invalidate();
}

void LinkLabelA::OnPaintForeground( CPaint *paint, const RECT& clipRect )
{
	String text = GetText();
	if (!text.empty())
	{
		int width = GetWidth();
		int height = GetHeight();
		if (width > 0 && height > 0)
		{
			FONT *font = GetFont();
			SIZE size = paint->TextSize(text.c_str(), font);
			_int64 paintingLinkColor = GetPaintingLinkColor();
			POINT point = {(width - size.cx) / 2, (height - size.cy) / 2};
			PADDING padding = GetPadding();
			switch (m_textAlign)
			{
			case ContentAlignmentA_BottomCenter:
				point.y = height - size.cy;
				break;

			case ContentAlignmentA_BottomLeft:
				point.x = padding.left;
				point.y = height - size.cy - padding.bottom;
				break;

			case ContentAlignmentA_BottomRight:
				point.x = width - size.cx - padding.right;
				point.y = height - size.cy - padding.bottom;
				break;

			case ContentAlignmentA_MiddleLeft:
				point.x = padding.left;
				break;

			case ContentAlignmentA_MiddleRight:
				point.x = width - size.cx - padding.right;
				break;

			case ContentAlignmentA_TopCenter:
				point.y = padding.top;
				break;

			case ContentAlignmentA_TopLeft:
				point.x = padding.left;
				point.y = padding.top;
				break;

			case ContentAlignmentA_TopRight:
				point.x = width - size.cx - padding.right;
				point.y = padding.top;
				break;
			}
			RECT rect = {point.x, point.y, point.x + size.cx, point.y + size.cy};
			if (AutoEllipsis() && (rect.right > clipRect.right || rect.bottom > clipRect.bottom))
			{
				if (rect.right > clipRect.right)
				{
					rect.right = clipRect.right;
				}
				if (rect.bottom > clipRect.bottom)
				{
					rect.bottom = clipRect.bottom;
				}
				paint->DrawTextAutoEllipsis(text.c_str(), paintingLinkColor, font, rect);
			}
			else
			{
				paint->DrawText(text.c_str(), paintingLinkColor, font, rect);
			}
			NativeBase *native = GetNative();
			if (m_linkBehavior == LinkBehaviorA_AlwaysUnderLine 
				|| m_linkBehavior == LinkBehaviorA_HoverUnderLine
				&& (this == native->GetPushedControl() || this == native->GetHoveredControl()))
			{
				paint->DrawLine(paintingLinkColor, 1.0f, 0, point.x, point.y + size.cy, point.x + size.cx, point.y + size.cy);
			}
		}
	}
}

void LinkLabelA::SetProperty( const String& name, const String& value )
{
	if (name == L"activelinkcolor")
	{
		SetActiveLinkColor(CStr::ConvertStrToColor(value));
	}
	else if (name == L"disabledlinkcolor")
	{
		SetDisabledLinkColor(CStr::ConvertStrToColor(value));
	}
	else if (name == L"linkbehavior")
	{
		String temp = CStr::ToLower(value);
		if (temp == L"alwaysunderline")
		{
			SetLinkBehavior(LinkBehaviorA_AlwaysUnderLine);
		}
		else if (temp == L"hoverunderline")
		{
			SetLinkBehavior(LinkBehaviorA_HoverUnderLine);
		}
		else
		{
			SetLinkBehavior(LinkBehaviorA_NeverUnderLine);
		}
	}
	else if (name == L"linkcolor")
	{
		SetLinkColor(CStr::ConvertStrToColor(value));
	}
	else if (name == L"linkvisited")
	{
		SetLinkVisited(CStr::ConvertStrToBool(value));
	}
	else if (name == L"visitedlinkcolor")
	{
		SetVisitedLinkColor(CStr::ConvertStrToColor(value));
	}
	else
	{
		LabelA::SetProperty(name, value);
	}
}