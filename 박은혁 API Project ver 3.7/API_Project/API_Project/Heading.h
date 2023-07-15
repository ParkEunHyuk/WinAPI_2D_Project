#pragma once

#ifndef __HEADING_H_
#define __HEADING_H_
#include "Obj.h"
class CHeading : public CObj
{
	enum STATE { ATTACK };
public:
	CHeading();
	~CHeading();

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
