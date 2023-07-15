#pragma once

#ifndef __TILE_H_
#define __TILE_H_
#include "Obj.h"
class CTile : public CObj //�ϴ� ������� �־����� Ÿ�� �����ҵ�
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