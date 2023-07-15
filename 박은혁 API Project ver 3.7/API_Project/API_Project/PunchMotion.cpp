#include "stdafx.h"
#include "PunchMotion.h"
#include "Manager.h"
#include "Punching.h"

float g_fSoundBigSlimePunching = 0.8f;

CPunchMotion::CPunchMotion()
{
}


CPunchMotion::~CPunchMotion()
{
}
void CPunchMotion::Initialize(void)
{
	m_tInfo.fCX = 600.f;
	m_tInfo.fCY = 300.f;

	m_pTarget = nullptr;
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/SlimeMonster/PunchMotion.bmp", L"PunchMotion");
	m_pFrameKey = L"PunchMotion";


	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 12;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_BACK;

	m_tTimeSound = GetTickCount();
}

int CPunchMotion::Update(void)
{
	LookPlayer();
	State_Change();
	Update_Rect();
	Move_Frame();
	Attacking();
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		return OBJ_DEAD;
	}
	return OBJ_NOEVENT;
}

void CPunchMotion::Late_Update(void)
{
}

void CPunchMotion::Render(HDC hDC)
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
		600,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		300.f,
		RGB(237, 28, 36));
}

void CPunchMotion::Release(void)
{
}

void CPunchMotion::Attacking(void)
{
	if (50 < m_tInfo.fX && WINCX - 50 > m_tInfo.fX)
	{
		if (m_pTarget->Get_Info().fX < m_tInfo.fX&& m_bMontion == false) // �÷��̾ ���ʿ� �ְ� ���ʹ� �����ʿ� ������ ������ ���� �ʴ� ����...
		{
			m_bMontion = true;
			if (m_fDistance < 250)
			{

				m_eCurState = PUNCH_LEFT;
				if (m_eCurState == PUNCH_LEFT)
				{
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"BigSlimePunch.wav", CSoundMgr::EFFECT, g_fSoundBigSlimePunching);
					m_tFrame.iFrameStart = 0;
				}
				//if (m_tTimeSound + 2400 < GetTickCount())
				//{
				//	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
				//}
			}
			//���Ͱ� ������ ���鼭 ����

		}
		else if (m_pTarget->Get_Info().fX > m_tInfo.fX && m_bMontion == false)
		{
			m_bMontion = true;
			if (m_fDistance < 250)
			{
				m_eCurState = PUNCH_RIGHT;
				if (m_eCurState == PUNCH_RIGHT)
				{
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"BigSlimePunch.wav", CSoundMgr::EFFECT, g_fSoundBigSlimePunching);
					m_tFrame.iFrameStart = 0;
				}
			}
			//���Ͱ� �������� ���鼭 ����
		}
	}

	if (m_eCurState == PUNCH_LEFT && m_tFrame.iFrameStart == 5 && m_iMotionCount == 0)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CPunching>::Create((m_tInfo.fX - 180), m_tInfo.fY - 20));
		++m_iMotionCount;
	}
	else if (m_eCurState == PUNCH_RIGHT && m_tFrame.iFrameStart == 5 && m_iMotionCount == 0)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CPunching>::Create((m_tInfo.fX + 180), m_tInfo.fY - 20));
		++m_iMotionCount;
	}
}

void CPunchMotion::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case PUNCH_LEFT:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case PUNCH_RIGHT:
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

void CPunchMotion::LookPlayer(void)
{
	// CObj* m_pTarget = �÷��̾�� ������ �Ÿ��� ���
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);

	if (nullptr != m_pTarget)
	{
		// fX = player�� x - monster�� ����x
		float	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		// fY = player�� y - monster�� ����y
		float	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

		// player�� monster ������ �Ÿ� 
		m_fDistance = sqrtf(fX * fX + fY * fY);
	}
}
