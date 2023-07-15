#pragma once

#ifndef __TOMBMONSTER_H_
#define __TOMBMONSTER_H_
#include "Obj.h"

class CTombMonster : public CObj
{
public:
	enum STATE { INTRO, LEFT, RIGHT, ATTACK,DIE };
public:
	CTombMonster();
	~CTombMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Jumping(void);      //점프에 관한 함수

	void		Attacking(void);   // 벽에 튕기고 난 이후 때리기위한 준비과정

	void		HIT_CoolTime(void);  // 플레이어가 슬라임 몸체랑 충돌했을 경우 히트 쿨타임

	void		LookPlayer(void); //플레이어의 거리를 알기 위해 존재

private:
	void		State_Change(void);

	STATE					m_ePreState;
	STATE					m_eCurState;
	STATE					m_eTempState;


	/////////////////점프에 관한 변수들
	bool					m_bJump;
	float					m_fJumpY;
	float					m_fJumpPower;
	float					m_fTime;
	float					m_fGravity;
	//////////////////////////////////////

	///////////////////////공격에 관한 변수들
	int						m_iJumpCount;
	bool					m_bAttack;
	bool					m_PlayerSpot;

	int						m_iDownAttackCount;

	DWORD					m_tAttackCoolTime;
	////////////////////////////////////////

	DWORD					m_tTimeHit;

	////////////////////////////////////////프레임 패턴에 대한 변수
	bool					m_bIntroEnd;
	bool					m_bIntroSwitch;
	bool					m_bDIESwitch;
	bool					m_bFrameCount;

	////////////////////////////////////////// 사운드
	int						m_iSoundCount;
	DWORD					m_tTimeSound;

};

#endif
