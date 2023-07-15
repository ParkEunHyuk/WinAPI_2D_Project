#pragma once

#ifndef __QUEST_H_
#define __QUEST_H_
#include "Obj.h"
class CQuest : public CObj
{
	enum STATE { START, PROGRESS, SUCCESS };
public:
	CQuest();
	~CQuest();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	void		Key_Input(void);
	void		State_Change(void);

private:
	STATE					m_ePreState;
	STATE					m_eCurState;

};

#endif