#pragma once
#ifndef __CARROTMONSTER_H_
#define __CARROTMONSTER_H_
#include "Obj.h"
class CCarrotMonster : public CObj
{
	enum STATE { INTRO, IDLE, ATTACK, ATTACK_2, DIE };
public:
	CCarrotMonster();
	~CCarrotMonster();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void State_Change(void);
	void LooK_Player(void);
	void Caorrt_Bullet(void);
	void Caorrt_Ring(void);

private:
	POINT					m_tGun;
	float					m_fGun_Distance;

	//당근 미사일에 관한 변수
	DWORD					m_tTimeCarrotBullet;

	//당근 링에 관한 변수
	DWORD					m_tTimeRingBullet;
	DWORD					m_tTimeRingCount;
	int						m_iRingCount;

	bool					m_bIntroEnd;

	//스테이트 패턴에 관한 변수
	DWORD					m_tTimePattern;
	bool					m_bIDLE_Switch;
	int						m_iRand;

	STATE					m_ePreState;
	STATE					m_eCurState;

	////////////////////////////////////////// 사운드
	int						m_iSoundCount;
	DWORD					m_tTimeSound;
};
#endif