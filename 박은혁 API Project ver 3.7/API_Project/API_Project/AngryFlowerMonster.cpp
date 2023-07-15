#include "stdafx.h"
#include "AngryFlowerMonster.h"
#include "Manager.h"
#include "FlowerBullet.h"
#include "VineWhip.h"
#include "Bravo.h"

float g_fSoundAngryFlower = 0.9f;

CAngryFlowerMonster::CAngryFlowerMonster()
	:m_bIntroEnd(false)
{
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_COLLISION_BULLET, CAbstractFactory<CVineWhip>::Create(370, 525));
}


CAngryFlowerMonster::~CAngryFlowerMonster()
{
	//�̰� ���� ���� ���ִ� ��
	CObjMgr::Get_Instance()->Delete_ID(OBJID::MONSTER_COLLISION_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJID::MONSTER_BULLET);
	CObjMgr::Get_Instance()->Delete_Render(RENDER_BACK);
	CObjMgr::Get_Instance()->Delete_Render(RENDER_OBJ);
	CObjMgr::Get_Instance()->Add_Object(OBJID::UI, CAbstractFactory<CBravo>::Create(400, 300));
}

void CAngryFlowerMonster::Initialize(void)
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 350.f;

	//ü�°� ���õ�
	m_tStamina.iMaxHp = 20;
	m_tStamina.iAtt = 1;

	m_fSpeed = 2.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/AngryFlowerMonster.bmp", L"AngryFlowerMonster");

	m_pFrameKey = L"AngryFlowerMonster";
	m_ePreState = INTRO;
	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	iCount = 0;

	m_eRenderGroup = RENDER_BACK;
}

int CAngryFlowerMonster::Update(void)
{
	if (INTRO == m_eCurState && 4 == m_tFrame.iFrameStart)
	{
		m_eCurState = ATTACK;
		m_bIntroEnd = true;
	}

	if (0 == m_tStamina.iMaxHp)
	{
		m_bCollsion = true;
		m_bDead = true;
	}

	if (true == m_bDead)
	{
		m_eCurState = DIE;
		CSoundMgr::Get_Instance()->PlaySound(L"AngryFlowerDie.wav", CSoundMgr::MONSTER, g_fSoundAngryFlower);
		m_tInfo.fX = m_tInfo.fX;
		if (false == m_bFrameDieCheck)
		{
			m_tFrame.iFrameStart = 0;
			m_bFrameDieCheck = true;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			CObjMgr::Get_Instance()->Set_FlowerClear(true);
			return OBJ_DEAD;
		}
	}

	if (false == m_bDead && m_bIntroEnd == true)
	{
		FlowerBullet();
		m_bCollsion = false;
	}
	State_Change();
	Move_Frame();
	Update_Rect(); //�̰� �ؾ� ȭ�鿡 ��µ�

	return OBJ_NOEVENT;
}

void CAngryFlowerMonster::Late_Update(void)
{
}

void CAngryFlowerMonster::Render(HDC hDC)
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
		200,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		350,
		RGB(237, 28, 36));

}

void CAngryFlowerMonster::Release(void)
{
}

void CAngryFlowerMonster::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case ATTACK:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case DIE:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CAngryFlowerMonster::FlowerBullet(void)
{
	//���� �� ������ ��ŸƮ�� X���~ �ҷ� �߻�
	if (m_tFrame.iFrameStart == 7 && iCount == 0)
	{
		m_tGun.x = m_tInfo.fX - 50.f;
		m_tGun.y = m_tInfo.fY - 60.f;

		CSoundMgr::Get_Instance()->PlaySound(L"FlowerBullet.wav", CSoundMgr::MONSTER_BULLET, g_fSoundAngryFlower);
		CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CFlowerBullet>::Create((m_tGun.x), (m_tGun.y), BULLET::LEFT));
		++iCount;
	}

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		iCount = 0;
	}
}