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

	////////////////////////////////////////////////////////����
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
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"WorldMap"); // �����
	HDC	hBackBuferDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer"); //����

	BitBlt(hBackBuferDC, //����������
		0 + iScrollX,
		0 + iScrollY,
		2778,
		1800,
		hMemDC, //����
		0,
		0,
		SRCCOPY);

	//CSceneMgr::Get_Instance()->Render(hBackBuferDC);					 //�̰� ������ �� �����ϼ� �� ���µ� �о ���� �� �������� �ּ�Ǫ��
	CObjMgr::Get_Instance()->Render(hBackBuferDC);						//�̰� ������ �� �����ϼ� �� ���µ� �о ���� �� �������� �ּ�Ǫ��
	BitBlt(hDC,			//	���� ����, ���������� �׸��� �׸� DC //ȭ��
		0,					// 2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		0,
		2778,				//4,5���� ���� ���� X,Y�� ���̸� ����
		1800,
		hBackBuferDC,		// ��Ʈ�� ������ ������ �ִ� DC //������ ���� ����
		0,					// 7,8���� ��Ʈ���� ����� ������ǥ
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
	// ������ �����ϴ� �Լ�					//World_Line, Farm_Line
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

		//CObjMgr::Get_Instance()->Add_Object(OBJID::LINE, CAbstractFactory<CLine>::Create(tInfoLine));
		CLineMgr::Get_Instance()->Set_LineList(CLine(tInfoLine));
	}

	CloseHandle(hFile);


	//////////////////////////////////////////////////////////������� ��Ʈ �ε�
												//World_Rect, Farm_Rect
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

		CObjMgr::Get_Instance()->Add_Object(OBJID::MYRECT, CAbstractFactory<CMyRect>::Create(tInfoRect));
		CLineMgr::Get_Instance()->Set_RectList(CMyRect(tInfoRect));
	}

	CloseHandle(hFileTest);
	//MessageBox(g_hWnd, _T("Load ����"), _T("Success"), MB_OKCANCEL);
}