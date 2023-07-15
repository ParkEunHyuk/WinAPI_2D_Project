#include "stdafx.h"
#include "StageButton.h"
#include "Manager.h"
#include "Quest.h"


CStageButton::CStageButton()
	:m_bStageSwitch(false)
{
}


CStageButton::~CStageButton()
{
	Release();
}

void CStageButton::Initialize(void)
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 90.f;

	m_eRenderGroup = RENDER_BACK;
}

int CStageButton::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CStageButton::Late_Update(void)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	if(m_bStageSwitch)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('Z'))
			{
				if (!lstrcmp(L"WorldFarm", m_pFrameKey))
				{
					CSceneMgr::Get_Instance()->Scene_Change(SCENE_STAGEFARM);
				}
				else if (!lstrcmp(L"WorldFlower", m_pFrameKey))
				{
					CSceneMgr::Get_Instance()->Scene_Change(SCENE_STAGEFLOWER);
				}
				else if (!lstrcmp(L"WorldSlime", m_pFrameKey))
				{
					CSceneMgr::Get_Instance()->Scene_Change(SCENE_STAGESLIME);
				}
				else if (!lstrcmp(L"WorldHome", m_pFrameKey))
				{
					CObjMgr::Get_Instance()->Add_Object(OBJID::UI, CAbstractFactory<CQuest>::Create((538+ 60), (738.f + 100)));
					/*브라보처럼 객체 생성해서 대화
						다이나믹 캐스트로 값들이 트루라면!
						if문 돌려서 씬 전환!
						엔딩!*/
				
				}
				return;
			}
		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;
}

void CStageButton::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),				//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top  + iScrollY),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hMemDC,							// 비트맵 정보를 가지고 있는 DC
		m_iDrawID * (int)m_tInfo.fCX,	// 7,8인자 비트맵을 출력할 시작좌표
		0,
		(int)m_tInfo.fCX,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		(int)m_tInfo.fCY,
		RGB(255, 242, 0));
#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
#endif // !_DEBUG
}

void CStageButton::Release(void)
{
}

void CStageButton::Set_StageSwitch(bool _Switch)
{
	m_bStageSwitch = _Switch;
}
