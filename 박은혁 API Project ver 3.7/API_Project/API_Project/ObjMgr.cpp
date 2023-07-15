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
		float fWidth = iter->Get_Info().fX - pObj->Get_Info().fX;			//_eID�� pObj�� ���� ����
		float fHeight = iter->Get_Info().fY - pObj->Get_Info().fY;			//_eID�� pObj�� ���� ����

		float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);		//��Ÿ����� ������ �̿��Ͽ� ������ ���̸� ����

		//�� ����� ǥ���� ã����
		if (fDistance > fDiagonal || !pTarget)								//���� 1ȸ�� !pTarget�� ����Ǹ� fDistance�� fDiagonal���� ����.
		{																	//�׸��� _eID�� fDiagonal�� �߿��� fDistance��  Ŀ���� ���� ǥ���� �ٲ۴�.
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

			RENDERID eRender = iter->Get_RenderID(); //������ ���̵� ����
			m_RenderSort[eRender].push_back(iter);	//������ Y������ ���ؼ� ����
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

	//�ݸ��� ���� �׽�Ʈ��
	//CCollisionMgr::Collision_Bullet(m_ObjList[OBJID::MONSTER], m_ObjList[OBJID::PLAYER_BULLET], 1);
	//CCollisionMgr::Collision_Bullet(m_ObjList[OBJID::MONSTER_COLLISION_BULLET], m_ObjList[OBJID::PLAYER_BULLET], 1);

	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_BULLET], 1);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_COLLISION_BULLET], 1);

	CCollisionMgr::Collision_Monster(m_ObjList[OBJID::MONSTER], m_ObjList[OBJID::PLAYER_BULLET], 1);
	CCollisionMgr::Collision_Monster(m_ObjList[OBJID::MONSTER_COLLISION_BULLET], m_ObjList[OBJID::PLAYER_BULLET], 1);
}

void CObjMgr::Render(HDC m_DC)
{	
	for (int i = 0; i < RENDER_END; ++i)  //Y�����Ͽ� m_RenderSort�� ���� ũ�⸦ ���Ͽ� �켱������ ���Ѵ�.
	{
		m_RenderSort[i].sort(CompareY<CObj*>);

		for (auto& iter : m_RenderSort[i])//���࿡ iter�� ���ٸ� ���� ����� ����ó���Ϸ���?
		{
			iter->Render(m_DC);
		}
		m_RenderSort[i].clear();		// �� �����Ӹ��� ���� �׷��� ������ �����ش�.
	}

	////////////////////////////���� �ڵ尡 �ɶ����ְ� �ȵɶ��� ����

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

void CObjMgr::Delete_ID(OBJID::ID eID) // Ư�� OBJ ID�� ����°�
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

//���¼� ����
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
