#include "stdafx.h"
#include "Player.h"
#include "Manager.h"
#include "BasicBullet.h"

float g_fSoundPlayer = 1.0f;

CPlayer::CPlayer()
	:m_bOff_Set(false), m_fGravity(9.8f), m_bDownSwitch(false), m_bPlayerHitCheck(false)
	, m_iSoundCount(0)
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 400.f;

	//이미지는 100, 100으로 하자!
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_tStamina.iMaxHp = 5;
	m_tStamina.iAtt = 1;
	m_PullHp = m_tStamina.iMaxHp;

	m_fSpeed = 5.f;

	m_iOffSetX = WINCX >> 1;
	m_iOffSetY = WINCY >> 1;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RIGHT.bmp", L"Player_RIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Left_DOWN.bmp", L"Player_Left_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Right_DOWN.bmp", L"Player_Right_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_HIT.bmp", L"Player_HIT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/HPbar.bmp", L"HPbar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/HP.bmp", L"HP");

	m_pFrameKey = L"Player_RIGHT";

	m_ePreState = IDLE;
	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	
	m_eRenderGroup = RENDER_OBJ;

	m_tTimePhoenix = GetTickCount();

	m_tSoundTime = GetTickCount();

}

int CPlayer::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	Player_Hit();

	if (false == m_bPlayerHitCheck)
	{
		m_tInfo.fY += m_fGravity;
		Jumping();
	}
	State_Change();
	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (false == m_bPlayerHitCheck)
	{
		Key_Input();
	}
	OffSet();
}

void CPlayer::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	//소숫점은 %f 정수는 %d
	TCHAR	szTemp[32] = L"";
	swprintf_s(szTemp, L"PlayerHp : %d", m_tStamina.iMaxHp);	// visual c++라이브러리에서 제공(모든 서식 문자를 지원)
	TextOut(hDC, 150, 50, szTemp, lstrlen(szTemp));
#endif // !_DEBUG

	if (50 == m_tInfo.fCY)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	//	2, 3인자 복사 받을 위치의 좌표를 전달
			int(m_tRect.top),
			(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
			(int)m_tInfo.fCY,
			hMemDC,							// 비트맵 정보를 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8인자 비트맵을 출력할 시작좌표
			m_tFrame.iFrameScene * (int)m_tInfo.fCY,
			100,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
			50,
			RGB(237, 28, 36));			// 제거하고자 하는 색상
	}
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	//	2, 3인자 복사 받을 위치의 좌표를 전달
			int(m_tRect.top),
			(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
			(int)m_tInfo.fCY,
			hMemDC,							// 비트맵 정보를 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8인자 비트맵을 출력할 시작좌표
			m_tFrame.iFrameScene * (int)m_tInfo.fCY,
			100,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
			100,
			RGB(237, 28, 36));			// 제거하고자 하는 색상
	}

	HDC	hMemHpDC = CBmpMgr::Get_Instance()->Find_Image(L"HP");

	GdiTransparentBlt(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		50,	//	2, 3인자 복사 받을 위치의 좌표를 전달
		550,
		200 * m_tStamina.iMaxHp / m_PullHp,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		18,
		hMemHpDC,							// 비트맵 정보를 가지고 있는 DC
		0,								// 7,8인자 비트맵을 출력할 시작좌표
		0,
		200,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		18,
		RGB(255, 255, 255));			// 제거하고자 하는 색상

	HDC	hMemHPbarDC = CBmpMgr::Get_Instance()->Find_Image(L"HPbar");

	GdiTransparentBlt(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		50,	//	2, 3인자 복사 받을 위치의 좌표를 전달
		550,
		200,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		18,
		hMemHPbarDC,							// 비트맵 정보를 가지고 있는 DC
		0,								// 7,8인자 비트맵을 출력할 시작좌표
		0,
		200,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		18,
		RGB(255, 255, 255));			// 제거하고자 하는 색상

}

void CPlayer::Release(void)
{
}

void CPlayer::Set_OffSet(bool OffSet_Switch)
{
	m_bOff_Set = OffSet_Switch;
}

void CPlayer::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		if (m_pFrameKey == L"Player_LEFT")
		{
			m_pFrameKey = L"Player_Left_DOWN";
			m_eCurState = PLAYER_LEFT_DOWN;
			m_tInfo.fCY = 50.f;
			m_tInfo.fCX = 100.f;
		}
		if (m_pFrameKey == L"Player_RIGHT")
		{
			m_pFrameKey = L"Player_Right_DOWN";
			m_eCurState = PLAYER_RIGHT_DOWN;
			m_tInfo.fCY = 50.f;
			m_tInfo.fCX = 100.f;
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			m_pFrameKey = L"Player_RIGHT";
			m_tInfo.fCY = 100.f;
			m_tInfo.fCX = 100.f;
			m_eCurState = JUMP;
			if (!m_bJump)
			{
				m_fJumpY = m_tInfo.fY;
				m_bJump = true;
			}
		}
	}else if(m_pFrameKey == L"Player_Left_DOWN")
	{
		m_pFrameKey = L"Player_LEFT";
		m_tInfo.fCY = 100.f;
		m_tInfo.fCX = 100.f;
	}else if(m_pFrameKey == L"Player_Right_DOWN")
	{
		m_pFrameKey = L"Player_RIGHT";
		m_tInfo.fCY = 100.f;
		m_tInfo.fCX = 100.f;
	}else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		//CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);
		m_pFrameKey = L"Player_LEFT";
		if (m_eCurState == IDLE)
		{
			m_eCurState = WALK_LEFT;
		}
		if (true == m_bJump)
		{
			m_eCurState = JUMP;
		}
		else
		{
			if (m_tFrame.iFrameStart == (m_tFrame.iFrameEnd - 1))
			{
				m_eCurState = WALK_LEFT;
			}
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		//CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
		m_pFrameKey = L"Player_RIGHT";
		if (m_eCurState == IDLE)
		{
			m_eCurState = WALK_RIGHT;
		}
		if (true == m_bJump)
		{
			m_eCurState = JUMP;
		}
		else
		{
			if (m_tFrame.iFrameStart == (m_tFrame.iFrameEnd - 1))
			{
				m_eCurState = WALK_RIGHT;
			}
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		if (true == m_bJump)
		{
			m_eCurState = JUMP;
		}
		else
		{
			if (UP_SHOOT == m_eCurState)
			{
				if (m_tFrame.iFrameStart == (m_tFrame.iFrameEnd - 1))
				{
					m_eCurState = UP;
				}
			}
			else
			{
				m_eCurState = UP;
			}
		}

	}
	else     ////////////////////////////////여기서부턴 기본적으로 IDLE를 유지하겠단 뜻
	{
		if (!m_bJump)
		{
			if (STOP_SHOOT == m_eCurState)
			{
				if (m_tFrame.iFrameStart == (m_tFrame.iFrameEnd - 1))
				{
					m_eCurState = IDLE;
				}
			}
			else
			{
				m_eCurState = IDLE;
			}
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_eCurState = JUMP;
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
		CSoundMgr::Get_Instance()->PlaySound(L"PlayerJump.wav", CSoundMgr::PLAYER, g_fSoundPlayer);
		if (!m_bJump)
		{
			m_fJumpY = m_tInfo.fY;
			m_bJump = true;
		}
	}

	//////////////////////////////////////////////////////////////////// 총알 관련된 것들
	if (CKeyMgr::Get_Instance()->Key_Down('A'))
	{
		float fScrollX = (float)CScrollMgr::Get_Instance()->Get_ScrollX(); //이건 별로 안 중요한듯?

		if (JUMP == m_eCurState && CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tGun.x = m_tInfo.fX;
			m_tGun.y = m_tInfo.fY + (m_tInfo.fCY * 0.5f);
			CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER_BULLET, CAbstractFactory<CBasicBullet>::Create(m_tGun.x, m_tGun.y, BULLET::DOWN));
		}
		else if (JUMP == m_eCurState && CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tGun.x = m_tInfo.fX;
			m_tGun.y = m_tInfo.fY - (m_tInfo.fCY * 0.5f);
			CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER_BULLET, CAbstractFactory<CBasicBullet>::Create(m_tGun.x, m_tGun.y, BULLET::UP));
		}
		else if (UP == m_eCurState && L"Player_RIGHT" == m_pFrameKey) ////////오른쪽 위를 바라보고 있다!
		{
			m_eCurState = UP_SHOOT;
			m_tGun.x = m_tInfo.fX + 40.f ;
			m_tGun.y = m_tInfo.fY - (m_tInfo.fCY * 0.5f);
			CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER_BULLET, CAbstractFactory<CBasicBullet>::Create(m_tGun.x, m_tGun.y, BULLET::UP));
		}
		else if (UP == m_eCurState && L"Player_LEFT" == m_pFrameKey) ////////왼쪽 위를 바라보고 있다!
		{
			m_eCurState = UP_SHOOT;
			m_tGun.x = m_tInfo.fX - 40.f ;
			m_tGun.y = m_tInfo.fY - (m_tInfo.fCY * 0.5f) ;
			CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER_BULLET, CAbstractFactory<CBasicBullet>::Create(m_tGun.x, m_tGun.y, BULLET::UP));
		}
		else if (UP != m_eCurState && UP_SHOOT != m_eCurState && L"Player_RIGHT" == m_pFrameKey)   /////오른쪽을 바라보고 있다!
		{
			if (!m_bJump)
			{
				if (true == CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
				{
					m_eCurState = RIGHT_RUN_SHOOT;
				}
				else
				{
					m_eCurState = STOP_SHOOT;
				}
			}
			m_tGun.x = m_tInfo.fX + (m_tInfo.fCX * 0.5f);
			m_tGun.y = m_tInfo.fY;
			CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER_BULLET, CAbstractFactory<CBasicBullet>::Create(m_tGun.x, m_tGun.y, BULLET::RIGHT));
		}
		else if (UP != m_eCurState && UP_SHOOT != m_eCurState && L"Player_LEFT" == m_pFrameKey) /////왼쪽을 바라보고 있다!
		{
			if (!m_bJump)
			{
				if (true == CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
				{
					m_eCurState = RIGHT_RUN_SHOOT;
				}
				else
				{
					m_eCurState = STOP_SHOOT;
				}
			}
			m_tGun.x = m_tInfo.fX -(m_tInfo.fCX * 0.5f);
			m_tGun.y = m_tInfo.fY;
			CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER_BULLET, CAbstractFactory<CBasicBullet>::Create(m_tGun.x, m_tGun.y, BULLET::LEFT));
		}
		else if (m_pFrameKey == L"Player_Left_DOWN" && CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_eCurState = LEFT_DOWN_SHOOT;
			m_tGun.x = m_tInfo.fX - (m_tInfo.fCX * 0.5f);
			m_tGun.y = m_tInfo.fY;;
			CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER_BULLET, CAbstractFactory<CBasicBullet>::Create(m_tGun.x, m_tGun.y, BULLET::LEFT));
		}
		else if (m_pFrameKey == L"Player_Right_DOWN" && CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_eCurState = RIGHT_DOWN_SHOOT;
			m_tGun.x = m_tInfo.fX + (m_tInfo.fCX * 0.5f);
			m_tGun.y = m_tInfo.fY;
			CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER_BULLET, CAbstractFactory<CBasicBullet>::Create(m_tGun.x, m_tGun.y, BULLET::RIGHT));
		}
	}

	/////////////////////////////////////////////////////////
	if (CKeyMgr::Get_Instance()->Key_Down('T'))
	{
		m_tStamina.iMaxHp += 5;
	}
}

void CPlayer::Jumping(void)
{
	float		fY = 0.f;

	if (true == m_bJump)
	{
		//점프를 눌렀을 경우 그래비티만큼 더한다.
		m_fJumpY -= m_fGravity;
		m_tInfo.fY -= m_fGravity;
		//	플레이어의 현재 밑변 Y좌표
		float	fCurrentBottom = m_tInfo.fY + m_tInfo.fCY * 0.5f;

		//	포물선 공식
		//	(힘(속도) * 시간) - ( 1/2(0.5) * 중력가속도(9.8) * 시간 * 시간)
		//	플레이어의 Y 좌표 = (원래 위치) - (포물선 공식)
		//	점프 했을 때의 플레이어의 밑변 Y좌표
		float	fNextBottom = m_fJumpY - ((m_fJumpPower * m_fTime) - (0.5f * 9.8f * m_fTime * m_fTime));

		bool	bLineCol = CLineMgr::Get_Instance()->Collision_LineEx(m_tInfo.fX, fCurrentBottom, fNextBottom, &fNextBottom);

		m_tInfo.fY = fNextBottom - (m_tInfo.fCY * 0.5f);

		//	시간은 강제로 0.2씩 증가하게 만듬
		m_fTime += 0.2f;

		if (bLineCol)
		{
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

void CPlayer::OffSet(void)
{
	//if (false == m_bOff_Set)
	//{
	//	//if (m_iOffSetX != m_tInfo.fX)
	//	//{
	//	//	if (m_iOffSetX < m_tInfo.fX)
	//	//	{
	//	//		m_iOffSetX += (int)m_fSpeed;
	//	//	}
	//	//	if (m_iOffSetX > m_tInfo.fX)
	//	//	{
	//	//		m_iOffSetX -= (int)m_fSpeed;
	//	//	}
	//	//}

	//	//if (m_iOffSetY != m_tInfo.fY)
	//	//{
	//	//	if (m_iOffSetY < m_tInfo.fY)
	//	//	{
	//	//		m_iOffSetY += (int)m_fSpeed;
	//	//	}
	//	//	if (m_iOffSetY > m_tInfo.fY)
	//	//	{
	//	//		m_iOffSetY -= (int)m_fSpeed;
	//	//	}
	//	//}
	//}

	if (true == m_bOff_Set)
	{
		if (0 > m_tInfo.fX)
		{
			m_tInfo.fX = 0.f;
		}
		if (WINCX < m_tInfo.fX)
		{
			m_tInfo.fX = WINCX;
		}
		if (WINCY < m_tInfo.fY)
		{
			m_tInfo.fY = WINCY;
		}
	}
}

void CPlayer::State_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0; //프레임의 시작부분 배열처럼 0번째 시작
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case STOP_SHOOT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case WALK_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case WALK_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		case RIGHT_RUN_SHOOT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case LEFT_RUN_SHOOT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 4;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case UP_SHOOT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 5;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 8;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case PLAYER_LEFT_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case LEFT_DOWN_SHOOT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case PLAYER_RIGHT_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case RIGHT_DOWN_SHOOT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case PLAYER_HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CPlayer::Player_Hit(void)
{
	if (0 < m_tStamina.iMaxHp )
	{
		if (true == m_bCollsion)
		{
			m_eCurState = PLAYER_HIT;
			m_pFrameKey = L"Player_HIT";
			m_tInfo.fCX = 100.f;
			m_tInfo.fCY = 100.f;
			if (false == m_bPlayerHitCheck)
			{
				m_tFrame.iFrameStart = 0;
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
				CSoundMgr::Get_Instance()->PlaySound(L"PlayerHit.wav", CSoundMgr::PLAYER, g_fSoundPlayer);
				m_bPlayerHitCheck = true;
			}
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_bPlayerHitCheck = false;
				m_bCollsion = false;
			}
		}
	}
	else
	{
		m_bCollsion = false;
		m_tStamina.iMaxHp = 0;
	}
}