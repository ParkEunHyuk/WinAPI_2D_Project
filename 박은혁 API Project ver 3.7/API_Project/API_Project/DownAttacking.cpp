#include "stdafx.h"
#include "DownAttacking.h"


CDownAttacking::CDownAttacking()
{
}


CDownAttacking::~CDownAttacking()
{
}


void CDownAttacking::Initialize(void)
{
	m_tInfo.fCX = 200;
	m_tInfo.fCY = 150.f;

	m_eCurState = ATTACK;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CDownAttacking::Update(void)
{
	if (m_tFrame.iFrameStart > 4)
	{
		return OBJ_DEAD;
	}
	if (m_bDead == true)
	{
		return OBJ_DEAD;
	}
	State_Change();
	Update_Rect();
	Move_Frame();
	return OBJ_NOEVENT;
}

void CDownAttacking::Late_Update(void)
{
}

void CDownAttacking::Render(HDC hDC)
{
#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
#endif // !_DEBUG
}

void CDownAttacking::Release(void)
{
}

void CDownAttacking::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ATTACK:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
