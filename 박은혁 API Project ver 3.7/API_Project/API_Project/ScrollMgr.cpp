#include "stdafx.h"
#include "ScrollMgr.h"

//스태틱들을 선언하고 있는 중이다.
CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

float CScrollMgr::m_fScrollX = 0.f;
float CScrollMgr::m_fScrollY = 0.f;

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
	Release();
}

void CScrollMgr::Initialize(void)
{
}

void CScrollMgr::Update(void)
{
}

void CScrollMgr::Late_Update(void)
{
}

void CScrollMgr::Render(HDC _DC)
{
}

void CScrollMgr::Release(void)
{
}

void CScrollMgr::Scroll_Lock(void)
{

	if (0 < m_fScrollX)
		m_fScrollX = 0.f;

	// WINCX - TILEX * TILECX는 음수임 
	if (WINCX - MAPCX > m_fScrollX) //플레이어가 오른쪽으로 간다면 스크롤은 왼쪽으로 가기 때문에 점점 음수가 된다.
		m_fScrollX = WINCX - MAPCX; //WINCX를 쓰지 않는다면 타일의 마지막 부분이 사라질 때 스크롤이 멈춘다. 그렇게 되면 뒷 배경이 보인다.

	if (0 < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCY - MAPCY > m_fScrollY) //윗 내용과 같다. 단지 X와 Y의 차이일 뿐
		m_fScrollY = WINCY - MAPCY;
}
