#pragma once

#ifndef __RECTMGR_H_
#define __RECTMGR_H_
class CMyRect;
class CRectMgr
{
public:
	CRectMgr();
	~CRectMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC _DC);
	void		Release(void);

public:
	bool		Save_Data(void);
	bool		Load_Data(void);
	void		Picking_Rect(void);

public:
	void		Set_RectList(CMyRect(_tInfo));


public:
	static	CRectMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CRectMgr;

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
	static CRectMgr*	m_pInstance;

	list<CMyRect*>		m_RectList;
};

#endif