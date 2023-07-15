#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"


CLine::CLine()
{
}

CLine::CLine(LINEINFO & _tInfoLine)
	:m_tInfo(_tInfoLine)
{
}

CLine::CLine(LINEPOS & _tLeft, LINEPOS & _tRight)
	: m_tInfo(_tLeft,_tRight)
{
}


CLine::~CLine()
{
}

void CLine::Initialize(void)
{
}

int CLine::Update(void)
{
	return 0;
}

void CLine::Late_Update(void)
{
}

void CLine::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(hDC, (int)m_tInfo.tLeftPos.fX + iScrollX, (int)m_tInfo.tLeftPos.fY + iScrollY, nullptr);
	LineTo(hDC, (int)m_tInfo.tRightPos.fX + iScrollX, (int)m_tInfo.tRightPos.fY + iScrollY);
}

void CLine::Release(void)
{
}
