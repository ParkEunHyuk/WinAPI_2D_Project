#include "stdafx.h"
#include "RedMonster.h"
#include "Manager.h"

float g_fSoundRedMonster = 0.8f;

CRedMonster::CRedMonster()
{
}


CRedMonster::~CRedMonster()
{
}

void CRedMonster::Initialize(void)
{
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;

	//�̰� ��� ũ����Ʈ�� �� �̴ϼȶ����� �Ἥ �� ���� �ϴµ� Ȥ�� �𸣴ϱ� �ϴ� �־����!
	// �׸��� m_tGun���� ����Ʈ ������Ʈ�� ������ ����!!! �̴ϼȶ������� �߸� ���� �̻��� ���� ���� �ȴܴ�!
	m_tInfo.fX = 400;
	m_tInfo.fY = 500;

	m_tStamina.iMaxHp = 30;
	m_tStamina.iAtt = 1;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/RedMonster.bmp", L"RedMonster");

	m_pFrameKey = L"RedMonster";
	m_ePreState = IDLE;
	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_tTimeDIE = GetTickCount();

	m_eRenderGroup = RENDER_BACK;
}

int CRedMonster::Update(void)
{
	if (m_bDead == false)
	{
		m_bCollsion = false;
	}
	if (true == m_bDead)
	{
		m_eCurState = DIE;
	
		m_bCollsion = true;
		m_tInfo.fX = m_tInfo.fX;
		if (false == m_bFrameDieCheck)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"MonsterDie.wav", CSoundMgr::MONSTER, g_fSoundRedMonster);
			m_tFrame.iFrameStart = 0;
			m_bFrameDieCheck = true;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			return OBJ_DEAD;
		}
	}
	if (m_tTimeDIE + 4000 < GetTickCount())
	{
		m_bDead = true;
		m_tTimeDIE = GetTickCount();
	}
	State_Change();
	Move_Frame();
	Update_Rect(); //�̰� �ؾ� ȭ�鿡 ��µ�
	return OBJ_NOEVENT;
}

void CRedMonster::Late_Update(void)
{
}

void CRedMonster::Render(HDC hDC)
{
#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
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
		70,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		70,
		RGB(237, 28, 36));
}

void CRedMonster::Release(void)
{
}

void CRedMonster::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case DIE:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
