#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "MyRect.h"
#include "StageButton.h"
#include "Player.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Src->Get_Rect())))
			{
				Dest->Set_Dead();		
				Src->Set_Dead();

				// IntersectRect
				// 1. �浹�Ͽ� ��Ʈ���� ��ģ ������ �簢���� ����
				// 2.3 �浹�ϴ� ��Ʈ���� �ּҰ�
			}
		}
	}

}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src)//destination�� �������� source�� �浹�ߴ��� üũ�Ѵ�.
{
	for (auto& Dest : _Dest)										//destination ��ü�� for������ ������ �ִ�.
	{
		for (auto& Src : _Src)										//source ��ü�� for������ ������ �ִ�.
		{
			float	fWidth = 0.f, fHeight = 0.f;

			if (Check_Rect(Dest, Src, &fWidth, &fHeight))			// �� ��ü�� �浹 ���θ� üũ�ϰ� �ִ�.
			{	
				if (fWidth > fHeight)								//���� ���ΰ� ���κ��� ũ�ٸ� �� �� �浹�̴�.
				{
					if (Dest->Get_Info().fY < Src->Get_Info().fY)	//������ �Ǵ°ͺ��� source�� ũ�ٸ� �� �浹�̴�.
					{
						Src->Set_PosY(fHeight);						//�� �浹�� fHeight�� �������״� ���θ� Src�� �и���.
					}
					else											//������ �Ǵ°ͺ��� source�� �۴ٸ� �� �浹�̴�.
					{
						Src->Set_PosY(-fHeight);					//�� �浹�� fHeight�� �����̴� -�� �ٿ� ����� �ٲٸ� Src�� �и���.
					}
				}
				else												//���� ���ΰ� ���κ��� ũ�ٸ�. �� �� �浹�̴�.
				{
					if (Dest->Get_Info().fX < Src->Get_Info().fX)	//������ �Ǵ°ͺ��� source�� ũ�ٸ� �� �浹�̴�.
					{
						Src->Set_PosX(fWidth);						//�� �浹�� fWidth�� �������״� ���θ� Src�� �и���.
					}
					else											//������ �Ǵ°ͺ��� source�� �۴ٸ� �� �浹�̴�.
					{
						Src->Set_PosX(-fWidth);						//�� �浹�� fWidth�� �����̹Ƿ� -�� �ٿ� ����� �ٲٸ� Src�� �и���.
					}
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT	rc{};
	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dest, Src))
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSrc)
{
	float	fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);			//�� ��ü���� ���� �Ÿ�
	float	fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);			// �� ��ü���� ���� �Ÿ�

	float	fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);				//��Ÿ����� ������ �̿��Ͽ� ������ �Ÿ��� ���Ѵ�. *sqrtf�� ��Ʈ�� �����ִ� �Լ��̴�.

	float	fRadius = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;	//destination�� �������� source�� �������� �������� ũ���̰� fDistance�� �� ��ü�� �Ÿ��̴�.

	return	fRadius > fDistance;												//fRadius �� ��ü�� �������� fDistance���� Ŀ���� �Ǹ� �浹�ȴ�.
}

bool CCollisionMgr::Check_Rect(CObj * pDest, CObj * pSrc, float *_pWidth, float * _pHeight)
{
	//Width ����				Height ����
	float		fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);		// �� ��ü�� ���� �Ÿ�
	float		fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);		// �� ��ü�� ���� �Ÿ�

	float		fCX = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;	//�� ��ü�� ���� ũ��
	float		fCY = (pDest->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;	//�� ��ü�� ���� ũ��

	if (fCX > fWidth && fCY > fHeight)
	{
		*_pWidth = fCX - fWidth;		//fCX�� �� ��ü�� �������� ���� ũ���̰� fWidth�� �� ��ü�� �Ÿ��̴�.
		*_pHeight = fCY - fHeight;		//fCY�� �� ��ü�� �������� ���� ũ���̰� fHeight�� �� ��ü�� �Ÿ��̴�.

		return true;
	}
	return false;
}

////////////////////////////////////�������� �n �������� �浹 ���θ� Ȯ���ϰ� ����
void CCollisionMgr::Collision_Rect_Stage(list<CObj*> _Dest, list<CObj*> _Src)
{
	for (auto& Dest : _Dest)										
	{
		for (auto& Src : _Src)										
		{
			float	fWidth = 0.f, fHeight = 0.f;

			if (Check_Rect(Dest, Src, &fWidth, &fHeight))			
			{
				if (fWidth > fHeight)								
				{
					if (Dest->Get_Info().fY < Src->Get_Info().fY)	
					{
						dynamic_cast<CStageButton*>(Dest)->Set_StageSwitch(true);
					}
					else											
					{
						dynamic_cast<CStageButton*>(Dest)->Set_StageSwitch(true);
					}
				}
				else												
				{
					if (Dest->Get_Info().fX < Src->Get_Info().fX)	
					{
						dynamic_cast<CStageButton*>(Dest)->Set_StageSwitch(true);
					}
					else											
					{
						dynamic_cast<CStageButton*>(Dest)->Set_StageSwitch(true);
					}
				}
			}
			else
			{
				dynamic_cast<CStageButton*>(Dest)->Set_StageSwitch(false);
			}
		}
	}
}
////////////////////////////////////////////////////�÷��̾� �Ѿ��� �浹���θ� üũ�ϰ� ���� �̰� üũ ��Ʈ�� �ؿ��ִ°� üũ ���׶����
void CCollisionMgr::Collision_Bullet(list<CObj*> _Dest, list<CObj*> _Src, int _Damage)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			float	fWidth = 0.f, fHeight = 0.f;
			bool Check_Bullet = Src->Get_m_bCollsion();
			if (Check_Rect(Dest, Src, &fWidth, &fHeight)&& false == Check_Bullet) //üũ��Ʈ�� �浹 ���θ� Ȯ���ϰ� �ִ�����
			{
				Dest->Set_Hp(_Damage);
				Src->Set_Dead();
				Src->Set_Collsion(true);				//�Ѿ��� ������� ����� �ʿ��ϴϱ� Set_Collsion�� Ʈ���� ��� 175��°�� ���� Ʈ�簡 �ȴ�.
			}
		}
	}
}
/////////////////////////////////////////////�÷��̾ Dest  �Ѿ��� Src�̴�.
void CCollisionMgr::Collision_Player(list<CObj*> _Dest, list<CObj*> _Src, int _Damage)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			float	fWidth = 0.f, fHeight = 0.f;
			bool Check_Bullet = Src->Get_m_bCollsion();
			bool Check_Player = Dest->Get_m_bCollsion();
			if (Check_Rect(Dest, Src, &fWidth, &fHeight) && false == Check_Bullet && false == Check_Player) //üũ��Ʈ�� �浹 ���θ� Ȯ���ϰ� �ִ�����
			{
				Dest->Set_Hp(_Damage);
				Dest->Set_Collsion(true);
				Src->Set_Dead();
				Src->Set_Collsion(true);				//�Ѿ��� ������� ����� �ʿ��ϴϱ� Set_Collsion�� Ʈ���� ��� 175��°�� ���� Ʈ�簡 �ȴ�.
			}
		}
	}
}
void CCollisionMgr::Collision_Monster(list<CObj*> _Dest, list<CObj*> _Src, int _Damage)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			float	fWidth = 0.f, fHeight = 0.f;
			bool Check_Bullet = Src->Get_m_bCollsion();
			bool Check_Player = Dest->Get_m_bCollsion();
			if (Check_Rect(Dest, Src, &fWidth, &fHeight) && false == Check_Bullet && false == Check_Player) //üũ��Ʈ�� �浹 ���θ� Ȯ���ϰ� �ִ�����
			{
				Dest->Set_Hp(_Damage);
				Dest->Set_Collsion(true);
				Src->Set_Dead();
				Src->Set_Collsion(true);				//�Ѿ��� ������� ����� �ʿ��ϴϱ� Set_Collsion�� Ʈ���� ��� 175��°�� ���� Ʈ�簡 �ȴ�.
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
bool CCollisionMgr::Check_Rect_Stage(CObj * pDest, CObj * pSrc, float * _pWidth, float * _pHeight)
{
	//Width ����				Height ����
	float		fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);		// �� ��ü�� ���� �Ÿ�
	float		fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);		// �� ��ü�� ���� �Ÿ�

	float		fCX = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;	//�� ��ü�� ���� ũ��
	float		fCY = (pDest->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;	//�� ��ü�� ���� ũ��

	if (fCX > fWidth && fCY > fHeight)
	{
		*_pWidth = fCX - fWidth;		//fCX�� �� ��ü�� �������� ���� ũ���̰� fWidth�� �� ��ü�� �Ÿ��̴�.
		*_pHeight = fCY - fHeight;		//fCY�� �� ��ü�� �������� ���� ũ���̰� fHeight�� �� ��ü�� �Ÿ��̴�.

		return true;
	}
	return false;
}
