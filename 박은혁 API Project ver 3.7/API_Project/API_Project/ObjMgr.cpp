#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Player.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;

/////////////////////////////////////////////////////// test
bool		CObjMgr::m_bSlimeClear = false;
bool		CObjMgr::m_bFarmClear = false;
bool		CObjMgr::m_bFlowerClear = false;

CObjMgr::CObjMgr()
{

}


CObjMgr::~CObjMgr()
{
}

CObj * CObjMgr::Get_Target(OBJID::ID _eID, CObj * pObj)
{
	CObj*		pTarget = nullptr;

	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[_eID])
	{
		float fWidth = iter->Get_Info().fX - pObj->Get_Info().fX;			//_eID와 pObj의 가로 길이
		float fHeight = iter->Get_Info().fY - pObj->Get_Info().fY;			//_eID와 pObj의 세로 길이

		float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);		//피타고라스의 정리를 이용하여 빗변의 길이를 구함

		//더 가까운 표적을 찾는중
		if (fDistance > fDiagonal || !pTarget)								//최초 1회는 !pTarget로 실행되며 fDistance에 fDiagonal값이 들어간다.
		{																	//그리고 _eID의 fDiagonal들 중에서 fDistance가  커지는 순간 표적을 바꾼다.
			pTarget = iter;
			fDistance = fDiagonal;
		}

	}

	return pTarget;
}

void CObjMgr::Add_Object(OBJID::ID eID, CObj * pObj)
{
	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		auto& iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end();)
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty()) 
				break;

			RENDERID eRender = iter->Get_RenderID(); //렌더의 아이디를 지정
			m_RenderSort[eRender].push_back(iter);	//렌더의 Y정렬을 위해서 존재
		}
	}

	//CCollisionMgr::Collision_Rect(m_ObjList[OBJID::BULLET], m_ObjList[OBJID::MONSTER]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::BULLET], m_ObjList[OBJID::MONSTER]);
	//CCollisionMgr::Collision_RectEx(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER]);
	//CCollisionMgr::Collision_Bullet(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_BULLET], 1);
	//CCollisionMgr::Collision_Bullet(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_COLLISION_BULLET], 1);

	CCollisionMgr::Collision_RectEx(m_ObjList[OBJID::MYRECT], m_ObjList[OBJID::OVER_PLAYER]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJID::MYRECT], m_ObjList[OBJID::PLAYER]);
	CCollisionMgr::Collision_Rect_Stage(m_ObjList[OBJID::WORLDUI], m_ObjList[OBJID::OVER_PLAYER]);

	//콜리전 몬스터 테스트중
	//CCollisionMgr::Collision_Bullet(m_ObjList[OBJID::MONSTER], m_ObjList[OBJID::PLAYER_BULLET], 1);
	//CCollisionMgr::Collision_Bullet(m_ObjList[OBJID::MONSTER_COLLISION_BULLET], m_ObjList[OBJID::PLAYER_BULLET], 1);

	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_BULLET], 1);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_COLLISION_BULLET], 1);

	CCollisionMgr::Collision_Monster(m_ObjList[OBJID::MONSTER], m_ObjList[OBJID::PLAYER_BULLET], 1);
	CCollisionMgr::Collision_Monster(m_ObjList[OBJID::MONSTER_COLLISION_BULLET], m_ObjList[OBJID::PLAYER_BULLET], 1);
}

void CObjMgr::Render(HDC m_DC)
{	
	for (int i = 0; i < RENDER_END; ++i)  //Y소팅하여 m_RenderSort에 서로 크기를 비교하여 우선순위를 정한다.
	{
		m_RenderSort[i].sort(CompareY<CObj*>);

		for (auto& iter : m_RenderSort[i])//만약에 iter가 없다면 읽지 말라고 예외처리하려면?
		{
			iter->Render(m_DC);
		}
		m_RenderSort[i].clear();		// 매 프레임마다 기존 그룹의 내용을 지워준다.
	}

	////////////////////////////위에 코드가 될때가있고 안될때가 있음

	//for (int i = 0; i < OBJID::END; ++i)
	//{
	//	for (auto& iter : m_ObjList[i])
	//		iter->Render(m_DC);
	//}
	//
}

void CObjMgr::Release(void) 
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj());
		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJID::ID eID) // 특정 OBJ ID를 지우는것
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}

void CObjMgr::Delete_Render(RENDERID eRender)
{
	for (auto& iter : m_RenderSort[eRender])
	{
		iter = nullptr;
	}
	m_RenderSort[eRender].clear();

}

//오픈셋 조절
void CObjMgr::Stage_OffSet(OBJID::ID eID)
{
	for (auto& iter : m_ObjList[eID])
	{
		dynamic_cast<CPlayer*>(iter)->Set_OffSet(true);
	}
}

void CObjMgr::Set_SlimeClear(bool _bClear)
{
	m_bSlimeClear = _bClear;
}

void CObjMgr::Set_FarmClear(bool _bClear)
{
	m_bFarmClear = _bClear;
}

void CObjMgr::Set_FlowerClear(bool _bClear)
{
	m_bFlowerClear = _bClear;
}
