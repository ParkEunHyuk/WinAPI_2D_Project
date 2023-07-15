#pragma once

#ifndef __OBJ_H_
#define __OBJ_H_

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY);		//���� �� �� ��� ��ǥ�� ������ �� ����     �ܺο��� ��ǥ���� ����
	void		Set_PosX(float _fX);				//��ǥ�� X���� �־��						�ܺο��� X��ǥ���� ����
	void		Set_PosY(float _fY);				//��ǥ�� Y���� �־��						�ܺο��� Y��ǥ���� ����
	void		Set_Dead(void);						//�׾����� ��Ҵ��� ����					�ܺο��� ��Ҵ��� �׾����� ����
	void		Set_Angle(float _fAngle);			//��� ������ �� �� ����					�ܺο��� � ������ ���� ����
	void		Set_FrameKey(TCHAR* pFrameKey);		//� ������Ű�� ���� ����					�ܺο��� � ������Ű�� ���� ����
	void		Set_DrawID(int _iDrawID);			//���° �̹������� ����					�ܺο��� ���° �̹����� ���� ����
	void		Set_Hp(int _Damage);				//��ü�� ü���� ������

	void		Set_Collsion(bool _Collsion);		//��ü�� �浹 ���θ� üũ�Ѵ�. �Ѿ��� �浹�ƴ��� üũ�Ѵ�. !

	//test���Դϴ�.
	void		Set_InfoTest(LINEINFO _LineInfo);   //���ο� ���� ����

	//���� �������� ������
	void		Set_Target(CObj* _pTarget);			//��ǥ�� �־��
	void		Set_Direction(BULLET::DIR _eDir);	//�Ѿ��� ����

public:
	const	RECT&		Get_Rect(void) const { return m_tRect; }	//�ܺο��� m_tRect(�׸����)�� ����
	const	INFO&		Get_Info(void) const { return m_tInfo; }	//�ܺο��� m_tInfo(�����)�� ����
	const	int&		Get_DrawID(void) const { return m_iDrawID; }//�ܺο��� ���° �̹������� ����

	const	bool&		Get_m_bCollsion(void) const { return m_bCollsion; } //�Ѿ˵� �浹 ���θ� Ȯ���ϰ� ���� ***********�߿��մϴ�!!!

	//Y������ �� ����
	const	RENDERID	Get_RenderID(void)	const { return m_eRenderGroup; }//�ܺο��� ������ ������ ����

public:
	void		Update_Rect(void);					//��Ʈ�� �׽� ������Ʈ �����ְ� ����
	void		Move_Frame(void);					//�������� �������� �����ϰ� ����

//���������Լ��� ������ �߻� Ŭ������ �Ҹ����. PURE�� = 0���� Define.h�� �����Ѵ�.
public:
	virtual void Initialize(void)PURE;				//���������Լ��� �ʱ�ȭ�� ���
	virtual int Update(void)PURE;					//���������Լ��� ���� �� ������ ���
	virtual void Late_Update(void)PURE;				//���������Լ��� �̺�Ʈ �߻��� ���
	virtual void Render(HDC hDC)PURE;				//���������Լ��� �̹����� ���
	virtual void Release(void)PURE;					//���������Լ��� ��ü �Ҹ��� ���



protected:
	RECT		m_tRect;		//�׸���� ��Ʈ
	INFO		m_tInfo;		//����� ����
	STAMINA		m_tStamina;		//��ü�� ü�� �� ����

	BULLET::DIR m_eDir;			//�Ѿ��� ������ ����ü�� ��Ÿ��
	CObj*		m_pTarget;		//Ÿ���� ������ CObj*�� ����

	float		m_fAngle;		//��ü�� ����
	float		m_fSpeed;		//��ü�� �ӵ�
	float		m_fDistance;	//��ü�� �Ÿ�

	bool		m_bDead;		//��ü�� ��������
	bool		m_bCollsion;	//��ü�� �浹����

	int			m_iDrawID;		//�̹����� ���° �׸��� �������� ����

	TCHAR*		m_pFrameKey;	//map���� ������ �������� Ű��
	FRAME		m_tFrame;		//�̹����� ������
	bool		m_bFrameDieCheck; //��ü�� �Ҹ� ����

	//Y������ �� ����
	RENDERID		m_eRenderGroup; //�̹����� ����
};


#endif // !__OBJ_H_
