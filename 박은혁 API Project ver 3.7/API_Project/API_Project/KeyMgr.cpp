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
	// 이전에 눌림이 없고 현재 눌렸을 경우

	if (!m_bKeyState[_Key] && (GetAsyncKeyState(_Key) & 0x8000))	//m_bKeyState[_Key]는 false이기 때문에 !를 붙이면 true가 되고 GetAsyncKeyState는 키가 눌릴 경우 true가 된다.
	{
		m_bKeyState[_Key] = !m_bKeyState[_Key];						//그 상황에서 !m_bKeyState[_Key]하여 나온 true를 m_bKeyState[_Key]에 대입하고 있다.
		return true;
	}

	if (m_bKeyState[_Key] && !(GetAsyncKeyState(_Key) & 0x8000))	//이것도 마찬가지로 true 상태인 m_bKeyState[_Key]와 눌리지 않을 경우 false인 GetAsyncKeyState()에 !를 붙여 true로 만들고
		m_bKeyState[_Key] = !m_bKeyState[_Key];						//true 상태인 m_bKeyState[_Key]에 !를 붙여 false로 바꾸고 그걸 다시 대입한다.

	return false;
}																	//키 다운은 이 행동으로 인해 키가 눌렸을 경우에만 작동하게 만들었다.

bool CKeyMgr::Key_Up(int _Key)										//키 업도 키 다운과 비슷한 맥락으로 이어진다. Key_Down은 윗 if문부터 시작했지만.
{																	//키 업은 밑 if문부터 시작한다. tmi)그냥 간단하게 bool로 Key_Down와 Key_Up를 구현했다.
	// 이전에 눌림이 있고 현재 눌리지 않았을 경우

	if (m_bKeyState[_Key] && !(GetAsyncKeyState(_Key) & 0x8000))
	{
		m_bKeyState[_Key] = !m_bKeyState[_Key];
		return true;
	}

	if (!m_bKeyState[_Key] && (GetAsyncKeyState(_Key) & 0x8000))
		m_bKeyState[_Key] = !m_bKeyState[_Key];


	return false;
}

