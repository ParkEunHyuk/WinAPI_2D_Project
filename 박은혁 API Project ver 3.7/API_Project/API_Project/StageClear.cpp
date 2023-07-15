#include "stdafx.h"
#include "StageClear.h"
#include "Manager.h"

float		g_fSoundStageClear = 0.5f;
//StageClear

CStageClear::CStageClear()
{
}


CStageClear::~CStageClear()
{
}

void CStageClear::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/ClearMap/ClearMap.bmp", L"ClearMap");

	CSoundMgr::Get_Instance()->PlaySound(L"StageClear.mp3", CSoundMgr::BGM, g_fSoundStageClear);
}

int CStageClear::Update(void)
{
	return 0;
}

void CStageClear::Late_Update(void)
{
}

void CStageClear::Render(HDC hDC)
{
	HDC	hMemSlimeDC = CBmpMgr::Get_Instance()->Find_Image(L"ClearMap");
	HDC	hBackBuferSlimeDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer");
	BitBlt(hBackBuferSlimeDC,
		0,
		0,
		800,
		600,
		hMemSlimeDC,
		0,
		0,
		SRCCOPY);
	CObjMgr::Get_Instance()->Render(hBackBuferSlimeDC);
	BitBlt(hDC,			//	���� ����, ���������� �׸��� �׸� DC //ȭ��
		0,					// 2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		0,
		800,				//4,5���� ���� ���� X,Y�� ���̸� ����
		600,
		hBackBuferSlimeDC,		// ��Ʈ�� ������ ������ �ִ� DC //������ ���� ����
		0,					// 7,8���� ��Ʈ���� ����� ������ǥ
		0,
		SRCCOPY);

	CLineMgr::Get_Instance()->Render(hDC);
}

void CStageClear::Release(void)
{
}
