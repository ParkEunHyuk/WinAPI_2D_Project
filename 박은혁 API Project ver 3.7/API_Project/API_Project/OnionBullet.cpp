#include "stdafx.h"
#include "OnionBullet.h"
#include "Manager.h"

float g_fSoundCryBullet = 0.5f;
COnionBullet::COnionBullet()
{
}


COnionBullet::~COnionBullet()
{
	Release();
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER_BULLET);
}

void COnionBullet::Initialize(void)
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 40.f;

	m_fSpeed = 5.f;

	m_tStamina.iMaxHp = 1;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FarmMonster/OnionBullet.bmp", L"OnionBullet");

	m_pFrameKey = L"OnionBullet";

	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_BACK;
}

int COnionBullet::Update(void)
{
	if (true == m_bDead)
	{
		m_eCurState = DIE;
		m_tInfo.fX = m_tInfo.fX;
		if (false == m_bFrameDieCheck)
		{
			m_tFrame.iFrameStart = 0;
			m_bFrameDieCheck = true;
			CSoundMgr::Get_Instance()->PlaySound(L"OnionBulletBoom.wav", CSoundMgr::MONSTER_BULLET, g_fSoundCryBullet);
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			return OBJ_DEAD;
		}
	}
	if (0 == m_tStamina.iMaxHp)
	{
		m_bDead = true;
		m_bCollsion = true;
	}

	if (false == m_bDead)
	{
		if (BULLET::DOWN == m_eDir)
			m_tInfo.fY += 5.f;
		m_bCollsion = false;
	}

	State_Change();
	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void COnionBullet::Late_Update(void)
{
	if (WINCY-20	<	m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void COnionBullet::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hMemDC,							// 비트맵 정보를 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8인자 비트맵을 출력할 시작좌표
		m_tFrame.iFrameScene * (int)m_tInfo.fCY,
		20,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		40,
		RGB(237, 28, 36));
}

void COnionBullet::Release(void)
{
}

void COnionBullet::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DIE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
