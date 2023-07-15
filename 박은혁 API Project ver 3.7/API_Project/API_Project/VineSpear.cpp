#include "stdafx.h"
#include "VineSpear.h"
#include "Manager.h"

float g_fSoundVineSpear = 0.8f;

CVineSpear::CVineSpear()
	:m_bIntroEnd(false), m_bDieSwitch(false), m_iSoundCount(0)
{
}


CVineSpear::~CVineSpear()
{
}

void CVineSpear::Initialize(void)
{
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 250.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/VineSpear.bmp", L"VineSpear");
	m_pFrameKey = L"VineSpear";

	m_eCurState = ATTACK;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();


	m_eRenderGroup = RENDER_OBJ;

	m_bCollsion = true;

	/////////////////////////////////////////////사운드
	m_tTimeSound = GetTickCount();
}

int CVineSpear::Update(void)
{
	if (m_eCurState == ATTACK && m_bIntroEnd == false)
	{
		if (m_tFrame.iFrameStart == 7)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
			CSoundMgr::Get_Instance()->PlaySound(L"VineSpear.wav", CSoundMgr::UI, g_fSoundVineSpear);
			m_bCollsion = false;
		}
	}

	/////////////////////////////////사운드에 관한 내용
	if (m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"VineSpearReady.wav", CSoundMgr::UI, g_fSoundVineSpear);
	}
	if (m_tTimeSound + 400 < GetTickCount() && m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
		++m_iSoundCount;
	}
	//////////////////////////

	/////////////////////////////////////////////////////////
	if (ATTACK == m_eCurState && m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_bIntroEnd == false)
	{
		m_bIntroEnd = true;
		m_eCurState = DIE;
	}
	////////////////////////////////////////////////////////////
	////////////////////////// 덩굴 재정렬
	if (m_bIntroEnd == true)
	{
		if (m_eCurState == DIE)
		{
			if (m_bDieSwitch == false)
			{
				m_tFrame.iFrameStart = 0;
				m_bDieSwitch = true;
			}
			if (m_tFrame.iFrameStart == 5)
			{
				m_bCollsion = true;
			}
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				return OBJ_DEAD;
			}
		}
	}

	State_Change();
	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CVineSpear::Late_Update(void)
{
}

void CVineSpear::Render(HDC hDC)
{
#ifdef _DEBUG
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
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
		250,
		RGB(237, 28, 36));
}

void CVineSpear::Release(void)
{
}

void CVineSpear::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case DIE:
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
