#pragma once
#ifndef __LINE_H_
#define __LINE_H_
#include "Obj.h"
class CLine : public CObj
{
public:
	CLine();
	CLine(LINEINFO& _tInfo);
	CLine(LINEPOS& _tLeft, LINEPOS& _tRight);
	~CLine();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	
public:
	void		Set_Info(LINEINFO& _tInfoLine) { m_tInfo= _tInfoLine; }

public:
	const	LINEINFO&		Get_Info(void) const { return m_tInfo; }


private:
	LINEINFO		m_tInfo;  //라인을 그릴때 필요한 좌표들을 구조체로 만듬
};


#endif // !__LINE_H_