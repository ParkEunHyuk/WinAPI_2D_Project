#pragma once

#ifndef __VINESPEAR_H_
#define __VINESPEAR_H_
#include "Obj.h"
class CVineSpear : public CObj
{
public:
	enum STATE { ATTACK, DIE};
public:
	CVineSpear();
	~CVineSpear();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		State_Change(void);

private:
	STATE					m_ePreState;
	STATE					m_eCurState;

	bool					m_bIntroEnd;
	bool					m_bDieSwitch;

	////////////////////////////////////////// »ç¿îµå
	int						m_iSoundCount;
	DWORD					m_tTimeSound;
};

#endif