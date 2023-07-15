#pragma once

#ifndef __FACEWHIP_H_
#define __FACEWHIP_H_
#include "Obj.h"
class CFaceWhip : public CObj
{
public:
	enum STATE { ATTACK };
public:
	CFaceWhip();
	~CFaceWhip();

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

	////////////////////////////////////////// »ç¿îµå
	int						m_iSoundCount;
	DWORD					m_tTimeSound;
};

#endif

