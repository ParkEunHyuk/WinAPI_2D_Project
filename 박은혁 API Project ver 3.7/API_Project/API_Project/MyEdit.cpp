#include "stdafx.h"
#include "MyEdit.h"
#include "Manager.h"

CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Key_Input(void)
{

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);

	/*if (CKeyMgr::Get_Instance()->Key_Down(VK_F1)) //Tile를 설치할 수 있음 다만 지금 당장 사용하지 않을것!!!
		CTileMgr::Get_Instance()->Save_Tile();
*/
	/*if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	CTileMgr::Get_Instance()->Load_Tile();*/

}

void CMyEdit::Initialize(void)
{
	//////////////////////////////////////////////라인 매니저에서 저장 경로도 바꿔줘야함!!!
	/////////////////////////////월드맵 부분
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/WorldMap/CupHeadWorldMap.bmp", L"WorldMap");

	/////////////////////////////농장맵 부분
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/FarmMap/StageFarmMap.bmp", L"StageFarmMap");

	/////////////////////////////꽃맵 부분
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/FlowerMap/StageFlowerMap.bmp", L"StageFlowerMap");

	/////////////////////////////슬라임맵 부분
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/SlimeMap/StageSlimeMap.bmp", L"StageSlimeMap");

	CLineMgr::Get_Instance()->Initialize();

	float		g_fSoundOverWorld = 0.2f;

	CSoundMgr::Get_Instance()->PlaySound(L"OverWorld.mp3", CSoundMgr::BGM, g_fSoundOverWorld);
}

int CMyEdit::Update(void)
{
	//CObjMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();

	Key_Input();

	return 0;
}

void CMyEdit::Late_Update(void)
{
	//CObjMgr::Get_Instance()->Late_Update();
	CLineMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{
	////////////////////////////////////////////////////////////////월드맵 부분
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"WorldMap"); // 월드맵
	HDC	hBackBuferDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer"); //수지

	BitBlt(hBackBuferDC, //수지열었고
		0 + iScrollX,
		0 + iScrollY,
		2778,
		1800,
		hMemDC, //월드맵
		0,
		0,
		SRCCOPY);

	BitBlt(hDC,			//	복사 받을, 최종적으로 그림을 그릴 DC //화면
		0,					// 2, 3인자 복사 받을 위치의 좌표를 전달
		0,
		2778,				//4,5인자 복사 받을 X,Y의 길이를 전달
		1800,
		hBackBuferDC,		// 비트맵 정보를 가지고 있는 DC //수지에 열린 간디
		0,					// 7,8인자 비트맵을 출력할 시작좌표
		0,
		SRCCOPY);
	CLineMgr::Get_Instance()->Render(hDC);



	//////////////////////////////////////////////////////////////////////////////농장부분
	//HDC	hMemFarmDC = CBmpMgr::Get_Instance()->Find_Image(L"StageFarmMap");
	//HDC	hBackBuferFarmDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer");
	//BitBlt(hBackBuferFarmDC,
	//	0,
	//	0,
	//	1221,
	//	621,
	//	hMemFarmDC,
	//	0,
	//	0,
	//	SRCCOPY);
	//BitBlt(hDC,			//	복사 받을, 최종적으로 그림을 그릴 DC //화면
	//	0,					// 2, 3인자 복사 받을 위치의 좌표를 전달
	//	0,
	//	1221,				//4,5인자 복사 받을 X,Y의 길이를 전달
	//	621,
	//	hBackBuferFarmDC,		// 비트맵 정보를 가지고 있는 DC //수지에 열린 간디
	//	0,					// 7,8인자 비트맵을 출력할 시작좌표
	//	0,
	//	SRCCOPY);
	//CLineMgr::Get_Instance()->Render(hDC);


	//////////////////////////////////////////////////////////////////////////////////플라워 맵 부분
	//HDC	hMemFlowerDC = CBmpMgr::Get_Instance()->Find_Image(L"StageFlowerMap");
	//HDC	hBackBuferFlowerDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer");
	//BitBlt(hBackBuferFlowerDC,
	//	0,
	//	0,
	//	1221,
	//	621,
	//	hMemFlowerDC,
	//	0,
	//	0,
	//	SRCCOPY);
	//BitBlt(hDC,			//	복사 받을, 최종적으로 그림을 그릴 DC //화면
	//	0,					// 2, 3인자 복사 받을 위치의 좌표를 전달
	//	0,
	//	1221,				//4,5인자 복사 받을 X,Y의 길이를 전달
	//	621,
	//	hBackBuferFlowerDC,		// 비트맵 정보를 가지고 있는 DC //수지에 열린 간디
	//	0,					// 7,8인자 비트맵을 출력할 시작좌표
	//	0,
	//	SRCCOPY);
	//CLineMgr::Get_Instance()->Render(hDC);

	//////////////////////////////////////////////////////////////////////////////////슬라임 맵 부분
	//HDC	hMemSlimeDC = CBmpMgr::Get_Instance()->Find_Image(L"StageSlimeMap");
	//HDC	hBackBuferSlimeDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer");
	//BitBlt(hBackBuferSlimeDC,
	//	0,
	//	0,
	//	1221,
	//	621,
	//	hMemSlimeDC,
	//	0,
	//	0,
	//	SRCCOPY);
	//BitBlt(hDC,			//	복사 받을, 최종적으로 그림을 그릴 DC //화면
	//	0,					// 2, 3인자 복사 받을 위치의 좌표를 전달
	//	0,
	//	1221,				//4,5인자 복사 받을 X,Y의 길이를 전달
	//	621,
	//	hBackBuferSlimeDC,		// 비트맵 정보를 가지고 있는 DC //수지에 열린 간디
	//	0,					// 7,8인자 비트맵을 출력할 시작좌표
	//	0,
	//	SRCCOPY);
	//CLineMgr::Get_Instance()->Render(hDC);
}

void CMyEdit::Release(void)
{
	CLineMgr::Get_Instance()->Destroy_Intance();
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
}
