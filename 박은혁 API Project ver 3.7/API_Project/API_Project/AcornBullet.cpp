#include "stdafx.h"
#include "AcornBullet.h"
#include "Manager.h"

float g_fSoundAcorn = 0.8f;

CAcornBullet::CAcornBullet()
	:m_bIntroEnd(false), m_iSoundCount(0)
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER_BULLET);
}


CAcornBullet::~CAcornBullet()
{
}

void CAcornBullet::Initialize(void)
{
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;

	m_fSpeed = 10.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/AcornBullet.bmp", L"AcornBullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/AcornBulletIntro.bmp", L"AcornBulletIntro");
	m_pFrameKey = L"AcornBulletIntro";

	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_BACK;

	m_tTimeSound = GetTickCount();
}

int CAcornBullet::Update(void)
{
	if (m_bIntroEnd == true)
	{
		m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;
	}

	/////////////////////////////////사운드에 관한 내용
	if (m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"AcornBullet.wav", CSoundMgr::MONSTER_BULLET, g_fSoundAcorn);
	}
	if (m_tTimeSound + 1200 < GetTickCount() && m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
		++m_iSoundCount;
	}
	//////////////////////////

	if (m_eCurState == INTRO && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_tInfo.fX = m_tInfo.fX;
		m_tInfo.fY = m_tInfo.fY;
		m_tInfo.fCX = 70.f;
		m_tInfo.fCY = 30.f;
		m_eCurState = IDLE;
		m_bIntroEnd = true;
	}
	State_Change();
	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CAcornBullet::Late_Update(void)
{
	if (-100			>	m_tRect.left ||
		WINCX + 100 	<	m_tRect.right ||
		-100			>	m_tRect.top ||
		WINCY + 100		<	m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CAcornBullet::Render(HDC hDC)
{
#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
#endif // !_DEBUG
	if (70 == m_tInfo.fCY)
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
			70,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
			70,
			RGB(237, 28, 36));
	}
	else
	{
		m_pFrameKey = L"AcornBullet";
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left),	//	2, 3인자 복사 받을 위치의 좌표를 전달
			int(m_tRect.top),
			(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
			(int)m_tInfo.fCY,
			hMemDC,							// 비트맵 정보를 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8인자 비트맵을 출력할 시작좌표
			m_tFrame.iFrameScene * (int)m_tInfo.fCY,
			70,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
			30,
			RGB(237, 28, 36));
	}
}

void CAcornBullet::Release(void)
{
}

void CAcornBullet::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case IDLE:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
