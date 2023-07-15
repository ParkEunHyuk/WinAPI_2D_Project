#include "stdafx.h"
#include "BasicBullet.h"
#include "Manager.h"

float g_fSoundPlayerBullet = 1.0f;
CBasicBullet::CBasicBullet()
{
}


CBasicBullet::~CBasicBullet()
{
	Release();
}

void CBasicBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_BULLET.bmp", L"PlayerBullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_BULLET_DIE.bmp", L"PlayerBulletDie");

	m_pFrameKey = L"PlayerBullet";

	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_BACK;
	
	/////////////////////////////////////////사운드
	//CSoundMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->PlaySound(L"PlayerBullet.wav", CSoundMgr::BULLET, g_fSoundPlayerBullet);
	m_tSoundTime = GetTickCount();
}

int CBasicBullet::Update(void)
{

	if (true == m_bDead)
	{
		m_eCurState = DIE;
		m_pFrameKey = L"PlayerBulletDie";
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 100.f;
		if (false == m_bFrameDieCheck)
		{
			m_tFrame.iFrameStart = 0;
			m_bFrameDieCheck = true;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			return OBJ_DEAD;
		}
	}
	if (m_tSoundTime + 5 < GetTickCount())
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BULLET);
		m_tSoundTime = GetTickCount();
	}

	if (false == m_bDead)
	{
		if (BULLET::RIGHT == m_eDir)
			m_tInfo.fX += 10.f;
		else if (BULLET::LEFT == m_eDir)
			m_tInfo.fX -= 10.f;
		else if (BULLET::UP == m_eDir)
			m_tInfo.fY -= 10.f;
		else if (BULLET::DOWN == m_eDir)
			m_tInfo.fY += 10.f;
		Update_Rect();
	}

	State_Change();
	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBasicBullet::Late_Update(void)
{
	//원래는 0과 WINCX인데 화면 밖에서 소멸시킬려고 -40이랑 +40시킴
	if (-70				>	m_tRect.left	|| //플레이어가 오른쪽으로 가면 스크롤은 왼쪽으로 간다 -가 되므로 --해서 양수로 바꿔줘야한다.
		WINCX+70		<	m_tRect.right	||
		-70				>	m_tRect.top		||
		WINCY			<	m_tRect.bottom	)
	{
		m_bDead = true;
	}
}

void CBasicBullet::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
#endif // !_DEBUG

	if (m_pFrameKey != L"PlayerBulletDie")
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	//	2, 3인자 복사 받을 위치의 좌표를 전달
			int(m_tRect.top),
			(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
			(int)m_tInfo.fCY,
			hMemDC,							// 비트맵 정보를 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8인자 비트맵을 출력할 시작좌표
			m_tFrame.iFrameScene * (int)m_tInfo.fCY,
			30,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
			30,
			RGB(237, 28, 36));			// 제거하고자 하는 색상
	}
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	//	2, 3인자 복사 받을 위치의 좌표를 전달
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
}

void CBasicBullet::Release(void)
{
}

void CBasicBullet::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DIE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
