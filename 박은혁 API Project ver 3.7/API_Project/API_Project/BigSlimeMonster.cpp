#include "stdafx.h"
#include "BigSlimeMonster.h"
#include "Manager.h"
#include "PunchMotion.h"
#include "TombMonster.h"

float g_fSoundBigSlime = 0.8f;

CBigSlimeMonster::CBigSlimeMonster()
	:m_fGravity(9.8f), m_bAttack(false), m_bIntroEnd(false), m_PlayerSpot(false), m_bDeadSwitch(false), m_bNewTypeDeadSwitch(false)
	, m_iDeadCount(0)
{
}


CBigSlimeMonster::~CBigSlimeMonster()
{
}

void CBigSlimeMonster::Initialize(void)
{
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 300.f;

	m_fSpeed = 5.f;

	m_tStamina.iMaxHp = 20;

	m_pTarget = nullptr;
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/SlimeMonster/BigSlimeMonster.bmp", L"BigSlimeMonster");
	m_pFrameKey = L"BigSlimeMonster";

	m_eCurState = INTRO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 14;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();


	m_eRenderGroup = RENDER_BACK;



	m_tTimeHit = GetTickCount();
	m_tAttackCoolTime = GetTickCount();

	//////////////////////////////////����
	m_tTimeSound = GetTickCount();
}

int CBigSlimeMonster::Update(void)
{
	if (m_eCurState == INTRO && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_tInfo.fX = m_tInfo.fX;
		m_tInfo.fY = m_tInfo.fY;
		m_eCurState = LEFT;
		m_bIntroEnd = true;
	}

	/////////////////////////////////���忡 ���� ����
	if (m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"LittleSlimeTransform.wav", CSoundMgr::MONSTER, g_fSoundBigSlime);
	}
	if (m_tTimeSound + 2400 < GetTickCount() && m_iSoundCount == 0)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
		++m_iSoundCount;
	}
	//////////////////////////

	if (m_tStamina.iMaxHp < 0 )
	{
		if (!m_bJump)
		{
			m_bNewTypeDeadSwitch = true;
		}
	}
	if (m_bNewTypeDeadSwitch == true)
	{
		m_eCurState = DIE;
		if (m_bDeadSwitch == false)
		{
			m_tFrame.iFrameStart = 0;
			m_bDeadSwitch = true;
		}
		if (m_tFrame.iFrameStart == 5 && m_iDeadCount == 0)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, CAbstractFactory<CTombMonster>::Create(m_tInfo.fX, m_tInfo.fY - 600));
			++m_iDeadCount;
		}
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			return OBJ_DEAD;
		}
	}

		//return OBJ_DEAD;
	State_Change();
	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBigSlimeMonster::Late_Update(void)
{
	if (m_bNewTypeDeadSwitch == false)
	{
		if (m_bIntroEnd == true)
		{
			if (40 >= m_tRect.left)
			{
				m_fSpeed *= -1.f;
				m_eCurState = RIGHT;
				m_eTempState = RIGHT;
				++m_iJumpCount;
			}
			if (WINCX-40 <= m_tRect.right)
			{
				m_fSpeed *= -1.f;
				m_eCurState = LEFT;
				m_eTempState = LEFT;
				++m_iJumpCount;
			}
			HIT_CoolTime();
			Attacking();
			LookPlayer();
			if (false == m_bAttack)
			{
				if (m_eTempState == LEFT)
				{
					m_eCurState = LEFT;
				}
				else if (m_eTempState == RIGHT)
				{
					m_eCurState = RIGHT;
				}
				Jumping();
			}
		}
	}
}

void CBigSlimeMonster::Render(HDC hDC)
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
		300,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		300,
		RGB(237, 28, 36));
}

void CBigSlimeMonster::Release(void)
{
}

void CBigSlimeMonster::Jumping(void)
{
	if (!m_bJump)
	{
		m_fJumpY = m_tInfo.fY;
		m_bJump = true;
	}
	m_tInfo.fY += m_fGravity;
	m_tInfo.fX -= m_fSpeed;

	float		fY = 0.f;

	if (true == m_bJump)
	{
		//������ ������ ��� �׷���Ƽ��ŭ ���Ѵ�.
		m_fJumpY -= m_fGravity;
		m_tInfo.fY -= m_fGravity;
		//	�÷��̾��� ���� �غ� Y��ǥ
		float	fCurrentBottom = m_tInfo.fY + m_tInfo.fCY * 0.5f;

		//	������ ����
		//	(��(�ӵ�) * �ð�) - ( 1/2(0.5) * �߷°��ӵ�(9.8) * �ð� * �ð�)
		//	�÷��̾��� Y ��ǥ = (���� ��ġ) - (������ ����)
		//	���� ���� ���� �÷��̾��� �غ� Y��ǥ
		float	fNextBottom = m_fJumpY - ((m_fJumpPower * m_fTime) - (0.5f * 9.8f * m_fTime * m_fTime));

		bool	bLineCol = CLineMgr::Get_Instance()->Collision_LineEx(m_tInfo.fX, fCurrentBottom, fNextBottom, &fNextBottom);

		m_tInfo.fY = fNextBottom - (m_tInfo.fCY * 0.5f);

		//	�ð��� ������ 0.2�� �����ϰ� ����
		m_fTime += 0.2f;

		if (bLineCol)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"BigSlimeJump.wav", CSoundMgr::MONSTER, g_fSoundBigSlime);
			m_bJump = false;
			m_fTime = 0.f;

		}
	}
	else
	{
		bool	bLineCol = CLineMgr::Get_Instance()->Collision_LineEx(m_tInfo.fX, m_tRect.bottom - 10.f, m_tRect.bottom + 10.f, &fY);
		if (bLineCol)
		{
			m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
		}
	}
}

void CBigSlimeMonster::Attacking(void)
{
	if (m_iJumpCount > 1)
	{
		if (50 < m_tInfo.fX && WINCX - 50 > m_tInfo.fX)
		{
			if (m_pTarget->Get_Info().fX < m_tInfo.fX && !m_bJump) // �÷��̾ ���ʿ� �ְ� ���ʹ� �����ʿ� ������ ������ ���� �ʴ� ����...
			{
				if (m_fDistance < 250)
				{
					m_bAttack = true;
					m_eCurState = ATTACK;
					CObjMgr::Get_Instance()->Add_Object(OBJID::NOT_COLLISION_MONSTER, CAbstractFactory<CPunchMotion>::Create(m_tInfo.fX, m_tInfo.fY ));
					m_iJumpCount = 0;
					m_tAttackCoolTime = GetTickCount();

				}
				//���Ͱ� ������ ���鼭 ����

			}
			else if (m_pTarget->Get_Info().fX > m_tInfo.fX && !m_bJump)
			{
				if (m_fDistance < 250)
				{
					m_bAttack = true;
					m_eCurState = ATTACK;
					CObjMgr::Get_Instance()->Add_Object(OBJID::NOT_COLLISION_MONSTER, CAbstractFactory<CPunchMotion>::Create(m_tInfo.fX, m_tInfo.fY ));
					m_iJumpCount = 0;
					m_tAttackCoolTime = GetTickCount();
				}
				//���Ͱ� �������� ���鼭 ����
			}
		}
	}
	if (m_tAttackCoolTime + 2280 < GetTickCount())
	{
		m_bAttack = false;
	}
}

void CBigSlimeMonster::HIT_CoolTime(void)
{
	if (m_tTimeHit + 100 < GetTickCount())
	{
		m_bCollsion = false;

		m_tTimeHit = GetTickCount();
	}
}

void CBigSlimeMonster::LookPlayer(void)
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

void CBigSlimeMonster::State_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 14;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case LEFT:
			m_tFrame.iFrameStart = 0; //�������� ���ۺκ� �迭ó�� 0��° ����
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case DIE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 4;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
