#include "..\\stdafx.h"
#include "..\\include\\TabControl\\TabControl.h"
using namespace OwLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TabControlA::DrawMoving()
{
	if (m_animationState > 0)
	{
		bool drawing = false;
		int tabPageSize = (int)m_tabPages.size();
		TabPageA *selectedTabPage = GetSelectedTabPage();
		for (int i = 0; i < tabPageSize; i++)
		{
			TabPageA *tabPage = m_tabPages[i];
			if (tabPage != selectedTabPage || m_animationState != 1)
			{
				ButtonA *headerButton = tabPage->GetHeaderButton();
				if (headerButton->IsVisible())
				{
					int moving = headerButton->GetLeft();
					int pos = tabPage->GetHeaderLocation().x;
					if (m_layout == TabPageLayout_Left || m_layout == TabPageLayout_Right)
					{
						pos = tabPage->GetHeaderLocation().y;
						moving = headerButton->GetTop();
					}
					if (pos != moving)
					{
						int relative = moving;
						int sub = abs((int)(pos - relative));
						int step = 20;
						if (m_useAnimation)
						{
							if (tabPage == selectedTabPage)
							{
								if (sub > 200)
								{
									step = (sub / 200) * 100;
								}
							}
							else
							{
								step = sub;
							}
						}
						else
						{
							step = sub;
						}
						if (relative != pos)
						{
							if (pos > relative + step)
							{
								relative += step;
							}
							else if (pos < relative - step)
							{
								relative -= step;
							}
							else
							{
								relative = pos;
							}
							if (m_layout == TabPageLayout_Left || m_layout == TabPageLayout_Right)
							{
								headerButton->SetTop(relative);
							}
							else
							{
								headerButton->SetLeft(relative);
							}
							drawing = true;
						}
					}
				}
			}
		}
		if (!drawing && (m_animationState == 2))
		{
			m_animationState = 0;
		}
		Update();
		Invalidate();
	}
}

int TabControlA::GetTabPageIndex(TabPageA *tabPage)
{
	int tabPageSize = (int)m_tabPages.size();
	for(int i = 0; i < tabPageSize; i++)
	{
		if(m_tabPages[i] == tabPage)
		{
			return i;
		}
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TabControlA::TabControlA()
{
	m_animationState = 0;
	m_layout = TabPageLayout_Top;
	m_selectedIndex = -1;
	m_timerID = ControlA::GetNewTimerID();
	m_useAnimation = false;
}

TabControlA::~TabControlA()
{
	StopTimer(m_timerID);
	ClearControls();
}

TabPageLayout TabControlA::GetLayout()
{
	return m_layout;
}

void TabControlA::SetLayout(TabPageLayout layout)
{
	m_layout = layout;
}

int TabControlA::GetSelectedIndex()
{
	return m_selectedIndex;
}

void TabControlA::SetSelectedIndex(int selectedIndex)
{
	int tabPageSize = (int)m_tabPages.size();
	if (tabPageSize > 0 && selectedIndex >= 0 && selectedIndex < tabPageSize)
	{
		m_selectedIndex = selectedIndex;
		SetSelectedTabPage(m_tabPages[selectedIndex]);
	}
}

TabPageA* TabControlA::GetSelectedTabPage()
{
	int tabPageSize = (int)m_tabPages.size();
	if (tabPageSize > 0 && m_selectedIndex >= 0 && m_selectedIndex < tabPageSize)
	{
		return m_tabPages[m_selectedIndex];
	}
	return 0;
}

void TabControlA::SetSelectedTabPage(TabPageA *selectedTabPage)
{
	int index = -1;
	int tabPageSize = (int)m_tabPages.size();
	if (selectedTabPage && tabPageSize > 0)
	{
		TabPageA *oldSelectedTabPage = GetSelectedTabPage();
		for (int i = 0; i < tabPageSize; i++)
		{
			TabPageA *tabPage = m_tabPages[i];
			if (tabPage == selectedTabPage)
			{
				index = i;
				tabPage->SetVisible(true);
			}
			else
			{
				tabPage->SetVisible(false);
			}
		}
		if (index != -1)
		{
			m_selectedIndex = index;
		}
		else if (tabPageSize > 0)
		{
			m_selectedIndex = 0;
		}
		TabPageA *newSelectedTabPage = GetSelectedTabPage();
		if (oldSelectedTabPage != newSelectedTabPage)
		{
			OnSelectedTabPageChanged();
		}
		newSelectedTabPage->BringToFront();
		newSelectedTabPage->GetHeaderButton()->BringToFront();
	}
	else
	{
		m_selectedIndex = -1;
	}
}

bool TabControlA::UseAnimation()
{
	return m_useAnimation;
}

void TabControlA::SetUseAnimation(bool useAnimation)
{
	m_useAnimation = useAnimation;
	if (m_useAnimation)
	{
		StartTimer(m_timerID, 20);
	}
	else
	{
		StopTimer(m_timerID);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TabControlA::AddControl(ControlA *control)
{
	TabPageA *item = dynamic_cast<TabPageA*>(control);
	if (item)
	{
		item->SetTabControl(this);
	}
	ControlA::AddControl(control);
	if (item)
	{
		m_tabPages.push_back(item);
		SetSelectedTabPage(item);
	}
}

String TabControlA::GetControlType()
{
	return L"TabControl";
}

void TabControlA::ClearControls()
{
	m_tabPages.clear();
	m_selectedIndex = -1;
	ControlA::ClearControls();
}

vector<wstring> TabControlA::GetEventNames()
{
	vector<wstring> ws = ControlA::GetEventNames();
	ws.push_back(L"SelectedTabPageChanged");
	return ws;
}

void TabControlA::GetProperty(const String& name, String *value, String *type)
{
	if (name == L"layout")
	{
		*type = L"enum:TabPageLayout";
		if (GetLayout() == TabPageLayout_Left)
		{
			*value = L"Left";
		}
		else if (GetLayout() == TabPageLayout_Right)
		{
			*value = L"Right";
		}
		else if (GetLayout() == TabPageLayout_Bottom)
		{
			*value = L"Bottom";
		}
		else
		{
			*value = L"Top";
		}
	}
	else if (name == L"selectedindex")
	{
		*type = L"int";
		*value = CStr::ConvertIntToStr(GetSelectedIndex());
	}
	else if (name == L"useanimation")
	{
		*type = L"bool";
		*value = CStr::ConvertBoolToStr(UseAnimation());
	}
	else
	{
		DivA::GetProperty(name, value, type);
	}
}

vector<String> TabControlA::GetPropertyNames()
{
	vector<String> propertyNames = DivA::GetPropertyNames();
	propertyNames.push_back(L"Layout");
	propertyNames.push_back(L"SelectedIndex");
	propertyNames.push_back(L"UseAnimation");
	return propertyNames;
}

void TabControlA::InsertControl(int index, ControlA *control)
{
	TabPageA *item = dynamic_cast<TabPageA*>(control);
	if (item)
	{
		item->SetTabControl(this);
	}
	DivA::AddControl(control);
	if(item)
	{
		m_tabPages.insert(m_tabPages.begin() + index, item);
		SetSelectedTabPage(item);
	}
}

void TabControlA::OnDragTabHeaderBegin(TabPageA *tabPage)
{
	m_animationState = 1;
	tabPage->GetHeaderButton()->BringToFront();
}

void TabControlA::OnDragTabHeaderEnd(TabPageA *tabPage)
{
	if (m_animationState == 1)
	{
		m_animationState = 2;
		DrawMoving();
	}
}

void TabControlA::OnDraggingTabHeader(TabPageA *tabPage)
{
	ButtonA *headerButton = tabPage->GetHeaderButton();
	int moving = headerButton->GetLeft();
	if (m_layout == TabPageLayout_Left || m_layout == TabPageLayout_Right)
	{
		moving = headerButton->GetTop();
	}
	int tabPageSize = (int)m_tabPages.size();
	for (int i = 0; i < tabPageSize; i++)
	{
		TabPageA *page = m_tabPages[i];
		if (page != tabPage)
		{
			ButtonA *tpHeader = page->GetHeaderButton();
			if (tpHeader->IsVisible())
			{
				int pos = page->GetHeaderLocation().x;
				int size = tpHeader->GetWidth();
				int sSize = headerButton->GetWidth();
				if (m_layout == TabPageLayout_Left || m_layout == TabPageLayout_Right)
				{
					pos = page->GetHeaderLocation().y;
					size = tpHeader->GetHeight();
					sSize = headerButton->GetHeight();
				}
				bool instead = false;
				if (moving > pos && moving < pos + size / 2)
				{
					instead = true;
				}
				if (moving < pos && moving + sSize > pos + size / 2 && moving + sSize < pos + size)
				{
					instead = true;
				}
				if (instead)
				{
					POINT headerLocation = tabPage->GetHeaderLocation();
					if (m_layout == TabPageLayout_Left || m_layout == TabPageLayout_Right)
					{
						POINT point1 = { tabPage->GetHeaderLocation().x, pos };
						POINT point2 = { page->GetHeaderLocation().x, headerLocation.y };
						tabPage->SetHeaderLocation(point1);
						page->SetHeaderLocation(point2);
					}
					else
					{
						POINT point1 = { pos, tabPage->GetHeaderLocation().y };
						POINT point2 = { headerLocation.x, page->GetHeaderLocation().y };
						tabPage->SetHeaderLocation(point1);
						page->SetHeaderLocation(point2);
					}
					int oIndex = GetTabPageIndex(tabPage);
					int nIndex = GetTabPageIndex(page);
					m_tabPages[oIndex] = page;
					m_tabPages[nIndex] = tabPage;
					m_selectedIndex = nIndex;
					break;
				}
			}
		}
	}
	DrawMoving();
}

void TabControlA::OnLoad()
{
	ControlA::OnLoad();
	if (m_useAnimation)
	{
		StartTimer(m_timerID, 20);
	}
	else
	{
		StopTimer(m_timerID);
	}
}

void TabControlA::OnSelectedTabPageChanged()
{
	ControlA::CallEvents(EVENTID::SELECTEDTABPAGECHANGED);
}

void TabControlA::OnTimer(int timerID)
{
	ControlA::OnTimer(timerID);
	if (m_timerID == timerID)
	{
		DrawMoving();
	}
}

void TabControlA::RemoveControl(ControlA *control)
{
	TabPageA *tabPage = dynamic_cast<TabPageA*>(control);
	if (tabPage)
	{
		int tabPageSize = (int)m_tabPages.size();
		if (tabPageSize > 0)
		{
			TabPageA *selectedTabPage = GetSelectedTabPage();
			if (selectedTabPage == tabPage)
			{
				if (m_selectedIndex > 0)
				{
					if (m_selectedIndex < tabPageSize - 1)
					{
						selectedTabPage = m_tabPages[m_selectedIndex + 1];
					}
					else
					{
						selectedTabPage = m_tabPages[m_selectedIndex - 1];
					}
				}
				else if (tabPageSize > 1)
				{
					selectedTabPage = m_tabPages[m_selectedIndex + 1];
				}
			}
			vector<TabPageA*>::iterator sIter = m_tabPages.begin();
			for(; sIter != m_tabPages.end(); ++sIter)
			{
				if(*sIter == tabPage)
				{
					m_tabPages.erase(sIter);
					break;
				}
			}
			ButtonA *headerButton = tabPage->GetHeaderButton();
			DivA::RemoveControl(headerButton);
			DivA::RemoveControl(tabPage);
			tabPage->SetTabControl(0);
			SetSelectedTabPage(selectedTabPage);
		}
	}
	else
	{
		DivA::RemoveControl(control);
	}
}

void TabControlA::SetProperty(const String& name, const String& value)
{
	if (name == L"layout")
	{
		String valueLower = CStr::ToLower(value);
		if (valueLower == L"left")
		{
			SetLayout(TabPageLayout_Left);
		}
		else if (valueLower == L"top")
		{
			SetLayout(TabPageLayout_Top);
		}
		else if (valueLower == L"right")
		{
			SetLayout(TabPageLayout_Right);
		}
		else if (valueLower == L"bottom")
		{
			SetLayout(TabPageLayout_Bottom);
		}
	}
	else if (name == L"selectedindex")
	{
		SetSelectedIndex(CStr::ConvertStrToInt(value));
	}
	else if (name == L"useanimation")
	{
		SetUseAnimation(CStr::ConvertStrToBool(value));
	}
	else
	{
		DivA::SetProperty(name, value);
	}
}

void TabControlA::Update()
{
	if (GetNative())
	{
		DivA::Update();
		PADDING padding = GetPadding();
		int left = padding.left;
		int top = padding.top;
		int width = GetWidth() - padding.left - padding.right;
		int height = GetHeight() - padding.top - padding.bottom;
		int tabPageSize = (int)m_tabPages.size();
		for (int i = 0; i < tabPageSize; i++)
		{
			TabPageA *tabPage = m_tabPages[i];
			ButtonA *headerButton = tabPage->GetHeaderButton();
			if (headerButton->IsVisible())
			{
				PADDING margin = headerButton->GetMargin();
				int tw = headerButton->GetWidth() + margin.left + margin.right;
				int th = headerButton->GetHeight() + margin.top + margin.bottom;
				RECT bounds = {0};
				POINT headerLocation = {0};
				switch (m_layout)
				{
				case TabPageLayout_Bottom:
					bounds.left = padding.left;
					bounds.top = padding.top;
					bounds.right = width;
					bounds.bottom = height - th;
					headerLocation.x = left + margin.left;
					headerLocation.y = (height - th) + margin.top;
					break;
				case TabPageLayout_Left:
					bounds.left = tw;
					bounds.top = padding.top;
					bounds.right = width;
					bounds.bottom = height;
					headerLocation.x = padding.left + margin.left;
					headerLocation.y = top + margin.top;
					break;
				case TabPageLayout_Right:
					bounds.left = padding.left;
					bounds.top = padding.top;
					bounds.right = width - tw;
					bounds.bottom = height;
					headerLocation.x = (width - tw) + margin.left;
					headerLocation.y = top + margin.top;
					break;
				case TabPageLayout_Top:
					bounds.left = padding.left;
					bounds.top = th;
					bounds.right = width;
					bounds.bottom = height;
					headerLocation.x = left + margin.left;
					headerLocation.y = padding.top + margin.top;
					break;
				}
				tabPage->SetBounds(bounds);
				tabPage->SetHeaderLocation(headerLocation);
				if (m_animationState > 0)
				{
					if (m_layout == TabPageLayout_Left || m_layout == TabPageLayout_Right)
					{
						headerLocation.y = headerButton->GetTop();
					}
					else if (m_layout == TabPageLayout_Bottom || m_layout == TabPageLayout_Top)
					{
						headerLocation.x = headerButton->GetLeft();
					}
				}
				headerButton->SetLocation(headerLocation);
				left += tw;
				top += th;
				continue;
			}
			tabPage->SetVisible(false);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////