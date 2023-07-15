#pragma once

#ifndef __PUNCHING_H_
#define __PUNCHING_H_
#include "Obj.h"
class CPunching : public CObj
{
	enum STATE { ATTACK };
public:
	CPunching();
	~CPunching();

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