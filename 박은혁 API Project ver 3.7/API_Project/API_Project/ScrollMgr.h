#pragma once

#ifndef __SCROLLMGR_H_
#define __SCROLLMGR_H_

//스크롤 매니저를 싱글톤으로 만들었다.
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();

public:										//이니셜라이즈,업데이트,레이트업데이트,렌더,릴리즈 등등 지금 당장 필요하진 않지만 언제 사용될지 모르니 일단 만듬
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC _DC);
	void		Release(void);

public:
	float			Get_ScrollX() { return m_fScrollX; }			//Get_Instance를 통하여 Get_ScrollX()를 부르고 m_fScrollX의 정보를 받고 있다.
	float			Get_ScrollY() { return m_fScrollY; }			//Get_Instance를 통하여 Get_ScrollY()를 부르고 m_fScrollY의 정보를 받고 있다.
	void			Set_ScrollX(float _fX) { m_fScrollX += _fX; }	//m_fScrollX에 좌표를 넣고 있다.
	void			Set_ScrollY(float _fY) { m_fScrollY += _fY; }	//m_fScrollY에 좌표를 넣고 있다.
	void			Scroll_Lock(void);

public:
	static	CScrollMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CScrollMgr;

		return m_pInstance;
	}

	static	void		Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CScrollMgr*	m_pInstance;
	static float				m_fScrollX;
	static float				m_fScrollY;
};

#endif