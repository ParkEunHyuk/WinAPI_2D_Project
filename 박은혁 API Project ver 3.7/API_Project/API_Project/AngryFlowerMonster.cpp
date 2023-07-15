#include "stdafx.h"
#include "AngryFlowerMonster.h"
#include "Manager.h"
#include "FlowerBullet.h"
#include "VineWhip.h"
#include "Bravo.h"

float g_fSoundAngryFlower = 0.9f;

CAngryFlowerMonster::CAngryFlowerMonster()
	:m_bIntroEnd(false)
{
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_COLLISION_BULLET, CAbstractFactory<CVineWhip>::Create(370, 525));
}


CAngryFlowerMonster::~CAngryFlowerMonster()
{
	//이거 덩굴 몬스터 없애는 용
	CObjMgr::Get_Instance()->Delete_ID(OBJID::MONSTER_COLLISION_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJID::MONSTER_BULLET);
	CObjMgr::Get_Instance()->Delete_Render(RENDER_BACK);
	CObjMgr::Get_Instance()->Delete_Render(RENDER_OBJ);
	CObjMgr::Get_Instance()->Add_Object(OBJID::UI, CAbstractFactory<CBravo>::Create(400, 300));
}

void CAngryFlowerMonster::Initialize(void)
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 350.f;

	//체력과 관련됨
	m_tStamina.iMaxHp = 20;
	m_tStamina.iAtt = 1;

	m_fSpeed = 2.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/AngryFlowerMonster.bmp", L"AngryFlowerMonster");

	m_pFrameKey = L"AngryFlowerMonster";
	m_ePreState = INTRO;
	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	iCount = 0;

	m_eRenderGroup = RENDER_BACK;
}

int CAngryFlowerMonster::Update(void)
{
	if (INTRO == m_eCurState && 4 == m_tFrame.iFrameStart)
	{
		m_eCurState = ATTACK;
		m_bIntroEnd = true;
	}

	if (0 == m_tStamina.iMaxHp)
	{
		m_bCollsion = true;
		m_bDead = true;
	}

	if (true == m_bDead)
	{
		m_eCurState = DIE;
		CSoundMgr::Get_Instance()->PlaySound(L"AngryFlowerDie.wav", CSoundMgr::MONSTER, g_fSoundAngryFlower);
		m_tInfo.fX = m_tInfo.fX;
		if (false == m_bFrameDieCheck)
		{
			m_tFrame.iFrameStart = 0;
			m_bFrameDieCheck = true;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			CObjMgr::Get_Instance()->Set_FlowerClear(true);
			return OBJ_DEAD;
		}
	}

	if (false == m_bDead && m_bIntroEnd == true)
	{
		FlowerBullet();
		m_bCollsion = false;
	}
	State_Change();
	Move_Frame();
	Update_Rect(); //이걸 해야 화면에 출력됨

	return OBJ_NOEVENT;
}

void CAngryFlowerMonster::Late_Update(void)
{
}

void CAngryFlowerMonster::Render(HDC hDC)
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

void CAngryFlowerMonster::Release(void)
{
}

void CAngryFlowerMonster::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case ATTACK:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case DIE:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CAngryFlowerMonster::FlowerBullet(void)
{
	//만약 꽃 괴물의 스타트가 X라면~ 불렛 발사
	if (m_tFrame.iFrameStart == 7 && iCount == 0)
	{
		m_tGun.x = m_tInfo.fX - 50.f;
		m_tGun.y = m_tInfo.fY - 60.f;

		CSoundMgr::Get_Instance()->PlaySound(L"FlowerBullet.wav", CSoundMgr::MONSTER_BULLET, g_fSoundAngryFlower);
		CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CFlowerBullet>::Create((m_tGun.x), (m_tGun.y), BULLET::LEFT));
		++iCount;
	}

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		iCount = 0;
	}
}