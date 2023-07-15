#pragma once

#ifndef __ABSTRACTFACTORY_H
#define __ABSTRACTFACTORY_H

#include "Obj.h"
#include "Include.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	/////////////////////이건 옛버전
	//static CObj*		Create(RECTPOS _tPos)
	//{

	//	CObj*		pObj = new T;
	//	pObj->Initialize();
	//	pObj->Set_Pos(_tPos.fX, _tPos.fY);
	//	return pObj;
	//}

	////////////////////이건 라인 태우기용 Set_Info Obj아님 그 하위 애들 Line이랑 Rect 애들꺼임
	static CObj*		Create(LINEINFO _tInfo)
	{

		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_InfoTest(_tInfo);
		//dynamic_cast<T*>(pObj)->Set_Info(_tInfo);

		//m_tInfo.fX = m_tInfoRect.tLeftPos.fX + abs((m_tInfoRect.tLeftPos.fX - m_tInfoRect.tRightPos.fX) * 0.5f);
		//m_tInfo.fY = m_tInfoRect.tLeftPos.fY + abs((m_tInfoRect.tLeftPos.fY - m_tInfoRect.tRightPos.fY) * 0.5f);

		//m_tInfo.fCX = abs(m_tInfoRect.tLeftPos.fX - m_tInfoRect.tRightPos.fX);
		//m_tInfo.fCY = abs(m_tInfoRect.tLeftPos.fY - m_tInfoRect.tRightPos.fY);

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, BULLET::DIR eDir = BULLET::UP)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Direction(eDir);

		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _Angle)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_Angle);

		return pObj;
	}
};

#endif // !__ABSTRACTFACTORY_H
