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
					/*���ó�� ��ü �����ؼ� ��ȭ
						���̳��� ĳ��Ʈ�� ������ Ʈ����!
						if�� ������ �� ��ȯ!
						����!*/
				
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

	GdiTransparentBlt(hDC,				//	���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),				//	2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		int(m_tRect.top  + iScrollY),
		(int)m_tInfo.fCX,				//	4, 5���� ���� ���� X,Y�� ���̸� ����	
		(int)m_tInfo.fCY,
		hMemDC,							// ��Ʈ�� ������ ������ �ִ� DC
		m_iDrawID * (int)m_tInfo.fCX,	// 7,8���� ��Ʈ���� ����� ������ǥ
		0,
		(int)m_tInfo.fCX,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
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
