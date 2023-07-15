#include "stdafx.h"
#include "PunchMotion.h"
#include "Manager.h"
#include "Punching.h"

float g_fSoundBigSlimePunching = 0.8f;

CPunchMotion::CPunchMotion()
{
}


CPunchMotion::~CPunchMotion()
{
}
void CPunchMotion::Initialize(void)
{
	m_tInfo.fCX = 600.f;
	m_tInfo.fCY = 300.f;

	m_pTarget = nullptr;
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/SlimeMonster/PunchMotion.bmp", L"PunchMotion");
	m_pFrameKey = L"PunchMotion";


	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 12;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_BACK;

	m_tTimeSound = GetTickCount();
}

int CPunchMotion::Update(void)
{
	LookPlayer();
	State_Change();
	Update_Rect();
	Move_Frame();
	Attacking();
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		return OBJ_DEAD;
	}
	return OBJ_NOEVENT;
}

void CPunchMotion::Late_Update(void)
{
}

void CPunchMotion::Render(HDC hDC)
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
		600,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		300.f,
		RGB(237, 28, 36));
}

void CPunchMotion::Release(void)
{
}

void CPunchMotion::Attacking(void)
{
	if (50 < m_tInfo.fX && WINCX - 50 > m_tInfo.fX)
	{
		if (m_pTarget->Get_Info().fX < m_tInfo.fX&& m_bMontion == false) // 플레이어가 왼쪽에 있고 몬스터는 오른쪽에 있으며 점프를 하지 않는 상태...
		{
			m_bMontion = true;
			if (m_fDistance < 250)
			{

				m_eCurState = PUNCH_LEFT;
				if (m_eCurState == PUNCH_LEFT)
				{
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"BigSlimePunch.wav", CSoundMgr::EFFECT, g_fSoundBigSlimePunching);
					m_tFrame.iFrameStart = 0;
				}
				//if (m_tTimeSound + 2400 < GetTickCount())
				//{
				//	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
				//}
			}
			//몬스터가 왼쪽을 보면서 공격

		}
		else if (m_pTarget->Get_Info().fX > m_tInfo.fX && m_bMontion == false)
		{
			m_bMontion = true;
			if (m_fDistance < 250)
			{
				m_eCurState = PUNCH_RIGHT;
				if (m_eCurState == PUNCH_RIGHT)
				{
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"BigSlimePunch.wav", CSoundMgr::EFFECT, g_fSoundBigSlimePunching);
					m_tFrame.iFrameStart = 0;
				}
			}
			//몬스터가 오른쪽을 보면서 공격
		}
	}

	if (m_eCurState == PUNCH_LEFT && m_tFrame.iFrameStart == 5 && m_iMotionCount == 0)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CPunching>::Create((m_tInfo.fX - 180), m_tInfo.fY - 20));
		++m_iMotionCount;
	}
	else if (m_eCurState == PUNCH_RIGHT && m_tFrame.iFrameStart == 5 && m_iMotionCount == 0)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CPunching>::Create((m_tInfo.fX + 180), m_tInfo.fY - 20));
		++m_iMotionCount;
	}
}

void CPunchMotion::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case PUNCH_LEFT:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case PUNCH_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPunchMotion::LookPlayer(void)
{
	// CObj* m_pTarget = 플레이어와 몬스터의 거리를 계산
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);

	if (nullptr != m_pTarget)
	{
		// fX = player의 x - monster의 중점x
		float	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		// fY = player의 y - monster의 중점y
		float	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

		// player와 monster 사이의 거리 
		m_fDistance = sqrtf(fX * fX + fY * fY);
	}
}
