#include "stdafx.h"
#include "dxBoardEmitter.h"

HRESULT dxBoardEmitter::init(string textureFileName, int OneTimePaticleNum, float spawnTime, int totalPaticleNum)
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
	//hr = D3DXCreateTextureFromFile(_device, textureFileName.c_str(), &_texture);

	//if (FAILED(hr))	return E_FAIL;

	//파티클 사이즈 정함.
	_ptcList.resize(_totalPtcNum);


	/*_posCenter = new D3DXVECTOR3[_totalPtcNum];

	for (int i = 0; i < _totalPtcNum; i++)
	{
		_posCenter[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}*/
	_activeCurrentTime = 0.0f;

	return S_OK;
}

void dxBoardEmitter::relese()
{
	//dxEmitter::release();
	//SAFE_DELETE_ARRAY(_ptcVertex);
	//SAFE_DELETE_ARRAY(_ptcIndex);
	//SAFE_DELETE_ARRAY(_trans);
	SAFE_DELETE(_module);
}



void dxBoardEmitter::update()
{
	//시간
	float DeltaTime = _timeDelta*_emitterNum;

	//시작 시간 체크
	if (autoStartTimeCheck(DeltaTime)) return;

	//작동시간 체크
	if (autoActiveTimeCheck(DeltaTime)) return;

	//초기값
	int checkNum = 0;
	//tagDxParticle* ptcVtx;
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
			//iter->isInit = false;
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

				//프리 업데이트 재가동
				//_preUpdateOn = TRUE;

				//this->InitCreatePlane(&_ptcVertex[InitNum * 4], &_ptcIndex[InitNum * 6], iter, InitNum);

				//초기 회전용 - 자동 회전을 위하여
				//_allRotate += _allRotateSpeed*DeltaTime;
				//iter->allRotAngle = _allRotate;

				checkNum++;
				//if (checkNum >= _onePtcNum) break;

				//iter->allRotAngle.y = D3DXToDegree(angle.y);
			}
			//_ptcVtx++;

			//iter->allRotAngle.x = D3DXToDegree(_psTrans->GetWorldRotateMatrix()._11);
			//iter->allRotAngle.y = D3DXToDegree(_psTrans->GetWorldRotateMatrix()._22);
			//iter->allRotAngle.z = D3DXToDegree(_psTrans->GetWorldRotateMatrix()._33);
			//D3DXVeDot(_psTrans->GetWorldRotateMatrix()._41, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
			//iter->allRotAngle.y += 20.0f;

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

void dxBoardEmitter::render()
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

	//Trans.LookPosition(cameraPos);

   /*if (_bLocal == false)
   {
   D3DXMatrixIdentity(&matWorld);
   }
   else
   {
   matWorld = this->_transform->GetFinalMatrix();
   }*/
   //_device->SetTransform(D3DTS_WORLD, &matWorld);

   //_trans->SetDeviceWorld();

   //파티클 Texture 셋팅
	_device->SetTexture(0, _texture);

	//파티클 정점 출력
	_device->SetFVF(ParticleExFVF);

	_device->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST,
		0,
		_drawPtcNum * 4,
		_drawPtcNum * 2,
		_ptcIndex,
		D3DFMT_INDEX32,
		_ptcVertex,
		sizeof(tagDxParticleEX));


	//for (int i = 0; i < _drawPtcNum; i++)
	//{
	//	//tagDxParticleEX*	InPtcVertex = _ptcVertex + i*6;		//파티클 버텍스
	//	//DWORD*				InPtcIndex = _ptcIndex + i*4;			//파티클 인덱스

	//	_device->DrawIndexedPrimitiveUP(
	//		D3DPT_TRIANGLELIST,
	//		i*4,
	//		4,
	//		2,
	//		&_ptcIndex[i*6],
	//		D3DFMT_INDEX32,
	//		&_ptcVertex[i*4],
	//		sizeof(tagDxParticleEX));
	//}

	//파티클 그리고 난후 후처리
	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, true);

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	_device->SetTexture(0, NULL);
}





void dxBoardEmitter::ActiveUpdatePlane(tagDxParticleEX * ptcVertex, DWORD * ptcIndex, vector<tagDxAttribute>::iterator iter, DWORD drawParticleNum)
{
	//파티클 위치 값
	dx::transform ptcTrans;

	//ptcTrans.SetWorldPosition(iter->position);
	//ptcTrans.RotateSelf(D3DXVECTOR3(0.0f,D3DXToRadian(RandomFloatRange(10.0f,45.0f)),0.0f));
	//ptcTrans.RotateSelf(iter->rotateAngle);

	//_psTrans->SetDeviceWorld();

	//카메라 행렬 가져오기
	D3DXMATRIXA16 getView;
	D3DXMATRIXA16 getViewInverse;
	_device->GetTransform(D3DTS_VIEW, &getView);
	D3DXMatrixInverse(&getViewInverse, NULL, &getView);
	//D3DXVECTOR3 cameraPos = D3DXVECTOR3(getView._41, getView._42, getView._43);

	D3DXMATRIXA16 matInit;
	D3DXMatrixIsIdentity(&matInit);

	//_device->SetTransform(D3DTS_WORLD, &matInit);

	getViewInverse._41 = getView._41;
	getViewInverse._42 = getView._42;
	getViewInverse._43 = getView._43;
	//vectorReverse

	//Y축 빌보드
	/*getView._11 = getViewInverse._11;
	getView._13 = getViewInverse._13;
	getView._31 = getViewInverse._31;
	getView._33 = getViewInverse._33;*/

	//D3DXVECTOR3 cameraDir;

	//D3DXVec3Normalize(&cameraDir,&cameraPos);

	//빌보드 세팅
	if (_psTrans == NULL)
	{
		D3DXMATRIXA16 psTransInverse;
		D3DXMatrixInverse(&psTransInverse, NULL, &(_psBoardTrans->GetFinalMatrix()*getView));
		ptcTrans.SetWorldMatrix(psTransInverse);
	}
	else
	{
		ptcTrans.SetWorldMatrix(getViewInverse);
	}

	//회전 적용
	ptcTrans.RotateSelf(iter->rotateAngle);

	//ptcTrans.SetWorldMatrix(_psTrans->GetFinalMatrix()*getViewInverse);
	//ptcTrans.SetWorldMatrix(_psTrans->GetFinalMatrix()*getView);

	//ptcTrans.SetWorldMatrix(psTransInverse);

	//ptcTrans.LookDirection(cameraDir,cameraPos);
	//ptcTrans.LookPosition(cameraPos);


	//ptcTrans.RotateSelf(iter->rotateAngle);

	D3DXVECTOR3 x = ptcTrans.GetRight()*iter->horizontal;
	D3DXVECTOR3 y = ptcTrans.GetUp()*iter->vertical;
	//D3DXVECTOR3 z = ptcTrans.GetForward()*iter->vertical;

	//float halfScale = iter->size*0.5;

	//그려지는 중심 위치에 따른 보정
	D3DXVECTOR2 scale0 = iter->scaleHV0;
	D3DXVECTOR2 scale1 = iter->scaleHV1;
	D3DXVECTOR2 scale2 = iter->scaleHV2;
	D3DXVECTOR2 scale3 = iter->scaleHV3;



	D3DXCOLOR inColor = iter->color;


	D3DXMATRIXA16 matPos;
	D3DXMATRIXA16 matRot;
	D3DXMATRIXA16 matRotY;
	D3DXMATRIXA16 matFin;

	//

	D3DXMatrixIdentity(&matPos);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matRotY);


	//D3DXMatrixTranslation(&matPos, iter->vectorDir.x, iter->vectorDir.y, iter->vectorDir.z);
	//D3DXMatrixTranslation(&matPos, iter->velocity.x*_timeDelta, iter->velocity.y*_timeDelta, iter->velocity.z*_timeDelta);
	//D3DXMatrixTranslation(&matPos, iter->velocity.x, iter->velocity.y, iter->velocity.z);
	//D3DXMatrixTranslation(&matPos,0.0, 0.0f, 1.0f);

	//D3DXVECTOR3 inPos = D3DXVECTOR3(0.0f,0.0f,1.0f);

	//D3DXMatrixRotation

	//사원수 준비
	//D3DXQUATERNION quatRot;
	//D3DXQuaternionRotationYawPitchRoll(&quatRot, D3DXToRadian(0), D3DXToRadian(90), D3DXToRadian(90));


	//사원수에 의한 행렬준비
	//D3DXMATRIXA16 matRotate;
	//D3DXMatrixRotationQuaternion(&matRot, &quatRot);		//사원수에 의한 회전값으로 회전행렬이 만들어진다.
	//D3DXMatrixAffineTransformation(&matFin,1.0f,NULL,&quatRot,&inPos);
	//D3DXMatrixInverse(&matRot,NULL,&matRot);

	//D3DXMatrixRotationY(&matRotY,D3DXToRadian(90));

	//matFin = matPos*matRotY;

	/*matPos._41 = 0.0f;
	matPos._42 = 0.0f;
	matPos._43 = 1.0f;*/

	//matFin = matWorld*matRot;

	//matFin = matRotY;

//	iter->posCenter += dir; // *_timeDelta;
	//_posCenter[drawParticleNum] += dir;
	//D3DXVECTOR3 posCenter = _posCenter[drawParticleNum];
	//iter->posCenter = iter->posCenter;


	//D3DXVECTOR3 posCenter = iter->posCenter;

	//D3DXVECTOR3 posCenter = _posCenter[drawParticleNum];

	D3DXVECTOR3 posCenter = iter->posCenter;

	//_device->SetTransform(D3DTS_WORLD, &matWorld);
	//float distance = D3DXVec3Length(&iter->posCenter);

	//D3DXVECTOR3 forward = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//float angleF = D3DXVec3Dot(&_psTrans->GetForward(), &iter->posCenter);

	//D3DXVECTOR3 anglePos = D3DXVECTOR3(cosf(D3DXToRadian(angle))*distance,0.0f, sinf(D3DXToRadian(angle)*distance));

	//D3DXVECTOR3 posCenter = D3DXVECTOR3(cosf(D3DXToRadian(angleF))*distance, 0.0f, sinf(D3DXToRadian(angleF)*distance));
	//D3DXVECTOR3 anglePos = D3DXVECTOR3(cosf(angle)*distance, 0.0f, sinf(angle)*distance);


	D3DXVECTOR2 uv0 = iter->UV0;
	D3DXVECTOR2 uv1 = iter->UV1;
	D3DXVECTOR2 uv2 = iter->UV2;
	D3DXVECTOR2 uv3 = iter->UV3;

	//정점 정보 대입
	(ptcVertex + 0)->position = posCenter + (-x * scale0.x) + (y * scale0.y);
	(ptcVertex + 1)->position = posCenter + (x * scale1.x) + (y * scale1.y);
	(ptcVertex + 2)->position = posCenter + (-x * scale2.x) + (-y * scale2.y);
	(ptcVertex + 3)->position = posCenter + (x * scale3.x) + (-y * scale3.y);

	/*(ptcVertex + 0)->position = posCenter + (-x * halfScale) + (y * halfScale);
	(ptcVertex + 1)->position = posCenter + (x * halfScale) + (y * halfScale);
	(ptcVertex + 2)->position = posCenter + (-x * halfScale) + (-y * halfScale);
	(ptcVertex + 3)->position = posCenter + (x * halfScale) + (-y * halfScale);*/

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