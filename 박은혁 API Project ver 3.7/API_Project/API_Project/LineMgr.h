#pragma once

#ifndef __LINEMGR_H_
#define __LINEMGR_H_

#include "Line.h"
#include "MyRect.h"

//싱글톤으로 만든 라인 매니저 객체들의 라인 태우기 용
class CLineMgr
{
public:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release();

	void		Picking_Line(void);
	void		Picking_Rect(void);
	bool		Collision_Line(const float& _fX, float* _fY);
	bool		Collision_LineEx(const float& _fX, const float& _fCB, const float& _fNB, float* _fY);

public:
	void		Set_LineList(CLine(_tInfo));
	void		Set_RectList(CMyRect(_tInfo));

public:
	void		Save_Data(void);
	void		Load_Data(void);

public:
	static	CLineMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CLineMgr;

		return m_pInstance;
	}

	static	void		Destroy_Intance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CLineMgr*	m_pInstance;
	LINEPOS				m_tLinePos[2];

	list<CLine*>		m_LineList;
	list<CMyRect*>		m_RectList;
};

#endif
