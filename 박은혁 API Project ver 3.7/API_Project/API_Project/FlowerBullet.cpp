#include "stdafx.h"
#include "FlowerBullet.h"
#include "Manager.h"


CFlowerBullet::CFlowerBullet()
{
}


CFlowerBullet::~CFlowerBullet()
{
	Release();
}

void CFlowerBullet::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 5.f;
	m_fDistance = 5.f;
	m_fAngle = 0.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FlowerMonster/FlowerBullet.bmp", L"FlowerBullet");

	m_pFrameKey = L"FlowerBullet";

	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_OBJ;
}

int CFlowerBullet::Update(void)
{
	if (true == m_bDead)
	{
		return OBJ_DEAD;
	}
	if (BULLET::LEFT == m_eDir)
	{

		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY = m_tInfo.fY + (m_fDistance * sinf(m_fAngle * PI / 180.f));
	}

	m_fAngle += m_fSpeed;


	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CFlowerBullet::Late_Update(void)
{
	if (-100			>	m_tRect.left ||
		WINCX + 100 	<	m_tRect.right ||
		0			>	m_tRect.top ||
		WINCY		<	m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CFlowerBullet::Render(HDC hDC)
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
		int(m_tRect.left ),	//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hMemDC,							// 비트맵 정보를 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 7,8인자 비트맵을 출력할 시작좌표
		m_tFrame.iFrameScene * (int)m_tInfo.fCY,
		50,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		50,
		RGB(237, 28, 36));

}

void CFlowerBullet::Release(void)
{
}
