#pragma once

#ifndef __OBJMGR_H_
#define __OBJMGR_H_

#include "CollisionMgr.h"
//Obj�Ŵ����� �̱������� �������.
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

	//�̰� ������������ ���¼� ������ �ٸ��� �ϱ� ������

public:
	void			Stage_OffSet(OBJID::ID eID);

private:
	list<CObj*>		m_ObjList[OBJID::END];

	//Y������ �� ����

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
	static	CObjMgr*		m_pInstance; //Info�� ���������� CObjMgr*�� �����ν� �ȿ� �ִ� ��� �Լ��� ��� ������ ����� �� �ְ� �ȴ�.

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