#include "stdafx.h"
#include "FaceAttack.h"
#include "Manager.h"
#include "FaceWhip.h"


CFaceAttack::CFaceAttack()
	:m_bFace_Switch(false), iCount(0)
{
}


CFaceAttack::~CFaceAttack()
{
}

void CFaceAttack::Initialize(void)
{
	m_tInfo.fCX = 750;
	m_tInfo.fCY = 350.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/FaceAttack.bmp", L"FaceAttack");
	m_pFrameKey = L"FaceAttack"; 

	m_eCurState = FACEATTACK_UP;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();


	m_eRenderGroup = RENDER_BACK;


	m_tTimePattern = GetTickCount();
}

int CFaceAttack::Update(void)
{

	if (m_bFace_Switch == false)
	{
		m_tRandomFaceAttack = rand() % 2;
		switch (m_tRandomFaceAttack)
		{
		case 0:
			m_eCurState = FACEATTACK_UP;
			break;
		case 1:
			m_eCurState = FACEATTACK_DOWN;
			break;
		}
		m_bFace_Switch = true;
	}
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		return OBJ_DEAD;
	}
	if (m_tFrame.iFrameStart == 4 && m_eCurState == FACEATTACK_UP)
	{
		if (iCount < 1)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_COLLISION_BULLET, CAbstractFactory<CFaceWhip>::Create(400, 350));
			++iCount;
		}
	}
	else if (m_tFrame.iFrameStart == 4 && m_eCurState == FACEATTACK_DOWN)
	{
		if (iCount < 1)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_COLLISION_BULLET, CAbstractFactory<CFaceWhip>::Create(400, 550));
			++iCount;
		}
	}
	State_Change();
	Update_Rect();
	Move_Frame();
	return OBJ_NOEVENT;
}

void CFaceAttack::Late_Update(void)
{
}

void CFaceAttack::Render(HDC hDC)
{
#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
#endif // !_DEBUG

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,				//	���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),	//	2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5���� ���� ���� X,Y�� ���̸� ����	
		(int)m_tInfo.fCY,
		hMemDC,							// ��Ʈ�� ������ ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8���� ��Ʈ���� ����� ������ǥ
		m_tFrame.iFrameScene * (int)m_tInfo.fCY,
		750,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		350.f,
		RGB(237, 28, 36));
}

void CFaceAttack::Release(void)
{
}

void CFaceAttack::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case FACEATTACK_UP:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case FACEATTACK_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
