#include "stdafx.h"
#include "StageSlime.h"
#include "Player.h"
#include "Manager.h"
#include "LittleSlimeMonster.h"

float		g_fSoundStageSlime = 0.2f;

CStageSlime::CStageSlime()
{
}


CStageSlime::~CStageSlime()
{
	Release();
}

void CStageSlime::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/SlimeMap/StageSlimeMap.bmp", L"StageSlimeMap");

	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(400, 400));
	CObjMgr::Get_Instance()->Stage_OffSet(OBJID::PLAYER); //�̰� ������������ ���¼��� �޶������� ���� �Լ��̴�!

														  //////////////////////////////////////////////OBJID�� ���� ���ͷ� �ϸ� ��� �ɱ�? �׽�Ʈ�� ���� ������ �߸� OBJID�� �� �� �������� ��!
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_COLLISION_BULLET, CAbstractFactory<CLittleSlimeMonster>::Create(600, 400));

	CScrollMgr::Get_Instance()->Set_ScrollX(3000.f);
	CScrollMgr::Get_Instance()->Set_ScrollY(3000.f);

	Load_Data();

	////////////////////////////////////////////////////////����
	//CSoundMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->PlaySound(L"StageSlime.mp3", CSoundMgr::BGM, g_fSoundStageSlime);
}

int CStageSlime::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CStageSlime::Late_Update(void)
{
	Key_Input();
	CObjMgr::Get_Instance()->Late_Update();
}

void CStageSlime::Render(HDC hDC)
{
	HDC	hMemSlimeDC = CBmpMgr::Get_Instance()->Find_Image(L"StageSlimeMap");
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

void CStageSlime::Release(void)
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
}

void CStageSlime::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		g_fSoundStageSlime += 0.1f;

		if (g_fSoundStageSlime > 1.f)
			g_fSoundStageSlime = 1.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(CSoundMgr::BGM, g_fSoundStageSlime);
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		g_fSoundStageSlime -= 0.1f;

		if (g_fSoundStageSlime < 0.f)
			g_fSoundStageSlime = 0.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(CSoundMgr::BGM, g_fSoundStageSlime);
		return;
	}
}

void CStageSlime::Load_Data()
{
	// ������ �����ϴ� �Լ�
	HANDLE			hFile = CreateFile(L"../Data/Slime_Line.dat",  // ���� ��ο� �̸��� ���
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

	HANDLE			hFileTest = CreateFile(L"../Data/Slime_Rect.dat",  // ���� ��ο� �̸��� ���
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
