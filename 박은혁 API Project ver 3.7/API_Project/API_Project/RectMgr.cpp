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
	// ������ �����ϴ� �Լ�
	HANDLE			hFile = CreateFile(L"../Data/World_Rect.dat",  // ���� ��ο� �̸��� ���
		GENERIC_WRITE,		// ���� ���ٸ��(���� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㤷���ϴ� �Ϳ� ���� ���� ����(NULL�� �����ϸ� �������� �ʴ´�)
		NULL,				// ���ȸ��, NULL�� ��� DEFAULT����
		CREATE_ALWAYS,		// ���� ���, CREATE_ALWAYS(������ ������ �����, ������ ����⸦ �Ѵ�), OPEN_EXITING ���� ���� ��쿡�� ���ڴٴ� �ǹ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ� �Ӽ��� ���ٴ� ��
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ���������� ����� ���� ��� NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return false;
	}

	// ���� ����
	DWORD		dwByte = 0;

	for (auto& iter : m_RectList)
	{
		// 1���� : ������ ����
		// 2���� : ���� ���Ͽ� �����ϰ��� �ϴ� ������
		// 3���� : �����ϰ��� �ϴ� ������ ũ�� ����
		// 4���� : dwByte ���� 0�̸� ������ ���� ����. 
		WriteFile(hFile, &(iter->Get_Info()), sizeof(RECTPOS), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save �Ϸ�"), _T("Success"), MB_OKCANCEL);

	return true;
}

bool CRectMgr::Load_Data(void)
{
	// ������ �����ϴ� �Լ�
	HANDLE			hFile = CreateFile(L"../Data/World_Rect.dat",  // ���� ��ο� �̸��� ���
		GENERIC_READ,		// ���� ���ٸ��(���� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㤷���ϴ� �Ϳ� ���� ���� ����(NULL�� �����ϸ� �������� �ʴ´�)
		NULL,				// ���ȸ��, NULL�� ��� DEFAULT����
		OPEN_EXISTING,		// ���� ���, CREATE_ALWAYS(������ ������ �����, ������ ����⸦ �Ѵ�), OPEN_EXITING ���� ���� ��쿡�� ���ڴٴ� �ǹ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ� �Ӽ��� ���ٴ� ��
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ���������� ����� ���� ��� NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return false;
	}

	// ���� �б�
	DWORD		dwByte = 0;
	RECTPOS		tPos{};

	while (true)
	{
		// 1���� : ������ ����
		// 2���� : ���� ���Ͽ� �����ϰ��� �ϴ� ������
		// 3���� : �����ϰ��� �ϴ� ������ ũ�� ����
		// 4���� : dwByte ���� 0�̸� ������ ���� ����. 
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
