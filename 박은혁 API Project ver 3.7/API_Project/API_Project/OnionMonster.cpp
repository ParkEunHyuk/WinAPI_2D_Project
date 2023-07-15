#include "stdafx.h"
#include "OnionMonster.h"
#include "OnionBullet.h"
#include "Manager.h"
#include "CarrotMonster.h"

float g_fSoundOnion = 0.5f;

COnionMonster::COnionMonster()
{
}


COnionMonster::~COnionMonster()
{
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, CAbstractFactory<CCarrotMonster>::Create(400, 150));
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
}

void COnionMonster::Initialize(void)
{
	m_tInfo.fCX = 250.f;
	m_tInfo.fCY = 250.f;

	//체력과 관련됨
	m_tStamina.iMaxHp = 20;
	m_tStamina.iAtt = 1;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FarmMonster/OnionMonster.bmp", L"OnionMonster");

	m_pFrameKey = L"OnionMonster";
	m_ePreState = INTRO;
	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_tTimeCry = GetTickCount();

	m_eRenderGroup = RENDER_BACK;


	m_tSoundTime = GetTickCount();

}

int COnionMonster::Update(void)
{
	if (INTRO == m_eCurState && 6 == m_tFrame.iFrameStart)
	{
		m_eCurState = IDLE;
	}
	if (m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OnionIntro.wav", CSoundMgr::MONSTER, g_fSoundOnion);
	}
	if (m_tSoundTime + 2000 < GetTickCount())
	{
		++m_iSoundCount;
	}
	if (0 == m_tStamina.iMaxHp)
	{
		m_bCollsion = true;
		m_bDead = true;
	}

	if (true == m_bDead)
	{
		m_eCurState = DIE;
		CSoundMgr::Get_Instance()->PlaySound(L"OnionDie.wav", CSoundMgr::MONSTER, g_fSoundOnion);
		m_tInfo.fX = m_tInfo.fX;
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

	if (false == m_bDead)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OnionCrying.wav", CSoundMgr::EFFECT, g_fSoundOnion);
		Onion_Crying();
		m_bCollsion = false;
	}
	State_Change();
	Move_Frame();
	Update_Rect(); //이걸 해야 화면에 출력됨

	return OBJ_NOEVENT;
}

void COnionMonster::Late_Update(void)
{
}

void COnionMonster::Render(HDC hDC)
{

#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
#endif // !_DEBUG

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hMemDC,							// 비트맵 정보를 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8인자 비트맵을 출력할 시작좌표
		m_tFrame.iFrameScene * (int)m_tInfo.fCY,
		250,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		250,
		RGB(237, 28, 36));
}

void COnionMonster::Release(void)
{
}

void COnionMonster::State_Change(void)
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
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case ATTACK:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case DIE:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}


void COnionMonster::Onion_Crying(void)
{
	int iRand = rand()% 800;
	m_tGun.x = iRand;
	m_tGun.y = 0.f;
	if (m_tTimeCry + 400 < GetTickCount())
	{
		m_eCurState = ATTACK;
		CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_COLLISION_BULLET, CAbstractFactory<COnionBullet>::Create(m_tGun.x, m_tGun.y, BULLET::DOWN));
		m_tTimeCry = GetTickCount();
	}
}