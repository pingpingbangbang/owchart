#include "..\\stdafx.h"
#include "..\\include\\Base\\ControlHost.h"
using namespace OwLib;

ControlHost::ControlHost()
{

}

ControlHost::~ControlHost()
{

}

NativeBase* ControlHost::GetNative()
{
	return 0;
}

void ControlHost::SetNative( NativeBase *native )
{

}

void ControlHost::ActiveMirror()
{

}

bool ControlHost::AllowOperate()
{
	return true;
}

bool ControlHost::AllowPartialPaint()
{
	return true;
}

void ControlHost::BeginInvoke( ControlA *control, void *args )
{

}

void ControlHost::Copy( string text )
{

}

ControlA* ControlHost::CreateInternalControl( ControlA *parent, const String& clsid )
{
	return 0;
}

CursorsA ControlHost::GetCursor()
{
	return CursorsA_Arrow;
}

int ControlHost::GetIntersectRect( LPRECT lpDestRect, const RECT *lpSrc1Rect, const RECT *lpSrc2Rect )
{
	return 0;
}

POINT ControlHost::GetMousePoint()
{
	return POINT();
}

SIZE ControlHost::GetSize()
{
	return SIZE();
}

int ControlHost::GetUnionRect( LPRECT lpDestRect, const RECT *lpSrc1Rect, const RECT *lpSrc2Rect )
{
	return 0;
}

void ControlHost::Invalidate()
{

}

void ControlHost::Invalidate( const RECT& rect )
{

}

void ControlHost::Invoke( ControlA *control, void *args )
{

}

bool ControlHost::IsKeyPress( char key )
{
	return false;
}

string ControlHost::Paste()
{
	return "";
}

void ControlHost::SetAllowOperate( bool allowOperate )
{

}

void ControlHost::SetAllowPartialPaint( bool allowPartialPaint )
{

}

void ControlHost::SetCursor( CursorsA cursor )
{

}

void ControlHost::ShowToolTip( void *sender, const wstring& text, const POINT& mp)
{

}

void ControlHost::StartTimer( int timerID, int interval )
{

}

void ControlHost::StopTimer( int timerID )
{

}