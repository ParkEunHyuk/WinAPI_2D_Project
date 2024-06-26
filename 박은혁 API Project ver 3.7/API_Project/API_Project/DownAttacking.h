#pragma once

#ifndef __DOWNATTACKING_H_
#define __DEOWNATTACKING_H_
#include "Obj.h"
class CDownAttacking : public CObj
{
public:
	enum STATE { ATTACK };
public:
	CDownAttacking();
	~CDownAttacking();

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