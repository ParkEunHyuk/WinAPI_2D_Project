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

	//������Ʈ ���Ͽ� ���� ����
	DWORD					m_tTimePattern;
	bool					m_bFace_Switch;

	//��� ����ġ
	bool					m_bMontion;
	int						m_iMotionCount;

	////////////////////////////////////////// ����
	int						m_iSoundCount;
	DWORD					m_tTimeSound;
};

#endif