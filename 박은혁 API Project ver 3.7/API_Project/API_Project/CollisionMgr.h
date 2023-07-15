#pragma once

#ifndef __COLLISIONMGR_H_
#define __COLLISIONMGR_H_

class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:																					// dest: destination (목적지: 데이터가 갈곳) src: source (원본: 원래의 데이터)
	static void Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src);					//렉트끼리 충돌했을경우 둘 다 사라짐
	static void	Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src);					//렉트끼리 밀어냄
	static void	Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src);					//범위가 렉트가 아닌 동그라미

	//////////////////////////스테이지 충돌여부
	static void	Collision_Rect_Stage(list<CObj*> _Dest, list<CObj*> _Src);

	/////////////////////////총알 충돌 여부
	static void CCollisionMgr::Collision_Bullet(list<CObj*> _Dest, list<CObj*> _Src, int _Damage);

	/////////////////////////플레이어 충돌 여부
	static void CCollisionMgr::Collision_Player(list<CObj*> _Dest, list<CObj*> _Src, int _Damage);
	static void CCollisionMgr::Collision_Monster(list<CObj*> _Dest, list<CObj*> _Src, int _Damage);

private:
	static bool Check_Rect_Stage(CObj* pDest, CObj* pSrc, float* _pWidth, float* _pHeight);

	
private:
	static bool Check_Sphere(CObj* pDest, CObj* pSrc);									//동그라미의 충돌 여부를 확인하는 함수
	static bool Check_Rect(CObj* pDest, CObj* pSrc, float* _pWidth, float* _pHeight);	//렉트의 충돌 여부를 확인하는 함수

};

#endif