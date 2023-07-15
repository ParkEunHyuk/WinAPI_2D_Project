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

	GdiTransparentBlt(hDC,				//	���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),				//	2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5���� ���� ���� X,Y�� ���̸� ����	
		(int)m_tInfo.fCY,
		hMemDC,							// ��Ʈ�� ������ ������ �ִ� DC
		m_iDrawID * (int)m_tInfo.fCX,	// 7,8���� ��Ʈ���� ����� ������ǥ
		0,
		(int)m_tInfo.fCX,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));
}

void CMyButton::Release(void)
{

}
