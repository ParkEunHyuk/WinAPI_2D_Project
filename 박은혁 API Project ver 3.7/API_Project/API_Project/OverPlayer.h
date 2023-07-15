#pragma once

#ifndef __OVERPLAYER_H_
#define __OVERPLAYER_H_
#include "Obj.h"
class COverPlayer :public CObj
{
public:
	enum STATE{IDLE,WALK_UP, WALK_DOWN,WALK_LEFT,WALK_RIGHT, END };
public:
	COverPlayer();
	~COverPlayer();

public: //override�� C++11 ���Ŀ� ���� Ű����� �����Լ��� ��ӹ޾Ƽ� �������̵� �ߴٴ� ���̴�.
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
	void		OffSet(void);
	void		State_Change(void);

private:

	int						m_iOffSetX;
	int						m_iOffSetY;

	STATE					m_eCurState; // ������ ����
	STATE					m_ePreState; // ������ ����ġ��
};

#endif