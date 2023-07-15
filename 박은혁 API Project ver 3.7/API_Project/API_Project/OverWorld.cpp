#include "stdafx.h"
#include "OverWorld.h"
#include "OverPlayer.h"
#include "Manager.h"
#include "MyButton.h"
#include "Line.h"
#include "StageButton.h"

float		g_fSoundOverWorld = 0.2f;

COverWorld::COverWorld()
{
}


COverWorld::~COverWorld()
{
	Release();

}

void COverWorld::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/WorldMap/CupHeadWorldMap.bmp", L"WorldMap");
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/WorldMap/WorldFarm.bmp", L"WorldFarm");

	CObj*		pObj = CAbstractFactory<CStageButton>::Create(1293, 1302.f);
	dynamic_cast<CStageButton*>(pObj)->Set_FrameKey(L"WorldFarm");
	CObjMgr::Get_Instance()->Add_Object(OBJID::WORLDUI, pObj);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/WorldMap/WorldFlower.bmp", L"WorldFlower");
	pObj = CAbstractFactory<CStageButton>::Create(1467, 878.f);
	dynamic_cast<CStageButton*>(pObj)->Set_FrameKey(L"WorldFlower");
	CObjMgr::Get_Instance()->Add_Object(OBJID::WORLDUI, pObj);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/WorldMap/WorldSlime.bmp", L"WorldSlime");
	pObj = CAbstractFactory<CStageButton>::Create(1559, 715.f);
	dynamic_cast<CStageButton*>(pObj)->Set_FrameKey(L"WorldSlime");
	CObjMgr::Get_Instance()->Add_Object(OBJID::WORLDUI, pObj);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/WorldMap/WorldHome.bmp", L"WorldHome");
	pObj = CAbstractFactory<CStageButton>::Create(538, 738.f);
	dynamic_cast<CStageButton*>(pObj)->Set_FrameKey(L"WorldHome");
	CObjMgr::Get_Instance()->Add_Object(OBJID::WORLDUI, pObj);


	CObjMgr::Get_Instance()->Add_Object(OBJID::OVER_PLAYER, CAbstractFactory<COverPlayer>::Create(600,850));

	Load_Data();

	////////////////////////////////////////////////////////사운드
	//CSoundMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->PlaySound(L"OverWorld.mp3", CSoundMgr::BGM, g_fSoundOverWorld);
}

int COverWorld::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	//CLineMgr::Get_Instance()->Update();
	//CRectMgr::Get_Instance()->Update();
	return 0;
}

void COverWorld::Late_Update(void)
{
	Key_Input();
	CObjMgr::Get_Instance()->Late_Update();
	//CLineMgr::Get_Instance()->Late_Update();
	//CRectMgr::Get_Instance()->Late_Update();
}

void COverWorld::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"WorldMap"); // 월드맵
	HDC	hBackBuferDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer"); //수지

	BitBlt(hBackBuferDC, //수지열었고
		0 + iScrollX,
		0 + iScrollY,
		2778,
		1800,
		hMemDC, //간디
		0,
		0,
		SRCCOPY);

	//CSceneMgr::Get_Instance()->Render(hBackBuferDC);					 //이거 복사할 때 조심하셈 값 없는데 읽어서 터짐 값 있을때만 주석푸셈
	CObjMgr::Get_Instance()->Render(hBackBuferDC);						//이거 복사할 때 조심하셈 값 없는데 읽어서 터짐 값 있을때만 주석푸셈
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
	CObjMgr::Get_Instance()->Render(hDC);
}

void COverWorld::Release(void)
{

	CObjMgr::Get_Instance()->Delete_ID(OBJID::WORLDUI);

	CObjMgr::Get_Instance()->Delete_ID(OBJID::OVER_PLAYER);
	CLineMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Delete_Render(RENDER_OBJ);
	CObjMgr::Get_Instance()->Delete_Render(RENDER_BACK);
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	//StopSound(CHANNELID eID)
	//CSoundMgr::Get_Instance()->Release();
}

void COverWorld::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		g_fSoundOverWorld += 0.1f;

		if (g_fSoundOverWorld > 1.f)
			g_fSoundOverWorld = 1.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(CSoundMgr::BGM, g_fSoundOverWorld);
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		g_fSoundOverWorld -= 0.1f;

		if (g_fSoundOverWorld < 0.f)
			g_fSoundOverWorld = 0.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(CSoundMgr::BGM, g_fSoundOverWorld);
		return;
	}
}

void COverWorld::Load_Data()
{
	// 파일을 개방하는 함수					//World_Line, Farm_Line
	HANDLE			hFile = CreateFile(L"../Data/World_Line.dat",  // 파일 경로와 이름을 명시
		GENERIC_READ,		// 파일 접근모드(쓰기 전용)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허ㅇ가하는 것에 대해 설정 가능(NULL로 지정하면 공유하지 않는다)
		NULL,				// 보안모드, NULL인 경우 DEFAULT상태
		OPEN_EXISTING,		// 생성 방식, CREATE_ALWAYS(파일이 없으면 만들고, 있으면 덮어쓰기를 한다), OPEN_EXITING 파일 있을 경우에만 열겠다는 의미
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김 등), FILE_ATTRIBUTE_NORMAL 아무 속성이 없다는 뜻
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(우리는 졸업때까지 사용할 일이 없어서 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 파일 읽기
	DWORD		dwByte = 0;
	LINEINFO		tInfoLine{};

	while (true)
	{
		// 1인자 : 개방한 파일
		// 2인자 : 내가 파일에 저장하고자 하는 데이터
		// 3인자 : 저장하고자 하는 데이터 크기 단위
		// 4인자 : dwByte 값이 0이면 저장할 것이 없다. 
		ReadFile(hFile, &tInfoLine, sizeof(LINEINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		//CObjMgr::Get_Instance()->Add_Object(OBJID::LINE, CAbstractFactory<CLine>::Create(tInfoLine));
		CLineMgr::Get_Instance()->Set_LineList(CLine(tInfoLine));
	}

	CloseHandle(hFile);


	//////////////////////////////////////////////////////////여기부턴 렉트 로드
												//World_Rect, Farm_Rect
	HANDLE			hFileTest = CreateFile(L"../Data/World_Rect.dat",  // 파일 경로와 이름을 명시
		GENERIC_READ,		// 파일 접근모드(쓰기 전용)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허ㅇ가하는 것에 대해 설정 가능(NULL로 지정하면 공유하지 않는다)
		NULL,				// 보안모드, NULL인 경우 DEFAULT상태
		OPEN_EXISTING,		// 생성 방식, CREATE_ALWAYS(파일이 없으면 만들고, 있으면 덮어쓰기를 한다), OPEN_EXITING 파일 있을 경우에만 열겠다는 의미
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김 등), FILE_ATTRIBUTE_NORMAL 아무 속성이 없다는 뜻
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(우리는 졸업때까지 사용할 일이 없어서 NULL)

	if (INVALID_HANDLE_VALUE == hFileTest)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 파일 읽기
	DWORD		dwByteTest = 0;
	LINEINFO		tInfoRect{};

	while (true)
	{
		// 1인자 : 개방한 파일
		// 2인자 : 내가 파일에 저장하고자 하는 데이터
		// 3인자 : 저장하고자 하는 데이터 크기 단위
		// 4인자 : dwByte 값이 0이면 저장할 것이 없다. 
		ReadFile(hFile, &tInfoRect, sizeof(LINEINFO), &dwByteTest, NULL);

		if (0 == dwByteTest)
			break;

		CObjMgr::Get_Instance()->Add_Object(OBJID::MYRECT, CAbstractFactory<CMyRect>::Create(tInfoRect));
		CLineMgr::Get_Instance()->Set_RectList(CMyRect(tInfoRect));
	}

	CloseHandle(hFileTest);
	//MessageBox(g_hWnd, _T("Load 성공"), _T("Success"), MB_OKCANCEL);
}