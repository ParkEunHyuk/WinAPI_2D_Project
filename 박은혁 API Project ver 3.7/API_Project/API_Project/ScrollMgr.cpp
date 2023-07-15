#include "stdafx.h"
#include "ScrollMgr.h"

//����ƽ���� �����ϰ� �ִ� ���̴�.
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

	// WINCX - TILEX * TILECX�� ������ 
	if (WINCX - MAPCX > m_fScrollX) //�÷��̾ ���������� ���ٸ� ��ũ���� �������� ���� ������ ���� ������ �ȴ�.
		m_fScrollX = WINCX - MAPCX; //WINCX�� ���� �ʴ´ٸ� Ÿ���� ������ �κ��� ����� �� ��ũ���� �����. �׷��� �Ǹ� �� ����� ���δ�.

	if (0 < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCY - MAPCY > m_fScrollY) //�� ����� ����. ���� X�� Y�� ������ ��
		m_fScrollY = WINCY - MAPCY;
}
