#pragma once

#ifndef __VINEWHIP_H_
#define __VINEWHIP_H_
#include "Obj.h"
class CVineWhip : public CObj
{
public:
	enum STATE { INTRO, IDLE };
public:
	CVineWhip();
	~CVineWhip();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		State_Change(void);

	void		Vine_Spear(void);

private:
	STATE					m_ePreState;
	STATE					m_eCurState;

	DWORD					m_tTimeCollision;
	bool					m_bIntroEnd;

	DWORD					m_tTimePattern;
	bool					m_tVineSpearSwitch;
	int						m_tRandomVineAttack;
	int						iCount;

	////////////////////////////////////////// »ç¿îµå
	int						m_iSoundCount;
	DWORD					m_tTimeSound;


};
#endif