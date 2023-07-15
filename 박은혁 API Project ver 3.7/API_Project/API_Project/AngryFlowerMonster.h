#pragma once

#ifndef __ANGRYFLOWERMONSTER_H_
#define __ANGRYFLOWERMONSTER_H_
#include "Obj.h"
class CAngryFlowerMonster : public CObj
{
public:
	enum STATE { INTRO, ATTACK, DIE};
public:
	CAngryFlowerMonster();
	~CAngryFlowerMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void		FlowerBullet(void);

private:
	void		State_Change(void);

	STATE					m_ePreState;
	STATE					m_eCurState;

	bool					m_bIntroEnd;

	int						iCount;

	POINT		m_tGun;
	DWORD		m_tTimeFlowerBullet;

};
#endif
