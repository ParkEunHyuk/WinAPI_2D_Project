#pragma once

#ifndef __ONIONMONSTER_H_
#define __ONIONMONSTER_H_

#include "Obj.h"
class COnionMonster : public CObj
{
	enum STATE { INTRO, IDLE, ATTACK, DIE };
public:
	COnionMonster();
	~COnionMonster();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Onion_Crying(void);

private:
	void		State_Change(void);

private:
	POINT		m_tGun;
	DWORD		m_tTimeCry;

	STATE					m_ePreState;
	STATE					m_eCurState;

	/////////////////////////////////////// »ç¿îµå
	int						m_iSoundCount;
	DWORD					m_tSoundTime;
};

#endif