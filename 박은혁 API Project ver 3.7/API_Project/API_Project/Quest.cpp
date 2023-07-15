#include "stdafx.h"
#include "Quest.h"
#include "Manager.h"


CQuest::CQuest()
{
}


CQuest::~CQuest()
{
}

void CQuest::Initialize(void)
{
	m_tInfo.fY;

	m_tInfo.fCX = 700.f;
	m_tInfo.fCY = 400.f;

	m_fSpeed = 5.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Quest/QuestStart.bmp", L"QuestStart");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Quest/QuestProgress.bmp", L"QuestProgress");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Quest/QuestSuccess.bmp", L"QuestSuccess");

	m_pFrameKey = L"QuestStart";

	m_eCurState = START;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_UI;

	m_pTarget = nullptr;
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::OVER_PLAYER, this);

}

int CQuest::Update(void)
{
	if (true == m_bDead)
	{
		if (m_eCurState == SUCCESS)
		{
			CSceneMgr::Get_Instance()->Scene_Change(SCENE_STAGECLEAR);
		}
		return OBJ_DEAD;
	}
	Update_Rect();
	Move_Frame();
	return OBJ_NOEVENT;
}

void CQuest::Late_Update(void)
{
	bool SlimeDie = CObjMgr::Get_Instance()->Get_Slime();
	bool FarmDie = CObjMgr::Get_Instance()->Get_Farm();
	bool FlowerDie = CObjMgr::Get_Instance()->Get_Flower();
	Key_Input();
	if (false == SlimeDie && false == FarmDie && false == FlowerDie)
	{
		m_eCurState = START;
		m_pFrameKey = L"QuestStart";
	}
	if (true == SlimeDie && true == FarmDie && true == FlowerDie)
	{
		m_eCurState = SUCCESS;
		m_pFrameKey = L"QuestSuccess";
	}
	else if (false == SlimeDie && true == FarmDie && true == FlowerDie)
	{
		//내용
		m_eCurState = PROGRESS;
		m_pFrameKey = L"QuestProgress";
	}
	else if (false == SlimeDie && false == FarmDie && true == FlowerDie)
	{
		//내용
		m_eCurState = PROGRESS;
		m_pFrameKey = L"QuestProgress";
	}
	else if (false == SlimeDie && true == FarmDie && false == FlowerDie)
	{
		//내용
		m_eCurState = PROGRESS;
		m_pFrameKey = L"QuestProgress";
	}
	else if (true == SlimeDie && false == FarmDie && true == FlowerDie)
	{
		//내용
		m_eCurState = PROGRESS;
		m_pFrameKey = L"QuestProgress";
	}
	else if (false == SlimeDie && false == FarmDie && true == FlowerDie)
	{
		//내용
		m_eCurState = PROGRESS;
		m_pFrameKey = L"QuestProgress";
	}
	else if (true == SlimeDie && false == FarmDie && false == FlowerDie)
	{
		//내용
		m_eCurState = PROGRESS;
		m_pFrameKey = L"QuestProgress";
	}
	else if (true == SlimeDie && true == FarmDie && false == FlowerDie)
	{
		//내용
		m_eCurState = PROGRESS;
		m_pFrameKey = L"QuestProgress";
	}
	else if (true == SlimeDie && false == FarmDie && false == FlowerDie)
	{
		//내용
		m_eCurState = PROGRESS;
		m_pFrameKey = L"QuestProgress";
	}
	else if (false == SlimeDie && true == FarmDie && false == FlowerDie)
	{
		//내용
		m_eCurState = PROGRESS;
		m_pFrameKey = L"QuestProgress";
	}





	State_Change();
}

void CQuest::Render(HDC hDC)
{
	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY + 30.f;

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
#endif // !_DEBUG

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top + iScrollY),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hMemDC,							// 비트맵 정보를 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8인자 비트맵을 출력할 시작좌표
		m_tFrame.iFrameScene * (int)m_tInfo.fCY,
		700,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		400,
		RGB(237, 28, 36));
}

void CQuest::Release(void)
{
}

void CQuest::Key_Input(void)
{
	//if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	//{
	//	m_tInfo.fY -= m_fSpeed;
	//}
	//if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	//{
	//	m_tInfo.fX += m_fSpeed;
	//}
	//if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	//{
	//	m_tInfo.fX -= m_fSpeed;
	//}
	//if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	//{
	//	m_tInfo.fY += m_fSpeed;
	//}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		m_bDead = true;
	}
}

void CQuest::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case START:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case SUCCESS:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case PROGRESS:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
