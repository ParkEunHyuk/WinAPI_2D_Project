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

public: //override는 C++11 이후에 나온 키워드로 가상함수가 상속받아서 오버라이딩 했다는 뜻이다.
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

	STATE					m_eCurState; // 프레임 동작
	STATE					m_ePreState; // 프레임 스위치용
};

#endif