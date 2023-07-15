#pragma once

#ifndef __COLLISIONMGR_H_
#define __COLLISIONMGR_H_

class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:																					// dest: destination (������: �����Ͱ� ����) src: source (����: ������ ������)
	static void Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src);					//��Ʈ���� �浹������� �� �� �����
	static void	Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src);					//��Ʈ���� �о
	static void	Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src);					//������ ��Ʈ�� �ƴ� ���׶��

	//////////////////////////�������� �浹����
	static void	Collision_Rect_Stage(list<CObj*> _Dest, list<CObj*> _Src);

	/////////////////////////�Ѿ� �浹 ����
	static void CCollisionMgr::Collision_Bullet(list<CObj*> _Dest, list<CObj*> _Src, int _Damage);

	/////////////////////////�÷��̾� �浹 ����
	static void CCollisionMgr::Collision_Player(list<CObj*> _Dest, list<CObj*> _Src, int _Damage);
	static void CCollisionMgr::Collision_Monster(list<CObj*> _Dest, list<CObj*> _Src, int _Damage);

private:
	static bool Check_Rect_Stage(CObj* pDest, CObj* pSrc, float* _pWidth, float* _pHeight);

	
private:
	static bool Check_Sphere(CObj* pDest, CObj* pSrc);									//���׶���� �浹 ���θ� Ȯ���ϴ� �Լ�
	static bool Check_Rect(CObj* pDest, CObj* pSrc, float* _pWidth, float* _pHeight);	//��Ʈ�� �浹 ���θ� Ȯ���ϴ� �Լ�

};

#endif