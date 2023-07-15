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

	bool					m_bIntroEnd;			//인트로를 관리하는 변수
																			
	DWORD					m_tTimePattern;			//객체의 패턴을 관리하는 변수
	bool					m_bPatternSwitch;		//객체의 패턴을 스위치로 만듬
	bool					m_RandomSwitch;			//객체의 랜덤 스위치
	int						m_iPatternRandom;       //객체의 랜덤성
	int						m_iPatternCount;		//객체의 반복 횟수


	DWORD					m_tTimeSeedBullet;		//객체의 패턴 중 하나
	bool					m_bSeedBulletSwitch;	//패턴 스위치
	//int						m_iSeedCount;			//패턴 동작 횟수

	DWORD					m_tTimeAcornBullet;
	bool					m_bAcornBulletSwitch;
	//int						m_iAcornCount;

	DWORD					m_tTimeFaceAttack;
	bool					m_bFaceSwitch;
	int						m_iRandomFace;


	POINT					m_tGunAcorn;			//건 시작좌표 
	float					m_fGun_Distance; //건 길이

									 ////////////////////////////////////////// 사운드
	int						m_iSoundCount;
	DWORD					m_tTimeSound;

};

#endif
