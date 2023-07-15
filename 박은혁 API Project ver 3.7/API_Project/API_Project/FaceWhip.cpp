#include "stdafx.h"
#include "FaceWhip.h"
#include "Manager.h"

float g_fSoundFaceWhip = 0.8f;

CFaceWhip::CFaceWhip()
	:m_iSoundCount(0)
{
}


CFaceWhip::~CFaceWhip()
{
}

void CFaceWhip::Initialize(void)
{
	m_tInfo.fCX = 750.f;
	m_tInfo.fCY = 175.f;

	m_eCurState = ATTACK;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_tTimeSound = GetTickCount();
}

int CFaceWhip::Update(void)
{
	if (m_tFrame.iFrameStart == 6 )
	{
		return OBJ_DEAD;
	}

	/////////////////////////////////사운드에 관한 내용
	if (m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"FaceWhip.wav", CSoundMgr::MONSTER_BULLET, g_fSoundFaceWhip);
	}
	if (m_tTimeSound + 400 < GetTickCount() && m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
		++m_iSoundCount;
	}
	//////////////////////////

	State_Change();
	Update_Rect();
	Move_Frame();
	return OBJ_NOEVENT;
}

void CFaceWhip::Late_Update(void)
{
}

void CFaceWhip::Render(HDC hDC)
{
#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
#endif // !_DEBUG
}

void CFaceWhip::Release(void)
{
}

void CFaceWhip::State_Change(void)
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
