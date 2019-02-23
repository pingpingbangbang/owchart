#include "..\\stdafx.h"
#include "..\\include\\Base\\CPaint.h"

_int64 COLOR::ARGB( int r, int g, int b )
{
    return r | g << 8 | b << 16;
}

_int64 COLOR::ARGB( int a, int r, int g, int b )
{
    if (a == 255) 
	{
      return ARGB(r, g, b);
    }
    if (a == 0) 
	{
      return COLOR_EMPTY;
    }
    _int64 rgb = (_int64)ARGB(r, g, b);
    _int64 argb = -(rgb * 1000 + a);
    return argb;
}

void COLOR::ToARGB( CPaint *paint, _int64 dwPenColor, int *a, int *r, int *g, int *b )
{
	if (paint != 0)
    {
        dwPenColor = paint->GetColor(dwPenColor);
    }
    *a = 255;
    if (dwPenColor < 0L)
    {
        dwPenColor = abs((double)dwPenColor);
		if(dwPenColor >= 1)
		{
			*a = dwPenColor % 1000;
		}
		else
		{
			*a = 255;
		}
        dwPenColor /= 1000;
    }
    *r = (int) (dwPenColor & 0xffL);
    *g = (int) ((dwPenColor >> 8) & 0xffL);
    *b = (int) ((dwPenColor >> 16) & 0xffL);
}

_int64 COLOR::RatioColor( CPaint *paint, _int64 originalColor, double ratio )
{
	int a = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    ToARGB(paint, originalColor, &a, &r, &g, &b);
    r = (int) (r * ratio);
    g = (int) (g * ratio);
    b = (int) (b * ratio);
    if (r > 255)
    {
        r = 255;
    }
    if (g > 255)
    {
        g = 255;
    }
    if (b > 255)
    {
        b = 255;
    }
    return ARGB(a, r, g, b);
}

_int64 COLOR::Reverse( CPaint *paint, _int64 originalColor )
{
    int a = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    ToARGB(paint, originalColor, &a, &r, &g, &b);
    return ARGB(a, 255 - r, 255 - g, 255 - b);
}

CPaint::CPaint()
{

}

CPaint::~CPaint()
{

}

void CPaint::AddArc( const RECT& rect, float startAngle, float sweepAngle )
{

}

void CPaint::AddBezier( POINT *apt, int cpt )
{

}

void CPaint::AddCurve( POINT *apt, int cpt )
{

}

void CPaint::AddEllipse( const RECT& rect )
{

}

void CPaint::AddLine( int x1, int y1, int x2, int y2 )
{

}

void CPaint::AddRect( const RECT& rect )
{

}

void CPaint::AddPie( const RECT& rect, float startAngle, float sweepAngle )
{

}

void CPaint::AddText( LPCWSTR strText, FONT *font, const RECT& rect )
{

}

void CPaint::BeginExport( const String& exportPath, const RECT& rect )
{

}

void CPaint::BeginPaint( HDC hDC, const RECT& wRect, const RECT& pRect )
{

}

void CPaint::BeginPath()
{

}

void CPaint::ClearCaches()
{

}

void CPaint::ClipPath()
{

}

void CPaint::CloseFigure()
{

}

void CPaint::ClosePath()
{

}

void CPaint::DrawArc( _int64 dwPenColor, float width, int style, const RECT& rect, float startAngle, float sweepAngle )
{

}

void CPaint::DrawBezier( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{

}

void CPaint::DrawCurve( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{

}

void CPaint::DrawEllipse( _int64 dwPenColor, float width, int style, const RECT& rect )
{

}

void CPaint::DrawEllipse( _int64 dwPenColor, float width, int style, int left, int top, int right, int bottom )
{

}

void CPaint::DrawImage( LPCWSTR imagePath, const RECT& rect )
{

}

void CPaint::DrawLine( _int64 dwPenColor, float width, int style, const POINT& x, const POINT& y )
{

}

void CPaint::DrawLine( _int64 dwPenColor, float width, int style, int x1, int y1, int x2, int y2 )
{

}

void CPaint::DrawPath( _int64 dwPenColor, float width, int style )
{

}

void CPaint::DrawPie( _int64 dwPenColor, float width, int style, const RECT& rect, float startAngle, float sweepAngle )
{

}

void CPaint::DrawPolygon( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{

}

void CPaint::DrawPolyline( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{

}

void CPaint::DrawRect( _int64 dwPenColor, float width, int style, int left, int top, int right, int bottom )
{

}

void CPaint::DrawRect( _int64 dwPenColor, float width, int style, const RECT& rect )
{

}

void CPaint::DrawRoundRect( _int64 dwPenColor, float width, int style, const RECT& rect, int cornerRadius )
{

}

void CPaint::DrawText( LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECT& rect )
{

}

void CPaint::DrawText( LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECTF& rect )
{

}

void CPaint::DrawTextAutoEllipsis( LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECT& rect )
{

}

void CPaint::EndExport()
{

}

void CPaint::EndPaint()
{

}

void CPaint::ExcludeClipPath()
{

}

void CPaint::FillEllipse( _int64 dwPenColor, const RECT& rect )
{

}

void CPaint::FillGradientEllipse( _int64 dwFirst, _int64 dwSecond, const RECT& rect, int angle )
{

}

void CPaint::FillGradientPath( _int64 dwFirst, _int64 dwSecond, const RECT& rect, int angle )
{

}

void CPaint::FillGradientPolygon( _int64 dwFirst, _int64 dwSecond, POINT *apt, int cpt, int angle )
{

}

void CPaint::FillGradientRect( _int64 dwFirst, _int64 dwSecond, const RECT& rect, int cornerRadius, int angle )
{

}

void CPaint::FillPath( _int64 dwPenColor )
{

}

void CPaint::FillPie( _int64 dwPenColor, const RECT& rect, float startAngle, float sweepAngle )
{

}

void CPaint::FillPolygon( _int64 dwPenColor, POINT *apt, int cpt )
{

}

void CPaint::FillRect( _int64 dwPenColor, const RECT& rect )
{

}

void CPaint::FillRect( _int64 dwPenColor, int left, int top, int right, int bottom )
{

}

void CPaint::FillRoundRect( _int64 dwPenColor, const RECT& rect, int cornerRadius )
{

}

_int64 CPaint::GetColor( _int64 dwPenColor )
{
	return 0;
}

_int64 CPaint::GetPaintColor( _int64 dwPenColor )
{
	return 0;
}

POINT CPaint::GetOffset()
{
	return POINT();
}

POINT CPaint::Rotate( const POINT& op, const POINT& mp, int angle )
{
	return POINT();
}

void CPaint::SetClip( const RECT& rect )
{

}

void CPaint::SetLineCap( int startLineCap, int endLineCap )
{

}

void CPaint::SetOffset( const POINT& offset )
{

}

void CPaint::SetOpacity( float opacity )
{

}

void CPaint::SetResourcePath( const String& resourcePath )
{

}

void CPaint::SetRotateAngle( int rotateAngle )
{

}

void CPaint::SetScaleFactor( double scaleFactorX, double scaleFactorY )
{

}

void CPaint::SetSmoothMode( int smoothMode )
{

}

void CPaint::SetTextQuality( int textQuality )
{

}

bool CPaint::SupportTransparent()
{
	return false;
}

SIZE CPaint::TextSize( LPCWSTR strText, FONT *font )
{
	return SIZE();
}

SIZEF CPaint::TextSizeF( LPCWSTR strText, FONT *font )
{
	SIZEF sz = {0, 0};
	return sz;
}
