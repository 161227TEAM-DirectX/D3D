#include "stdafx.h"
#include "dxPlaneEmitter.h"

HRESULT dxPlaneEmitter::init(string textureFileName, int OneTimePaticleNum, float spawnTime, int totalPaticleNum)
{
	_startDelayTimeOn = false;
	_onePtcNum = OneTimePaticleNum;
	_totalPtcNum = totalPaticleNum;
	_spawnTime = spawnTime;
	_spawnCurrentTime = _spawnTime;

	_startDelayTime = 0.0f;
	_currentDelayTime = 0.0f;


	_ptcVertex = new tagDxParticleEX[_totalPtcNum * 4];
	_ptcIndex = new DWORD[_totalPtcNum * 6];

	//_trans = new transform[_totalPtcNum];


	
	HRESULT hr = NULL;

	//�ؽ��� �ҷ�����
	hr = D3DXCreateTextureFromFile(_device, textureFileName.c_str(), &_texture);

	if (FAILED(hr))	return E_FAIL;

	//��ƼŬ ������ ����.
	_ptcList.resize(_totalPtcNum);

	return S_OK;
}

void dxPlaneEmitter::relese()
{
	SAFE_DELETE_ARRAY(_ptcVertex);
	SAFE_DELETE_ARRAY(_ptcIndex);
	SAFE_DELETE_ARRAY(_trans);
}

void dxPlaneEmitter::update()
{


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
			//ptcVtx->position = iter->position;
		}


		if (_spawnTime <= _spawnCurrentTime)
		{
			if (iter->isAlive == false && checkNum < _onePtcNum)
			{
				//��Ȱ��ȭ
				//iter->size = _constPaticleSize;
				iter->isAlive = true;
				_module->InitUpdate(iter);

				//this->InitCreatePlane(&_ptcVertex[InitNum * 4], &_ptcIndex[InitNum * 6], iter, InitNum);

				checkNum++;
				//if (checkNum >= _onePtcNum) break;
			}
			//_ptcVtx++;

		}
		InitNum++;

		

		//Ȱ��ȭ
		if (iter->isAlive)
		{

			//this->CreatePlane(&_ptcVertex[ActiveNum*4],&_ptcIndex[ActiveNum*6],iter);

			//iter->acceleration += iter->acceleration*0.01;
			//ptcVtx->position += (iter->velocity + iter->acceleration)*_timeDelta;
			//_ptcVtx[ActiveNum].position -= iter->circleSpeed;
			_module->ActiveUpdate(iter);
			//ptcVtx->position = D3DXVECTOR3(sinf(angle),0.0f,cosf(angle));
			//ptcVtx->position = iter
			//_ptcVtx[ActiveNum].position += iter->circleSpeed + iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta) / 2.0f) + iter->posDirectVel*_timeDelta;
			//ptcVtx->position += iter->angleSpeed*_timeDelta+ iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta)/2.0f);
			//_ptcVtx[ActiveNum].size = iter->size;
			//_ptcVtx[ActiveNum].color = iter->color;
			this->ActiveUpdatePlane(&_ptcVertex[_drawPtcNum * 4], &_ptcIndex[_drawPtcNum * 6], iter, _drawPtcNum);
			//���� ���ϱ�
			iter->age += _timeDelta;
			//_drawVtx[_drawPtcNum] = _ptcVtx[ActiveNum];
			_drawPtcNum++;
		}
		ActiveNum++;
		//_ptcVtx++;
	}

	//�ð� �ʱ�ȭ
	if (_spawnTime <= _spawnCurrentTime)
	{
		_spawnCurrentTime = 0.0f;
	}



	if (_startDelayTime <= _currentDelayTime)
	{
		_spawnCurrentTime += _timeDelta;
	}
	else
	{
		_currentDelayTime += _timeDelta;
	}



}

void dxPlaneEmitter::render()
{
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

	/*if (_bLocal == false)
	{
		D3DXMatrixIdentity(&matWorld);
	}
	else
	{
		matWorld = this->_transform->GetFinalMatrix();
	}*/
	//_device->SetTransform(D3DTS_WORLD, &matWorld);

	//��ƼŬ Texture ����
	_device->SetTexture(0, _texture);

	//��ƼŬ ���� ���
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


	//��ƼŬ �׸��� ���� ��ó��
	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, true);

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	_device->SetTexture(0, NULL);
}




void dxPlaneEmitter::InitCreatePlane(tagDxParticleEX * ptcVertex, DWORD * ptcIndex, vector<tagDxAttribute>::iterator iter, DWORD drawParticleNum)
{
	//��ƼŬ ��ġ ��
	dx::transform ptcTrans;

	ptcTrans.SetWorldPosition(iter->position);
	ptcTrans.RotateSelf(iter->rotateAngle);

	//ptcTrans.RotateSelf(D3DXVECTOR3(0.0f, D3DXToRadian(RandomFloatRange(10.0f, 45.0f)), 0.0f));

	D3DXVECTOR3 x = ptcTrans.GetRight()*iter->horizontal;
	D3DXVECTOR3 z = ptcTrans.GetForward()*iter->vertical;

	float halfScale = iter->size*0.5;

	D3DXCOLOR inColor = iter->color;

	D3DXVECTOR3 posCenter = iter->position;

	D3DXVECTOR2 uv0 = iter->UV0;
	D3DXVECTOR2 uv1 = iter->UV1;
	D3DXVECTOR2 uv2 = iter->UV2;
	D3DXVECTOR2 uv3 = iter->UV3;


	

	//int dwPtcNum = drawParticleNum;

	//D3DXVECTOR3 center = _transform.GetWorldPosition();

	//+= iter->circleSpeed + iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta) / 2.0f) + iter->posDirectVel*_timeDelta;

	//���� ���� ����
	(ptcVertex + 0)->position = posCenter + (-x * halfScale) + (z * halfScale);
	(ptcVertex + 1)->position = posCenter + (x * halfScale) + (z * halfScale);
	(ptcVertex + 2)->position = posCenter + (-x * halfScale) + (-z * halfScale);
	(ptcVertex + 3)->position = posCenter + (x * halfScale) + (-z * halfScale);

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




void dxPlaneEmitter::ActiveUpdatePlane(tagDxParticleEX * ptcVertex, DWORD * ptcIndex, vector<tagDxAttribute>::iterator iter, DWORD drawParticleNum)
{
	//��ƼŬ ��ġ ��
	dx::transform ptcTrans;

	ptcTrans.SetWorldPosition(iter->position);
	//ptcTrans.RotateSelf(D3DXVECTOR3(0.0f,D3DXToRadian(RandomFloatRange(10.0f,45.0f)),0.0f));
	ptcTrans.RotateSelf(iter->rotateAngle);


	D3DXVECTOR3 x = ptcTrans.GetRight()*iter->horizontal;
	D3DXVECTOR3 z = ptcTrans.GetForward()*iter->vertical;

	float halfScale = iter->size*0.5;

	D3DXCOLOR inColor = iter->color;


	D3DXVECTOR3 posCenter = iter->posCenter;

	//int dwPtcNum = drawParticleNum;

	D3DXVECTOR2 uv0 = iter->UV0;
	D3DXVECTOR2 uv1 = iter->UV1;
	D3DXVECTOR2 uv2 = iter->UV2;
	D3DXVECTOR2 uv3 = iter->UV3;

	//D3DXVECTOR3 center = _transform.GetWorldPosition();

	//iter->circleSpeed + iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta) / 2.0f) + iter->posDirectVel*_timeDelta;

	//���� ���� ����
	(ptcVertex + 0)->position = posCenter + (-x * halfScale) + (z * halfScale);
	(ptcVertex + 1)->position = posCenter + (x * halfScale) + (z * halfScale);
	(ptcVertex + 2)->position = posCenter + (-x * halfScale) + (-z * halfScale);
	(ptcVertex + 3)->position = posCenter + (x * halfScale) + (-z * halfScale);

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

	//�ε��� ���� ���� ( �ε��� ������ ���ݱ��� �׷����� Quad ����ŭ �������� ���� �־�� �Ѵ� )
	*(ptcIndex + 0) = (drawParticleNum * 4) + 0;
	*(ptcIndex + 1) = (drawParticleNum * 4) + 1;
	*(ptcIndex + 2) = (drawParticleNum * 4) + 2;
	*(ptcIndex + 3) = (drawParticleNum * 4) + 2;
	*(ptcIndex + 4) = (drawParticleNum * 4) + 1;
	*(ptcIndex + 5) = (drawParticleNum * 4) + 3;
}