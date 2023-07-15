#pragma once

#ifndef __FLOWERBULLET_H_
#define __FLOWERBULLET_H_

#include "Obj.h"
class CFlowerBullet : public CObj
{
public:
	enum STATE { IDLE };
public:
	CFlowerBullet();
	~CFlowerBullet();

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