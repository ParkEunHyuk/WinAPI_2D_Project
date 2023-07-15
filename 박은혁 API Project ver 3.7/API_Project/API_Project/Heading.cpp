#include "stdafx.h"
#include "Heading.h"


CHeading::CHeading()
{
}


CHeading::~CHeading()
{
}

void CHeading::Initialize(void)
{
	m_tInfo.fCX = 200;
	m_tInfo.fCY = 200.f;

	m_eCurState = ATTACK;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CHeading::Update(void)
{
	if (m_tFrame.iFrameStart == 4)
	{
		return OBJ_DEAD;
	}
	State_Change();
	Update_Rect();
	Move_Frame();
	return OBJ_NOEVENT;
}

void CHeading::Late_Update(void)
{
}

void CHeading::Render(HDC hDC)
{
#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
#endif // !_DEBUG
}

void CHeading::Release(void)
{
}

void CHeading::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ATTACK:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
