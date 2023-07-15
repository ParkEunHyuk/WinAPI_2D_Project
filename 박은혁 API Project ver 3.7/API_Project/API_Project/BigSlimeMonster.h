#pragma once

#ifndef __BIGSLIMEMONSTER_H_
#define __BIGSLIMEMONSTER_H_
#include "Obj.h"
class CBigSlimeMonster : public CObj
{
public:
	enum STATE { INTRO, LEFT, RIGHT, DIE, ATTACK};
public:
	CBigSlimeMonster();
	~CBigSlimeMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Jumping(void);      //������ ���� �Լ�

	void		Attacking(void);   // ���� ƨ��� �� ���� ���������� �غ����

	void		HIT_CoolTime(void);  // �÷��̾ ������ ��ü�� �浹���� ��� ��Ʈ ��Ÿ��

	void		LookPlayer(void); //�÷��̾��� �Ÿ��� �˱� ���� ����

private:
	void		State_Change(void);

	STATE					m_ePreState;
	STATE					m_eCurState;
	STATE					m_eTempState;


	/////////////////������ ���� ������
	bool					m_bJump;
	float					m_fJumpY;
	float					m_fJumpPower;
	float					m_fTime;
	float					m_fGravity;
	//////////////////////////////////////

	///////////////////////���ݿ� ���� ������
	int						m_iJumpCount;
	bool					m_bAttack;
	bool					m_PlayerSpot;

	DWORD					m_tAttackCoolTime;
	////////////////////////////////////////

	DWORD					m_tTimeHit;

	////////////////////////////////////////������ ���Ͽ� ���� ����
	bool					m_bIntroEnd;

	////////////////////////////////////////���� ����ġ
	bool					m_bDeadSwitch;

	// ���� �������ʹ� �ݸ��� �Ѿ˷� �Ǿ� �ִ�. �� �÷��̾�� �浹�Ǹ� ���ó���� �ȴ�. �׷��� Obj�� m_tDead�� ����������� ���� ������ ���������!
	bool					m_bNewTypeDeadSwitch;


	////////////////////////////���浹 ���� �ذ�
	bool					m_bLEFT;
	bool					m_bRIGHT;

	//
	int						m_iDeadCount;

	////////////////////////////////////////// ����
	int						m_iSoundCount;
	DWORD					m_tTimeSound;
};

#endif