#include "stdafx.h"
#include "RingBullet.h"
#include "Manager.h"

float g_fSoundCarrotRing = 0.8f;

CRingBullet::CRingBullet()
{
}


CRingBullet::~CRingBullet()
{
	Release();
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER_BULLET);
}

void CRingBullet::Initialize(void)
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FarmMonster/RingBullet.bmp", L"RingBullet");

	m_pFrameKey = L"RingBullet";

	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_fSpeed = 5.f;

	m_eRenderGroup = RENDER_BACK;

	CSoundMgr::Get_Instance()->PlaySound(L"CarrotRing.wav", CSoundMgr::MONSTER_BULLET, g_fSoundCarrotRing);
}

int CRingBullet::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed; //0
	m_tInfo.fY +=  m_fSpeed;

	//////////////////////////////////////////////////////////////당근 몬스터 위에 있는것도 되고 아래에 있는것도 됨 주석 삭제하지 말 것.
	//m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed; //0
	//m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed; //0

	Update_Rect();

	return OBJ_NOEVENT;
}

void CRingBullet::Late_Update(void)
{
	if (WINCY - 20	<	m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CRingBullet::Render(HDC hDC)
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
	100,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
	100,
	RGB(237, 28, 36));
}

void CRingBullet::Release(void)
{
}
