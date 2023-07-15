#include "stdafx.h"
#include "StageFarm.h"
#include "Manager.h"
#include "Player.h"
#include "PotatoMonster.h"

float		g_fSoundStageFarm = 0.2f;

CStageFarm::CStageFarm()
{
}


CStageFarm::~CStageFarm()
{
	Release();
}

void CStageFarm::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/FarmMap/StageFarmMap.bmp", L"StageFarmMap");

	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(400, 400));
	CObjMgr::Get_Instance()->Stage_OffSet(OBJID::PLAYER); //이건 스테이지마다 오픈셋이 달라지도록 만든 함수이다!

	//////////////////////////////////////////////OBJID를 전부 몬스터로 하면 어떻게 될까? 테스트중 만약 컴파일 뜨면 OBJID를 각 각 지정해줄 것!
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, CAbstractFactory<CPotatoMonster>::Create(680, 400));


	CScrollMgr::Get_Instance()->Set_ScrollX(3000.f);
	CScrollMgr::Get_Instance()->Set_ScrollY(3000.f);
	
	//CSoundMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->PlaySound(L"StageFarm.mp3", CSoundMgr::BGM, g_fSoundStageFarm);

	Load_Data();
}

int CStageFarm::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CStageFarm::Late_Update(void)
{
	Key_Input();
	//잘보면 스크롤매니저에 Set_ScrollX랑 Y이 있으니깐 새로 지정해주면 될 듯?
	//각각 스테이지별로 스크롤 락을 걸어줘야함
	//CScrollMgr::Get_Instance()->Scroll_Lock();
	//if (0 < m_fScrollX)
	//	m_fScrollX = 0.f;

	//// WINCX - TILEX * TILECX는 음수임 
	//if (WINCX - MAPCX > m_fScrollX) //플레이어가 오른쪽으로 간다면 스크롤은 왼쪽으로 가기 때문에 점점 음수가 된다.
	//	m_fScrollX = WINCX - MAPCX; //WINCX를 쓰지 않는다면 타일의 마지막 부분이 사라질 때 스크롤이 멈춘다. 그렇게 되면 뒷 배경이 보인다.

	//if (0 < m_fScrollY)
	//	m_fScrollY = 0.f;

	//if (WINCY - MAPCY > m_fScrollY) //윗 내용과 같다. 단지 X와 Y의 차이일 뿐
	//	m_fScrollY = WINCY - MAPCY;

	CObjMgr::Get_Instance()->Late_Update();
}

void CStageFarm::Render(HDC hDC)
{

	HDC	hMemFarmDC = CBmpMgr::Get_Instance()->Find_Image(L"StageFarmMap");
	HDC	hBackBuferFarmDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer");
	BitBlt(hBackBuferFarmDC,
		0,
		0,
		1221,
		621,
		hMemFarmDC,
		0,
		0,
		SRCCOPY);
	CObjMgr::Get_Instance()->Render(hBackBuferFarmDC);
	BitBlt(hDC,			//	복사 받을, 최종적으로 그림을 그릴 DC //화면
		0,					// 2, 3인자 복사 받을 위치의 좌표를 전달
		0,
		1221,				//4,5인자 복사 받을 X,Y의 길이를 전달
		621,
		hBackBuferFarmDC,		// 비트맵 정보를 가지고 있는 DC //수지에 열린 간디
		0,					// 7,8인자 비트맵을 출력할 시작좌표
		0,
		SRCCOPY);

	//CLineMgr::Get_Instance()->Render(hDC);
}

void CStageFarm::Release(void)
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
}

void CStageFarm::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		g_fSoundStageFarm += 0.1f;

		if (g_fSoundStageFarm > 1.f)
			g_fSoundStageFarm = 1.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(CSoundMgr::BGM, g_fSoundStageFarm);
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		g_fSoundStageFarm -= 0.1f;

		if (g_fSoundStageFarm < 0.f)
			g_fSoundStageFarm = 0.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(CSoundMgr::BGM, g_fSoundStageFarm);
		return;
	}
}

void CStageFarm::Load_Data()
{
	// 파일을 개방하는 함수
	HANDLE			hFile = CreateFile(L"../Data/Farm_Line.dat",  // 파일 경로와 이름을 명시
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

	HANDLE			hFileTest = CreateFile(L"../Data/Farm_Rect.dat",  // 파일 경로와 이름을 명시
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
