#pragma once

#ifndef __STAGEBUTTON_H_
#define __STAGEBUTTON_H_
#include "Obj.h"
class CStageButton : public CObj
{
public:
	CStageButton();
	virtual ~CStageButton();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	//test¿ë
public:
	void Set_StageSwitch(bool Switch);

public:
	bool		m_bStageSwitch;
};

#endif