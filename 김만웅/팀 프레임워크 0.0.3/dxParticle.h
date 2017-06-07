#pragma once
//전처리기 선언

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
	
	//float		sizeRatio;			//크기비율(스케일)
};

struct tagDxParticleEX
{
	D3DXVECTOR3	position;
	D3DCOLOR	color;
	D3DXVECTOR2 uv;

};


//파티클의 속성들
struct tagDxAttribute
{
	//transform		trans;				//트랜스폼
	D3DXVECTOR3		posCenter;			//평면 파티클용 - 중심점
	D3DXVECTOR3		FinalPos;			//최종 위치

	D3DXVECTOR3		position;			// 월드내 파티클 위치
	D3DXVECTOR3		posDirectVel;		// 위치 방향성 속도
	D3DXVECTOR3		posDirection;		// 방향성
	float			posDirectSpeed;		// 방향성 속도
	D3DXVECTOR3		velocity;			// 파티클의 속도(초당 이동 단위)
	D3DXVECTOR3		acceleration;		// 파티클의 가속(초당 이동 단위)
	float			lifeTime;			// 파티클이 소멸할 때까지 유지되는 시간.
	float			age;				// 파티클의 현재 나이 
	float			size;				// 파티클 현재 크기
	float			sizeInit;			// 파티클 초기 크기
	float			sizeEnd;			// 파티클 나중 크기
	D3DXCOLOR		color;				// 파티클의 현재색
	D3DXCOLOR		colorInit;			// 파티클의 초기색
	D3DXCOLOR		colorFade;			// 파티클의 컬러가 시간의 흐름에 따라 퇴색하는 방법
	bool			isAlive;			// 파티클이 생존할 경우 TRUE, 소멸한 경우 FALSE
	D3DXVECTOR3		preCircleSpeed;		// 전의 원 스피드 (1초당)
	D3DXVECTOR3		circleSpeed;		// 원 스피드 (1초당)
	//D3DXVECTOR3		circleRotX;		// 원 회전 X
	//D3DXVECTOR3		circleRotY;		// 원 회전 Y
	//D3DXVECTOR3		circleRotZ;		// 원 회전 Z
	D3DXVECTOR3		circelAngleSpeed;	// 원각도 속도
	D3DXVECTOR3		circleAngle;		// 원각도
	D3DXVECTOR3		radius;				// 반지름 현재값
	D3DXVECTOR3		radiusInit;			// 반지름 초기값
	D3DXVECTOR3		radiusEnd;			// 반지름 마지막값

	D3DXVECTOR3		rotateAngle;		//회전 각도
	D3DXVECTOR3		rotateAngleSpeed;	//회전 각도 속도

	float			horizontal;
	float			vertical;


	D3DXVECTOR2		UV0;
	D3DXVECTOR2		UV1;
	D3DXVECTOR2		UV2;
	D3DXVECTOR2		UV3;
	


	//초기화
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


//최소 최대
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

//파티클의 속성들
struct tagDxAttributeMaxMin
{
	//좌표
	tagMaxMin	 positionX;
	tagMaxMin	 positionY;
	tagMaxMin	 positionZ;
	bool radPosOn;

	//속도
	tagMaxMin	 velocityX;
	tagMaxMin	 velocityY;
	tagMaxMin	 velocityZ;
	bool radVelOn;

	//방향 속도
	//tagMaxMin directonVel;
	//bool radDirectionVelOn;

	tagMaxMin posDirectionVel;
	bool radPosDirectionVelOn;

	//가속
	tagMaxMin	 accelerationX;
	tagMaxMin	 accelerationY;
	tagMaxMin	 accelerationZ;
	bool radAccelOn;

	//유지시간
	tagMaxMin	lifeTime;
	bool radLifeOn;
	
	//초기색깔
	tagMaxMin	 colorInitR;
	tagMaxMin	 colorInitG;
	tagMaxMin	 colorInitB;
	bool radColorOn;

	//소멸색깔
	tagMaxMin	 colorFadeR;
	tagMaxMin	 colorFadeG;
	tagMaxMin	 colorFadeB;
	bool radColorFadeOn;

	//알파값
	tagMaxMin	 alphaInit;
	tagMaxMin	 alphaFade;
	bool radAlphaInitOn;
	bool radAlphaFadeOn;

	//사이즈
	tagMaxMin sizeInit;
	tagMaxMin sizeEnd;
	bool radSizeInitOn;
	bool radSizeEndOn;

	//원 시작각도
	tagMaxMin circleStartAngleX;
	tagMaxMin circleStartAngleY;
	tagMaxMin circleStartAngleZ;

	//원 각도 회전
	tagMaxMin radiusInitX;
	tagMaxMin radiusInitY;
	tagMaxMin radiusInitZ;

	//원 각도회전 변형
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

	//위치 좌표 구형-반지름
	tagMaxMin posSphereRadius;

	//회전 -이미터용
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

	//가로 세로
	float vertical;
	float horizontal;

	//UV프레임
	int frameMaxNumX;
	int frameMaxNumY;
	int	totalFrameNum;

	bool animationOn;

	int reactivateNum;


	//초기화
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

//그래프용
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