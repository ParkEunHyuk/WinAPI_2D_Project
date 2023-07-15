#pragma once

#ifndef __FACEATTACK_H_
#define __FACEATTACK_H_
#include "Obj.h"
class CFaceAttack : public CObj
{
public:
	enum STATE { FACEATTACK_UP, FACEATTACK_DOWN };
public:
	CFaceAttack();
	~CFaceAttack();
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

	//스테이트 패턴에 관한 변수
	DWORD					m_tTimePattern;
	bool					m_bFace_Switch;
	int						m_tRandomFaceAttack;
	int						iCount;
};
#endif