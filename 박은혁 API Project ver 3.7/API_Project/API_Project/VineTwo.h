#pragma once

#ifndef __VINETWO_H_
#define __VINETWO_H_
#include "Obj.h"
class CVineTwo : public CObj
{
public:
	enum STATE { IDLE };

public:
	CVineTwo();
	~CVineTwo();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	STATE					m_ePreState;
	STATE					m_eCurState;

	DWORD					m_tTime;

	DWORD					m_tTimeBlueMonster;
	int						iCount;
};

#endif