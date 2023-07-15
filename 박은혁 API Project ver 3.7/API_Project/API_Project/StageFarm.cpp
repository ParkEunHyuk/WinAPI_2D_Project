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
	CObjMgr::Get_Instance()->Stage_OffSet(OBJID::PLAYER); //�̰� ������������ ���¼��� �޶������� ���� �Լ��̴�!

	//////////////////////////////////////////////OBJID�� ���� ���ͷ� �ϸ� ��� �ɱ�? �׽�Ʈ�� ���� ������ �߸� OBJID�� �� �� �������� ��!
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
	//�ߺ��� ��ũ�ѸŴ����� Set_ScrollX�� Y�� �����ϱ� ���� �������ָ� �� ��?
	//���� ������������ ��ũ�� ���� �ɾ������
	//CScrollMgr::Get_Instance()->Scroll_Lock();
	//if (0 < m_fScrollX)
	//	m_fScrollX = 0.f;

	//// WINCX - TILEX * TILECX�� ������ 
	//if (WINCX - MAPCX > m_fScrollX) //�÷��̾ ���������� ���ٸ� ��ũ���� �������� ���� ������ ���� ������ �ȴ�.
	//	m_fScrollX = WINCX - MAPCX; //WINCX�� ���� �ʴ´ٸ� Ÿ���� ������ �κ��� ����� �� ��ũ���� �����. �׷��� �Ǹ� �� ����� ���δ�.

	//if (0 < m_fScrollY)
	//	m_fScrollY = 0.f;

	//if (WINCY - MAPCY > m_fScrollY) //�� ����� ����. ���� X�� Y�� ������ ��
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
	BitBlt(hDC,			//	���� ����, ���������� �׸��� �׸� DC //ȭ��
		0,					// 2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		0,
		1221,				//4,5���� ���� ���� X,Y�� ���̸� ����
		621,
		hBackBuferFarmDC,		// ��Ʈ�� ������ ������ �ִ� DC //������ ���� ����
		0,					// 7,8���� ��Ʈ���� ����� ������ǥ
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
	// ������ �����ϴ� �Լ�
	HANDLE			hFile = CreateFile(L"../Data/Farm_Line.dat",  // ���� ��ο� �̸��� ���
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

	HANDLE			hFileTest = CreateFile(L"../Data/Farm_Rect.dat",  // ���� ��ο� �̸��� ���
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
