#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}


void CMyButton::Initialize(void)
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;
}

int CMyButton::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"Button_Start", m_pFrameKey))
			{
				CSceneMgr::Get_Instance()->Scene_Change(SCENE_OVERWORLD);
			}
			else if (!lstrcmp(L"Button_Edit", m_pFrameKey))
			{
				CSceneMgr::Get_Instance()->Scene_Change(SCENE_EDIT);
			}
			else if (!lstrcmp(L"Button_Exit", m_pFrameKey))
			{
				DestroyWindow(g_hWnd);
			}

			return;
		}
		m_iDrawID = 1;
	}

	else
		m_iDrawID = 0;
}

void CMyButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),				//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hMemDC,							// 비트맵 정보를 가지고 있는 DC
		m_iDrawID * (int)m_tInfo.fCX,	// 7,8인자 비트맵을 출력할 시작좌표
		0,
		(int)m_tInfo.fCX,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));
}

void CMyButton::Release(void)
{

}
