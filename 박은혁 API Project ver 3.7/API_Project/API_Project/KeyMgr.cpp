#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr*	CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::Key_Pressing(int _Key)
{
	if (GetAsyncKeyState(_Key) & 0x8000)
		return true;

	return false;
}

bool CKeyMgr::Key_Down(int _Key)
{
	// ������ ������ ���� ���� ������ ���

	if (!m_bKeyState[_Key] && (GetAsyncKeyState(_Key) & 0x8000))	//m_bKeyState[_Key]�� false�̱� ������ !�� ���̸� true�� �ǰ� GetAsyncKeyState�� Ű�� ���� ��� true�� �ȴ�.
	{
		m_bKeyState[_Key] = !m_bKeyState[_Key];						//�� ��Ȳ���� !m_bKeyState[_Key]�Ͽ� ���� true�� m_bKeyState[_Key]�� �����ϰ� �ִ�.
		return true;
	}

	if (m_bKeyState[_Key] && !(GetAsyncKeyState(_Key) & 0x8000))	//�̰͵� ���������� true ������ m_bKeyState[_Key]�� ������ ���� ��� false�� GetAsyncKeyState()�� !�� �ٿ� true�� �����
		m_bKeyState[_Key] = !m_bKeyState[_Key];						//true ������ m_bKeyState[_Key]�� !�� �ٿ� false�� �ٲٰ� �װ� �ٽ� �����Ѵ�.

	return false;
}																	//Ű �ٿ��� �� �ൿ���� ���� Ű�� ������ ��쿡�� �۵��ϰ� �������.

bool CKeyMgr::Key_Up(int _Key)										//Ű ���� Ű �ٿ�� ����� �ƶ����� �̾�����. Key_Down�� �� if������ ����������.
{																	//Ű ���� �� if������ �����Ѵ�. tmi)�׳� �����ϰ� bool�� Key_Down�� Key_Up�� �����ߴ�.
	// ������ ������ �ְ� ���� ������ �ʾ��� ���

	if (m_bKeyState[_Key] && !(GetAsyncKeyState(_Key) & 0x8000))
	{
		m_bKeyState[_Key] = !m_bKeyState[_Key];
		return true;
	}

	if (!m_bKeyState[_Key] && (GetAsyncKeyState(_Key) & 0x8000))
		m_bKeyState[_Key] = !m_bKeyState[_Key];


	return false;
}

