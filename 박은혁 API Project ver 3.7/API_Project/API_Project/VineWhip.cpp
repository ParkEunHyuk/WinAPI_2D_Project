#include "stdafx.h"
#include "VineWhip.h"
#include "Manager.h"
#include "VineSpear.h"

float g_fSoundVineWhip = 0.8f;

CVineWhip::CVineWhip()
	:m_bIntroEnd(false), m_tVineSpearSwitch(false),m_iSoundCount(0)
{
}


CVineWhip::~CVineWhip()
{
}

void CVineWhip::Initialize(void)
{
	m_tInfo.fCX = 700;
	m_tInfo.fCY = 120.f;
	m_tInfo.fX = 400;
	m_tInfo.fY = 300;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/VineWhip.bmp", L"VineWhip");

	m_pFrameKey = L"VineWhip";

	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_tTimePattern = GetTickCount();
	m_tTimeCollision = GetTickCount();

	m_bCollsion = true;

	//////////////////////////////사운드
	m_tTimeSound = GetTickCount();
}

int CVineWhip::Update(void)
{
	//인트로때는 이걸 사용해서 충돌처리 취소시키면 될 듯
	//m_bCollsion = true;
	//Set_Collsion(true);
	if (INTRO == m_eCurState && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_eCurState = IDLE;
		m_bIntroEnd = true;
		m_bCollsion = false;
	}

	/////////////////////////////////사운드에 관한 내용
	if (m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"VineWhip.wav", CSoundMgr::MONSTER_BULLET, g_fSoundVineWhip);
	}
	if (m_tTimeSound + 1200 < GetTickCount() && m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER_BULLET);
		++m_iSoundCount;
	}
	//////////////////////////

	Vine_Spear();
	State_Change();
	Move_Frame();
	Update_Rect();
	//덩굴채찍을 MONSTER_COLLISION_BULLET로 만들어서 예외처리해줘야함
	if (m_bCollsion == true)
	{
		if (m_tTimeCollision + 3000 < GetTickCount())
		{
			m_bCollsion = false;
			m_tTimeCollision = GetTickCount();
		}
	}
	return OBJ_NOEVENT;
}

void CVineWhip::Late_Update(void)
{
}

void CVineWhip::Render(HDC hDC)
{
#ifdef _DEBUG
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
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
		700,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		120,
		RGB(237, 28, 36));
}

void CVineWhip::Release(void)
{
}

void CVineWhip::State_Change(void)
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
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CVineWhip::Vine_Spear(void)
{
	if (m_tVineSpearSwitch == false && m_bIntroEnd == true)
	{
		m_tRandomVineAttack = rand() % 3;
		switch (m_tRandomVineAttack)
		{
		case 0:
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CVineSpear>::Create(115, 400));
			break;
		case 1:
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CVineSpear>::Create(290, 400));
		case 2:
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CVineSpear>::Create(460, 400));
			break;
		}
		++iCount;
		if (iCount > 1)
		{
			m_tTimePattern = GetTickCount();
			m_tVineSpearSwitch = true;
		}
	}
	if (m_tVineSpearSwitch == true)
	{
		if (m_tTimePattern + 3000 < GetTickCount())
		{
			m_tVineSpearSwitch = false;
			m_tTimePattern = GetTickCount();
		}
	}

}
