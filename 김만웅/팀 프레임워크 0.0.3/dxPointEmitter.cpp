#include "stdafx.h"
#include "dxPointEmitter.h"


HRESULT dxPointEmitter::init(string textureFileName,int OneTimePaticleNum, float spawnTime, int totalPaticleNum)
{
	_startDelayTimeOn = false;
	_spawnTime = spawnTime;
	_spawnCurrentTime = _spawnTime;
	//_constPaticleSize = 1.0f;
	_currentDelayTime = 0.0f;
	_startDelayTime = 0.0f;

	int plusPtc = 1;
	if		(_spawnTime < 0.06f) { plusPtc = (int)(1000 * spawnTime);}
	else if (_spawnTime <= 0.5f) {plusPtc = (int)(100 * spawnTime);}

	//��ƼŬ ���� �Ǵ� _vb ����
	_totalPtcNum = totalPaticleNum;
	if (totalPaticleNum == 0) { _totalPtcNum = OneTimePaticleNum * 50 * plusPtc; }	// + (OneTimePaticleNum * ->lifeTime);	//�� ��ƼŬ ����(���Ƿ� ���� ������)
	_onePtcNum = OneTimePaticleNum;				//�ѹ��� ������ ��ƼŬ ����

	HRESULT hr = NULL;
	/*hr = _device->CreateVertexBuffer(_vbSize * sizeof(tagDxParticle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		PARTICLE_FVF,
		D3DPOOL_DEFAULT,
		&_vb,
		0);*/

	if (FAILED(hr))	return E_FAIL;

	//�ؽ��� �ҷ�����
	hr = D3DXCreateTextureFromFile(_device, textureFileName.c_str(), &_texture);

	if (FAILED(hr))	return E_FAIL;

	//��ƼŬ ������ ����.
	_ptcList.resize(_totalPtcNum);
	
	_ptcVtx = new tagDxParticle[(int)_totalPtcNum];
	_drawVtx = new tagDxParticle[(int)_totalPtcNum];

	return S_OK;
}

void dxPointEmitter::relese()
{
	SAFE_DELETE(_module);
	SAFE_DELETE(_trans);
}


void dxPointEmitter::update()
{
	
	//�ʱⰪ
	int checkNum = 0;
	//tagDxParticle* ptcVtx;
	//list<tagDxAttribute>::iterator iter;
	vector<tagDxAttribute>::iterator iter;

	//_ptcVtx[0].color = 0x00000000;

	//�վ��
	//if (_spawnTime <= _spawnCurrentTime)
	//{
	//	_spawnCurrentTime = 0.0f;

	//	int num = 0;
	//	//_vb->Lock(0, 0, (void**)&ptcVtx, 0);
	//	for (iter = _ptcList.begin(); iter != _ptcList.end(); ++iter)
	//	{
	//		if (iter->isAlive == false)
	//		{
	//			//��Ȱ��ȭ
	//			iter->size = _constPaticleSize;
	//			iter->isAlive = true;
	//			_module->InitUpdate(iter);
	//			_ptcVtx[num].position = iter->position;
	//			//_ptcVtx->position = iter->position;
	//			//ptcVtx->size = RandomFloatRange(1.0f,10.0f);->�������� ������.
	//			//_ptcVtx->color = iter->color;
	//			_ptcVtx[num].color = iter->color;

	//			checkNum++;
	//			if (checkNum >= _onePtcNum) break;
	//		}
	//		//_ptcVtx++;
	//		num++;
	//	}
	//	//_vb->Unlock();
	//}

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

		

		//�ʱ�ȭ�κ�
		if (_spawnTime <= _spawnCurrentTime)
		{
			if (iter->isAlive == false && checkNum < _onePtcNum)
			{
				//��Ȱ��ȭ
				//iter->size = _constPaticleSize;
				iter->isAlive = true;
				_module->InitUpdate(iter);
				_ptcVtx[InitNum].position = iter->position;
				//_ptcVtx->position = iter->position;
				//ptcVtx->size = RandomFloatRange(1.0f,10.0f);->�������� ������.
				//_ptcVtx->color = iter->color;
				_ptcVtx[InitNum].size = iter->size;
				_ptcVtx[InitNum].color = iter->color;

				checkNum++;
				//if (checkNum >= _onePtcNum) break;
			}

		}
		InitNum++;
		
		//Ȱ��ȭ
		if (iter->isAlive)
		{
			//iter->acceleration += iter->acceleration*0.01;
			//ptcVtx->position += (iter->velocity + iter->acceleration)*_timeDelta;
			//_ptcVtx[ActiveNum].position -= iter->circleSpeed;
			_module->ActiveUpdate(iter);
			//ptcVtx->position = D3DXVECTOR3(sinf(angle),0.0f,cosf(angle));

			//�̰� ����
			//_ptcVtx[ActiveNum].position += (-iter->preCircleSpeed) + iter->circleSpeed + iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta) / 2.0f) + iter->posDirectVel*_timeDelta;
			//�̰� ������
			_ptcVtx[ActiveNum].position += iter->FinalPos;
			//ptcVtx->position += iter->angleSpeed*_timeDelta+ iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta)/2.0f);
			_ptcVtx[ActiveNum].size = iter->size;
			_ptcVtx[ActiveNum].color = iter->color;

			//���� ���ϱ�
			iter->age += _timeDelta;

			_drawVtx[_drawPtcNum] = _ptcVtx[ActiveNum];
			_drawPtcNum++;

		}
		ActiveNum++;

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






	////�վ��
	//if (_spawnTime <= _spawnCurrentTime)
	//{
	//	_spawnCurrentTime = 0.0f;

	//	_vb->Lock(0, 0, (void**)&ptcVtx, 0);
	//	for (iter = _ptcList.begin(); iter != _ptcList.end(); ++iter)
	//	{
	//		if (iter->isAlive == false)
	//		{
	//			//��Ȱ��ȭ
	//			iter->size = _constPaticleSize;
	//			iter->isAlive = true;
	//			_module->InitUpdate(iter);
	//			ptcVtx->position = iter->position;
	//			//ptcVtx->size = RandomFloatRange(1.0f,10.0f);->�������� ������.
	//			ptcVtx->color = iter->color;

	//			checkNum++;
	//			if (checkNum >= _onePtcNum) break;
	//		}
	//		ptcVtx++;
	//	}
	//	//_vb->Unlock();
	//}

	////Ȱ��ȭ �� �� ������
	//_vb->Lock(0, 0, (void**)&ptcVtx, 0);
	//for (iter = _ptcList.begin(); iter != _ptcList.end(); ++iter)
	//{
	//	////����
	//	if (iter->lifeTime <= iter->age)
	//	{
	//		iter->isAlive = false;
	//		iter->age = 0.0f;
	//		//ptcVtx->position = iter->position;
	//	}

	//	//Ȱ��ȭ
	//	if (iter->isAlive)
	//	{
	//		//iter->acceleration += iter->acceleration*0.01;
	//		//ptcVtx->position += (iter->velocity + iter->acceleration)*_timeDelta;
	//		ptcVtx->position -= iter->circleSpeed;
	//		_module->ActiveUpdate(iter);
	//		//ptcVtx->position = D3DXVECTOR3(sinf(angle),0.0f,cosf(angle));
	//		//ptcVtx->position = iter
	//		ptcVtx->position += iter->circleSpeed + iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta) / 2.0f) + iter->posDirectVel*_timeDelta;
	//		//ptcVtx->position += iter->angleSpeed*_timeDelta+ iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta)/2.0f);
	//		ptcVtx->color = iter->color;

	//		//���� ���ϱ�
	//		iter->age += _timeDelta;
	//	}

	//	ptcVtx++;

	//	//������
	//	//if (_vbMaxStep*_ptcSize < num) break;
	//}

	//_vb->Unlock();

	///*if (_spawnTime <= _spawnCurrentTime)
	//{
	//	_spawnCurrentTime = 0.0f;
	//	_vbMaxStep++;
	//}*/
	//if (_startDelayTime <= _currentDelayTime)
	//{
	//	_spawnCurrentTime += _timeDelta;
	//}
	//else
	//{
	//	_currentDelayTime += _timeDelta;
	//}
	////D3DXMatrixRotationY(&_matWorld,D3DXToRadian(180));
	////D3DXMatrixScaling(&_matWorld, 2.0f,2.0f,2.0f);

	

}


void dxPointEmitter::render()
{


	_device->SetRenderState(D3DRS_ZENABLE, TRUE);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);


	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	//_device->SetRenderState(D3DRS_POINTSIZE, FtoDw(1.0f));
	_device->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.1f));
	//_device->SetRenderState(D3DRS_POINTSIZE_MAX, (DWORD)10000.0f);

	//�Ÿ��� ���� ����?
	_device->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(1.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(2.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(3.0f));

	//_device->SetTransform(D3DTS_WORLD, &_matWorld);
	_device->SetTexture(0, _texture);
	//_device->SetStreamSource(0, _vb, 0, sizeof(tagDxParticle));
	_device->SetFVF(PARTICLE_FVF);

	//_matWorld
	
	//this->_trans->RotateWorld(0.0f,D3DXToRadian(0.0f),0.0f);
	//this->_trans->SetRotateWorld(0.0f, D3DXToRadian(30.0f), 0.0f);
	////_matWorld = _trans->GetFinalMatrix();
	//_trans->SetDeviceWorld();
	//this->_trans->SetWorldMatrix(_matWorld);
	//_device->SetTransform(D3DTS_WORLD, &_matWorld);
	//int num = 0;
	//int drawNum = 0;
	////_device->DrawPrimitive(D3DPT_POINTLIST, 0, _ptcSize*_vbMaxStep);
	//list<tagDxAttribute>::iterator iter;
	//tagDxParticle* tmepVtx = _ptcVtx;
	//for (iter = _ptcList.begin(); iter != _ptcList.end(); ++iter)
	//{
	//	//tmepVtx = NULL;
	//	//tmepVtx = &_ptcVtx[num];
	//	if (iter->isAlive == true)
	//	{
	//		//_device->SetRenderState(D3DRS_POINTSIZE, FtoDw(1.0f));
	//		//_device->SetRenderState(D3DRS_POINTSIZE, FtoDw(RandomFloatRange(1.0f, 10.0f)));
	//		//_device->SetRenderState(D3DRS_POINTSIZE, FtoDw(iter->size));
	//		//_device->DrawPrimitive(D3DPT_POINTLIST, num , 1);
	//		//_device->DrawPrimitiveUP(D3DPT_POINTLIST, 1, tmepVtx, sizeof(tagDxParticle));
	//		_drawVtx[drawNum] = _ptcVtx[num];
	//		drawNum++;
	//	}
	//	num++;
	//}

	_device->DrawPrimitiveUP(D3DPT_POINTLIST, _drawPtcNum, _drawVtx, sizeof(tagDxParticle));

	_device->SetTexture(0, NULL);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//_device->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	//_device->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);

}

