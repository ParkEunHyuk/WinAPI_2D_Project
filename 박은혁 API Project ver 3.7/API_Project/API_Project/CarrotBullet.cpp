#include "stdafx.h"
#include "CarrotBullet.h"
#include "Manager.h"


float g_fSoundCarrotBullet = 0.8f;

CCarrotBullet::CCarrotBullet()
	:m_iCount(0)
{
}


CCarrotBullet::~CCarrotBullet()
{
	Release();
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER_BULLET);
}

void CCarrotBullet::Initialize(void)
{
	m_tInfo.fCX = 35.f;
	m_tInfo.fCY = 60.f;

	//ü�°� ���õ�
	m_tStamina.iMaxHp = 3;
	m_tStamina.iAtt = 1;


	m_pTarget = nullptr;
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY + 30.f;

	m_fSpeed = 2.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FarmMonster/CarrotBullet.bmp", L"CarrotBullet");

	m_pFrameKey = L"CarrotBullet";

	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_BACK;

}

int CCarrotBullet::Update(void)
{
	if (true == m_bDead)
	{
		m_eCurState = DIE;
		m_tInfo.fX = m_tInfo.fX;
		if (m_iCount == 0)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"CarrotBulletBoom.wav", CSoundMgr::MONSTER_BULLET, g_fSoundCarrotBullet);
			m_tFrame.iFrameStart = 0;
			++m_iCount;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			return OBJ_DEAD;
		}
	}

	if (m_tStamina.iMaxHp == 0)
	{
		m_bDead = true;
		m_bCollsion = true;
	}

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);
	if (false == m_bDead)
	{
		m_bCollsion = false;
		if (nullptr != m_pTarget)
		{
			float	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
			float	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

			float	fDistance = sqrtf(fX * fX + fY * fY);

			float	fRadian = acosf(fX / fDistance);

			m_fAngle = fRadian * 180.f / PI;

			if (m_pTarget->Get_Info().fY > m_tInfo.fY)
				m_fAngle *= -1.f;
		}

		m_tInfo.fX += (m_fSpeed * cosf(m_fAngle * PI / 180.f));
		m_tInfo.fY += m_fSpeed;
		//m_tInfo.fY -= (m_fSpeed * sinf(m_fAngle * PI / 180.f)); // ����� �����θ� ���������ϱ� ������ �̰� �ּ�ó����
	}
	
	State_Change();
	Move_Frame();

	Update_Rect();


	return OBJ_NOEVENT;
}

void CCarrotBullet::Late_Update(void)
{
	if (WINCY - 20	<	m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CCarrotBullet::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,				//	���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),	//	2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5���� ���� ���� X,Y�� ���̸� ����	
		(int)m_tInfo.fCY,
		hMemDC,							// ��Ʈ�� ������ ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8���� ��Ʈ���� ����� ������ǥ
		m_tFrame.iFrameScene * (int)m_tInfo.fCY,
		35,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		60,
		RGB(237, 28, 36));
}

void CCarrotBullet::Release(void)
{
}

void CCarrotBullet::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DIE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
