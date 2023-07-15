#include "stdafx.h"
#include "CarrotMonster.h"
#include "Manager.h"
#include "CarrotBullet.h"
#include "RingBullet.h"
#include "Bravo.h"

float g_fSoundCarrot = 0.5f;

CCarrotMonster::CCarrotMonster()
	:m_bIDLE_Switch(false), m_bIntroEnd(false)
{
}


CCarrotMonster::~CCarrotMonster()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJID::MONSTER_COLLISION_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJID::MONSTER_BULLET);
	CObjMgr::Get_Instance()->Delete_Render(RENDER_BACK);
	CObjMgr::Get_Instance()->Add_Object(OBJID::UI, CAbstractFactory<CBravo>::Create(400, 300));
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
}

void CCarrotMonster::Initialize(void)
{
	m_tInfo.fCX = 140.f;
	m_tInfo.fCY = 270.f;

	//체력과 관련됨
	m_tStamina.iMaxHp = 20;
	m_tStamina.iAtt = 1;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FarmMonster/CarrotMonster.bmp", L"CarrotMonster");

	m_pFrameKey = L"CarrotMonster";
	m_ePreState = INTRO;
	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_fGun_Distance = 10.f;

	m_tTimeCarrotBullet = GetTickCount();
	m_tTimeRingBullet = GetTickCount();
	m_tTimeRingCount = GetTickCount();
	m_tTimePattern = GetTickCount();

	m_eRenderGroup = RENDER_BACK;

	//////////////////////////////////사운드
	m_tTimeSound = GetTickCount();

}

int CCarrotMonster::Update(void)
{
	m_fAngle += m_fSpeed;

	if (INTRO == m_eCurState && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_eCurState = IDLE;
		m_bIntroEnd = true;
	}
	if (m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"CarrotIntro.wav", CSoundMgr::MONSTER, g_fSoundCarrot);
	}
	if (m_tTimeSound + 1000 < GetTickCount())
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
		CSoundMgr::Get_Instance()->PlaySound(L"CarrotDie.wav", CSoundMgr::MONSTER, g_fSoundCarrot);
		if (false == m_bFrameDieCheck)
		{
			m_tFrame.iFrameStart = 0;
			m_bFrameDieCheck = true;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			CObjMgr::Get_Instance()->Set_FarmClear(true);
			return OBJ_DEAD;
		}
	}


	if (false == m_bDead && m_bIntroEnd == true)
	{
		m_bCollsion = false;

		if (m_tTimePattern + 4000 <= GetTickCount())
		{
			m_iRand = rand() % 2;
			m_tTimePattern = GetTickCount();
		}
		switch (m_iRand)
		{
		case 0:
			Caorrt_Bullet();
			break;
		case 1:
			Caorrt_Ring();
			break;
		}
	}


	LooK_Player();       //플레이어 좌표를 받고 있음
	Move_Frame();
	State_Change();
	Update_Rect(); //이걸 해야 화면에 출력됨

	return OBJ_NOEVENT;
}

void CCarrotMonster::Late_Update(void)
{
	m_tGun.x = long(m_tInfo.fX - (cosf(m_fAngle * PI / 180.f) * m_fGun_Distance));
	m_tGun.y = long(m_tInfo.fY + (sinf(m_fAngle * PI / 180.f) * m_fGun_Distance));
}

void CCarrotMonster::Render(HDC hDC)
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
		140,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		270,
		RGB(237, 28, 36));
}

void CCarrotMonster::Release(void)
{
}

void CCarrotMonster::State_Change(void)
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
		case IDLE:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case ATTACK:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case ATTACK_2:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case DIE:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 4;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CCarrotMonster::LooK_Player(void)
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
		// 두 중점 간의 각
		float	fRadian = acosf(fX / m_fDistance);
		// Radian to Degree
		m_fAngle = fRadian * 180.f / PI;
		// 플레이어의 높이가 몬스터보다 높을 경우 위치 바꾸기
		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fAngle *= -1.f;
	}
}

void CCarrotMonster::Caorrt_Bullet(void)
{
	m_eCurState = ATTACK;
	int iRand = rand() % 800;
	float CarrotBulletfX = iRand;
	float CarrotBulletfY = 0.f;
	if (m_tTimeCarrotBullet + 1000 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_COLLISION_BULLET, CAbstractFactory<CCarrotBullet>::Create(CarrotBulletfX, CarrotBulletfY, BULLET::DOWN));
		m_tTimeCarrotBullet = GetTickCount();
	}
}

void CCarrotMonster::Caorrt_Ring(void)
{
	m_eCurState = ATTACK_2;
	if (nullptr != m_pTarget)
	{
		if (m_tTimeRingBullet + 700 <= GetTickCount())
		{
			if (m_tTimeRingCount + 20 <= GetTickCount())
			{
				CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CRingBullet>::Create(float(m_tGun.x), float(m_tGun.y), m_fAngle));
				m_tTimeRingCount = GetTickCount();
				++m_iRingCount;
			}
			if (m_iRingCount == 5)
			{
				m_tTimeRingBullet = GetTickCount();
				m_iRingCount = 0;
			}
		}
	}
}
