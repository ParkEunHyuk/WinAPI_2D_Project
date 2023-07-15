#pragma once
#ifndef __STRUCT_H_
#define __STRUCT_H_

typedef	struct tagInfo
{
	float		fX;
	float		fY;
	float		fCX;
	float		fCY;
}INFO;

typedef struct tagStamina     //��ü���� ü�� �� ���ݷ�
{
	int			iMaxHp;			// �ִ�ü��
	int			iAtt;			// ������

}STAMINA;

typedef struct tagLinePos //���� �׸��� �ʿ��� ��ǥ���� ����ü
{
	float		fX;
	float		fY;

	tagLinePos()
	{
		ZeroMemory(this, sizeof(tagLinePos));
	}
	tagLinePos(float _X, float _Y)
		:fX(_X), fY(_Y)
	{

	}
}LINEPOS;

typedef struct tagLineInfo //����Ʈ ��ǥ�� ����Ʈ ��ǥ Info�� ������ �׸���. ��Ʈ�� ����� ������� ������ ��
{
	LINEPOS		tLeftPos;
	LINEPOS		tRightPos;

	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOS& _tLeft, LINEPOS& _tRight)
		: tLeftPos(_tLeft), tRightPos(_tRight)
	{	}
}LINEINFO;

typedef	struct	tagRectPos
{
	float		fX;
	float		fY;

	tagRectPos()
	{
		ZeroMemory(this, sizeof(tagRectPos));
	}
	tagRectPos(float _X, float _Y)
		: fX(_X), fY(_Y)
	{

	}

}RECTPOS;

typedef struct tagFrame
{
	int iFrameStart;
	int iFrameEnd;
	int iFrameScene;

	DWORD dwFrameSpeed;
	DWORD dwFrameTime;
}FRAME;


template<typename T>
void Safe_Delete(T& Temp)
{
	delete Temp;
	Temp = nullptr;
}


class CDeleteObj
{
public:
	CDeleteObj() {}
	~CDeleteObj() {}

public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (nullptr != Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

class CDeleteMap
{
public:
	CDeleteMap() {}
	~CDeleteMap() {}

public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (nullptr != Temp.second)
		{
			delete Temp.second;
			Temp.second = nullptr;
		}
	}
};

class CTag_Finder
{
public:
	CTag_Finder(const TCHAR* pString)
		: m_pString(pString) {}

public:
	template<typename T>
	bool	operator()(T& Temp)
	{
		return !lstrcmp(m_pString, Temp.first);
	}

private:
	const TCHAR*		m_pString;
};

//Y������ �� ����

//                                   Src�� �÷��̾��� �����Ѵٸ�!
template<typename T>
bool CompareY(T Dest, T Src)
{
	return Dest->Get_Info().fY < Src->Get_Info().fY;
}

#endif