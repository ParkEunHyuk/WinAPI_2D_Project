#include "stdafx.h"
#include "OverPlayer.h"
#include "Manager.h"

COverPlayer::COverPlayer()
{
}


COverPlayer::~COverPlayer()
{
	Release();
}

void COverPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 400.f;

	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 100.f;

	m_fDistance = 100.f;

	m_fSpeed = 5.f;

	m_iOffSetX = WINCX >> 1;
	m_iOffSetY = WINCY >> 1;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/OverPlayer/OverPlayer_DOWN.bmp", L"OverPlayer_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/OverPlayer/OverPlayer_UP.bmp", L"OverPlayer_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/OverPlayer/OverPlayer_LEFT.bmp", L"OverPlayer_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/OverPlayer/OverPlayer_RIGHT.bmp", L"OverPlayer_RIGHT");

	m_pFrameKey = L"OverPlayer_DOWN";

	m_ePreState = IDLE;
	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_OBJ;
}

int COverPlayer::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;


	State_Change();
	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void COverPlayer::Late_Update(void)
{
	Key_Input();
	OffSet();
}

void COverPlayer::Render(HDC hDC)
{
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

	// ������ �� : BitBlt �÷��̾�� ������� �̹����� ����� ���ƾ� �������� ��ġ ����� ����

	//BitBlt(hDC,			//	���� ����, ���������� �׸��� �׸� DC
	//		int(m_tRect.left + iScrollX), // 2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
	//		int(m_tRect.top),
	//		(int)m_tInfo.fCX,		//4,5���� ���� ���� X,Y�� ���̸� ����
	//		(int)m_tInfo.fCY,
	//		hMemDC,					// ��Ʈ�� ������ ������ �ִ� DC
	//		0,						// 7,8���� ��Ʈ���� ����� ������ǥ
	//		0,
	//		SRCCOPY);				// ��� ȿ���� ����, �״�� ��� 


	GdiTransparentBlt(hDC,				//	���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	//	2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		int(m_tRect.top + iScrollY),
		(int)m_tInfo.fCX,				//	4, 5���� ���� ���� X,Y�� ���̸� ����	
		(int)m_tInfo.fCY,
		hMemDC,							// ��Ʈ�� ������ ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8���� ��Ʈ���� ����� ������ǥ
		m_tFrame.iFrameScene * (int)m_tInfo.fCY,
		70,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		100,
		RGB(237, 28, 36));			// �����ϰ��� �ϴ� ����
}

void COverPlayer::Release(void)
{
}

void COverPlayer::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		//CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);
		m_pFrameKey = L"OverPlayer_LEFT";
		m_eCurState = WALK_LEFT;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		//CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
		m_pFrameKey = L"OverPlayer_RIGHT";
		m_eCurState = WALK_RIGHT;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		//CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);
		m_pFrameKey = L"OverPlayer_UP";
		m_eCurState = WALK_UP;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		//CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
		m_pFrameKey = L"OverPlayer_DOWN";
		m_eCurState = WALK_DOWN;
	}
	else
		m_eCurState = IDLE;
}

void COverPlayer::OffSet(void)
{

	if (m_iOffSetX != m_tInfo.fX)
	{
		if (m_iOffSetX < m_tInfo.fX)
		{
			CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
			m_iOffSetX += (int)m_fSpeed;
		}
		if (m_iOffSetX > m_tInfo.fX)
		{
			CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);
			m_iOffSetX -= (int)m_fSpeed;
		}
	}

	if (m_iOffSetY != m_tInfo.fY)
	{
		if (m_iOffSetY < m_tInfo.fY)
		{
			CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
			m_iOffSetY += (int)m_fSpeed;
		}
		if (m_iOffSetY > m_tInfo.fY)
		{
			CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);
			m_iOffSetY -= (int)m_fSpeed;
		}
	}

}

void COverPlayer::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case WALK_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case WALK_UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 16;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case WALK_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 16;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case WALK_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 16;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}
