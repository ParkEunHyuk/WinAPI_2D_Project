#pragma once

#ifndef __REDSEEDBULLET_H_
#define __REDSEEDBULLET_H_

#include "Obj.h"
class CRedSeedBullet:public CObj
{
public:
	enum STATE { IDLE, DIE };

public:
	CRedSeedBullet();
	~CRedSeedBullet();

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
};

#endif