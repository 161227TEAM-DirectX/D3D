#include "stdafx.h"
#include "particleEmitter.h"

void particleEmitter::init(DWORD particleNum, float emission, float liveTimeMin, float liveTimeMax, const D3DXVECTOR3 & velocityMin, const D3DXVECTOR3 & velocityMax, const D3DXVECTOR3 & accelMin, const D3DXVECTOR3 & accelMax, const VEC_COLOR & colors, const VEC_SCALE & scales, float scaleMin, float scaleMax, LPDIRECT3DTEXTURE9 pParticleTexture, bool bLocal)
{
	//�ش� ��ƼŬ ������ �� ��ƼŬ ��
	_ParticleNum = particleNum;

	//�� ��ƼŬ ���� ŭ ���ؽ� �迭�� �����
	_pParticleVertices = new PARTICLE_VERTEX[_ParticleNum];

	//��ƼŬ ��ü ����
	_pParticles = new particle[_ParticleNum];

	//�ʴ� ������
	_fEmissionPerSec = emission;

	//�ʴ� ������ ���� �߻� ����
	_fEmissionIntervalTime = 1.0f / _fEmissionPerSec;

	//���� �ð��� 0
	_fEmissionDeltaTime = 0.0f;

	//�߻� ���� false
	_bEmission = false;

	//�÷� ����
	_Colors.clear();
	for (int i = 0; i < colors.size(); i++)
	{
		_Colors.push_back(colors[i]);
	}

	//������ ����
	_Scales.clear();
	for (int i = 0; i < scales.size(); i++)
	{
		_Scales.push_back(scales[i]);
	}

	//���� ���̺� Ÿ�� ����
	_fStartLiveTimeMin = liveTimeMin;
	_fStartLiveTimeMax = liveTimeMax;

	//���� �ӵ� ����
	_StartVelocityMin = velocityMin;
	_StartVelocityMax = velocityMax;

	//���� ���� ����
	_StartAccelateMin = accelMin;
	_StartAccelateMax = accelMax;

	//���� ������ ����
	_fStartScaleMin = scaleMin;
	_fStartScaleMax = scaleMax;

	//���ۼ��� �ʱ�ȭ
	_dwParticleCount = 0;

	//Texture ����
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
	//��� ��ƼŬ ������Ʈ
	for (int i = 0; i < _ParticleNum; i++)
	{
		_pParticles[i].Update();
	}

	//�ʴ� ���� �߻� ���´�?
	if (_bEmission)
	{
		// �ϳ� �߻��ϰ� ���� �ð�
		_fEmissionDeltaTime += _timeDelta;

		while (_fEmissionDeltaTime >= _fEmissionIntervalTime)
		{
			_fEmissionDeltaTime -= _fEmissionIntervalTime;
			//��ƼŬ �ϳ� �߻�
			StartOneParticle();
		}
	}
}

void particleEmitter::baseObjectRender()
{
	//�׸� ��ƼŬ ��
	DWORD drawParticleNum = 0;

	for (int i = 0; i < _ParticleNum; i++) 
	{
		//�ش���ƼŬ�� Ȱ��ȭ ���̴�?
		if (_pParticles[i].isLive()) 
		{
			//�ش� ��ƼŬ�� ������ ��´�.
			_pParticles[i].GetParticleVertex(
				_pParticleVertices + drawParticleNum,
				_Colors, _Scales);

			drawParticleNum++;
		}
	}

	_device->SetRenderState(D3DRS_LIGHTING, false);							//�������� ����.
	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);					//����Ʈ ���ö���Ʈ Ȱ��ȭ
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, true);					//����Ʈ�� �����ϰ� ���̰ڴ�.
	_device->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDWORD(0.0f));		//����Ʈ�� �ּ� ũ�� ( ȭ����� )
	_device->SetRenderState(D3DRS_POINTSIZE_MAX, FloatToDWORD(500.0f));		//����Ʈ�� �ִ� ũ�� ( ȭ����� )
	//_device->SetRenderState( D3DRS_POINTSIZE, FloatToDWORD( 10.0f ) );	//����Ʈ ���� ������ ( ������ ����Ʈ ����� ������ ���õǴµ� );
	_device->SetRenderState(D3DRS_ZWRITEENABLE, false);						//z ������ ���⸦ ���´�.

	//��µǴ� POINT size 
	//finalSize = viewportHeight * pointSize *  sqrt( 1 / ( A + B(D) + C(D^2) )  );
	//�Ʒ��� ���� �ϸ� �ڿ������� �Ÿ��� ���� �������� ��Ÿ��
	_device->SetRenderState(D3DRS_POINTSCALE_A, FloatToDWORD(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_B, FloatToDWORD(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_C, FloatToDWORD(1.0f));

	//���� ���� ����
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//Texture �� ���� Diffuse ���⼭�� �����÷��� ���İ� �� ���� ���� ����� �Ѵ�.
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

	D3DXMATRIXA16 matWorld;

	if (_bLocal == false) D3DXMatrixIdentity(&matWorld);
	else matWorld = this->_transform->GetFinalMatrix();

	_device->SetTransform(D3DTS_WORLD, &matWorld);

	//��ƼŬ Texture ����
	_device->SetTexture(0, _pTex);

	//��ƼŬ ���� ���
	_device->SetFVF(PARTICLE_VERTEX::FVF);
	_device->DrawPrimitiveUP(
		D3DPT_POINTLIST,
		drawParticleNum,
		_pParticleVertices,
		sizeof(PARTICLE_VERTEX));

	//��ƼŬ �׸��� ���� ��ó��
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
	//���̺� Ÿ�� ����
	float liveTime = RandomFloatRange(_fStartLiveTimeMin, _fStartLiveTimeMax);

	//��ƼŬ�� ������ ��ġ
	D3DXVECTOR3 position;

	//������ �ƴѰ�� �ڽ��� ���� ��ġ���� �����ϰ� 
	if (this->_bLocal == false)
	{
		position = this->_transform->GetWorldPosition();
	}
	//������ ��� 0 ���� �����Ѵ�.
	else
	{
		position = D3DXVECTOR3(0, 0, 0);
	}
	//���� ������ ���� �߰� ��ġ....
	if (EmissionType == PATICLE_EMISSION_TYPE::SPHERE)
	{
		//��������
		D3DXVECTOR3 randDir(
			RandomFloatRange(-1.0f, 1.0f),
			RandomFloatRange(-1.0f, 1.0f),
			RandomFloatRange(-1.0f, 1.0f));

		D3DXVec3Normalize(&randDir, &randDir);

		//�����Ÿ�
		float randDistance = RandomFloatRange(0, SphereEmissionRange);

		//�߰���ġ
		position += randDir * randDistance;
	}
	else if (EmissionType == PATICLE_EMISSION_TYPE::SPHERE_OUTLINE)
	{
		//��������
		D3DXVECTOR3 randDir(
			RandomFloatRange(-1.0f, 1.0f),
			RandomFloatRange(-1.0f, 1.0f),
			RandomFloatRange(-1.0f, 1.0f));

		D3DXVec3Normalize(&randDir, &randDir);

		//�߰���ġ
		position += randDir * SphereEmissionRange;
	}
	else if (EmissionType == PATICLE_EMISSION_TYPE::BOX)
	{
		//��������
		D3DXVECTOR3 randDir(
			RandomFloatRange(MinEmissionRangeX, MaxEmissionRangeX),
			RandomFloatRange(MinEmissionRangeY, MaxEmissionRangeY),
			RandomFloatRange(MinEmissionRangeZ, MaxEmissionRangeZ));

		//�߰���ġ
		position += randDir;
	}

	//���� ����
	D3DXVECTOR3 velocity;
	velocity.x = RandomFloatRange(_StartVelocityMin.x, _StartVelocityMax.x);
	velocity.y = RandomFloatRange(_StartVelocityMin.y, _StartVelocityMax.y);
	velocity.z = RandomFloatRange(_StartVelocityMin.z, _StartVelocityMax.z);

	D3DXVECTOR3 accelation;
	accelation.x = RandomFloatRange(_StartAccelateMin.x, _StartAccelateMax.x);
	accelation.y = RandomFloatRange(_StartAccelateMin.y, _StartAccelateMax.y);
	accelation.z = RandomFloatRange(_StartAccelateMin.z, _StartAccelateMax.z);

	//�ڽ��� ���� ��Ʈ������ ������ �´�.
	if (_bLocal == false)
	{
		D3DXMATRIXA16 matWorld = this->_transform->GetFinalMatrix();
		D3DXVec3TransformNormal(&velocity, &velocity, &matWorld);
		D3DXVec3TransformNormal(&accelation, &accelation, &matWorld);
	}

	//�����ϵ� ����
	float scale = RandomFloatRange(_fStartScaleMin, _fStartScaleMax);

	//������� �߻���Ų��
	_pParticles[_dwParticleCount].Start(
		liveTime, &position, &velocity, &accelation, scale);

	//���� ��ƼŬ�� ���� ���� ����
	_dwParticleCount++;
	if (_dwParticleCount == this->_ParticleNum)
	{
		_dwParticleCount = 0;
	}
}

void particleEmitter::StartOneParticle(D3DXVECTOR3 dir, float life)
{
	float liveTime = life;

	//��ƼŬ�� ������ ��ġ
	D3DXVECTOR3 position;
	if (this->_bLocal == false)
	{
		position = _transform->GetWorldPosition();
	}
	else
	{
		position = D3DXVECTOR3(0, 0, 0);
	}

	//���� ����
	D3DXVECTOR3 velocity;
	velocity.x = dir.x;
	velocity.y = dir.y;
	velocity.z = dir.z;

	D3DXVECTOR3 accelation;
	accelation.x = RandomFloatRange(_StartAccelateMin.x, _StartAccelateMax.x);
	accelation.y = RandomFloatRange(_StartAccelateMin.y, _StartAccelateMax.y);
	accelation.z = RandomFloatRange(_StartAccelateMin.z, _StartAccelateMax.z);

	//�ڽ��� ���� ��Ʈ������ ������ �´�.
	if (_bLocal == false)
	{
		D3DXMATRIXA16 matWorld = this->_transform->GetFinalMatrix();
		D3DXVec3TransformNormal(&velocity, &velocity, &matWorld);
		D3DXVec3TransformNormal(&accelation, &accelation, &matWorld);
	}

	//�����ϵ� ����
	float scale = RandomFloatRange(_fStartScaleMin, _fStartScaleMax);

	//�߻���Ų��
	_pParticles[_dwParticleCount].Start(
		liveTime, &position, &velocity, &accelation, scale);

	_dwParticleCount++;
	if (_dwParticleCount == this->_ParticleNum)
	{
		_dwParticleCount = 0;
	}
}