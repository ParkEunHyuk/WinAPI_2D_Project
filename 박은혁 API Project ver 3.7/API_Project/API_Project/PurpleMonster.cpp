#include "stdafx.h"
#include "PurpleMonster.h"
#include "Manager.h"
#include "PurpleBullet.h"

float				g_fSoundPurpleMonster = 0.8f;

CPurpleMonster::CPurpleMonster()
	:m_iBulletCount(0), m_bIntroEnd(false), m_bPatternSwitch(false)
{
}


CPurpleMonster::~CPurpleMonster()
{
}

void CPurpleMonster::Initialize(void)
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_tStamina.iMaxHp = 5;
	m_tStamina.iAtt = 1;

	m_fGun_Distance = 1.f;
	m_fSpeed = 2.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/PurpleMonster.bmp", L"PurpleMonster");

	m_pFrameKey = L"PurpleMonster";
	m_ePreState = INTRO;
	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_tTimeDIE = GetTickCount();
	m_tTimeBullet = GetTickCount();

	m_eRenderGroup = RENDER_OBJ;
}

int CPurpleMonster::Update(void)
{
	/////////////////////////////////�⺻������ �ʿ��� ���ǵ� ��
	if (m_bIntroEnd == true)
	{
		m_tInfo.fX += m_fSpeed;
		m_fAngle += m_fSpeed;
		LookPlayer();
	}
	/////////////////////////////////�⺻������ �ʿ��� ���ǵ� ��
	/////////////////////////////////////////��Ʈ��
	if (m_eCurState == INTRO && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_tInfo.fX = m_tInfo.fX;
		m_tInfo.fY = m_tInfo.fY;
		m_eCurState = IDLE;
		m_bIntroEnd = true;
	}
	////////////////////////////////////////��Ʈ��
	///////////////////////////////////////////// �״� ����
	if (false == m_bDead)
	{
		m_bCollsion = false;
	}
	if (true == m_bDead)
	{
		m_bCollsion = true;
		m_eCurState = DIE;
		m_tInfo.fX = m_tInfo.fX;
		m_tInfo.fY = m_tInfo.fY;
		if (m_iCount == 0)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"MonsterDie.wav", CSoundMgr::MONSTER, g_fSoundPurpleMonster);
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
	}
	///////////////////////////////////////////// �״� ����


	if (false == m_bDead && m_bIntroEnd == true)
	{
		MonsterPattern();
	}
	State_Change();
	Move_Frame();

	Update_Rect();
	return OBJ_NOEVENT;
}

void CPurpleMonster::Late_Update(void)
{
	m_tGun.x = long(m_tInfo.fX - (cosf(m_fAngle * PI / 180.f) * m_fGun_Distance));
	m_tGun.y = long(m_tInfo.fY + (sinf(m_fAngle * PI / 180.f) * m_fGun_Distance));

	if (m_bIntroEnd == true)
	{
		if (m_tInfo.fY > 40)
		{
			m_tInfo.fY -= 2;
		}
		if ((40 >= m_tRect.left) || (WINCX - 200 <= m_tRect.right))
			m_fSpeed *= -1.f;
	}
}

void CPurpleMonster::Render(HDC hDC)
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
		100,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		100,
		RGB(237, 28, 36));

}

void CPurpleMonster::Release(void)
{
}

void CPurpleMonster::LookPlayer()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);

	if (nullptr != m_pTarget)
	{
		// fX = player�� x - monster�� ����x
		float	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		// fY = player�� y - monster�� ����y
		float	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

		// player�� monster ������ �Ÿ� 
		m_fDistance = sqrtf(fX * fX + fY * fY);
		// �� ���� ���� ��
		float	fRadian = acosf(fX / m_fDistance);
		// Radian to Degree
		m_fAngle = fRadian * 180.f / PI;
		// �÷��̾��� ���̰� ���ͺ��� ���� ��� ��ġ �ٲٱ�
		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fAngle *= -1.f;
	}
}

void CPurpleMonster::MonsterPattern(void)
{
	if (m_bPatternSwitch == true) 
	{
			BulletFire();
	}
	if (m_tTimePattern + 3000 < GetTickCount() && m_bPatternSwitch == false)
	{
		m_bPatternSwitch = true;
	}
}

void CPurpleMonster::BulletFire(void)
{
	m_eCurState = ATTACK;

	if (m_tTimeBullet + 100 < GetTickCount())
	{

		CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_BULLET, CAbstractFactory<CPurpleBullet>::Create(m_tGun.x, m_tGun.y, m_fAngle));

		++m_iBulletCount;

		m_tTimeBullet = GetTickCount();

		if (m_iBulletCount > 5)
		{
			m_eCurState = IDLE;
			m_bPatternSwitch = false;
			m_tTimePattern = GetTickCount();
			m_iBulletCount = 0;
		}
	}
}

void CPurpleMonster::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case IDLE:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case ATTACK:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case DIE:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
