#include "stdafx.h"
#include "VineTwo.h"
#include "Manager.h"
#include "BlueMonster.h"


CVineTwo::CVineTwo()
{
}


CVineTwo::~CVineTwo()
{
	Release();
}

void CVineTwo::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 150.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/Vine.bmp", L"Vine");

	m_pFrameKey = L"Vine";

	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 400;
	m_tFrame.dwFrameTime = GetTickCount();

	m_tTime = GetTickCount();
	m_tTimeBlueMonster = GetTickCount();
	iCount = 0;

	/*m_eRenderGroup = RENDER_BACK;*/
}

int CVineTwo::Update(void)
{
	if (m_tFrame.iFrameEnd != m_tFrame.iFrameStart)
	{
		if (6 == m_tFrame.iFrameStart)
		{
			if (iCount == 0)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_COLLISION_BULLET, CAbstractFactory<CBlueMonster>::Create(m_tInfo.fX, (m_tInfo.fY - 75.f)));
				m_tTimeBlueMonster = GetTickCount();
				++iCount;
			}
		}
		Update_Rect();
		Move_Frame();
	}

	if (m_tTime + 4000 <= GetTickCount())
	{
		return OBJ_DEAD;
	}
	return OBJ_NOEVENT;
}

void CVineTwo::Late_Update(void)
{
}

void CVineTwo::Render(HDC hDC)
{
#ifdef _DEBUG
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
#endif // !_DEBUG

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hMemDC,							// 비트맵 정보를 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8인자 비트맵을 출력할 시작좌표
		m_tFrame.iFrameScene * (int)m_tInfo.fCY,
		50,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		150,
		RGB(237, 28, 36));
}

void CVineTwo::Release(void)
{
}
