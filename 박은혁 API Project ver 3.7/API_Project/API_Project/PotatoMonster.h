#pragma once

#ifndef __POTATOMONSTER_H_
#define __POTATOMONSTER_H_

#include "Obj.h"
class CPotatoMonster : public CObj
{
	enum STATE{ INTRO,IDLE, ATTACK,DIE};
public:
	CPotatoMonster();
	~CPotatoMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		State_Change(void);

private:
	void		Potato_Shoot(void);

private:
	POINT		m_tGun;			//불렛 발사 위치
	DWORD		m_tTimeBullet;

	STATE					m_ePreState;
	STATE					m_eCurState;

	//////////////////////////////////////////////
	DWORD					m_tSoundTime;
	
};

#endif