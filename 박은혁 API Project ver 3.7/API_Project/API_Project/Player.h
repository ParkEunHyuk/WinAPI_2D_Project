#pragma once

#ifndef __PLAYER_H_
#define __PLAYER_H_
#include "Obj.h"

class CPlayer :public CObj
{
public:
	enum STATE { IDLE, WALK_LEFT, WALK_RIGHT, UP ,PLAYER_LEFT_DOWN, PLAYER_RIGHT_DOWN, JUMP, STOP_SHOOT, UP_SHOOT, RIGHT_RUN_SHOOT, LEFT_RUN_SHOOT, LEFT_DOWN_SHOOT, RIGHT_DOWN_SHOOT, PLAYER_HIT, END };

public:
	CPlayer();
	~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	//����� �������� ���߿� �������� �ٲ� �ٸ��� ����ǰ� ������!
public:
	void Set_OffSet(bool OffSet_Switch);

private:
	void		Key_Input(void);
	void		Jumping(void);
	void		OffSet(void);
	void		State_Change(void);
	void		Player_Hit(void);



private:
	POINT					m_tGun;			//�ҷ� �߻� ��ġ

	bool					m_bJump;
	float					m_fJumpY;
	float					m_fJumpPower;
	float					m_fTime;
	float					m_fGravity; //test

	int						m_iOffSetX;
	int						m_iOffSetY;
	bool					m_bOff_Set;    //�������� ���� ���¼� true �� false����

	STATE					m_ePreState;
	STATE					m_eCurState;
/*
	bool					m_bStretch = true;
*/
	bool					m_bDownSwitch;

	//                      �÷��̾��� �浹�� üũ�ϰ� �ִ�.
	bool					m_bPlayerHitCheck;

	//						�÷��̾��� �浹 ���� �����ð��� �˷��ְ� �ִ�.
	DWORD					m_tTimePhoenix;

	/////////////////////////////////////// ����
	int						m_iSoundCount;
	DWORD					m_tSoundTime;

	///////////////////////////////////////////�÷��̾� ü��
	int						m_PullHp;
};

#endif