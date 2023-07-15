#pragma once

#ifndef __RINGBULLET_H_
#define __RINGBULLET_H_

#include "Obj.h"
class CRingBullet : public CObj
{
public:
	enum STATE { IDLE };
public:
	CRingBullet();
	~CRingBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	STATE					m_ePreState;
	STATE					m_eCurState;
};

#endif
