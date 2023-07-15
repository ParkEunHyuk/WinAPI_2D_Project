#include "stdafx.h"
#include "BlueSeedBullet.h"
#include "Manager.h"
#include "VineTwo.h"


CBlueSeedBullet::CBlueSeedBullet()
{
}


CBlueSeedBullet::~CBlueSeedBullet()
{
	Release();
	CObjMgr::Get_Instance()->Add_Object(OBJID::UI, CAbstractFactory<CVineTwo>::Create(m_tInfo.fX, (m_tInfo.fY - 60.f)));
}

void CBlueSeedBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/BlueSeedBullet.bmp", L"BlueSeedBullet");

	m_pFrameKey = L"BlueSeedBullet";

	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_OBJ;
}

int CBlueSeedBullet::Update(void)
{
	if (true == m_bDead)
	{
		m_eCurState = DIE;
		m_tInfo.fX = m_tInfo.fX;
		if (false == m_bFrameDieCheck)
		{
			m_tFrame.iFrameStart = 0;
			m_bFrameDieCheck = true;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			return OBJ_DEAD;
		}
	}
	if (false == m_bDead)
	{
		if (BULLET::DOWN == m_eDir)
			m_tInfo.fY += 5.f;
	}
	State_Change();
	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBlueSeedBullet::Late_Update(void)
{
	if (WINCY - 20	<	m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CBlueSeedBullet::Render(HDC hDC)
{
#ifdef _DEBUG
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
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
		30,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		30,
		RGB(255, 242, 0));
}

void CBlueSeedBullet::Release(void)
{
}

void CBlueSeedBullet::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DIE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
