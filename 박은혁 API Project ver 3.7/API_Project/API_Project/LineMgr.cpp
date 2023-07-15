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

		//Ǫ�ù��ϱ����� �� ���������ͼ� ������Ʈ ���� ���� �� �����ؼ� ��Ʈ 
		m_RectList.push_back(new CMyRect(m_tLinePos[0], m_tLinePos[1]));

		m_tLinePos[0].fX = 0.f;
		m_tLinePos[0].fY = 0.f;

	}
}
bool CLineMgr::Collision_Line(const float & _fX, float * _fY)
{
	// �� ���� ������ ������ ������
	// Y  - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)

	// �÷��̾���  Y ���� ���ϵ��� ������ ��������
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

			//	�浹 ������ ������ ������� ���� �����̸� �浹���� �ʾҴ�
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
	// ������ �����ϴ� �Լ�              World_Line, Farm_Line, Flower_Line, Slime_Line
	HANDLE			hFile = CreateFile(L"../Data/World_Line.dat",  // ���� ��ο� �̸��� ���
		GENERIC_WRITE,		// ���� ���ٸ��(���� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㤷���ϴ� �Ϳ� ���� ���� ����(NULL�� �����ϸ� �������� �ʴ´�)
		NULL,				// ���ȸ��, NULL�� ��� DEFAULT����
		CREATE_ALWAYS,		// ���� ���, CREATE_ALWAYS(������ ������ �����, ������ ����⸦ �Ѵ�), OPEN_EXITING ���� ���� ��쿡�� ���ڴٴ� �ǹ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ� �Ӽ��� ���ٴ� ��
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ���������� ����� ���� ��� NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	// ���� ����
	DWORD		dwByte = 0;

	for (auto& iter : m_LineList)
	{
		// 1���� : ������ ����
		// 2���� : ���� ���Ͽ� �����ϰ��� �ϴ� ������
		// 3���� : �����ϰ��� �ϴ� ������ ũ�� ����
		// 4���� : dwByte ���� 0�̸� ������ ���� ����. 
		WriteFile(hFile, &(iter->Get_Info()), sizeof(LINEINFO), &dwByte, NULL);
	}

	CloseHandle(hFile);

	/////////////////////////////////////////////////// ��Ʈ
	//									World_Rect, Farm_Rect, Flower_Rect, Slime_Rect
	HANDLE			hFileTest = CreateFile(L"../Data/World_Rect.dat",  // ���� ��ο� �̸��� ���
		GENERIC_WRITE,		// ���� ���ٸ��(���� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㤷���ϴ� �Ϳ� ���� ���� ����(NULL�� �����ϸ� �������� �ʴ´�)
		NULL,				// ���ȸ��, NULL�� ��� DEFAULT����
		CREATE_ALWAYS,		// ���� ���, CREATE_ALWAYS(������ ������ �����, ������ ����⸦ �Ѵ�), OPEN_EXITING ���� ���� ��쿡�� ���ڴٴ� �ǹ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ� �Ӽ��� ���ٴ� ��
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ���������� ����� ���� ��� NULL)

	if (INVALID_HANDLE_VALUE == hFileTest)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	// ���� ����
	DWORD		dwByteTest = 0;

	for (auto& iter : m_RectList)
	{
		// 1���� : ������ ����
		// 2���� : ���� ���Ͽ� �����ϰ��� �ϴ� ������
		// 3���� : �����ϰ��� �ϴ� ������ ũ�� ����
		// 4���� : dwByte ���� 0�̸� ������ ���� ����. 
		WriteFile(hFileTest, &(iter->Get_InfoRect()), sizeof(LINEINFO), &dwByteTest, NULL);
	}

	CloseHandle(hFileTest);

	MessageBox(g_hWnd, _T("Save �Ϸ�"), _T("Success"), MB_OKCANCEL);
}

void CLineMgr::Load_Data(void)
{
	// ������ �����ϴ� �Լ�			World_Line , Farm_Line, Flower_Line, Slime_Line
	HANDLE			hFile = CreateFile(L"../Data/World_Line.dat",  // ���� ��ο� �̸��� ���
		GENERIC_READ,		// ���� ���ٸ��(���� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㤷���ϴ� �Ϳ� ���� ���� ����(NULL�� �����ϸ� �������� �ʴ´�)
		NULL,				// ���ȸ��, NULL�� ��� DEFAULT����
		OPEN_EXISTING,		// ���� ���, CREATE_ALWAYS(������ ������ �����, ������ ����⸦ �Ѵ�), OPEN_EXITING ���� ���� ��쿡�� ���ڴٴ� �ǹ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ� �Ӽ��� ���ٴ� ��
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ���������� ����� ���� ��� NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// ���� �б�
	DWORD		dwByte = 0;
	DWORD		dwTest = 0;
	LINEINFO		tInfoLine{};

	while (true)
	{
		// 1���� : ������ ����
		// 2���� : ���� ���Ͽ� �����ϰ��� �ϴ� ������
		// 3���� : �����ϰ��� �ϴ� ������ ũ�� ����
		// 4���� : dwByte ���� 0�̸� ������ ���� ����. 
		ReadFile(hFile, &tInfoLine, sizeof(LINEINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfoLine));
	}

	CloseHandle(hFile);
	///////////////////////////////////////////////////////////////
	//										World_Rect, Farm_Rect, Flower_Rect, Slime_Rect
	HANDLE			hFileTest = CreateFile(L"../Data/World_Rect.dat",  // ���� ��ο� �̸��� ���
		GENERIC_READ,		// ���� ���ٸ��(���� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㤷���ϴ� �Ϳ� ���� ���� ����(NULL�� �����ϸ� �������� �ʴ´�)
		NULL,				// ���ȸ��, NULL�� ��� DEFAULT����
		OPEN_EXISTING,		// ���� ���, CREATE_ALWAYS(������ ������ �����, ������ ����⸦ �Ѵ�), OPEN_EXITING ���� ���� ��쿡�� ���ڴٴ� �ǹ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ� �Ӽ��� ���ٴ� ��
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ���������� ����� ���� ��� NULL)

	if (INVALID_HANDLE_VALUE == hFileTest)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// ���� �б�
	DWORD		dwByteTest = 0;
	LINEINFO		tInfoRect{};

	while (true)
	{
		// 1���� : ������ ����
		// 2���� : ���� ���Ͽ� �����ϰ��� �ϴ� ������
		// 3���� : �����ϰ��� �ϴ� ������ ũ�� ����
		// 4���� : dwByte ���� 0�̸� ������ ���� ����. 
		ReadFile(hFile, &tInfoRect, sizeof(LINEINFO), &dwByteTest, NULL);

		if (0 == dwByteTest)
			break;

		m_RectList.push_back(new CMyRect(tInfoRect));
	}

	CloseHandle(hFileTest);
	MessageBox(g_hWnd, _T("Load ����"), _T("Success"), MB_OKCANCEL);
}
