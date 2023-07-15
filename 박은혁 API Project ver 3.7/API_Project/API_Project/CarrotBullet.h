#pragma once

#ifndef __CARROTBULLET_H_
#define __CARROTBULLET_H_

#include "Obj.h"
class CCarrotBullet : public CObj
{
public:
	enum STATE { IDLE, DIE };

public:
	CCarrotBullet();
	~CCarrotBullet();

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

	int				m_iCount;


};

#endif

