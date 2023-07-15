#pragma once

#ifndef __REDMONSTER_H_
#define __REDMONSTER_H_

#include "Obj.h"
class CRedMonster : public CObj
{
	enum STATE { IDLE, DIE };
public:
	CRedMonster();
	~CRedMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		State_Change(void);


private:
	DWORD		m_tTimeDIE;

	STATE					m_ePreState;
	STATE					m_eCurState;

};

#endif
