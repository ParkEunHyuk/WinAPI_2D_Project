#pragma once

#ifndef __BLUEMONSTER_H_
#define __BLUEMONSTER_H_

#include "Obj.h"
class CBlueMonster : public CObj
{
	enum STATE { INTRO,LEFT, RIGHT, DIE };

public:
	CBlueMonster();
	~CBlueMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		State_Change(void);

private:
	STATE					m_ePreState;
	STATE					m_eCurState;

	int				m_iCount;
	bool			m_IntroEnd;
};

#endif