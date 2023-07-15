#pragma once
#ifndef __MAINWORLD_H
#define __MAINWORLD_H

class CMainWorld
{
public:
	CMainWorld();
	~CMainWorld();

public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render();
	void Release(void);

private:
	HDC			m_DC;
	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[256];
};

#endif