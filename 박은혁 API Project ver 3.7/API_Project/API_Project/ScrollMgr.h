#pragma once

#ifndef __SCROLLMGR_H_
#define __SCROLLMGR_H_

//��ũ�� �Ŵ����� �̱������� �������.
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();

public:										//�̴ϼȶ�����,������Ʈ,����Ʈ������Ʈ,����,������ ��� ���� ���� �ʿ����� ������ ���� ������ �𸣴� �ϴ� ����
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC _DC);
	void		Release(void);

public:
	float			Get_ScrollX() { return m_fScrollX; }			//Get_Instance�� ���Ͽ� Get_ScrollX()�� �θ��� m_fScrollX�� ������ �ް� �ִ�.
	float			Get_ScrollY() { return m_fScrollY; }			//Get_Instance�� ���Ͽ� Get_ScrollY()�� �θ��� m_fScrollY�� ������ �ް� �ִ�.
	void			Set_ScrollX(float _fX) { m_fScrollX += _fX; }	//m_fScrollX�� ��ǥ�� �ְ� �ִ�.
	void			Set_ScrollY(float _fY) { m_fScrollY += _fY; }	//m_fScrollY�� ��ǥ�� �ְ� �ִ�.
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