#pragma once

#ifndef __PLAYER_H_
#define __PLAYER_H_
#include "Obj.h"

class CPlayer :public CObj
{
public:
	enum STATE { IDLE, WALK_LEFT, WALK_RIGHT, UP ,PLAYER_LEFT_DOWN, PLAYER_RIGHT_DOWN, JUMP, STOP_SHOOT, UP_SHOOT, RIGHT_RUN_SHOOT, LEFT_RUN_SHOOT, LEFT_DOWN_SHOOT, RIGHT_DOWN_SHOOT, PLAYER_HIT, END };

public:
	CPlayer();
	~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	//농장맵 전용으로 나중에 스테이지 바뀔때 다르게 적용되게 만들자!
public:
	void Set_OffSet(bool OffSet_Switch);

private:
	void		Key_Input(void);
	void		Jumping(void);
	void		OffSet(void);
	void		State_Change(void);
	void		Player_Hit(void);



private:
	POINT					m_tGun;			//불렛 발사 위치

	bool					m_bJump;
	float					m_fJumpY;
	float					m_fJumpPower;
	float					m_fTime;
	float					m_fGravity; //test

	int						m_iOffSetX;
	int						m_iOffSetY;
	bool					m_bOff_Set;    //스테이지 별로 오픈셋 true 및 false지정

	STATE					m_ePreState;
	STATE					m_eCurState;
/*
	bool					m_bStretch = true;
*/
	bool					m_bDownSwitch;

	//                      플레이어의 충돌을 체크하고 있다.
	bool					m_bPlayerHitCheck;

	//						플레이어의 충돌 이후 무적시간을 알려주고 있다.
	DWORD					m_tTimePhoenix;

	/////////////////////////////////////// 사운드
	int						m_iSoundCount;
	DWORD					m_tSoundTime;

	///////////////////////////////////////////플레이어 체력
	int						m_PullHp;
};

#endif