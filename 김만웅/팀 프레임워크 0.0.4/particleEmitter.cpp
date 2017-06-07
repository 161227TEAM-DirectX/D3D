#include "stdafx.h"
#include "particleEmitter.h"

void particleEmitter::init(DWORD particleNum, float emission, float liveTimeMin, float liveTimeMax, const D3DXVECTOR3 & velocityMin, const D3DXVECTOR3 & velocityMax, const D3DXVECTOR3 & accelMin, const D3DXVECTOR3 & accelMax, const VEC_COLOR & colors, const VEC_SCALE & scales, float scaleMin, float scaleMax, LPDIRECT3DTEXTURE9 pParticleTexture, bool bLocal)
{
	//해당 파티클 렌더의 총 파티클 수
	_ParticleNum = particleNum;

	//총 파티클 수만 큼 버텍스 배열을 만든다
	_pParticleVertices = new PARTICLE_VERTEX[_ParticleNum];

	//파티클 객체 생성
	_pParticles = new particle[_ParticleNum];

	//초당 생성량
	_fEmissionPerSec = emission;

	//초당 생성량 따른 발생 간격
	_fEmissionIntervalTime = 1.0f / _fEmissionPerSec;

	//지난 시간도 0
	_fEmissionDeltaTime = 0.0f;

	//발생 여부 false
	_bEmission = false;

	//컬러 대입
	_Colors.clear();
	for (int i = 0; i < colors.size(); i++)
	{
		_Colors.push_back(colors[i]);
	}

	//사이즈 대입
	_Scales.clear();
	for (int i = 0; i < scales.size(); i++)
	{
		_Scales.push_back(scales[i]);
	}

	//시작 라이브 타임 대입
	_fStartLiveTimeMin = liveTimeMin;
	_fStartLiveTimeMax = liveTimeMax;

	//시작 속도 대입
	_StartVelocityMin = velocityMin;
	_StartVelocityMax = velocityMax;

	//시작 가속 대입
	_StartAccelateMin = accelMin;
	_StartAccelateMax = accelMax;

	//시작 스케일 대입
	_fStartScaleMin = scaleMin;
	_fStartScaleMax = scaleMax;

	//시작순번 초기화
	_dwParticleCount = 0;

	//Texture 참조
	_pTex = pParticleTexture;

	_bLocal = bLocal;

	EmissionType = PZERO;
}

void particleEmitter::release()
{
	SAFE_DELETE_ARRAY(_pParticles);
	SAFE_DELETE_ARRAY(_pParticleVertices);
}

void particleEmitter::baseObjectUpdate()
{
	//모든 파티클 업데이트
	for (int i = 0; i < _ParticleNum; i++)
	{
		_pParticles[i].Update();
	}

	//너는 지금 발생 상태니?
	if (_bEmission)
	{
		// 하나 발생하고 지난 시간
		_fEmissionDeltaTime += _timeDelta;

		while (_fEmissionDeltaTime >= _fEmissionIntervalTime)
		{
			_fEmissionDeltaTime -= _fEmissionIntervalTime;
			//파티클 하나 발사
			StartOneParticle();
		}
	}
}

void particleEmitter::baseObjectRender()
{
	//그릴 파티클 수
	DWORD drawParticleNum = 0;

	for (int i = 0; i < _ParticleNum; i++) 
	{
		//해당파티클이 활성화 중이니?
		if (_pParticles[i].isLive()) 
		{
			//해당 파티클의 정보를 얻는다.
			_pParticles[i].GetParticleVertex(
				_pParticleVertices + drawParticleNum,
				_Colors, _Scales);

			drawParticleNum++;
		}
	}

	_device->SetRenderState(D3DRS_LIGHTING, false);							//라이팅을 끈다.
	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);					//포인트 스플라이트 활성화
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, true);					//포인트의 스케일값 먹이겠다.
	_device->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDWORD(0.0f));		//포인트의 최소 크기 ( 화면기준 )
	_device->SetRenderState(D3DRS_POINTSIZE_MAX, FloatToDWORD(500.0f));		//포인트의 최대 크기 ( 화면기준 )
	//_device->SetRenderState( D3DRS_POINTSIZE, FloatToDWORD( 10.0f ) );	//포인트 기준 사이즈 ( 정점의 포인트 사이즈가 있으면 무시되는듯 );
	_device->SetRenderState(D3DRS_ZWRITEENABLE, false);						//z 버퍼의 쓰기를 막는다.

	//출력되는 POINT size 
	//finalSize = viewportHeight * pointSize *  sqrt( 1 / ( A + B(D) + C(D^2) )  );
	//아래와 같이 하면 자연스러운 거리에 따른 스케일이 나타남
	_device->SetRenderState(D3DRS_POINTSCALE_A, FloatToDWORD(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_B, FloatToDWORD(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_C, FloatToDWORD(1.0f));

	//알파 블렌딩 세팅
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//Texture 의 값과 Diffuse 여기서는 정점컬러의 알파값 을 섞어 최종 출력을 한다.
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

	D3DXMATRIXA16 matWorld;

	if (_bLocal == false) D3DXMatrixIdentity(&matWorld);
	else matWorld = this->_transform->GetFinalMatrix();

	_device->SetTransform(D3DTS_WORLD, &matWorld);

	//파티클 Texture 세팅
	_device->SetTexture(0, _pTex);

	//파티클 정점 출력
	_device->SetFVF(PARTICLE_VERTEX::FVF);
	_device->DrawPrimitiveUP(
		D3DPT_POINTLIST,
		drawParticleNum,
		_pParticleVertices,
		sizeof(PARTICLE_VERTEX));

	//파티클 그리고 난후 후처리
	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	_device->SetTexture(0, NULL);
}

void particleEmitter::StartEmission()
{
	_bEmission = true;
}

void particleEmitter::StopEmission()
{
	_bEmission = false;
}

void particleEmitter::Burst(int num, float minSpeed, float maxSpeed, float maxLife, float minLife)
{
	for (int i = 0; i < num; i++)
	{
		D3DXVECTOR3 randVec(
			RandomFloatRange(-1.0f, 1.0f),
			RandomFloatRange(-1.0f, 1.0f),
			RandomFloatRange(-1.0f, 1.0f)
		);

		D3DXVec3Normalize(&randVec, &randVec);
		randVec *= RandomFloatRange(minSpeed, maxSpeed);

		StartOneParticle(randVec, RandomFloatRange(maxLife, minLife));
	}
}

void particleEmitter::StartOneParticle()
{
	//라이브 타임 랜덤
	float liveTime = RandomFloatRange(_fStartLiveTimeMin, _fStartLiveTimeMax);

	//파티클이 생성될 위치
	D3DXVECTOR3 position;

	//로컬이 아닌경우 자신의 월드 위치에서 시작하고 
	if (this->_bLocal == false)
	{
		position = this->_transform->GetWorldPosition();
	}
	//로컬인 경우 0 에서 시작한다.
	else
	{
		position = D3DXVECTOR3(0, 0, 0);
	}
	//생성 범위에 따른 추가 위치....
	if (EmissionType == PATICLE_EMISSION_TYPE::SPHERE)
	{
		//랜덤벡터
		D3DXVECTOR3 randDir(
			RandomFloatRange(-1.0f, 1.0f),
			RandomFloatRange(-1.0f, 1.0f),
			RandomFloatRange(-1.0f, 1.0f));

		D3DXVec3Normalize(&randDir, &randDir);

		//랜덤거리
		float randDistance = RandomFloatRange(0, SphereEmissionRange);

		//추가위치
		position += randDir * randDistance;
	}
	else if (EmissionType == PATICLE_EMISSION_TYPE::SPHERE_OUTLINE)
	{
		//랜덤벡터
		D3DXVECTOR3 randDir(
			RandomFloatRange(-1.0f, 1.0f),
			RandomFloatRange(-1.0f, 1.0f),
			RandomFloatRange(-1.0f, 1.0f));

		D3DXVec3Normalize(&randDir, &randDir);

		//추가위치
		position += randDir * SphereEmissionRange;
	}
	else if (EmissionType == PATICLE_EMISSION_TYPE::BOX)
	{
		//랜덤벡터
		D3DXVECTOR3 randDir(
			RandomFloatRange(MinEmissionRangeX, MaxEmissionRangeX),
			RandomFloatRange(MinEmissionRangeY, MaxEmissionRangeY),
			RandomFloatRange(MinEmissionRangeZ, MaxEmissionRangeZ));

		//추가위치
		position += randDir;
	}

	//벡터 랜덤
	D3DXVECTOR3 velocity;
	velocity.x = RandomFloatRange(_StartVelocityMin.x, _StartVelocityMax.x);
	velocity.y = RandomFloatRange(_StartVelocityMin.y, _StartVelocityMax.y);
	velocity.z = RandomFloatRange(_StartVelocityMin.z, _StartVelocityMax.z);

	D3DXVECTOR3 accelation;
	accelation.x = RandomFloatRange(_StartAccelateMin.x, _StartAccelateMax.x);
	accelation.y = RandomFloatRange(_StartAccelateMin.y, _StartAccelateMax.y);
	accelation.z = RandomFloatRange(_StartAccelateMin.z, _StartAccelateMax.z);

	//자신의 월드 매트릭스를 가지고 온다.
	if (_bLocal == false)
	{
		D3DXMATRIXA16 matWorld = this->_transform->GetFinalMatrix();
		D3DXVec3TransformNormal(&velocity, &velocity, &matWorld);
		D3DXVec3TransformNormal(&accelation, &accelation, &matWorld);
	}

	//스케일도 랜덤
	float scale = RandomFloatRange(_fStartScaleMin, _fStartScaleMax);

	//순번대로 발생시킨다
	_pParticles[_dwParticleCount].Start(
		liveTime, &position, &velocity, &accelation, scale);

	//다음 파티클을 위한 순번 증가
	_dwParticleCount++;
	if (_dwParticleCount == this->_ParticleNum)
	{
		_dwParticleCount = 0;
	}
}

void particleEmitter::StartOneParticle(D3DXVECTOR3 dir, float life)
{
	float liveTime = life;

	//파티클이 생성될 위치
	D3DXVECTOR3 position;
	if (this->_bLocal == false)
	{
		position = _transform->GetWorldPosition();
	}
	else
	{
		position = D3DXVECTOR3(0, 0, 0);
	}

	//벡터 랜덤
	D3DXVECTOR3 velocity;
	velocity.x = dir.x;
	velocity.y = dir.y;
	velocity.z = dir.z;

	D3DXVECTOR3 accelation;
	accelation.x = RandomFloatRange(_StartAccelateMin.x, _StartAccelateMax.x);
	accelation.y = RandomFloatRange(_StartAccelateMin.y, _StartAccelateMax.y);
	accelation.z = RandomFloatRange(_StartAccelateMin.z, _StartAccelateMax.z);

	//자신의 월드 매트릭스를 가지고 온다.
	if (_bLocal == false)
	{
		D3DXMATRIXA16 matWorld = this->_transform->GetFinalMatrix();
		D3DXVec3TransformNormal(&velocity, &velocity, &matWorld);
		D3DXVec3TransformNormal(&accelation, &accelation, &matWorld);
	}

	//스케일도 랜덤
	float scale = RandomFloatRange(_fStartScaleMin, _fStartScaleMax);

	//발생시킨다
	_pParticles[_dwParticleCount].Start(
		liveTime, &position, &velocity, &accelation, scale);

	_dwParticleCount++;
	if (_dwParticleCount == this->_ParticleNum)
	{
		_dwParticleCount = 0;
	}
}