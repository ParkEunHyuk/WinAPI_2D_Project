#include "stdafx.h"
#include "Obj.h"



CObj::CObj()
	:m_fSpeed(0.f),m_fAngle(0.f), m_bDead(false)
	,m_fDistance(0.f),m_iDrawID(0),m_pFrameKey(nullptr), m_bCollsion(false)
	,m_bFrameDieCheck(false)
{
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));
}


CObj::~CObj()
{
}

void CObj::Set_Pos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}

void CObj::Set_PosX(float _fX)
{
	m_tInfo.fX += _fX;
}

void CObj::Set_PosY(float _fY)
{
	m_tInfo.fY += _fY;
}

void CObj::Set_Target(CObj * _pTarget)
{
	m_pTarget = _pTarget;
}

void CObj::Set_Direction(BULLET::DIR _eDir)
{
	m_eDir = _eDir;
}

void CObj::Update_Rect(void)
{
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Move_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;
		}
	}
}

void CObj::Set_Dead(void)
{
	m_bDead = true;
}

void CObj::Set_Angle(float _fAngle)
{
	m_fAngle = _fAngle;
}

void CObj::Set_FrameKey(TCHAR * pFrameKey)
{
	m_pFrameKey = pFrameKey;
}

void CObj::Set_DrawID(int _iDrawID)
{
	m_iDrawID = _iDrawID;
}

void CObj::Set_Hp(int _Damage)
{
		m_tStamina.iMaxHp -= _Damage;
}

void CObj::Set_Collsion(bool _Collsion)
{
	m_bCollsion = _Collsion;
}

void CObj::Set_InfoTest(LINEINFO _LineInfo)
{
	m_tInfo.fX =_LineInfo.tLeftPos.fX + abs((_LineInfo.tLeftPos.fX - _LineInfo.tRightPos.fX)*0.5f);
	m_tInfo.fY = _LineInfo.tLeftPos.fY + abs((_LineInfo.tLeftPos.fY - _LineInfo.tRightPos.fY)* 0.5f);

	
	m_tInfo.fCX = abs(_LineInfo.tLeftPos.fX - _LineInfo.tRightPos.fX);
	m_tInfo.fCY = abs(_LineInfo.tLeftPos.fY - _LineInfo.tRightPos.fY);
}
