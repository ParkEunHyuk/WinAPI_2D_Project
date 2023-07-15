#include "stdafx.h"
#include "MyRect.h"
#include "ScrollMgr.h"

CMyRect::CMyRect()
{
}

CMyRect::~CMyRect()
{
}

CMyRect::CMyRect(LINEINFO & tInfo)
	:m_tInfoRect(tInfo)
{
}

CMyRect::CMyRect(LINEPOS & _tLeft, LINEPOS & _tRight)
	: m_tInfoRect(_tLeft, _tRight)
{
}
void CMyRect::Initialize(void)
{
	//float		fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	//float		fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	//m_tInfo.fX = m_tInfoRect.tLeftPos.fX + abs((m_tInfoRect.tLeftPos.fX - m_tInfoRect.tRightPos.fX) * 0.5f);
	//m_tInfo.fY = m_tInfoRect.tLeftPos.fY + abs((m_tInfoRect.tLeftPos.fY - m_tInfoRect.tRightPos.fY) * 0.5f);

	//m_tInfo.fCX = abs(m_tInfoRect.tLeftPos.fX - m_tInfoRect.tRightPos.fX);
	//m_tInfo.fCY = abs(m_tInfoRect.tLeftPos.fY - m_tInfoRect.tRightPos.fY);
}
int CMyRect::Update(void)
{

	Update_Rect();
	return 0;
}
void CMyRect::Late_Update(void)
{
}
void CMyRect::Release(void)
{
}

void CMyRect::Render(HDC hDC)
{
	float		fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, float(m_tInfoRect.tLeftPos.fX + fScrollX), float(m_tInfoRect.tLeftPos.fY + fScrollY), float(m_tInfoRect.tRightPos.fX + fScrollX), float(m_tInfoRect.tRightPos.fY + fScrollY));

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

}