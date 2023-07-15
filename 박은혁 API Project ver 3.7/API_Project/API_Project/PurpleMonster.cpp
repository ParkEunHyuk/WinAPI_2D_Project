#include "stdafx.h"
#include "PurpleMonster.h"
#include "Manager.h"
#include "PurpleBullet.h"

float				g_fSoundPurpleMonster = 0.8f;

CPurpleMonster::CPurpleMonster()
	:m_iBulletCount(0), m_bIntroEnd(false), m_bPatternSwitch(false)
{
}


CPurpleMonster::~CPurpleMonster()
{
}

void CPurpleMonster::Initialize(void)
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_tStamina.iMaxHp = 5;
	m_tStamina.iAtt = 1;

	m_fGun_Distance = 1.f;
	m_fSpeed = 2.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/PurpleMonster.bmp", L"PurpleMonster");

	m_pFrameKey = L"PurpleMonster";
	m_ePreState = INTRO;
	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_tTimeDIE = GetTickCount();
	m_tTimeBullet = GetTickCount();

	m_eRenderGroup = RENDER_OBJ;
}

int CPurpleMonster::Update(void)
{
	/////////////////////////////////기본적으로 필요한 스피드 값
	if (m_bIntroEnd == true)
	{
		m_tInfo.fX += m_fSpeed;
		m_fAngle += m_fSpeed;
		LookPlayer();
	}
	/////////////////////////////////기본적으로 필요한 스피드 값
	/////////////////////////////////////////인트로
	if (m_eCurState == INTRO && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_tInfo.fX = m_tInfo.fX;
		m_tInfo.fY = m_tInfo.fY;
		m_eCurState = IDLE;
		m_bIntroEnd = true;
	}
	////////////////////////////////////////인트로
	///////////////////////////////////////////// 죽는 판정
	if (false == m_bDead)
	{
		m_bCollsion = false;
	}
	if (true == m_bDead)
	{
		m_bCollsion = true;
		m_eCurState = DIE;
		m_tInfo.fX = m_tInfo.fX;
		m_tInfo.fY = m_tInfo.fY;
		if (m_iCount == 0)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"MonsterDie.wav", CSoundMgr::MONSTER, g_fSoundPurpleMonster);
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
	///////////////////////////////////////////// 죽는 판정


	if (false == m_bDead && m_bIntroEnd == true)
	{
		MonsterPattern();
	}
	State_Change();
	Move_Frame();

	Update_Rect();
	return OBJ_NOEVENT;
}

void CPurpleMonster::Late_Update(void)
{
	m_tGun.x = long(m_tInfo.fX - (cosf(m_fAngle * PI / 180.f) * m_fGun_Distance));
	m_tGun.y = long(m_tInfo.fY + (sinf(m_fAngle * PI / 180.f) * m_fGun_Distance));

	if (m_bIntroEnd == true)
	{
		if (m_tInfo.fY > 40)
		{
			m_tInfo.fY -= 2;
		}
		if ((40 >= m_tRect.left) || (WINCX - 200 <= m_tRect.right))
			m_fSpeed *= -1.f;
	}
}

void CPurpleMonster::Render(HDC hDC)
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
		100,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		100,
		RGB(237, 28, 36));

}

void CPurpleMonster::Release(void)
{
}

void CPurpleMonster::LookPlayer()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);

	if (nullptr != m_pTarget)
	{
		// fX = player의 x - monster의 중점x
		float	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		// fY = player의 y - monster의 중점y
		float	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

		// player와 monster 사이의 거리 
		m_fDistance = sqrtf(fX * fX + fY * fY);
		// 두 중점 간의 각
		float	fRadian = acosf(fX / m_fDistance);
		// Radian to Degree
		m_fAngle = fRadian * 180.f / PI;
		// 플레이어의 높이가 몬스터보다 높을 경우 위치 바꾸기
		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fAngle *= -1.f;
	}
}

void CPurpleMonster::MonsterPattern(void)
{
	if (m_bPatternSwitch == true) 
	{
			BulletFire();
	}
	if (m_tTimePattern + 3000 < GetTickCount() && m_bPatternSwitch == false)
	{
		m_bPatternSwitch = true;
	}
}

void CPurpleMonster::BulletFire(void)
{
	m_eCurState = ATTACK;

	if (m_tTimeBullet + 100 < GetTickCount())
	{

		CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CPurpleBullet>::Create(m_tGun.x, m_tGun.y, m_fAngle));

		++m_iBulletCount;

		m_tTimeBullet = GetTickCount();

		if (m_iBulletCount > 5)
		{
			m_eCurState = IDLE;
			m_bPatternSwitch = false;
			m_tTimePattern = GetTickCount();
			m_iBulletCount = 0;
		}
	}
}

void CPurpleMonster::State_Change(void)
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
			m_tFrame.iFrameEnd = 5;
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
