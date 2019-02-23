#include "..\\stdafx.h"
#include "..\\include\\Window\\WindowFrame.h"
using namespace OwLib;

WindowFrameA::WindowFrameA()
{
	SetBackColor(COLOR_EMPTY);
	SetBorderColor(COLOR_EMPTY);
	SetDock(DockStyleA_Fill);
}

WindowFrameA::~WindowFrameA()
{
}

bool WindowFrameA::ContainsPoint( const POINT& point )
{
	vector<ControlA*> controls = GetControls();
	int count = (int)controls.size();
	for (int i = 0; i < count; i++)
	{
		WindowA *window = dynamic_cast<WindowA*>(controls[i]);
		if (window && window->GetFrame() == this)
		{
			return (window->IsDialog() || window->ContainsPoint(point));
		}
	}
	return false;
}

String WindowFrameA::GetControlType()
{
	return L"WindowFrame";
}

void WindowFrameA::Invalidate()
{
	if (m_native)
	{
		vector<ControlA*> controls = GetControls();
		int count = (int)controls.size();
		for (int i = 0; i < count; i++)
		{
			WindowA *wa = dynamic_cast<WindowA*>(controls[i]);
			if (wa)
			{
				m_native->Invalidate(wa->GetDynamicPaintRect());
				return;
			}
		}
	}
}

void WindowFrameA::OnPaintBackground( CPaint *paint, const RECT& clipRect )
{
	ControlA::OnPaintBackground(paint, clipRect);
	if (paint->SupportTransparent())
	{
		vector<ControlA*> controls = GetControls();
		int count = (int)controls.size();
		for (int i = 0; i < count; i++)
		{
			WindowA *wa = dynamic_cast<WindowA*>(controls[i]);
			if (wa)
			{
				_int64 shadowColor = wa->GetShadowColor();
				int shadowSize = wa->GetShadowSize();
				if (shadowColor != COLOR_EMPTY && shadowSize > 0 && wa->IsDialog() && wa->GetFrame() == this)
				{
					RECT bounds = wa->GetBounds();
					RECT rect;
					rect.left = bounds.left - shadowSize;
					rect.top = bounds.top - shadowSize;
					rect.right = bounds.left;
					rect.bottom = bounds.bottom + shadowSize;
					paint->FillRect(shadowColor, rect);

					RECT rect3;
					rect3.left = bounds.right;
					rect3.top = bounds.top - shadowSize;
					rect3.right = bounds.right + shadowSize;
					rect3.bottom = bounds.bottom + shadowSize;
					paint->FillRect(shadowColor, rect3);

					RECT rect4;
					rect4.left = bounds.left;
					rect4.top = bounds.top - shadowSize;
					rect4.right = bounds.right;
					rect4.bottom = bounds.top;
					paint->FillRect(shadowColor, rect4);

					RECT rect5;
					rect5.left = bounds.left;
					rect5.top = bounds.bottom;
					rect5.right = bounds.right;
					rect5.bottom = bounds.bottom + shadowSize;
					paint->FillRect(shadowColor, rect5);
					return;
				}
			}
		}
	}
}
