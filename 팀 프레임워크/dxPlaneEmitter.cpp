#include "stdafx.h"
#include "dxPlaneEmitter.h"

HRESULT dxPlaneEmitter::init(string textureFileName, int OneTimePaticleNum, float spawnTime, int totalPaticleNum)
{
	_onePtcNum = OneTimePaticleNum;
	_totalPtcNum = totalPaticleNum;
	_spawnTime = spawnTime;
	_spawnCurrentTime = _spawnTime;


	_ptcVertex = new tagDxParticleEX[_totalPtcNum * 4];
	_ptcIndex = new DWORD[_totalPtcNum * 6];

	//_trans = new transform[_totalPtcNum];


	
	//HRESULT hr = NULL;
	
	//텍스쳐 불러오기
	_texture = *PTM->LoadImgPathAndName(textureFileName);
	if (_texture == NULL)	return E_FAIL;

	/*hr = D3DXCreateTextureFromFile(_device, textureFileName.c_str(), &_texture);

	if (FAILED(hr))	return E_FAIL;*/

	//파티클 사이즈 정함.
	_ptcList.resize(_totalPtcNum);

	return S_OK;
}

void dxPlaneEmitter::release()
{
	//dxEmitter::release();

	SAFE_DELETE_ARRAY(_ptcVertex);
	SAFE_DELETE_ARRAY(_ptcIndex);
	//SAFE_DELETE_ARRAY(_trans);
	//SAFE_DELETE(_trans);
	SAFE_DELETE(_module);
}

void dxPlaneEmitter::update()
{
	//시간
	float DeltaTime = _timeDelta*_emitterNum;

	//시작 시간 체크
	if (autoStartTimeCheck(DeltaTime)) return;

	//작동시간 체크
	if (autoActiveTimeCheck(DeltaTime)) return;

	//초기값
	int checkNum = 0;

	//list<tagDxAttribute>::iterator iter;
	vector<tagDxAttribute>::iterator iter;

	//활성화 된 거 돌리기
	int InitNum = 0;
	int ActiveNum = 0;
	int DrawNum = 0;
	_drawPtcNum = 0;

	for (iter = _ptcList.begin(); iter != _ptcList.end(); ++iter)
	{
		//죽음
		if (iter->lifeTime <= iter->age)
		{
			iter->isAlive = false;
			iter->age = 0.0f;
		}

		if (_spawnTime <= _spawnCurrentTime)
		{
			if (iter->isAlive == false && checkNum < _onePtcNum)
			{
				//재활성화
				iter->isAlive = true;

				iter->emitterNum = _emitterNum;
				if (_psTrans != NULL)
				{
					iter->psTransPos = _psTrans->GetWorldPosition();
					iter->matPsRot = _psTrans->GetWorldRotateMatrix();
				}
				_module->InitUpdate(iter);

				checkNum++;
				
			}

		}
		InitNum++;

		

		//활성화
		if (iter->isAlive)
		{

			_module->ActiveUpdate(iter);
			this->ActiveUpdatePlane(&_ptcVertex[_drawPtcNum * 4], &_ptcIndex[_drawPtcNum * 6], iter, _drawPtcNum);
			//나이 더하기
			iter->age += DeltaTime;
			_drawPtcNum++;
		}
		ActiveNum++;
	}

	//시간 초기화
	if (_spawnTime <= _spawnCurrentTime)
	{
		_spawnCurrentTime = 0.0f;
	}
	
	//스폰 시간 업
	_spawnCurrentTime += DeltaTime;

	
}

void dxPlaneEmitter::render()
{
	//시작시간 과 동작시간에 따른 렌더
	if (_startRenderOn == FALSE) return;
	if (_activeRenderOn == FALSE) return;

	_device->SetRenderState(D3DRS_LIGHTING, false);		//라이팅을 끈다.
	_device->SetRenderState(D3DRS_ZWRITEENABLE, false);	//z 버퍼의 쓰기를 막는다.

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//알파 블렌딩 셋팅
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//_device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	//_device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Texture 의 값과 Diffuse 여기서는 정점컬러의 알파값 을 섞어 최종 출력을 한다.
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);


	//파티클 Texture 셋팅
	_device->SetTexture(0, _texture);

	//파티클 정점 출력
	_device->SetFVF(ParticleExFVF);
	_device->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST,
		0,
		_drawPtcNum*4,
		_drawPtcNum*2,
		_ptcIndex,
		D3DFMT_INDEX32,
		_ptcVertex,
		sizeof(tagDxParticleEX));
	
	//for (int i = 0; i < _totalPtcNum; i++)
	//{
	//	_device->DrawIndexedPrimitiveUP(
	//		D3DPT_TRIANGLELIST,
	//		i,
	//		4,
	//		2,
	//		_ptcIndex,
	//		D3DFMT_INDEX32,
	//		_ptcVertex,
	//		sizeof(tagDxParticleEX));
	//}


	//파티클 그리고 난후 후처리
	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, true);

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	_device->SetTexture(0, NULL);
}



void dxPlaneEmitter::ActiveUpdatePlane(tagDxParticleEX * ptcVertex, DWORD * ptcIndex, vector<tagDxAttribute>::iterator iter, DWORD drawParticleNum)
{
	//파티클 위치 값
	dx::transform ptcTrans;

	ptcTrans.SetWorldPosition(iter->position);
	//ptcTrans.RotateSelf(D3DXVECTOR3(0.0f,D3DXToRadian(RandomFloatRange(10.0f,45.0f)),0.0f));
	ptcTrans.RotateSelf(iter->rotateAngle);


	D3DXVECTOR3 x = ptcTrans.GetRight()*iter->horizontal;
	D3DXVECTOR3 z = ptcTrans.GetForward()*iter->vertical;

	//float halfScale = iter->size*0.5;

	//그려지는 중심 위치에 따른 보정
	D3DXVECTOR2 scale0 = iter->scaleHV0;
	D3DXVECTOR2 scale1 = iter->scaleHV1;
	D3DXVECTOR2 scale2 = iter->scaleHV2;
	D3DXVECTOR2 scale3 = iter->scaleHV3;

	D3DXCOLOR inColor = iter->color;


	D3DXVECTOR3 posCenter = iter->posCenter;

	//int dwPtcNum = drawParticleNum;

	D3DXVECTOR2 uv0 = iter->UV0;
	D3DXVECTOR2 uv1 = iter->UV1;
	D3DXVECTOR2 uv2 = iter->UV2;
	D3DXVECTOR2 uv3 = iter->UV3;


	//D3DXVECTOR3 center = _transform.GetWorldPosition();

	//iter->circleSpeed + iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta) / 2.0f) + iter->posDirectVel*_timeDelta;

	//정점 정보 대입
	(ptcVertex + 0)->position = posCenter + (-x * scale0.x) + (z * scale0.y);
	(ptcVertex + 1)->position = posCenter + (x * scale1.x) + (z * scale1.y);
	(ptcVertex + 2)->position = posCenter + (-x * scale2.x) + (-z * scale2.y);
	(ptcVertex + 3)->position = posCenter + (x * scale3.x) + (-z * scale3.y);

	/*(ptcVertex + 0)->position = posCenter + (-x * halfScale) + (z * halfScale);
	(ptcVertex + 1)->position = posCenter + (x * halfScale) + (z * halfScale);
	(ptcVertex + 2)->position = posCenter + (-x * halfScale) + (-z * halfScale);
	(ptcVertex + 3)->position = posCenter + (x * halfScale) + (-z * halfScale);*/

	/*(ptcVertex + 0)->uv = D3DXVECTOR2(0.0f, 0.0f);
	(ptcVertex + 1)->uv = D3DXVECTOR2(1.0f, 0.0f);
	(ptcVertex + 2)->uv = D3DXVECTOR2(0.0f, 1.0f);
	(ptcVertex + 3)->uv = D3DXVECTOR2(1.0f, 1.0f);*/

	(ptcVertex + 0)->uv = uv0;
	(ptcVertex + 1)->uv = uv1;
	(ptcVertex + 2)->uv = uv2;
	(ptcVertex + 3)->uv = uv3;

	(ptcVertex + 0)->color = inColor;
	(ptcVertex + 1)->color = inColor;
	(ptcVertex + 2)->color = inColor;
	(ptcVertex + 3)->color = inColor;

	//0----1
	//|   /|
	//|  / |
	//| /  |
	//|/   |
	//2----3

	//인덱스 정보 대입 ( 인덱스 넣을때 지금까지 그려지는 Quad 수만큼 점프해한 값을 넣어야 한다 )
	*(ptcIndex + 0) = (drawParticleNum * 4) + 0;
	*(ptcIndex + 1) = (drawParticleNum * 4) + 1;
	*(ptcIndex + 2) = (drawParticleNum * 4) + 2;
	*(ptcIndex + 3) = (drawParticleNum * 4) + 2;
	*(ptcIndex + 4) = (drawParticleNum * 4) + 1;
	*(ptcIndex + 5) = (drawParticleNum * 4) + 3;
}