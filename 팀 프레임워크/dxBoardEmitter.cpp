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

	//�ؽ��� �ҷ�����
	_texture = *PTM->LoadImgPathAndName(textureFileName);
	if (_texture == NULL)	return E_FAIL;
	//hr = D3DXCreateTextureFromFile(_device, textureFileName.c_str(), &_texture);

	//if (FAILED(hr))	return E_FAIL;

	//��ƼŬ ������ ����.
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
	//�ð�
	float DeltaTime = _timeDelta*_emitterNum;

	//���� �ð� üũ
	if (autoStartTimeCheck(DeltaTime)) return;

	//�۵��ð� üũ
	if (autoActiveTimeCheck(DeltaTime)) return;

	//�ʱⰪ
	int checkNum = 0;
	//tagDxParticle* ptcVtx;
	//list<tagDxAttribute>::iterator iter;
	vector<tagDxAttribute>::iterator iter;


	//Ȱ��ȭ �� �� ������
	int InitNum = 0;
	int ActiveNum = 0;
	int DrawNum = 0;
	_drawPtcNum = 0;

	for (iter = _ptcList.begin(); iter != _ptcList.end(); ++iter)
	{
		//����
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

				//��Ȱ��ȭ
				iter->isAlive = true;
				iter->emitterNum = _emitterNum;
				if (_psTrans != NULL)
				{
					iter->psTransPos = _psTrans->GetWorldPosition();
					iter->matPsRot = _psTrans->GetWorldRotateMatrix();
				}

				_module->InitUpdate(iter);

				//���� ������Ʈ �簡��
				//_preUpdateOn = TRUE;

				//this->InitCreatePlane(&_ptcVertex[InitNum * 4], &_ptcIndex[InitNum * 6], iter, InitNum);

				//�ʱ� ȸ���� - �ڵ� ȸ���� ���Ͽ�
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


		//Ȱ��ȭ
		if (iter->isAlive)
		{
			_module->ActiveUpdate(iter);

			this->ActiveUpdatePlane(&_ptcVertex[_drawPtcNum * 4], &_ptcIndex[_drawPtcNum * 6], iter, _drawPtcNum);
			//���� ���ϱ�
			iter->age += DeltaTime;
			_drawPtcNum++;

		}
		ActiveNum++;


	}

	//�ð� �ʱ�ȭ
	if (_spawnTime <= _spawnCurrentTime)
	{
		_spawnCurrentTime = 0.0f;
	}

	//���� �ð� ��
	_spawnCurrentTime += DeltaTime;

}

void dxBoardEmitter::render()
{
	//���۽ð� �� ���۽ð��� ���� ����
	if (_startRenderOn == FALSE) return;
	if (_activeRenderOn == FALSE) return;

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

   //��ƼŬ Texture ����
	_device->SetTexture(0, _texture);

	//��ƼŬ ���� ���
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
	//	//tagDxParticleEX*	InPtcVertex = _ptcVertex + i*6;		//��ƼŬ ���ؽ�
	//	//DWORD*				InPtcIndex = _ptcIndex + i*4;			//��ƼŬ �ε���

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

	//��ƼŬ �׸��� ���� ��ó��
	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, true);

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	_device->SetTexture(0, NULL);
}





void dxBoardEmitter::ActiveUpdatePlane(tagDxParticleEX * ptcVertex, DWORD * ptcIndex, vector<tagDxAttribute>::iterator iter, DWORD drawParticleNum)
{
	//��ƼŬ ��ġ ��
	dx::transform ptcTrans;

	//ptcTrans.SetWorldPosition(iter->position);
	//ptcTrans.RotateSelf(D3DXVECTOR3(0.0f,D3DXToRadian(RandomFloatRange(10.0f,45.0f)),0.0f));
	//ptcTrans.RotateSelf(iter->rotateAngle);

	//_psTrans->SetDeviceWorld();

	//ī�޶� ��� ��������
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

	//Y�� ������
	/*getView._11 = getViewInverse._11;
	getView._13 = getViewInverse._13;
	getView._31 = getViewInverse._31;
	getView._33 = getViewInverse._33;*/

	//D3DXVECTOR3 cameraDir;

	//D3DXVec3Normalize(&cameraDir,&cameraPos);

	//������ ����
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

	//ȸ�� ����
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

	//�׷����� �߽� ��ġ�� ���� ����
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

	//����� �غ�
	//D3DXQUATERNION quatRot;
	//D3DXQuaternionRotationYawPitchRoll(&quatRot, D3DXToRadian(0), D3DXToRadian(90), D3DXToRadian(90));


	//������� ���� ����غ�
	//D3DXMATRIXA16 matRotate;
	//D3DXMatrixRotationQuaternion(&matRot, &quatRot);		//������� ���� ȸ�������� ȸ������� ���������.
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

	//���� ���� ����
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

	//�ε��� ���� ���� ( �ε��� ������ ���ݱ��� �׷����� Quad ����ŭ �������� ���� �־�� �Ѵ� )
	*(ptcIndex + 0) = (drawParticleNum * 4) + 0;
	*(ptcIndex + 1) = (drawParticleNum * 4) + 1;
	*(ptcIndex + 2) = (drawParticleNum * 4) + 2;
	*(ptcIndex + 3) = (drawParticleNum * 4) + 2;
	*(ptcIndex + 4) = (drawParticleNum * 4) + 1;
	*(ptcIndex + 5) = (drawParticleNum * 4) + 3;
}