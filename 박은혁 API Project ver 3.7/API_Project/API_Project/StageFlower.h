#pragma once

#ifndef __STAGEFLOWER_H_
#define __STAGEFLOWER_H_

#include "Scene.h"
class CStageFlower: public CScene
{
public:
	CStageFlower();
	~CStageFlower();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	Key_Input(void);

public:
	void Load_Data();

};

#endif
