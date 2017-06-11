#pragma once
//��ó���� ����

const DWORD ParticleFVF = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE;
//const DWORD ParticleFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
#define PARTICLE_FVF (ParticleFVF)
//| D3DFVF_PSIZE

const DWORD ParticleExFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
#define ParticleExFVF (ParticleExFVF)

enum PTC_POSITION_TYPE
{
	PTC_DEFAULT,
	PTC_SPHERE,

};

#define PTC_DEFAULT			PTC_DEFAULT
#define PTC_SPHERE			PTC_SPHERE

struct tagDxParticle
{
	D3DXVECTOR3	position;
	float		size;
	D3DCOLOR	color;
	
	//float		sizeRatio;			//ũ�����(������)
};

struct tagDxParticleEX
{
	D3DXVECTOR3	position;
	D3DCOLOR	color;
	D3DXVECTOR2 uv;

};


//��ƼŬ�� �Ӽ���
struct tagDxAttribute
{
	//transform		trans;				//Ʈ������
	D3DXVECTOR3		posCenter;			//��� ��ƼŬ�� - �߽���
	D3DXVECTOR3		FinalPos;			//���� ��ġ

	D3DXVECTOR3		position;			// ���峻 ��ƼŬ ��ġ
	D3DXVECTOR3		posDirectVel;		// ��ġ ���⼺ �ӵ�
	D3DXVECTOR3		posDirection;		// ���⼺
	float			posDirectSpeed;		// ���⼺ �ӵ�
	D3DXVECTOR3		velocity;			// ��ƼŬ�� �ӵ�(�ʴ� �̵� ����)
	D3DXVECTOR3		acceleration;		// ��ƼŬ�� ����(�ʴ� �̵� ����)
	float			lifeTime;			// ��ƼŬ�� �Ҹ��� ������ �����Ǵ� �ð�.
	float			age;				// ��ƼŬ�� ���� ���� 
	float			size;				// ��ƼŬ ���� ũ��
	float			sizeInit;			// ��ƼŬ �ʱ� ũ��
	float			sizeEnd;			// ��ƼŬ ���� ũ��
	D3DXCOLOR		color;				// ��ƼŬ�� �����
	D3DXCOLOR		colorInit;			// ��ƼŬ�� �ʱ��
	D3DXCOLOR		colorFade;			// ��ƼŬ�� �÷��� �ð��� �帧�� ���� ����ϴ� ���
	bool			isAlive;			// ��ƼŬ�� ������ ��� TRUE, �Ҹ��� ��� FALSE
	D3DXVECTOR3		preCircleSpeed;		// ���� �� ���ǵ� (1�ʴ�)
	D3DXVECTOR3		circleSpeed;		// �� ���ǵ� (1�ʴ�)
	//D3DXVECTOR3		circleRotX;		// �� ȸ�� X
	//D3DXVECTOR3		circleRotY;		// �� ȸ�� Y
	//D3DXVECTOR3		circleRotZ;		// �� ȸ�� Z
	D3DXVECTOR3		circelAngleSpeed;	// ������ �ӵ�
	D3DXVECTOR3		circleAngle;		// ������
	D3DXVECTOR3		radius;				// ������ ���簪
	D3DXVECTOR3		radiusInit;			// ������ �ʱⰪ
	D3DXVECTOR3		radiusEnd;			// ������ ��������

	D3DXVECTOR3		rotateAngle;		//ȸ�� ����
	D3DXVECTOR3		rotateAngleSpeed;	//ȸ�� ���� �ӵ�

	float			horizontal;
	float			vertical;


	D3DXVECTOR2		UV0;
	D3DXVECTOR2		UV1;
	D3DXVECTOR2		UV2;
	D3DXVECTOR2		UV3;
	


	//�ʱ�ȭ
	tagDxAttribute()
	{
		position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		posDirection = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		posDirectVel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		posDirectSpeed = 0.0f;
		velocity = posDirectVel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		/*velocity = D3DXVECTOR3(RandomFloatRange(-1.0f, 1.0f),
								RandomFloatRange(0.5f, 1.5f),
								RandomFloatRange(-1.0f, 1.0f));*/
		//directionVel = 1.0f;
		acceleration = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		size = 1.0f;
		lifeTime = 5.0f;
		age = 0.0f;									
		color = 0xffffffff;
		colorFade = 0xffffffff;
		isAlive = false;
		preCircleSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		circleSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		circleAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		radius = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		rotateAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rotateAngleSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		horizontal = 1.0f;
		vertical = 1.0f;

		FinalPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


		UV0 = D3DXVECTOR2(0.0f, 0.0f);
		UV1 = D3DXVECTOR2(1.0f, 0.0f);
		UV2 = D3DXVECTOR2(0.0f, 1.0f);
		UV3 = D3DXVECTOR2(1.0f, 1.0f);

	}
};


//�ּ� �ִ�
struct tagMaxMin
{
	float Min;
	float Max;

	tagMaxMin(float inMin = 0.0f, float inMax = 0.0f)
	{
		Min = inMin;
		Max = inMax;
	};

};

//��ƼŬ�� �Ӽ���
struct tagDxAttributeMaxMin
{
	//��ǥ
	tagMaxMin	 positionX;
	tagMaxMin	 positionY;
	tagMaxMin	 positionZ;
	bool radPosOn;

	//�ӵ�
	tagMaxMin	 velocityX;
	tagMaxMin	 velocityY;
	tagMaxMin	 velocityZ;
	bool radVelOn;

	//���� �ӵ�
	//tagMaxMin directonVel;
	//bool radDirectionVelOn;

	tagMaxMin posDirectionVel;
	bool radPosDirectionVelOn;

	//����
	tagMaxMin	 accelerationX;
	tagMaxMin	 accelerationY;
	tagMaxMin	 accelerationZ;
	bool radAccelOn;

	//�����ð�
	tagMaxMin	lifeTime;
	bool radLifeOn;
	
	//�ʱ����
	tagMaxMin	 colorInitR;
	tagMaxMin	 colorInitG;
	tagMaxMin	 colorInitB;
	bool radColorOn;

	//�Ҹ����
	tagMaxMin	 colorFadeR;
	tagMaxMin	 colorFadeG;
	tagMaxMin	 colorFadeB;
	bool radColorFadeOn;

	//���İ�
	tagMaxMin	 alphaInit;
	tagMaxMin	 alphaFade;
	bool radAlphaInitOn;
	bool radAlphaFadeOn;

	//������
	tagMaxMin sizeInit;
	tagMaxMin sizeEnd;
	bool radSizeInitOn;
	bool radSizeEndOn;

	//�� ���۰���
	tagMaxMin circleStartAngleX;
	tagMaxMin circleStartAngleY;
	tagMaxMin circleStartAngleZ;

	//�� ���� ȸ��
	tagMaxMin radiusInitX;
	tagMaxMin radiusInitY;
	tagMaxMin radiusInitZ;

	//�� ����ȸ�� ����
	tagMaxMin radiusEndX;
	tagMaxMin radiusEndY;
	tagMaxMin radiusEndZ;

	tagMaxMin circleAngleSpeedX;
	tagMaxMin circleAngleSpeedY;
	tagMaxMin circleAngleSpeedZ;
	
	bool circleX_On;
	bool circleY_On;
	bool circleZ_On;

	bool radiusEndX_On;
	bool radiusEndY_On;
	bool radiusEndZ_On;

	//��ġ ��ǥ ����-������
	tagMaxMin posSphereRadius;

	//ȸ�� -�̹��Ϳ�
	tagMaxMin rotateInitX;
	tagMaxMin rotateInitY;
	tagMaxMin rotateInitZ;

	bool rotateInitX_On;
	bool rotateInitY_On;
	bool rotateInitZ_On;

	tagMaxMin rotateSpeedX;
	tagMaxMin rotateSpeedY;
	tagMaxMin rotateSpeedZ;

	bool rotateSpeedX_On;
	bool rotateSpeedY_On;
	bool rotateSpeedZ_On;

	//���� ����
	float vertical;
	float horizontal;

	//UV������
	int frameMaxNumX;
	int frameMaxNumY;
	int	totalFrameNum;

	bool animationOn;

	int reactivateNum;


	//�ʱ�ȭ
	tagDxAttributeMaxMin()
	{
		radPosOn = false;
		radVelOn = false;
		radAccelOn = false;
		radLifeOn = false;

		radColorOn = false;
		radColorFadeOn = false;

		radAlphaInitOn = false;
		radAlphaFadeOn = false;

		radSizeInitOn = false;
		radSizeEndOn = false;

		circleX_On = false;
		circleY_On = false;
		circleZ_On = false;

		radiusEndX_On = false;
		radiusEndY_On = false;
		radiusEndZ_On = false;

		radPosDirectionVelOn = false;

		rotateInitX_On = false;
		rotateInitY_On = false;
		rotateInitZ_On = false;

		rotateSpeedX_On = false;
		rotateSpeedY_On = false;
		rotateSpeedZ_On = false;

		vertical = 1.0f;
		horizontal = 1.0f;

		frameMaxNumX = 0;
		frameMaxNumY = 0;
		totalFrameNum = 0;

		animationOn = false;

		reactivateNum = 1;
	}

};

//�׷�����
struct tagDxGraph
{
	float point;
	float value;
	tagMaxMin radValue;

	tagDxGraph(float inPoint = 0.0f, float min =0.0f, float max = 0.0f)
	{
		point = inPoint;
		radValue = tagMaxMin(min, max);
		value = 0.0;
	}

};