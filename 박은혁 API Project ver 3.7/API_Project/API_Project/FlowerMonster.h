#pragma once
#ifndef __FLOWERMONSTER_H_
#define __FLOWERMONSTER_H_

#include "Obj.h"
class CFlowerMonster : public CObj
{
public:
	enum STATE { INTRO,IDLE, SEED_BULLET, ACORN_BULLET, FACEATTACK, DIE };

public:
	CFlowerMonster();
	~CFlowerMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		LookPlayer();

private:
	void		FlowerPattern(void);
	void		SeedFire(void);
	void		AcornFire(void);
	void		FaceAttack(void);

public:
	void		State_Change(void);

private:
	POINT					m_tGun;

	STATE					m_ePreState;
	STATE					m_eCurState;

	int						m_iRand;

	bool					m_bIntroEnd;			//��Ʈ�θ� �����ϴ� ����
																			
	DWORD					m_tTimePattern;			//��ü�� ������ �����ϴ� ����
	bool					m_bPatternSwitch;		//��ü�� ������ ����ġ�� ����
	bool					m_RandomSwitch;			//��ü�� ���� ����ġ
	int						m_iPatternRandom;       //��ü�� ������
	int						m_iPatternCount;		//��ü�� �ݺ� Ƚ��


	DWORD					m_tTimeSeedBullet;		//��ü�� ���� �� �ϳ�
	bool					m_bSeedBulletSwitch;	//���� ����ġ
	//int						m_iSeedCount;			//���� ���� Ƚ��

	DWORD					m_tTimeAcornBullet;
	bool					m_bAcornBulletSwitch;
	//int						m_iAcornCount;

	DWORD					m_tTimeFaceAttack;
	bool					m_bFaceSwitch;
	int						m_iRandomFace;


	POINT					m_tGunAcorn;			//�� ������ǥ 
	float					m_fGun_Distance; //�� ����

									 ////////////////////////////////////////// ����
	int						m_iSoundCount;
	DWORD					m_tTimeSound;

};

#endif
