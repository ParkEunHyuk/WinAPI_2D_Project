#include "stdafx.h"
#include "RedMonster.h"
#include "Manager.h"

float g_fSoundRedMonster = 0.8f;

CRedMonster::CRedMonster()
{
}


CRedMonster::~CRedMonster()
{
}

void CRedMonster::Initialize(void)
{
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;

	//이거 없어도 크레이트할 떄 이니셜라이저 써서 값 들어가긴 하는데 혹시 모르니깐 일단 넣어두자!
	// 그리고 m_tGun값은 레이트 업데이트에 쓰도록 하자!!! 이니셜라이저에 잘못 쓰면 이상한 값이 들어가게 된단다!
	m_tInfo.fX = 400;
	m_tInfo.fY = 500;

	m_tStamina.iMaxHp = 30;
	m_tStamina.iAtt = 1;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/RedMonster.bmp", L"RedMonster");

	m_pFrameKey = L"RedMonster";
	m_ePreState = IDLE;
	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_tTimeDIE = GetTickCount();

	m_eRenderGroup = RENDER_BACK;
}

int CRedMonster::Update(void)
{
	if (m_bDead == false)
	{
		m_bCollsion = false;
	}
	if (true == m_bDead)
	{
		m_eCurState = DIE;
	
		m_bCollsion = true;
		m_tInfo.fX = m_tInfo.fX;
		if (false == m_bFrameDieCheck)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"MonsterDie.wav", CSoundMgr::MONSTER, g_fSoundRedMonster);
			m_tFrame.iFrameStart = 0;
			m_bFrameDieCheck = true;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			return OBJ_DEAD;
		}
	}
	if (m_tTimeDIE + 4000 < GetTickCount())
	{
		m_bDead = true;
		m_tTimeDIE = GetTickCount();
	}
	State_Change();
	Move_Frame();
	Update_Rect(); //이걸 해야 화면에 출력됨
	return OBJ_NOEVENT;
}

void CRedMonster::Late_Update(void)
{
}

void CRedMonster::Render(HDC hDC)
{
#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
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
		70,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		70,
		RGB(237, 28, 36));
}

void CRedMonster::Release(void)
{
}

void CRedMonster::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case DIE:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
