#pragma once

#ifndef __PURPLEMONSTER_H_
#define __PURPLEMONSTER_H_
#include "Obj.h"
class CPurpleMonster : public CObj
{
	enum STATE { INTRO,IDLE,ATTACK,DIE };
public:
	CPurpleMonster();
	~CPurpleMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		LookPlayer();

public:
	void		MonsterPattern(void);
	void		BulletFire(void);

private:
	void		State_Change(void);


private:
	DWORD			m_tTimeDIE;

	STATE			m_ePreState;
	STATE			m_eCurState;

	int				m_iCount;
	bool			m_bIntroEnd;

	DWORD			m_tTimeBullet;
	int				m_iBulletCount;
	bool			m_bBulletSwitch;
	DWORD			m_tTimePattern;
	bool			m_bPatternSwitch;

	POINT					m_tGun;  //건 좌표
	float			m_fGun_Distance; //건 길이
};

#endif