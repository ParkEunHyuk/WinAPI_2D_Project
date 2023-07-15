#include "stdafx.h"
#include "BlueMonster.h"
#include "Manager.h"

float			g_fSoundBlueMonster = 0.8f;

CBlueMonster::CBlueMonster()
	:m_IntroEnd(false)
{
}


CBlueMonster::~CBlueMonster()
{
}

void CBlueMonster::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	//체력과 관련됨
	m_tStamina.iMaxHp = 1;
	m_tStamina.iAtt = 1;


	m_pTarget = nullptr;
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY + 30.f;

	m_fSpeed = 2.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/BlueMonster.bmp", L"BlueMonster");

	m_pFrameKey = L"BlueMonster";

	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_OBJ;
}

int CBlueMonster::Update(void)
{
	if (m_eCurState == INTRO && m_IntroEnd == false)
	{
		m_tInfo.fX = m_tInfo.fX;
		m_tInfo.fY = m_tInfo.fY;
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_eCurState = RIGHT;
			m_IntroEnd = true;
		}
	}
	///////////////////////////////////죽는 판정
	if (true == m_bDead)
	{
		m_bCollsion = true;

		m_eCurState = DIE;
		m_tInfo.fX = m_tInfo.fX;
		m_tInfo.fY = m_tInfo.fY;
		if (m_iCount == 0)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"MonsterDie.wav", CSoundMgr::MONSTER, g_fSoundBlueMonster);
			m_tFrame.iFrameStart = 0;
			++m_iCount;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			return OBJ_DEAD;
		}
	}

	if (m_tStamina.iMaxHp == 0)
	{
		m_bDead = true;
	}
	////////////////////////////////////////죽는 판정
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);
	if (false == m_bDead && m_IntroEnd == true)
	{
		m_bCollsion = false;
		if (nullptr != m_pTarget)
		{
			float	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
			float	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

			float	fDistance = sqrtf(fX * fX + fY * fY);

			float	fRadian = acosf(fX / fDistance);

			m_fAngle = fRadian * 180.f / PI;

			if (m_pTarget->Get_Info().fY > m_tInfo.fY)
				m_fAngle *= -1.f;
		}

		m_tInfo.fX += (m_fSpeed * cosf(m_fAngle * PI / 180.f));
		m_tInfo.fY -= (m_fSpeed * sinf(m_fAngle * PI / 180.f));
	}

	if (m_pTarget->Get_Info().fX < m_tInfo.fX && m_IntroEnd == true && false == m_bDead)
	{
		m_eCurState = LEFT;
	}
	else if(m_pTarget->Get_Info().fX > m_tInfo.fX && m_IntroEnd == true && false == m_bDead)
	{
		m_eCurState = RIGHT;
	}
	State_Change();
	Move_Frame();

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBlueMonster::Late_Update(void)
{
}

void CBlueMonster::Render(HDC hDC)
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
		50,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		50,
		RGB(237, 28, 36));
}

void CBlueMonster::Release(void)
{
}

void CBlueMonster::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case LEFT:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case RIGHT:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DIE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
