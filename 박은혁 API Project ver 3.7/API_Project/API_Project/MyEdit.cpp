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

	/*if (CKeyMgr::Get_Instance()->Key_Down(VK_F1)) //Tile�� ��ġ�� �� ���� �ٸ� ���� ���� ������� ������!!!
		CTileMgr::Get_Instance()->Save_Tile();
*/
	/*if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	CTileMgr::Get_Instance()->Load_Tile();*/

}

void CMyEdit::Initialize(void)
{
	//////////////////////////////////////////////���� �Ŵ������� ���� ��ε� �ٲ������!!!
	/////////////////////////////����� �κ�
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/WorldMap/CupHeadWorldMap.bmp", L"WorldMap");

	/////////////////////////////����� �κ�
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/FarmMap/StageFarmMap.bmp", L"StageFarmMap");

	/////////////////////////////�ɸ� �κ�
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/FlowerMap/StageFlowerMap.bmp", L"StageFlowerMap");

	/////////////////////////////�����Ӹ� �κ�
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
	////////////////////////////////////////////////////////////////����� �κ�
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"WorldMap"); // �����
	HDC	hBackBuferDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer"); //����

	BitBlt(hBackBuferDC, //����������
		0 + iScrollX,
		0 + iScrollY,
		2778,
		1800,
		hMemDC, //�����
		0,
		0,
		SRCCOPY);

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



	//////////////////////////////////////////////////////////////////////////////����κ�
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
	//BitBlt(hDC,			//	���� ����, ���������� �׸��� �׸� DC //ȭ��
	//	0,					// 2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
	//	0,
	//	1221,				//4,5���� ���� ���� X,Y�� ���̸� ����
	//	621,
	//	hBackBuferFarmDC,		// ��Ʈ�� ������ ������ �ִ� DC //������ ���� ����
	//	0,					// 7,8���� ��Ʈ���� ����� ������ǥ
	//	0,
	//	SRCCOPY);
	//CLineMgr::Get_Instance()->Render(hDC);


	//////////////////////////////////////////////////////////////////////////////////�ö�� �� �κ�
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
	//BitBlt(hDC,			//	���� ����, ���������� �׸��� �׸� DC //ȭ��
	//	0,					// 2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
	//	0,
	//	1221,				//4,5���� ���� ���� X,Y�� ���̸� ����
	//	621,
	//	hBackBuferFlowerDC,		// ��Ʈ�� ������ ������ �ִ� DC //������ ���� ����
	//	0,					// 7,8���� ��Ʈ���� ����� ������ǥ
	//	0,
	//	SRCCOPY);
	//CLineMgr::Get_Instance()->Render(hDC);

	//////////////////////////////////////////////////////////////////////////////////������ �� �κ�
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
	//BitBlt(hDC,			//	���� ����, ���������� �׸��� �׸� DC //ȭ��
	//	0,					// 2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
	//	0,
	//	1221,				//4,5���� ���� ���� X,Y�� ���̸� ����
	//	621,
	//	hBackBuferSlimeDC,		// ��Ʈ�� ������ ������ �ִ� DC //������ ���� ����
	//	0,					// 7,8���� ��Ʈ���� ����� ������ǥ
	//	0,
	//	SRCCOPY);
	//CLineMgr::Get_Instance()->Render(hDC);
}

void CMyEdit::Release(void)
{
	CLineMgr::Get_Instance()->Destroy_Intance();
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
}
