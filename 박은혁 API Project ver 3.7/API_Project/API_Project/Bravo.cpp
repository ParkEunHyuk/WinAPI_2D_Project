#include "stdafx.h"
#include "Bravo.h"
#include "Manager.h"

float	g_fSoundVictory = 0.7f;

CBravo::CBravo()
{
}


CBravo::~CBravo()
{
	Release();
	CLineMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Delete_ID(OBJID::PLAYER);
	CObjMgr::Get_Instance()->Delete_Render(RENDER_OBJ);
	CSceneMgr::Get_Instance()->Scene_Change(SCENE_OVERWORLD);
}

void CBravo::Initialize(void)
{
	m_tInfo.fX;
	m_tInfo.fY;

	m_tInfo.fCX = 400.f;
	m_tInfo.fCY = 300.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bravo.bmp", L"Bravo");

	m_pFrameKey = L"Bravo";

	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_tTime = GetTickCount();

	m_eRenderGroup = RENDER_BACK;

	CSoundMgr::Get_Instance()->PlaySound(L"Victory.wav", CSoundMgr::UI, g_fSoundVictory);
}

int CBravo::Update(void)
{
	//return OBJ_DEAD;

	if (9 != m_tFrame.iFrameStart)
	{
		Update_Rect();
		Move_Frame();
	}

	if (m_tTime + 4000 <= GetTickCount())
	{
		return OBJ_DEAD;
	}
	return OBJ_NOEVENT;
}

void CBravo::Late_Update(void)
{
}

void CBravo::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,				//	���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left ),	//	2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5���� ���� ���� X,Y�� ���̸� ����	
		(int)m_tInfo.fCY,
		hMemDC,							// ��Ʈ�� ������ ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8���� ��Ʈ���� ����� ������ǥ
		m_tFrame.iFrameScene * (int)m_tInfo.fCY,
		400,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		300,
		RGB(237, 28, 36));
}

void CBravo::Release(void)
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
}
