#include "stdafx.h"
#include "quadParticleEmitter.h"

HRESULT quadParticleEmitter::init(DWORD partcleNum, float emission, float liveTimeMin, float liveTimeMax, const D3DXVECTOR3 & velocityMin, const D3DXVECTOR3 & velocityMax, const D3DXVECTOR3 & accelMin, const D3DXVECTOR3 & accelMax, const D3DXVECTOR3 & startRotateMin, const D3DXVECTOR3 & startRotateMax, const D3DXVECTOR3 & rotateMin, const D3DXVECTOR3 & rotateMax, const D3DXVECTOR3 & rotateAccelMin, const D3DXVECTOR3 & rotateAccelMax, const VEC_COLOR & colors, const VEC_SCALE & scales, float scaleMin, float scaleMax, LPDIRECT3DTEXTURE9 pTex, bool bLocal)
{
	//�ش� ��ƼŬ ������ �� ��ƼŬ ��
	_PaticleNum = partcleNum;

	//����ƼŬ �� * 4 ��ŭ ���ؽ��� �����
	_ParticleVerticles = new PARTICLEQUAD_VERTEX[_PaticleNum * 4];

	//����ƼŬ �� * 6 ��ŭ �ε����� �����.
	_ParticleIndex = new DWORD[_PaticleNum * 6];

	//��ƼŬ ��ü ����
	_pPaticles = new particleQuad[_PaticleNum];

	//��ƼŬ ��Ʈ�� Array
	_pSortArray = new particleQuad*[_PaticleNum];

	//�ʴ� ������
	_fEmissionPerSec = emission;

	//�ʴ� ������ ���� �߻� ����
	_fEmisionIntervalTime = 1.0f / _fEmissionPerSec;

	//���� �ð��� 0
	_fEmisionDeltaTime = 0.0f;

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

	//���۽� ȸ������ ���� �Լ�
	_StartSetRotateMax = startRotateMax;
	_StartSetRotateMin = startRotateMin;

	//����ȸ�� �� ����
	_StartRotateMin = rotateMin;
	_StartRotateMax = rotateMax;

	//ȸ�� ���� �� ����
	_StartRotateAccelateMin = rotateAccelMin;
	_StartRotateAccelateMax = rotateAccelMax;

	//���ۼ��� �ʱ�ȭ
	_dwParticleCount = 0;

	//��ƼŬ �ؽ���
	_pTex = pTex;

	_bLocal = bLocal;

	return S_OK;
}

void quadParticleEmitter::release()
{
	SAFE_DELETE_ARRAY(_pSortArray);
	SAFE_DELETE_ARRAY(_pPaticles);
	SAFE_DELETE_ARRAY(_ParticleVerticles);
	SAFE_DELETE_ARRAY(_ParticleIndex);
	SAFE_RELEASE(_pTex);
}

void quadParticleEmitter::baseObjectUpdate()
{
	//�ʰ� ���� �߻� ���´�?
	if (_bEmission) 
	{
		//�ϳ� �߻��ϰ� �����ð�
		_fEmisionDeltaTime += _timeDelta;

		while (_fEmisionDeltaTime > _fEmisionIntervalTime) 
		{
			_fEmisionDeltaTime -= _fEmisionIntervalTime;

			//��ƼŬ �ϳ� �߻�
			StartOneParticle();
		}
	}

	//��� ��ƼŬ ������Ʈ
	for (int i = 0; i < _PaticleNum; i++) 
	{
		_pPaticles[i].Update();
	}
}

void quadParticleEmitter::baseObjectRender()
{
	//�׸� ��ƼŬ ��
	DWORD drawParticleNum = 0;

	//ī�޶� ��Ʈ�� �ϳ�?
	if (this->_bCameraSort && this->_pCameraTransform != NULL)
	{
		//�׸� ��ƼŬ ��
		for (int i = 0; i < _PaticleNum; i++) 
		{
			//�ش���ƼŬ�� Ȱ��ȭ ���̴�?
			if (_pPaticles[i].isLive()) 
			{
				//��Ʈ�迭�� �ش� ��ƼŬ�� ���� ��Ų��.
				_pSortArray[drawParticleNum] = &_pPaticles[i];
				drawParticleNum++;
			}
		}

		//ī�޶� ���� ��ġ
		D3DXVECTOR3 cameraWorld = _pCameraTransform->GetWorldPosition();

		//�׷����� ���� ��� ī�޶� �Ÿ��� ��Ʈ�� �����Ѵ�.
		for (int i = 0; i < (drawParticleNum - 1); i++) 
		{
			for (int j = i + 1; j < drawParticleNum; j++) 
			{
				//2���� ī�޶� �Ÿ��� ���
				//i �� ī�޶���� �Ÿ� ����
				D3DXVECTOR3 dirI = cameraWorld - _pSortArray[i]->_transform.GetWorldPosition();
				float distI = D3DXVec3LengthSq(&dirI);

				//J �� ī�޶���� �Ÿ� ����
				D3DXVECTOR3 dirJ = cameraWorld - _pSortArray[j]->_transform.GetWorldPosition();
				float distJ = D3DXVec3LengthSq(&dirJ);

				//�հŸ� ������
				if (distJ > distI) 
				{
					particleQuad* pTemp = _pSortArray[j];
					_pSortArray[j] = _pSortArray[i];
					_pSortArray[i] = pTemp;
				}
			}
		}

		//��Ʈ�迭 ������ŭ���� �޽� ����
		for (int i = 0; i < drawParticleNum; i++) 
		{
			//��Ʈ�迭�� �ش� ��ƼŬ�� ���� ��Ų��.
			_pSortArray[i]->GetParticleVertex(
				&(_ParticleVerticles[i * 4]),
				&(_ParticleIndex[i * 6]),
				_Colors, _Scales, i);
		}
	}
	//��Ʈ ���ϳ�?
	else
	{
		for (int i = 0; i < _PaticleNum; i++) 
		{
			//�ش���ƼŬ�� Ȱ��ȭ ���̴�?
			if (_pPaticles[i].isLive()) 
			{
				//�ش� ��ƼŬ�� ������ ��´�.
				_pPaticles[i].GetParticleVertex(
					&(_ParticleVerticles[drawParticleNum * 4]),		//���� ���� �ּ� 4 �� ����.
					&(_ParticleIndex[drawParticleNum * 6]),			//���� �ε��� �ּ� 6 �� ����.
					_Colors,
					_Scales,
					drawParticleNum	 //�ε��� ������ ������� �׷��� ��ƼŬ���� ���� �Ѱܾ� �Ѵ�....
				);
				drawParticleNum++;
			}
		}
	}

	_device->SetRenderState(D3DRS_LIGHTING, false);		//�������� ����.
	_device->SetRenderState(D3DRS_ZWRITEENABLE, false);	//z ������ ���⸦ ���´�.

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���� ���� ����
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//_device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	//_device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Texture �� ���� Diffuse ���⼭�� �����÷��� ���İ� �� ���� ���� ����� �Ѵ�.
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

	D3DXMATRIXA16 matWorld;

	if (_bLocal == false)
	{
		D3DXMatrixIdentity(&matWorld);
	}
	else
	{
		matWorld = this->_transform->GetFinalMatrix();
	}
	_device->SetTransform(D3DTS_WORLD, &matWorld);

	//��ƼŬ Texture ����
	_device->SetTexture(0, _pTex);

	//��ƼŬ ���� ���
	_device->SetFVF(PARTICLEQUAD_VERTEX::FVF);
	_device->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST,
		0,
		drawParticleNum * 4,			//������
		drawParticleNum * 2,			//�ﰢ�� ��
		_ParticleIndex,
		D3DFMT_INDEX32,
		_ParticleVerticles,
		sizeof(PARTICLEQUAD_VERTEX));

	//��ƼŬ �׸��� ���� ��ó��
	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, true);

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	_device->SetTexture(0, NULL);
}

void quadParticleEmitter::StartEmission()
{
	this->_bEmission = true;
}

void quadParticleEmitter::StopEmission()
{
	this->_bEmission = false;
}

void quadParticleEmitter::setCameraSort(dx::transform * pCameraTrans, bool bSort)
{
	this->_pCameraTransform = pCameraTrans;		//ī�޶� ��Ʈ ���
	this->_bCameraSort = bSort;
}

void quadParticleEmitter::StartOneParticle()
{
	//���̺� Ÿ�� ����
	float liveTime = RandomFloatRange(_fStartLiveTimeMin, _fStartLiveTimeMax);

	D3DXVECTOR3 position = _transform->GetWorldPosition();

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

	//���� ����
	D3DXVECTOR3 velocity;
	velocity.x = RandomFloatRange(_StartVelocityMin.x, _StartVelocityMax.x);
	velocity.y = RandomFloatRange(_StartVelocityMin.y, _StartVelocityMax.y);
	velocity.z = RandomFloatRange(_StartVelocityMin.z, _StartVelocityMax.z);

	D3DXVECTOR3 accelation;
	accelation.x = RandomFloatRange(_StartAccelateMin.x, _StartAccelateMax.x);
	accelation.y = RandomFloatRange(_StartAccelateMin.y, _StartAccelateMax.y);
	accelation.z = RandomFloatRange(_StartAccelateMin.z, _StartAccelateMax.z);

	D3DXVECTOR3 setRotate;
	setRotate.x = RandomFloatRange(_StartSetRotateMin.x, _StartSetRotateMax.x);
	setRotate.y = RandomFloatRange(_StartSetRotateMin.y, _StartSetRotateMax.y);
	setRotate.z = RandomFloatRange(_StartSetRotateMin.z, _StartSetRotateMax.z);

	//�������� ȸ���� ����
	D3DXVECTOR3 rotate;
	rotate.x = RandomFloatRange(_StartRotateMin.x, _StartRotateMax.x);
	rotate.y = RandomFloatRange(_StartRotateMin.y, _StartRotateMax.y);
	rotate.z = RandomFloatRange(_StartRotateMin.z, _StartRotateMax.z);

	//�������� ȸ�� ���ӷ� ����
	D3DXVECTOR3 rotateAccel;
	rotateAccel.x = RandomFloatRange(_StartRotateAccelateMin.x, _StartRotateAccelateMax.x);
	rotateAccel.y = RandomFloatRange(_StartRotateAccelateMin.y, _StartRotateAccelateMax.y);
	rotateAccel.z = RandomFloatRange(_StartRotateAccelateMin.z, _StartRotateAccelateMax.z);

	//�ڽ��� ���� ��Ʈ������ ������ �´�.
	if (_bLocal == false)
	{
		D3DXMATRIXA16 matWorld = this->_transform->GetFinalMatrix();
		D3DXVec3TransformNormal(&velocity, &velocity, &matWorld);
		D3DXVec3TransformNormal(&accelation, &accelation, &matWorld);
	}

	//�����ϵ� ����
	float scale = RandomFloatRange(_fStartScaleMin, _fStartScaleMax);

	_pPaticles[_dwParticleCount]._transform.SetRotateLocal(
		setRotate.x, setRotate.y, setRotate.z);

	//������� �߻���Ų��
	_pPaticles[_dwParticleCount].Start(
		liveTime,			//���̺� Ÿ��
		&position,			//��ġ
		&velocity,			//���� ��Ƽ
		&accelation,		//����
		&rotate,			//ȸ����
		&rotateAccel,		//ȸ�� ����
		scale				//������
	);

	//���� ��ƼŬ�� ���� ���� ����
	_dwParticleCount++;
	if (_dwParticleCount == this->_PaticleNum)
	{ 
		_dwParticleCount = 0;
	}
}
