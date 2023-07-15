#pragma once

#ifndef __STAGESLIME_H_
#define __STAGESLIME_H_

#include "Scene.h"
class CStageSlime : public CScene
{
public:
	CStageSlime();
	~CStageSlime();

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
