#pragma once

#ifndef __LITTLESLIMEMONSTER_H_
#define __LITTLESLIMEMONSTER_H_
#include "Obj.h"
class CLittleSlimeMonster : public CObj
{
public:
	enum STATE { INTRO, LEFT,RIGHT,ATTACK, };
public:
	CLittleSlimeMonster();
	~CLittleSlimeMonster();

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

	////////////////////////////////////////// ����
	int						m_iSoundCount;
	DWORD					m_tTimeSound;
	
};
#endif
