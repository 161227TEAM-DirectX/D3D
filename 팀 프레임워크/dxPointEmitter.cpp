#include "stdafx.h"
#include "dxPointEmitter.h"


HRESULT dxPointEmitter::init(string textureFileName,int OneTimePaticleNum, float spawnTime, int totalPaticleNum)
{

	_spawnTime = spawnTime;
	_spawnCurrentTime = _spawnTime;

	//int plusPtc = 1;
	//if		(_spawnTime < 0.06f) { plusPtc = (int)(1000 * spawnTime);}
	//else if (_spawnTime <= 0.5f) {plusPtc = (int)(100 * spawnTime);}

	//��ƼŬ ���� �Ǵ� _vb ����
	_totalPtcNum = totalPaticleNum;
	//if (totalPaticleNum == 0) { _totalPtcNum = OneTimePaticleNum * 50 * plusPtc; }	// + (OneTimePaticleNum * ->lifeTime);	//�� ��ƼŬ ����(���Ƿ� ���� ������)
	_onePtcNum = OneTimePaticleNum;				//�ѹ��� ������ ��ƼŬ ����

	HRESULT hr = NULL;
	/*hr = _device->CreateVertexBuffer(_vbSize * sizeof(tagDxParticle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		PARTICLE_FVF,
		D3DPOOL_DEFAULT,
		&_vb,
		0);*/

	//if (FAILED(hr))	return E_FAIL;


	//�ؽ��� �ҷ�����
	_texture = *PTM->LoadImgPathAndName(textureFileName);
	if(_texture == NULL)	return E_FAIL;

	//hr = D3DXCreateTextureFromFile(_device, textureFileName.c_str(), &_texture);
	
	//if (FAILED(hr))	return E_FAIL;
	
	//hr = D3DXCreateTextureFromFile(_device, textureFileName.c_str(), &_testTex);
	//hr = D3DXCreateTextureFromFile(_device, textureFileName.c_str(), &_testTex2);

	//memcpy(_testTex2, _testTex, sizeof(LPDIRECT3DTEXTURE9));

	////�ؽ��� �ռ� ����

	//D3DSURFACE_DESC dsc;
	//D3DLOCKED_RECT	drc;
	//DWORD*	pColorSrc = NULL;
	//DWORD*	pColorDst = NULL;


	//// ���� �ؽ�ó ���� ���
	//_testTex2->GetLevelDesc(0, &dsc);

	//int		texImgW = dsc.Width;
	//int		texImgH = dsc.Height;

	//// �ӽ� ���� ����
	//pColorSrc = new DWORD[texImgW * texImgH];


	//// ���� �ؽ�ó �ȼ� ���� �ӽ� ���ۿ� ����
	////_testTex2->LockRect(0, &drc, NULL, 0);
	//memcpy(pColorSrc, drc.pBits, texImgW * texImgH * sizeof(DWORD));
	//pColorDst = (DWORD*)drc.pBits;
	////_testTex2->UnlockRect(0);

	//D3DXCOLOR texColor;

	//for (int y = 0; y < texImgH; ++y)
	//{
	//	for (int x = 0; x < texImgW; ++x)
	//	{
	//		int nIdx = y*texImgW + x;

	//		texColor = pColorSrc[nIdx];

	//		//I = 0.30R + 0.59G + 0.11B
	//		float grayScale = texColor.r * 0.2126f + texColor.g * 0.7152f + texColor.b * 0.0722f;

	//		//pColorDst[nIdx] = D3DXCOLOR(grayScale, grayScale, grayScale, texColor.a);
	//		pColorDst[nIdx] = D3DXCOLOR(texColor.r, texColor.g, texColor.b, grayScale);
	//	}
	//}

	/*D3DXCreateTexture(m_pd3dDevice
		, m_pTxSrc->GetImageWidth()
		, m_pTxSrc->GetImageHeight()
		, 1, 0
		, D3DFMT_A8B8G8R8, D3DPOOL_MANAGED, &m_pTxMono);*/

	//void McColor_TransColorMono(DWORD* pOut, DWORD* pIn, INT iImgW, INT iImgH)
	//McColor_ColorRed(pColorDst, pColorSrc, nImgW, nImgH);

	//m_pTxMono->UnlockRect(0);
	//McColor_TransColorMono(pColorDst, pColorSrc, nImgW, nImgH);


	// �ӽ� ���� ����
	//SAFE_DELETE_ARRAY(pColorSrc);

	////�ؽ��� ����
	//_device->SetTexture(0, _testTex);
	//_device->SetTexture(1, _testTex2);
	//
	////�ؽ���
	//_device->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	//_device->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);

	////�̹��� ����
	//_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//_device->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	////(�������� ��ȣ, ó�����, ���޹��?)
	////_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	//_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	////_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	////_device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	//_device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//_device->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//_device->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	//_device->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTOP_DISABLE);

	//_device->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
	//_device->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_DISABLE);



	//_device->GetTexture(1, (IDirect3DBaseTexture9**)&_texture);

	//�ȼ�Į��(RGB) * �ȼ����İ�(100 % �ΰ��) * ���ϴ� ���İ�(100 % �ΰ��)
	/*_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);*/
	//m_pD3dD9->SetRenderState(D3DRS_TEXTUREFACTOR,  D3DCOLOR_ARGB(���ϴ� ���İ�, 255, 255, 255));



	/*_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	_device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);*/

	//_testTex

	//_device->SetTexture(0, NULL);
	 
	

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
				iter->emitterNum = _emitterNum;
				if (_psTrans != NULL)
				{
					iter->psTransPos = _psTrans->GetWorldPosition();
					iter->matPsRot = _psTrans->GetWorldRotateMatrix();
				}

				_module->InitUpdate(iter);
				_ptcVtx[InitNum].position = iter->InitPos;

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
			//if (_realtimeTrackingPosOn) { iter->matPsRot = _psTrans->GetWorldRotateMatrix(); iter->psTransPos = _psTrans->GetWorldPosition();}
			_module->ActiveUpdate(iter);
			//ptcVtx->position = D3DXVECTOR3(sinf(angle),0.0f,cosf(angle));

			//�̰� ����
			//_ptcVtx[ActiveNum].position += (-iter->preCircleSpeed) + iter->circleSpeed + iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta) / 2.0f) + iter->posDirectVel*_timeDelta;
			//�̰� ������
		/*	if (_realtimeTrackingPosOn)
			{
				_module->setRealTimeTrackingOn();
				iter->matPsRot = _psTrans->GetWorldRotateMatrix(); iter->psTransPos = _psTrans->GetWorldPosition();
				_ptcVtx[ActiveNum].position = iter->TrackingPos;
			}
			else
			{
				_ptcVtx[ActiveNum].position += iter->FinalDir;
			}
			*/
			_ptcVtx[ActiveNum].position += iter->FinalDir;

			//ptcVtx->position += iter->angleSpeed*_timeDelta+ iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta)/2.0f);
			_ptcVtx[ActiveNum].size = iter->size;
			_ptcVtx[ActiveNum].color = iter->color;

			//���� ���ϱ�
			iter->age += DeltaTime;

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

	//���� �ð� ��
	_spawnCurrentTime += DeltaTime;




}


void dxPointEmitter::render()
{
	//���۽ð� �� ���۽ð��� ���� ����
	if (_startRenderOn == FALSE) return;
	if (_activeRenderOn == FALSE) return;

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

