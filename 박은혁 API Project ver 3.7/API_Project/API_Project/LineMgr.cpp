#include "stdafx.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"

CLineMgr* CLineMgr::m_pInstance;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
}

void CLineMgr::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		Picking_Line();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		Picking_Rect();

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Down('P'))
		Save_Data();

	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
		Load_Data();
}

void CLineMgr::Late_Update(void)
{
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);

	for (auto& iter : m_RectList)
		iter->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();

	for_each(m_RectList.begin(), m_RectList.end(), CDeleteObj());
	m_RectList.clear();
}

void CLineMgr::Picking_Line(void)
{
	POINT	pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (long)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (long)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (!m_tLinePos[0].fX && !m_tLinePos[0].fY)
	{
		m_tLinePos[0].fX = (float)pt.x;
		m_tLinePos[0].fY = (float)pt.y;
	}
	else
	{
		m_tLinePos[1].fX = (float)pt.x;
		m_tLinePos[1].fY = (float)pt.y;

		m_LineList.push_back(new CLine(m_tLinePos[0], m_tLinePos[1]));

		m_tLinePos[0].fX = 0.f;
		m_tLinePos[0].fY = 0.f;

	}
}
void CLineMgr::Picking_Rect(void)
{
	POINT	pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (long)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (long)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (!m_tLinePos[0].fX && !m_tLinePos[0].fY)
	{
		m_tLinePos[0].fX = (float)pt.x;
		m_tLinePos[0].fY = (float)pt.y;
	}
	else
	{
		m_tLinePos[1].fX = (float)pt.x;
		m_tLinePos[1].fY = (float)pt.y;

		//푸시백하기전에 걍 정보가져와서 오브젝트 템프 만들어서 셋 인포해서 렉트 
		m_RectList.push_back(new CMyRect(m_tLinePos[0], m_tLinePos[1]));

		m_tLinePos[0].fX = 0.f;
		m_tLinePos[0].fY = 0.f;

	}
}
bool CLineMgr::Collision_Line(const float & _fX, float * _fY)
{
	// 두 점을 지나는 직선의 방정식
	// Y  - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)

	// 플레이어의  Y 값을 구하도록 공식을 변경하자
	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	if (m_LineList.empty())
		return false;

	for (auto& iter : m_LineList)
	{
		if (iter->Get_Info().tLeftPos.fX < _fX &&
			iter->Get_Info().tRightPos.fX > _fX)
		{
			float x1 = iter->Get_Info().tLeftPos.fX;
			float y1 = iter->Get_Info().tLeftPos.fY;

			float x2 = iter->Get_Info().tRightPos.fX;
			float y2 = iter->Get_Info().tRightPos.fY;

			*_fY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;
			return true;
		}
	}

	return false;
}

bool CLineMgr::Collision_LineEx(const float & _fX, const float & _fCB, const float & _fNB, float * _fY)
{
	if (m_LineList.empty())
		return	false;

	for (auto&iter : m_LineList)
	{
		if (iter->Get_Info().tLeftPos.fX < _fX &&
			iter->Get_Info().tRightPos.fX > _fX)
		{
			float	x1 = iter->Get_Info().tLeftPos.fX;
			float	y1 = iter->Get_Info().tLeftPos.fY;

			float	x2 = iter->Get_Info().tRightPos.fX;
			float	y2 = iter->Get_Info().tRightPos.fY;

			float fY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

			//	충돌 지점이 범위에 들어있지 않은 지점이면 충돌하지 않았다
			if (_fNB < fY || fY < _fCB)
			{
				continue;
			}

			*_fY = fY;
			return	true;
		}
	}

	return false;
}

void CLineMgr::Set_RectList(CMyRect(_tInfo))
{
	m_RectList.push_back(new CMyRect(_tInfo));
}

void CLineMgr::Set_LineList(CLine(_tInfo))
{
	m_LineList.push_back(new CLine(_tInfo));
}

void CLineMgr::Save_Data(void)
{
	// 파일을 개방하는 함수              World_Line, Farm_Line, Flower_Line, Slime_Line
	HANDLE			hFile = CreateFile(L"../Data/World_Line.dat",  // 파일 경로와 이름을 명시
		GENERIC_WRITE,		// 파일 접근모드(쓰기 전용)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허ㅇ가하는 것에 대해 설정 가능(NULL로 지정하면 공유하지 않는다)
		NULL,				// 보안모드, NULL인 경우 DEFAULT상태
		CREATE_ALWAYS,		// 생성 방식, CREATE_ALWAYS(파일이 없으면 만들고, 있으면 덮어쓰기를 한다), OPEN_EXITING 파일 있을 경우에만 열겠다는 의미
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김 등), FILE_ATTRIBUTE_NORMAL 아무 속성이 없다는 뜻
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(우리는 졸업때까지 사용할 일이 없어서 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	// 파일 쓰기
	DWORD		dwByte = 0;

	for (auto& iter : m_LineList)
	{
		// 1인자 : 개방한 파일
		// 2인자 : 내가 파일에 저장하고자 하는 데이터
		// 3인자 : 저장하고자 하는 데이터 크기 단위
		// 4인자 : dwByte 값이 0이면 저장할 것이 없다. 
		WriteFile(hFile, &(iter->Get_Info()), sizeof(LINEINFO), &dwByte, NULL);
	}

	CloseHandle(hFile);

	/////////////////////////////////////////////////// 렉트
	//									World_Rect, Farm_Rect, Flower_Rect, Slime_Rect
	HANDLE			hFileTest = CreateFile(L"../Data/World_Rect.dat",  // 파일 경로와 이름을 명시
		GENERIC_WRITE,		// 파일 접근모드(쓰기 전용)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허ㅇ가하는 것에 대해 설정 가능(NULL로 지정하면 공유하지 않는다)
		NULL,				// 보안모드, NULL인 경우 DEFAULT상태
		CREATE_ALWAYS,		// 생성 방식, CREATE_ALWAYS(파일이 없으면 만들고, 있으면 덮어쓰기를 한다), OPEN_EXITING 파일 있을 경우에만 열겠다는 의미
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김 등), FILE_ATTRIBUTE_NORMAL 아무 속성이 없다는 뜻
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(우리는 졸업때까지 사용할 일이 없어서 NULL)

	if (INVALID_HANDLE_VALUE == hFileTest)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	// 파일 쓰기
	DWORD		dwByteTest = 0;

	for (auto& iter : m_RectList)
	{
		// 1인자 : 개방한 파일
		// 2인자 : 내가 파일에 저장하고자 하는 데이터
		// 3인자 : 저장하고자 하는 데이터 크기 단위
		// 4인자 : dwByte 값이 0이면 저장할 것이 없다. 
		WriteFile(hFileTest, &(iter->Get_InfoRect()), sizeof(LINEINFO), &dwByteTest, NULL);
	}

	CloseHandle(hFileTest);

	MessageBox(g_hWnd, _T("Save 완료"), _T("Success"), MB_OKCANCEL);
}

void CLineMgr::Load_Data(void)
{
	// 파일을 개방하는 함수			World_Line , Farm_Line, Flower_Line, Slime_Line
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
	DWORD		dwTest = 0;
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

		m_LineList.push_back(new CLine(tInfoLine));
	}

	CloseHandle(hFile);
	///////////////////////////////////////////////////////////////
	//										World_Rect, Farm_Rect, Flower_Rect, Slime_Rect
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

		m_RectList.push_back(new CMyRect(tInfoRect));
	}

	CloseHandle(hFileTest);
	MessageBox(g_hWnd, _T("Load 성공"), _T("Success"), MB_OKCANCEL);
}
