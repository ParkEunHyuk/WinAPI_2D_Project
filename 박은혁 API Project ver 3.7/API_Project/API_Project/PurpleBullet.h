#pragma once

#ifndef _PURPLEBULLET_H_
#define _PURPLEBULLET_H_

#include "Obj.h"
class CPurpleBullet : public CObj
{
public:
	enum STATE { IDLE };
public:
	CPurpleBullet();
	~CPurpleBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	STATE					m_ePreState;
	STATE					m_eCurState;

	/////////////////////////////////////// »ç¿îµå
	int						m_iSoundCount;
	DWORD					m_tSoundTime;

};

#endif