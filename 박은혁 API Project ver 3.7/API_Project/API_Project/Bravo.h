#pragma once

#ifndef __BRAVO_H_
#define __BRAVO_H_
#include "Obj.h"
class CBravo : public CObj
{
public:
	enum STATE { IDLE };
public:
	CBravo();
	~CBravo();

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

};

#endif
