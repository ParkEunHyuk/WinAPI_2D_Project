#pragma once
#include "Scene.h"
class CMyEdit : public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

private:
	void		Key_Input(void);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

