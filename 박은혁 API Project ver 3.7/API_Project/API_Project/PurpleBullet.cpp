#include "stdafx.h"
#include "PurpleBullet.h"
#include "Manager.h"

float g_fSoundPurpleBullet = 0.5f;

CPurpleBullet::CPurpleBullet()
	:m_iSoundCount(0)
{
}


CPurpleBullet::~CPurpleBullet()
{
	Release();
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER_BULLET);
}

void CPurpleBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/Purpler_BULLET.bmp", L"Purpler_BULLET");

	m_pFrameKey = L"Purpler_BULLET";

	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_BACK;

	//////////////////////////////////////////사운드
	m_tSoundTime = GetTickCount();
}

int CPurpleBullet::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	if (m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"PurpleMonster_Bullet.wav", CSoundMgr::MONSTER_BULLET, g_fSoundPurpleBullet);
		++m_iSoundCount;
	}
	if (m_tSoundTime + 300 < GetTickCount())
	{
		++m_iSoundCount;
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER_BULLET);
	}

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CPurpleBullet::Late_Update(void)
{
	if (-100			>	m_tRect.left	||
		WINCX + 100 	<	m_tRect.right	||
		0				>	m_tRect.top		||
		WINCY			<	m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CPurpleBullet::Render(HDC hDC)
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
		30,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		30,
		RGB(237, 28, 36));
}

void CPurpleBullet::Release(void)
{
}
