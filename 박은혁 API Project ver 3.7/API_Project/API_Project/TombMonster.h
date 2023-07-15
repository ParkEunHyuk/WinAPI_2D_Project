#pragma once

#ifndef __TOMBMONSTER_H_
#define __TOMBMONSTER_H_
#include "Obj.h"

class CTombMonster : public CObj
{
public:
	enum STATE { INTRO, LEFT, RIGHT, ATTACK,DIE };
public:
	CTombMonster();
	~CTombMonster();

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

	int						m_iDownAttackCount;

	DWORD					m_tAttackCoolTime;
	////////////////////////////////////////

	DWORD					m_tTimeHit;

	////////////////////////////////////////������ ���Ͽ� ���� ����
	bool					m_bIntroEnd;
	bool					m_bIntroSwitch;
	bool					m_bDIESwitch;
	bool					m_bFrameCount;

	////////////////////////////////////////// ����
	int						m_iSoundCount;
	DWORD					m_tTimeSound;

};

#endif
