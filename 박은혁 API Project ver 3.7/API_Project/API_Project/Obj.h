#pragma once

#ifndef __OBJ_H_
#define __OBJ_H_

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY);		//생성 할 때 어느 좌표에 생성할 지 정함     외부에서 좌표값을 넣음
	void		Set_PosX(float _fX);				//좌표의 X값만 넣어둠						외부에서 X좌표값만 넣음
	void		Set_PosY(float _fY);				//좌표의 Y값만 넣어둠						외부에서 Y좌표값만 넣음
	void		Set_Dead(void);						//죽었는지 살았는지 정함					외부에서 살았는지 죽었는지 넣음
	void		Set_Angle(float _fAngle);			//어느 각도로 할 지 정함					외부에서 어떤 각도로 할지 넣음
	void		Set_FrameKey(TCHAR* pFrameKey);		//어떤 프레임키로 할지 정함					외부에서 어떤 프레임키로 할지 넣음
	void		Set_DrawID(int _iDrawID);			//몇번째 이미지인지 정함					외부에서 몇번째 이미지로 할지 넣음
	void		Set_Hp(int _Damage);				//객체의 체력을 조절함

	void		Set_Collsion(bool _Collsion);		//객체의 충돌 여부를 체크한다. 총알이 충돌됐는지 체크한다. !

	//test중입니다.
	void		Set_InfoTest(LINEINFO _LineInfo);   //라인에 관한 내용

	//자주 쓰이지는 않을듯
	void		Set_Target(CObj* _pTarget);			//목표를 넣어둠
	void		Set_Direction(BULLET::DIR _eDir);	//총알의 방향

public:
	const	RECT&		Get_Rect(void) const { return m_tRect; }	//외부에서 m_tRect(그리기용)를 받음
	const	INFO&		Get_Info(void) const { return m_tInfo; }	//외부에서 m_tInfo(연산용)를 받음
	const	int&		Get_DrawID(void) const { return m_iDrawID; }//외부에서 몇번째 이미지인지 받음

	const	bool&		Get_m_bCollsion(void) const { return m_bCollsion; } //총알들 충돌 여부를 확인하고 있음 ***********중요합니다!!!

	//Y소팅할 때 쓰임
	const	RENDERID	Get_RenderID(void)	const { return m_eRenderGroup; }//외부에서 렌더의 순서를 받음

public:
	void		Update_Rect(void);					//렉트를 항시 업데이트 시켜주고 있음
	void		Move_Frame(void);					//프레임의 움직임을 관리하고 있음

//순수가상함수가 있으면 추상 클래스로 불리운다. PURE는 = 0으로 Define.h에 존재한다.
public:
	virtual void Initialize(void)PURE;				//순수가상함수로 초기화를 담당
	virtual int Update(void)PURE;					//순수가상함수로 생성 및 삭제를 담당
	virtual void Late_Update(void)PURE;				//순수가상함수로 이벤트 발생을 담당
	virtual void Render(HDC hDC)PURE;				//순수가상함수로 이미지를 담당
	virtual void Release(void)PURE;					//순수가상함수로 객체 소멸을 담당



protected:
	RECT		m_tRect;		//그리기용 렉트
	INFO		m_tInfo;		//연산용 인포
	STAMINA		m_tStamina;		//객체의 체력 및 공격

	BULLET::DIR m_eDir;			//총알의 방향을 열거체로 나타냄
	CObj*		m_pTarget;		//타겟의 정보를 CObj*로 받음

	float		m_fAngle;		//객체의 각도
	float		m_fSpeed;		//객체의 속도
	float		m_fDistance;	//객체의 거리

	bool		m_bDead;		//객체의 생존여부
	bool		m_bCollsion;	//객체의 충돌여부

	int			m_iDrawID;		//이미지의 몇번째 그림을 가져올지 정함

	TCHAR*		m_pFrameKey;	//map으로 저장한 프레임의 키값
	FRAME		m_tFrame;		//이미지의 프레임
	bool		m_bFrameDieCheck; //객체의 소멸 여부

	//Y소팅할 때 쓰임
	RENDERID		m_eRenderGroup; //이미지의 순서
};


#endif // !__OBJ_H_
