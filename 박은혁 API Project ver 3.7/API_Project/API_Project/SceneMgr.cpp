#include "stdafx.h"
#include "SceneMgr.h"

#include "SceneInclude.h"
//Scene과 관련된 헤더들은 여기에 모여있음

// SceneMgr.h에도 헤더가 있음 둘 다 가지고 있으니 하나만 정해서 인크루드할 것

CSceneMgr*			CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	:m_pScene(nullptr)
{
}
CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eScene)
{
	if (nullptr != m_pScene)		// 왜 지우는지 생각을 합시다!
		Safe_Delete(m_pScene);		// 씬이 계속 쌓이기 때문!

	m_eScene = eScene;

	switch (eScene)
	{
	case SCENE_LOGO:
		m_pScene = new CLogo;
		break;

	case SCENE_MENU:
		m_pScene = new CMyMenu;
		break;

	case SCENE_OVERWORLD:
		m_pScene = new COverWorld;
		break;
	case SCENE_STAGEFARM:
		m_pScene = new CStageFarm;
		break;
	case SCENE_STAGEFLOWER:
		m_pScene = new CStageFlower;
		break;
	case SCENE_STAGESLIME:
		m_pScene = new CStageSlime;
		break;
	case SCENE_STAGECLEAR:
		m_pScene = new CStageClear;
		break;
	case SCENE_EDIT:
		m_pScene = new CMyEdit;
		break;
	}

	m_pScene->Initialize();
}

void CSceneMgr::Update(void)
{
	if (nullptr != m_pScene)
		m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	if (nullptr != m_pScene)
		m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC _DC)
{
	if (nullptr != m_pScene)
		m_pScene->Render(_DC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}
