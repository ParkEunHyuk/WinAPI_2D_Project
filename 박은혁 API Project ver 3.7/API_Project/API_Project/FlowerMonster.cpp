#include "stdafx.h"
#include "FlowerMonster.h"
#include "Manager.h"
#include "RedSeedBullet.h"
#include "BlueSeedBullet.h"
#include "PurpleSeedBullet.h"
#include "AcornBullet.h"
#include "FaceAttack.h"
#include "AngryFlowerMonster.h"

float g_fSoundFlower = 0.8f;

CFlowerMonster::CFlowerMonster()
	:m_bPatternSwitch(false), m_bIntroEnd(false), m_iPatternCount(0), m_bAcornBulletSwitch(false), m_RandomSwitch(false)
	,m_bFaceSwitch(false), m_iSoundCount(0)
{
}


CFlowerMonster::~CFlowerMonster()
{
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, CAbstractFactory<CAngryFlowerMonster>::Create(680, 400));
}

void CFlowerMonster::Initialize(void)
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 350.f;

	//체력과 관련됨
	m_tStamina.iMaxHp = 20;
	m_tStamina.iAtt = 1;

	m_fGun_Distance = 1.f;
	m_fSpeed = 2.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/FlowerMonster.bmp", L"FlowerMonster");

	m_pFrameKey = L"FlowerMonster";
	m_ePreState = INTRO;
	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_BACK;

	m_tTimePattern = GetTickCount();
	m_tTimeSeedBullet = GetTickCount();
	m_tTimeAcornBullet = GetTickCount();

	/////////////////////////////////////////// 사운드 
	m_tTimeSound = GetTickCount();
}

int CFlowerMonster::Update(void)
{
	if (INTRO == m_eCurState && m_tFrame.iFrameStart == m_tFrame.iFrameEnd )
	{
		m_eCurState = IDLE;
		m_bIntroEnd = true;
	}

	/////////////////////////////////사운드에 관한 내용
	if (m_iSoundCount == 0)
	{
		//CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
		CSoundMgr::Get_Instance()->PlaySound(L"FlowerIntro.wav", CSoundMgr::MONSTER, g_fSoundFlower);
	}
	if (m_tTimeSound + 1200 < GetTickCount() && m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
		++m_iSoundCount;
	}
	//////////////////////////

	///////////////////////////////////////////// 죽는 판정
	if (0 == m_tStamina.iMaxHp)
	{
		m_bDead = true;
	}
	if (true == m_bDead)
	{
		m_eCurState = DIE;
		m_tInfo.fX = m_tInfo.fX;
		if (false == m_bFrameDieCheck)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"FlowerTransform.wav", CSoundMgr::MONSTER, g_fSoundFlower);
			m_tFrame.iFrameStart = 0;
			m_bFrameDieCheck = true;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			return OBJ_DEAD;
		}
	}
	////////////////////////////////////////////////

	if (false == m_bDead && m_bIntroEnd == true)
	{
		m_bCollsion = false;
		m_fAngle += m_fSpeed;
		FlowerPattern();
		LookPlayer();
	}
	State_Change();
	Move_Frame();
	Update_Rect(); //이걸 해야 화면에 출력됨

	return OBJ_NOEVENT;
}

void CFlowerMonster::Late_Update(void)
{
	m_tGunAcorn.x = long(m_tInfo.fX - (cosf(m_fAngle * PI / 180.f) * m_fGun_Distance));
	m_tGunAcorn.y = long(m_tInfo.fY + (sinf(m_fAngle * PI / 180.f) * m_fGun_Distance));
}

void CFlowerMonster::Render(HDC hDC)
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
		200,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		350,
		RGB(237, 28, 36));
}

void CFlowerMonster::Release(void)
{
}

void CFlowerMonster::LookPlayer()
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

void CFlowerMonster::FlowerPattern(void)
{
	if (m_bPatternSwitch == true) 
	{
		if (m_RandomSwitch == false)
		{
			m_iPatternRandom = rand() % 3;
			m_RandomSwitch = true;
		}
		switch (m_iPatternRandom)
		{
		case 0:
		{
			SeedFire();
			break;
		}
		case 1:
		{
			AcornFire();
			break;
		}
		case 2:
		{
			FaceAttack();
			break;
		}
		}
	}
	if (m_tTimePattern + 5000 < GetTickCount() && m_bPatternSwitch == false)
	{
		m_bPatternSwitch = true;
	}
}

void CFlowerMonster::SeedFire(void)
{

	m_eCurState = SEED_BULLET;
	if (m_tTimeSeedBullet + 3000 < GetTickCount())
	{
		if (m_iPatternCount == 0)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER_BULLET);
			CSoundMgr::Get_Instance()->PlaySound(L"SeedGattling.wav", CSoundMgr::MONSTER_BULLET, g_fSoundFlower);
		}

		m_iRand = rand() % 400;
		m_tGun.x = m_iRand +20;
		CObjMgr::Get_Instance()->Add_Object(OBJID::NOT_COLLISION_MONSTER, CAbstractFactory<CRedSeedBullet>::Create(m_tGun.x+20, m_tGun.y, BULLET::DOWN));

		m_iRand = rand() % 400;
		m_tGun.x = m_iRand + 20;
		CObjMgr::Get_Instance()->Add_Object(OBJID::NOT_COLLISION_MONSTER, CAbstractFactory<CBlueSeedBullet>::Create(m_tGun.x+20, m_tGun.y, BULLET::DOWN));


		m_iRand = rand() % 400;
		m_tGun.x = m_iRand + 20;
		CObjMgr::Get_Instance()->Add_Object(OBJID::NOT_COLLISION_MONSTER, CAbstractFactory<CPurpleSeedBullet>::Create(m_tGun.x+20, m_tGun.y, BULLET::DOWN));
		
		++m_iPatternCount;

		m_tTimeSeedBullet = GetTickCount();

		if (m_iPatternCount > 1)
		{
			m_eCurState = IDLE;
			m_bPatternSwitch = false;
			m_RandomSwitch = false;
			m_tTimePattern = GetTickCount();
			m_iPatternCount = 0;
		}
	}
}

void CFlowerMonster::AcornFire(void)
{

	m_eCurState = ACORN_BULLET;
	if (m_bAcornBulletSwitch == false)
	{
		m_tFrame.iFrameStart = 0;
		m_bAcornBulletSwitch = true;
	}
	if (m_tFrame.iFrameStart == 3)
	{
		if (m_iPatternCount < 1)
		{
			++m_iPatternCount;
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CAcornBullet>::Create((m_tGunAcorn.x - 30), (m_tGunAcorn.y + 70), m_fAngle));

			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CAcornBullet>::Create((m_tGunAcorn.x - 30), m_tGunAcorn.y, m_fAngle));

			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CAcornBullet>::Create((m_tGunAcorn.x - 30), (m_tGunAcorn.y - 70), m_fAngle));
		}
	}
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_eCurState = IDLE;
		m_bPatternSwitch = false;
		m_RandomSwitch = false;
		m_bAcornBulletSwitch = false;
		m_tTimePattern = GetTickCount();
		m_iPatternCount = 0;
	}
}

void CFlowerMonster::FaceAttack(void)
{
	m_eCurState = FACEATTACK;
	if (m_bFaceSwitch == false)
	{
		m_tFrame.iFrameStart = 0;
		m_bFaceSwitch = true;
	}
	if (m_tFrame.iFrameStart == 0)
	{
		if (m_iPatternCount < 1)
		{
			++m_iPatternCount;
			CObjMgr::Get_Instance()->Add_Object(OBJID::NOT_COLLISION_MONSTER, CAbstractFactory<CFaceAttack>::Create(400, 400));
		}
	}
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_eCurState = IDLE;
		m_bPatternSwitch = false;
		m_RandomSwitch = false;
		m_bFaceSwitch = false;
		m_tTimePattern = GetTickCount();
		m_iPatternCount = 0;
	}
}

void CFlowerMonster::State_Change(void)
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
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case SEED_BULLET:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case ACORN_BULLET:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 400;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case FACEATTACK:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 5;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
			break;
		case DIE:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 4;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
