#pragma once

#ifndef __PUNCHMOTION_H_
#define __PUNCHMOTION_H_

#include "Obj.h"

class CPunchMotion : public CObj
{
	enum STATE { INTRO, PUNCH_LEFT, PUNCH_RIGHT };
public:
	CPunchMotion();
	~CPunchMotion();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Attacking(void);

public:
	void		State_Change(void);
	void		LookPlayer(void);

private:
	STATE					m_ePreState;
	STATE					m_eCurState;

	//스테이트 패턴에 관한 변수
	DWORD					m_tTimePattern;
	bool					m_bFace_Switch;

	//모션 스위치
	bool					m_bMontion;
	int						m_iMotionCount;

	////////////////////////////////////////// 사운드
	int						m_iSoundCount;
	DWORD					m_tTimeSound;
};

#endif