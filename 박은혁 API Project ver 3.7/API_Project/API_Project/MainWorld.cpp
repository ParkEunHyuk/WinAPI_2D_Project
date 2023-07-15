#include "stdafx.h"
#include "MainWorld.h"
#include "Manager.h"
//#include "AbstractFactory.h"
//#include "CollisionMgr.h"
//#include "ObjMgr.h"
//#include "BmpMgr.h"
//#include "ScrollMgr.h"
//#include "LineMgr.h"
//#include "KeyMgr.h"
//#include "SceneMgr.h"


CMainWorld::CMainWorld()
	: m_dwTime(0), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 256);
}

CMainWorld::~CMainWorld()
{
	Release();
}

void CMainWorld::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackBuffer.bmp", L"BackBuffer");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");

	CSceneMgr::Get_Instance()->Scene_Change(SCENE_LOGO);

	CSoundMgr::Get_Instance()->Initialize();
}

void CMainWorld::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainWorld::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CMainWorld::Render()
{
#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_DC, myBrush);
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	SelectObject(m_DC, oldBrush);
	DeleteObject(myBrush);
#endif // _DEBUG

	/*if (SCENE_LOGO == CSceneMgr::Get_Instance()->Get_Scene()) �̰� ���� �����?
		return;*/

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer");
	HDC	hBackBuferDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");


	BitBlt(hBackBuferDC,	//	���� ����, ���������� �׸��� �׸� DC
		0,					// 2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		0,
		WINCX,				//4,5���� ���� ���� X,Y�� ���̸� ����
		WINCY,
		hMemDC,				// ��Ʈ�� ������ ������ �ִ� DC
		0,					// 7,8���� ��Ʈ���� ����� ������ǥ
		0,
		SRCCOPY);


	CSceneMgr::Get_Instance()->Render(hBackBuferDC);


	BitBlt(m_DC,			//	���� ����, ���������� �׸��� �׸� DC
		0,					// 2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		0,
		WINCX,				//4,5���� ���� ���� X,Y�� ���̸� ����
		WINCY,
		hBackBuferDC,		// ��Ʈ�� ������ ������ �ִ� DC
		0,					// 7,8���� ��Ʈ���� ����� ������ǥ
		0,
		SRCCOPY);


	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);
		m_dwTime = GetTickCount();
		m_iFPS = 0;
	}
}

void CMainWorld::Release(void)
{
	ReleaseDC(g_hWnd, m_DC);

	CSoundMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
}
