#include "stdafx.h"
#include "quadParticleEmitter.h"

HRESULT quadParticleEmitter::init(DWORD partcleNum, float emission, float liveTimeMin, float liveTimeMax, const D3DXVECTOR3 & velocityMin, const D3DXVECTOR3 & velocityMax, const D3DXVECTOR3 & accelMin, const D3DXVECTOR3 & accelMax, const D3DXVECTOR3 & startRotateMin, const D3DXVECTOR3 & startRotateMax, const D3DXVECTOR3 & rotateMin, const D3DXVECTOR3 & rotateMax, const D3DXVECTOR3 & rotateAccelMin, const D3DXVECTOR3 & rotateAccelMax, const VEC_COLOR & colors, const VEC_SCALE & scales, float scaleMin, float scaleMax, LPDIRECT3DTEXTURE9 pTex, bool bLocal)
{
	//해당 파티클 렌더의 총 파티클 수
	_PaticleNum = partcleNum;

	//총파티클 수 * 4 만큼 버텍스를 만든다
	_ParticleVerticles = new PARTICLEQUAD_VERTEX[_PaticleNum * 4];

	//총파티클 수 * 6 만큼 인덱스를 만든다.
	_ParticleIndex = new DWORD[_PaticleNum * 6];

	//파티클 객체 생성
	_pPaticles = new particleQuad[_PaticleNum];

	//파티클 소트용 Array
	_pSortArray = new particleQuad*[_PaticleNum];

	//초당 생성량
	_fEmissionPerSec = emission;

	//초당 생성량 따른 발생 간격
	_fEmisionIntervalTime = 1.0f / _fEmissionPerSec;

	//지난 시간도 0
	_fEmisionDeltaTime = 0.0f;

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

	//시작시 회전방향 세팅 함수
	_StartSetRotateMax = startRotateMax;
	_StartSetRotateMin = startRotateMin;

	//시작회전 값 대입
	_StartRotateMin = rotateMin;
	_StartRotateMax = rotateMax;

	//회전 가속 값 대입
	_StartRotateAccelateMin = rotateAccelMin;
	_StartRotateAccelateMax = rotateAccelMax;

	//시작순번 초기화
	_dwParticleCount = 0;

	//파티클 텍스쳐
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
	//너가 지금 발생 상태니?
	if (_bEmission) 
	{
		//하나 발생하고 지난시간
		_fEmisionDeltaTime += _timeDelta;

		while (_fEmisionDeltaTime > _fEmisionIntervalTime) 
		{
			_fEmisionDeltaTime -= _fEmisionIntervalTime;

			//파티클 하나 발사
			StartOneParticle();
		}
	}

	//모든 파티클 업데이트
	for (int i = 0; i < _PaticleNum; i++) 
	{
		_pPaticles[i].Update();
	}
}

void quadParticleEmitter::baseObjectRender()
{
	//그릴 파티클 수
	DWORD drawParticleNum = 0;

	//카메라 소트를 하냐?
	if (this->_bCameraSort && this->_pCameraTransform != NULL)
	{
		//그릴 파티클 수
		for (int i = 0; i < _PaticleNum; i++) 
		{
			//해당파티클이 활성화 중이니?
			if (_pPaticles[i].isLive()) 
			{
				//소트배열에 해당 파티클을 참조 시킨다.
				_pSortArray[drawParticleNum] = &_pPaticles[i];
				drawParticleNum++;
			}
		}

		//카메라 월드 위치
		D3DXVECTOR3 cameraWorld = _pCameraTransform->GetWorldPosition();

		//그려지는 갯수 대로 카메라 거리별 소트를 진행한다.
		for (int i = 0; i < (drawParticleNum - 1); i++) 
		{
			for (int j = i + 1; j < drawParticleNum; j++) 
			{
				//2개의 카메라 거리를 잰다
				//i 의 카메라와의 거리 제곱
				D3DXVECTOR3 dirI = cameraWorld - _pSortArray[i]->_transform.GetWorldPosition();
				float distI = D3DXVec3LengthSq(&dirI);

				//J 의 카메라와의 거리 제곱
				D3DXVECTOR3 dirJ = cameraWorld - _pSortArray[j]->_transform.GetWorldPosition();
				float distJ = D3DXVec3LengthSq(&dirJ);

				//먼거를 앞으로
				if (distJ > distI) 
				{
					particleQuad* pTemp = _pSortArray[j];
					_pSortArray[j] = _pSortArray[i];
					_pSortArray[i] = pTemp;
				}
			}
		}

		//소트배열 갯수만큼돌며 메쉬 조합
		for (int i = 0; i < drawParticleNum; i++) 
		{
			//소트배열에 해당 파티클을 참조 시킨다.
			_pSortArray[i]->GetParticleVertex(
				&(_ParticleVerticles[i * 4]),
				&(_ParticleIndex[i * 6]),
				_Colors, _Scales, i);
		}
	}
	//소트 안하냐?
	else
	{
		for (int i = 0; i < _PaticleNum; i++) 
		{
			//해당파티클이 활성화 중이니?
			if (_pPaticles[i].isLive()) 
			{
				//해당 파티클의 정보를 얻는다.
				_pPaticles[i].GetParticleVertex(
					&(_ParticleVerticles[drawParticleNum * 4]),		//써질 정점 주소 4 씩 쓴다.
					&(_ParticleIndex[drawParticleNum * 6]),			//써질 인덱스 주소 6 씩 쓴다.
					_Colors,
					_Scales,
					drawParticleNum	 //인덱스 때문에 현재까지 그려진 파티클수도 같이 넘겨야 한다....
				);
				drawParticleNum++;
			}
		}
	}

	_device->SetRenderState(D3DRS_LIGHTING, false);		//라이팅을 끈다.
	_device->SetRenderState(D3DRS_ZWRITEENABLE, false);	//z 버퍼의 쓰기를 막는다.

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//알파 블렌딩 세팅
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//_device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	//_device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Texture 의 값과 Diffuse 여기서는 정점컬러의 알파값 을 섞어 최종 출력을 한다.
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

	//파티클 Texture 세팅
	_device->SetTexture(0, _pTex);

	//파티클 정점 출력
	_device->SetFVF(PARTICLEQUAD_VERTEX::FVF);
	_device->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST,
		0,
		drawParticleNum * 4,			//정점수
		drawParticleNum * 2,			//삼각형 수
		_ParticleIndex,
		D3DFMT_INDEX32,
		_ParticleVerticles,
		sizeof(PARTICLEQUAD_VERTEX));

	//파티클 그리고 난후 후처리
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
	this->_pCameraTransform = pCameraTrans;		//카메라 소트 기억
	this->_bCameraSort = bSort;
}

void quadParticleEmitter::StartOneParticle()
{
	//라이브 타임 랜덤
	float liveTime = RandomFloatRange(_fStartLiveTimeMin, _fStartLiveTimeMax);

	D3DXVECTOR3 position = _transform->GetWorldPosition();

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

	//벡터 랜덤
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

	//움직임의 회전량 랜덤
	D3DXVECTOR3 rotate;
	rotate.x = RandomFloatRange(_StartRotateMin.x, _StartRotateMax.x);
	rotate.y = RandomFloatRange(_StartRotateMin.y, _StartRotateMax.y);
	rotate.z = RandomFloatRange(_StartRotateMin.z, _StartRotateMax.z);

	//움직임의 회전 가속량 랜덤
	D3DXVECTOR3 rotateAccel;
	rotateAccel.x = RandomFloatRange(_StartRotateAccelateMin.x, _StartRotateAccelateMax.x);
	rotateAccel.y = RandomFloatRange(_StartRotateAccelateMin.y, _StartRotateAccelateMax.y);
	rotateAccel.z = RandomFloatRange(_StartRotateAccelateMin.z, _StartRotateAccelateMax.z);

	//자신의 월드 매트릭스를 가지고 온다.
	if (_bLocal == false)
	{
		D3DXMATRIXA16 matWorld = this->_transform->GetFinalMatrix();
		D3DXVec3TransformNormal(&velocity, &velocity, &matWorld);
		D3DXVec3TransformNormal(&accelation, &accelation, &matWorld);
	}

	//스케일도 랜덤
	float scale = RandomFloatRange(_fStartScaleMin, _fStartScaleMax);

	_pPaticles[_dwParticleCount]._transform.SetRotateLocal(
		setRotate.x, setRotate.y, setRotate.z);

	//순번대로 발생시킨다
	_pPaticles[_dwParticleCount].Start(
		liveTime,			//라이브 타입
		&position,			//위치
		&velocity,			//벨로 시티
		&accelation,		//가속
		&rotate,			//회전량
		&rotateAccel,		//회전 가속
		scale				//스케일
	);

	//다음 파티클을 위한 순번 증가
	_dwParticleCount++;
	if (_dwParticleCount == this->_PaticleNum)
	{ 
		_dwParticleCount = 0;
	}
}
