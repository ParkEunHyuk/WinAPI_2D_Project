#include "stdafx.h"
#include "RectMgr.h"
#include "Manager.h"
#include "MyRect.h"

CRectMgr* CRectMgr::m_pInstance;

CRectMgr::CRectMgr()
{
}


CRectMgr::~CRectMgr()
{
	Release();
}

bool CRectMgr::Save_Data(void)
{
	// 파일을 개방하는 함수
	HANDLE			hFile = CreateFile(L"../Data/World_Rect.dat",  // 파일 경로와 이름을 명시
		GENERIC_WRITE,		// 파일 접근모드(쓰기 전용)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허ㅇ가하는 것에 대해 설정 가능(NULL로 지정하면 공유하지 않는다)
		NULL,				// 보안모드, NULL인 경우 DEFAULT상태
		CREATE_ALWAYS,		// 생성 방식, CREATE_ALWAYS(파일이 없으면 만들고, 있으면 덮어쓰기를 한다), OPEN_EXITING 파일 있을 경우에만 열겠다는 의미
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김 등), FILE_ATTRIBUTE_NORMAL 아무 속성이 없다는 뜻
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(우리는 졸업때까지 사용할 일이 없어서 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return false;
	}

	// 파일 쓰기
	DWORD		dwByte = 0;

	for (auto& iter : m_RectList)
	{
		// 1인자 : 개방한 파일
		// 2인자 : 내가 파일에 저장하고자 하는 데이터
		// 3인자 : 저장하고자 하는 데이터 크기 단위
		// 4인자 : dwByte 값이 0이면 저장할 것이 없다. 
		WriteFile(hFile, &(iter->Get_Info()), sizeof(RECTPOS), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 완료"), _T("Success"), MB_OKCANCEL);

	return true;
}

bool CRectMgr::Load_Data(void)
{
	// 파일을 개방하는 함수
	HANDLE			hFile = CreateFile(L"../Data/World_Rect.dat",  // 파일 경로와 이름을 명시
		GENERIC_READ,		// 파일 접근모드(쓰기 전용)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허ㅇ가하는 것에 대해 설정 가능(NULL로 지정하면 공유하지 않는다)
		NULL,				// 보안모드, NULL인 경우 DEFAULT상태
		OPEN_EXISTING,		// 생성 방식, CREATE_ALWAYS(파일이 없으면 만들고, 있으면 덮어쓰기를 한다), OPEN_EXITING 파일 있을 경우에만 열겠다는 의미
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김 등), FILE_ATTRIBUTE_NORMAL 아무 속성이 없다는 뜻
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(우리는 졸업때까지 사용할 일이 없어서 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return false;
	}

	// 파일 읽기
	DWORD		dwByte = 0;
	RECTPOS		tPos{};

	while (true)
	{
		// 1인자 : 개방한 파일
		// 2인자 : 내가 파일에 저장하고자 하는 데이터
		// 3인자 : 저장하고자 하는 데이터 크기 단위
		// 4인자 : dwByte 값이 0이면 저장할 것이 없다. 
		ReadFile(hFile, &tPos, sizeof(RECTPOS), &dwByte, NULL);

		if (0 == dwByte)
			break;

		//CObj* pObj;
		//pObj = CAbstractFactory<CMyRect>::Create(tPos);
		//CObjMgr::Get_Instance()->Add_Object(OBJID::MYRECT, pObj);

		CObjMgr::Get_Instance()->Add_Object(OBJID::MYRECT, CAbstractFactory<CMyRect>::Create(tPos));
		//CRectMgr::Get_Instance()->Set_RectList(CMyRect(tPos));
	}

	CloseHandle(hFile);
	return true;
}

void CRectMgr::Picking_Rect(void)
{
	POINT	pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (long)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (long)CScrollMgr::Get_Instance()->Get_ScrollY();
	if (pt.x % 40)
	{
		pt.x = (pt.x / 40) * 40 + 20;
	}
	else
		pt.x = (pt.x / 40) * 40 - 20;

	if (pt.y % 40)
	{
		pt.y = (pt.y / 40) * 40 + 20;
	}
	else
		pt.y = (pt.y / 40) * 40 - 20;
	if (m_RectList.empty())
	{
		m_RectList.push_back(new CMyRect(pt.x, pt.y));
	}
	else if (!m_RectList.empty())
	{
		for (auto Rect : m_RectList)
		{
			if (!(Rect->Get_Info().fX == pt.x) && !(Rect->Get_Info().fY == pt.y))
				m_RectList.push_back(new CMyRect(pt.x, pt.y));
		}
	}
}

void CRectMgr::Set_RectList(CMyRect(_tInfo))
{
	m_RectList.push_back(new CMyRect(_tInfo));
}

void CRectMgr::Initialize(void)
{
	Load_Data();
}

void CRectMgr::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		Picking_Rect();

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		Save_Data();

	if (CKeyMgr::Get_Instance()->Key_Down('A'))
		Load_Data();
}

void CRectMgr::Late_Update(void)
{
}

void CRectMgr::Render(HDC _DC)
{
	for (auto& iter : m_RectList)
		iter->Render(_DC);
}

void CRectMgr::Release(void)
{
	for_each(m_RectList.begin(), m_RectList.end(), CDeleteObj());
	m_RectList.clear();
}
