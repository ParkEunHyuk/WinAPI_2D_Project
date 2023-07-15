#pragma once

#ifndef __OVERWORLD_H_
#define __OVERWORLD_H_

#include "Scene.h"
class COverWorld : public CScene
{
public:
	COverWorld();
	virtual ~COverWorld();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	Key_Input(void);

public:
	void Load_Data();

//public:
//	void	Load_Date(void);
};

#endif