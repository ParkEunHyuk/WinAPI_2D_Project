#pragma once

#ifndef __POTATOBULLET_H_
#define __POTATOBULLET_H_

#include "Obj.h"
class CPotatoBullet : public CObj
{
public:
	enum STATE { IDLE, DIE };

public:
	CPotatoBullet();
	~CPotatoBullet();

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