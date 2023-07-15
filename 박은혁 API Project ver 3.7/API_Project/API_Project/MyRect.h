#pragma once

#ifndef __MYRECT_H_
#define __MYRECT_H_

#include "Obj.h"
class CMyRect :public CObj
{
public:
	CMyRect();
	~CMyRect();
	CMyRect(LINEINFO& tInfo);
	CMyRect(LINEPOS& _tLeft, LINEPOS& _tRight);

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _DC) override;
	virtual void Release(void) override;


public:
	const	LINEINFO&		Get_InfoRect(void) const { return m_tInfoRect; }

	//
public:
	void		Set_Info(LINEINFO& _tInfoRect) { m_tInfoRect = _tInfoRect; }

private:
	LINEINFO		m_tInfoRect;
};

#endif