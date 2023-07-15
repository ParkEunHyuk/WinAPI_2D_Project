#pragma once

#ifndef __LOGO_H_
#define __LOGO_H_
#include "Scene.h"
class CLogo : public CScene
{
public:
	CLogo();
	~CLogo();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	HWND		m_hVideo; //비디오 사용할지 안할지 모르겠으나 일단 써둠
};

#endif // !1