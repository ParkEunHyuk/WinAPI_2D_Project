#pragma once

#ifndef __SCENE_H_
#define __SCENE_H_
class CScene abstract  //abstract는 추상클래스라는걸 명시하는것
{
public:
	CScene();
	virtual ~CScene();

public:

	virtual void		Initialize(void)PURE;
	virtual int			Update(void)PURE;
	virtual void		Late_Update(void)PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release(void)PURE;
};

#endif