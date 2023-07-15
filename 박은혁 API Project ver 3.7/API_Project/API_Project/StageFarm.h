#pragma once

#ifndef __STAGEFARM_H_
#define __STAGEFARM_H_

#include "Scene.h"
class CStageFarm : public CScene
{
public:
	CStageFarm();
	~CStageFarm();

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

#endif // !