#pragma once

#ifndef __MYBITMAP_H_
#define __MYBITMAP_H_
class CMyBitmap
{
public:
	CMyBitmap();
	~CMyBitmap();

public:
	HDC		Get_MemDC() { return m_hMemDC; }
	void	Load_Bmp(const TCHAR* pFilePath);
	void	Release(void);

private:
	HDC			m_hMemDC;

	HBITMAP		m_hBitBmp;
	HBITMAP		m_hOldBmp;
};

#endif