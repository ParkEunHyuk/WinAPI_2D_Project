#pragma once

#ifndef __ACORNBULLET_H_
#define __ACORNBULLET_H_
#include "Obj.h"
class CAcornBullet : public CObj
{
public:
	enum STATE { INTRO , IDLE };
public:
	CAcornBullet();
	~CAcornBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		State_Change(void);

private:
	STATE					m_ePreState;
	STATE					m_eCurState;

	bool					m_bIntroEnd;

	////////////////////////////////////////// »ç¿îµå
	int						m_iSoundCount;
	DWORD					m_tTimeSound;

};

#endif