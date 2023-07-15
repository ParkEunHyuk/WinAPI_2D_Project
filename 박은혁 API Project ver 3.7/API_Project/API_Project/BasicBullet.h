#pragma once

#ifndef __BASICBULLET_H_
#define __BASICBULLET_H_

#include "Obj.h"
class CBasicBullet : public CObj
{
public:
	enum STATE { IDLE, DIE };
public:
	CBasicBullet();
	~CBasicBullet();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		State_Change(void);

private:
	STATE					m_ePreState;
	STATE					m_eCurState;
	//PlayerBullet.wav
	/////////////////////////////////////////»ç¿îµå
	//float					g_fSoundPlayerBullet;
	DWORD					m_tSoundTime;
};

#endif