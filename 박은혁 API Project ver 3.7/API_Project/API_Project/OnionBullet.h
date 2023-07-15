#pragma once

#ifndef __ONIONBULLET_H_
#define __ONIONBULLET_H_

#include "Obj.h"
class COnionBullet : public CObj
{
public:
	enum STATE { IDLE, DIE };

public:
	COnionBullet();
	~COnionBullet();
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