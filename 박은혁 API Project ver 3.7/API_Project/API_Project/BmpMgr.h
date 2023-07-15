#pragma once

#ifndef __BMPMGR_H_
#define __BMPMGR_H_
#include "MyBitmap.h"

class CBmpMgr
{
public:
	CBmpMgr();
	~CBmpMgr();

public:
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC			Find_Image(const TCHAR* pImgKey);
	void		Release(void);

public:
	static	CBmpMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBmpMgr;

		return m_pInstance;
	}

	static	void		Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CBmpMgr*	m_pInstance;
	map<const TCHAR*, CMyBitmap*>		m_mapBit;
};

#endif