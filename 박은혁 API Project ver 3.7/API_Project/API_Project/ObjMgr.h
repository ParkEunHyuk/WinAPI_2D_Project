#pragma once

#ifndef __OBJMGR_H_
#define __OBJMGR_H_

#include "CollisionMgr.h"
//Obj매니저를 싱글톤으로 만들었다.
class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*			Get_Target(OBJID::ID _eID, CObj* pObj);


public:
	void			Add_Object(OBJID::ID eID, CObj* pObj);
	int				Update(void);
	void			Late_Update(void);
	void			Render(HDC m_DC);
	void			Release(void);
	void			Delete_ID(OBJID::ID eID);

	void			Delete_Render(RENDERID eRender);

	//이거 스테이지마자 오픈셋 적용을 다르게 하기 위함임

public:
	void			Stage_OffSet(OBJID::ID eID);

private:
	list<CObj*>		m_ObjList[OBJID::END];

	//Y소팅할 때 쓰임

	list<CObj*>		m_RenderSort[RENDER_END];

public:
	static	CObjMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}

	static	void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete	m_pInstance;
			m_pInstance = nullptr;
		}
	}



private:
	static	CObjMgr*		m_pInstance; //Info와 마찬가지로 CObjMgr*를 함으로써 안에 있는 멤버 함수와 멤버 변수를 사용할 수 있게 된다.

	/////////////////////////////////////////////////////// test
private:
	static bool		m_bSlimeClear;
	static bool		m_bFarmClear;
	static bool		m_bFlowerClear;

public:
	void			Set_SlimeClear(bool _bClear);
	bool			Get_Slime() { return m_bSlimeClear; }

	void			Set_FarmClear(bool _bClear);
	bool			Get_Farm() { return m_bFarmClear; }

	void			Set_FlowerClear(bool _bClear);
	bool			Get_Flower() { return m_bFlowerClear; }
};

#endif