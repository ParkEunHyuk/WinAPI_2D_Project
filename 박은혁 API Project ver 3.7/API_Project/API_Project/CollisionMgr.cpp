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
				// 1. 충돌하여 렉트끼리 겹친 영역의 사각형을 전달
				// 2.3 충돌하는 렉트들의 주소값
			}
		}
	}

}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src)//destination을 기준으로 source와 충돌했는지 체크한다.
{
	for (auto& Dest : _Dest)										//destination 객체를 for문으로 돌리고 있다.
	{
		for (auto& Src : _Src)										//source 객체를 for문으로 돌리고 있다.
		{
			float	fWidth = 0.f, fHeight = 0.f;

			if (Check_Rect(Dest, Src, &fWidth, &fHeight))			// 두 객체의 충돌 여부를 체크하고 있다.
			{	
				if (fWidth > fHeight)								//만약 가로가 세로보다 크다면 상 하 충돌이다.
				{
					if (Dest->Get_Info().fY < Src->Get_Info().fY)	//기준이 되는것보다 source가 크다면 상 충돌이다.
					{
						Src->Set_PosY(fHeight);						//상 충돌시 fHeight가 음수일테니 냅두면 Src가 밀린다.
					}
					else											//기준이 되는것보다 source가 작다면 하 충돌이다.
					{
						Src->Set_PosY(-fHeight);					//하 충돌시 fHeight가 음수이니 -를 붙여 양수로 바꾸면 Src가 밀린다.
					}
				}
				else												//만약 세로가 가로보다 크다면. 좌 우 충돌이다.
				{
					if (Dest->Get_Info().fX < Src->Get_Info().fX)	//기준이 되는것보다 source가 크다면 우 충돌이다.
					{
						Src->Set_PosX(fWidth);						//우 충돌시 fWidth는 음수일테니 냅두면 Src가 밀린다.
					}
					else											//기준이 되는것보다 source가 작다면 좌 충돌이다.
					{
						Src->Set_PosX(-fWidth);						//좌 충돌시 fWidth는 음수이므로 -를 붙여 양수로 바꾸면 Src가 밀린다.
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
	float	fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);			//두 객체간의 가로 거리
	float	fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);			// 두 객체간의 세로 거리

	float	fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);				//피타고라스의 정리를 이용하여 빗면의 거리를 구한다. *sqrtf는 루트를 구해주는 함수이다.

	float	fRadius = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;	//destination의 반지름과 source의 반지름이 실직적인 크기이고 fDistance는 두 객체의 거리이다.

	return	fRadius > fDistance;												//fRadius 두 객체의 반지름이 fDistance보다 커지게 되면 충돌된다.
}

bool CCollisionMgr::Check_Rect(CObj * pDest, CObj * pSrc, float *_pWidth, float * _pHeight)
{
	//Width 가로				Height 세로
	float		fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);		// 두 객체의 가로 거리
	float		fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);		// 두 객체의 세로 거리

	float		fCX = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;	//두 객체의 가로 크기
	float		fCY = (pDest->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;	//두 객체의 세로 크기

	if (fCX > fWidth && fCY > fHeight)
	{
		*_pWidth = fCX - fWidth;		//fCX는 두 객체의 실질적인 가로 크기이고 fWidth는 두 객체의 거리이다.
		*_pHeight = fCY - fHeight;		//fCY는 두 객체의 실질적인 세로 크기이고 fHeight는 두 객체의 거리이다.

		return true;
	}
	return false;
}

////////////////////////////////////스테이지 쳌 스테이지 충돌 여부를 확인하고 있음
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
////////////////////////////////////////////////////플레이어 총알의 충돌여부를 체크하고 있음 이건 체크 렉트임 밑에있는건 체크 동그라미임
void CCollisionMgr::Collision_Bullet(list<CObj*> _Dest, list<CObj*> _Src, int _Damage)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			float	fWidth = 0.f, fHeight = 0.f;
			bool Check_Bullet = Src->Get_m_bCollsion();
			if (Check_Rect(Dest, Src, &fWidth, &fHeight)&& false == Check_Bullet) //체크렉트는 충돌 여부를 확인하고 있는중임
			{
				Dest->Set_Hp(_Damage);
				Src->Set_Dead();
				Src->Set_Collsion(true);				//총알이 사라지는 모션이 필요하니깐 Set_Collsion가 트루일 경우 175번째에 값이 트루가 된다.
			}
		}
	}
}
/////////////////////////////////////////////플레이어가 Dest  총알이 Src이다.
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
			if (Check_Rect(Dest, Src, &fWidth, &fHeight) && false == Check_Bullet && false == Check_Player) //체크렉트는 충돌 여부를 확인하고 있는중임
			{
				Dest->Set_Hp(_Damage);
				Dest->Set_Collsion(true);
				Src->Set_Dead();
				Src->Set_Collsion(true);				//총알이 사라지는 모션이 필요하니깐 Set_Collsion가 트루일 경우 175번째에 값이 트루가 된다.
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
			if (Check_Rect(Dest, Src, &fWidth, &fHeight) && false == Check_Bullet && false == Check_Player) //체크렉트는 충돌 여부를 확인하고 있는중임
			{
				Dest->Set_Hp(_Damage);
				Dest->Set_Collsion(true);
				Src->Set_Dead();
				Src->Set_Collsion(true);				//총알이 사라지는 모션이 필요하니깐 Set_Collsion가 트루일 경우 175번째에 값이 트루가 된다.
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
bool CCollisionMgr::Check_Rect_Stage(CObj * pDest, CObj * pSrc, float * _pWidth, float * _pHeight)
{
	//Width 가로				Height 세로
	float		fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);		// 두 객체의 가로 거리
	float		fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);		// 두 객체의 세로 거리

	float		fCX = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;	//두 객체의 가로 크기
	float		fCY = (pDest->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;	//두 객체의 세로 크기

	if (fCX > fWidth && fCY > fHeight)
	{
		*_pWidth = fCX - fWidth;		//fCX는 두 객체의 실질적인 가로 크기이고 fWidth는 두 객체의 거리이다.
		*_pHeight = fCY - fHeight;		//fCY는 두 객체의 실질적인 세로 크기이고 fHeight는 두 객체의 거리이다.

		return true;
	}
	return false;
}
