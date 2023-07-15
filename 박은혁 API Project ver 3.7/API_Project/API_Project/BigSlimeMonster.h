#pragma once

#ifndef __BIGSLIMEMONSTER_H_
#define __BIGSLIMEMONSTER_H_
#include "Obj.h"
class CBigSlimeMonster : public CObj
{
public:
	enum STATE { INTRO, LEFT, RIGHT, DIE, ATTACK};
public:
	CBigSlimeMonster();
	~CBigSlimeMonster();

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

	DWORD					m_tAttackCoolTime;
	////////////////////////////////////////

	DWORD					m_tTimeHit;

	////////////////////////////////////////프레임 패턴에 대한 변수
	bool					m_bIntroEnd;

	////////////////////////////////////////데드 스위치
	bool					m_bDeadSwitch;

	// 지금 보스몬스터는 콜리전 총알로 되어 있다. 즉 플레이어랑 충돌되면 사망처리가 된다. 그러니 Obj의 m_tDead를 사용하지말고 새로 변수를 만들어주자!
	bool					m_bNewTypeDeadSwitch;


	////////////////////////////벽충돌 버그 해결
	bool					m_bLEFT;
	bool					m_bRIGHT;

	//
	int						m_iDeadCount;

	////////////////////////////////////////// 사운드
	int						m_iSoundCount;
	DWORD					m_tTimeSound;
};

#endif