#include "stdafx.h"
#include "PotatoMonster.h"
#include "Manager.h"
#include "OnionMonster.h"
#include "PotatoBullet.h"

float			g_fSoundPotato = 0.6f;
CPotatoMonster::CPotatoMonster()
{
}


CPotatoMonster::~CPotatoMonster()
{
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, CAbstractFactory<COnionMonster>::Create(400, 400));
}

void CPotatoMonster::Initialize(void)
{
	m_tInfo.fCX = 180.f;
	m_tInfo.fCY = 300.f;

	//�̰� ��� ũ����Ʈ�� �� �̴ϼȶ����� �Ἥ �� ���� �ϴµ� Ȥ�� �𸣴ϱ� �ϴ� �־����!
	// �׸��� m_tGun���� ����Ʈ ������Ʈ�� ������ ����!!! �̴ϼȶ������� �߸� ���� �̻��� ���� ���� �ȴܴ�!
	m_tInfo.fX = 680;
	m_tInfo.fY = 400;

	//ü�°� ���õ�
	m_tStamina.iMaxHp = 20;
	m_tStamina.iAtt = 1;

	m_tTimeBullet = GetTickCount();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FarmMonster/PotatoMonster.bmp", L"PotatoMonster");

	m_pFrameKey = L"PotatoMonster";
	m_ePreState = INTRO;
	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_BACK;
	//m_eRenderGroup = RENDER_OBJ;

	CSoundMgr::Get_Instance()->PlaySound(L"PotatoIntro.wav", CSoundMgr::MONSTER, g_fSoundPotato);

	m_tSoundTime = GetTickCount();
}

int CPotatoMonster::Update(void)
{
	//int iRand = (rand()%3) + 1;
	if (INTRO == m_eCurState && 6 == m_tFrame.iFrameStart)
	{
		m_eCurState = IDLE;
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
	}
	if (0 == m_tStamina.iMaxHp)
	{
		m_bCollsion = true;
		m_bDead = true;
	}
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

	State_Change();
	Move_Frame();
	if (false == m_bDead)
	{
		Potato_Shoot();
		m_bCollsion = false;

	}
	Update_Rect(); //�̰� �ؾ� ȭ�鿡 ��µ�
	return OBJ_NOEVENT;
}

void CPotatoMonster::Late_Update(void)
{
	m_tGun.x = long(m_tInfo.fX -(m_tInfo.fCX * 0.5f));
	m_tGun.y = long(m_tInfo.fY +(m_tInfo.fCY * 0.5f));
}

void CPotatoMonster::Render(HDC hDC)
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
		int(m_tRect.left ),	//	2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5���� ���� ���� X,Y�� ���̸� ����	
		(int)m_tInfo.fCY,
		hMemDC,							// ��Ʈ�� ������ ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8���� ��Ʈ���� ����� ������ǥ
		m_tFrame.iFrameScene * (int)m_tInfo.fCY,
		180,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		300,
		RGB(237, 28, 36));


}

void CPotatoMonster::Release(void)
{
}

void CPotatoMonster::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case IDLE:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case ATTACK:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case DIE:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPotatoMonster::Potato_Shoot(void)
{
	if (m_tTimeBullet + 800 < GetTickCount())
	{
		m_eCurState = ATTACK;
		CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CPotatoBullet>::Create(m_tGun.x, m_tGun.y, BULLET::LEFT));
		CSoundMgr::Get_Instance()->PlaySound(L"PotatoSpit.wav", CSoundMgr::EFFECT, g_fSoundPotato);
		m_tTimeBullet = GetTickCount();
	}
	if (m_tSoundTime + 900 < GetTickCount())
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
		m_tSoundTime = GetTickCount();
	}
}
