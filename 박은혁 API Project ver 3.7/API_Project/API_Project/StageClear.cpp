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
	BitBlt(hDC,			//	복사 받을, 최종적으로 그림을 그릴 DC //화면
		0,					// 2, 3인자 복사 받을 위치의 좌표를 전달
		0,
		800,				//4,5인자 복사 받을 X,Y의 길이를 전달
		600,
		hBackBuferSlimeDC,		// 비트맵 정보를 가지고 있는 DC //수지에 열린 간디
		0,					// 7,8인자 비트맵을 출력할 시작좌표
		0,
		SRCCOPY);

	CLineMgr::Get_Instance()->Render(hDC);
}

void CStageClear::Release(void)
{
}
