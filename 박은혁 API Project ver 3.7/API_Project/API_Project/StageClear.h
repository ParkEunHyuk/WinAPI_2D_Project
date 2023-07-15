#pragma once

#ifndef __STAGECLEAR_H_
#define __STAGECLEAR_H_

#include "Scene.h"
class CStageClear : public CScene
{
public:
	CStageClear();
	~CStageClear();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

#endif