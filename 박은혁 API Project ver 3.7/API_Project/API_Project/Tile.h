#pragma once

#ifndef __TILE_H_
#define __TILE_H_
#include "Obj.h"
class CTile : public CObj //일단 배웠으니 넣었지만 타일 사용안할듯
{
public:
	CTile();
	virtual ~CTile();
public:
	const int&		Get_Option(void)const { return m_iOption; }
	void			Set_TileOption(int _iOption);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int				m_iOption;
};

#endif