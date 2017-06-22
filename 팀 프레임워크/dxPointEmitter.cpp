#include "stdafx.h"
#include "dxPointEmitter.h"


HRESULT dxPointEmitter::init(string textureFileName,int OneTimePaticleNum, float spawnTime, int totalPaticleNum)
{

	_spawnTime = spawnTime;
	_spawnCurrentTime = _spawnTime;

	//int plusPtc = 1;
	//if		(_spawnTime < 0.06f) { plusPtc = (int)(1000 * spawnTime);}
	//else if (_spawnTime <= 0.5f) {plusPtc = (int)(100 * spawnTime);}

	//파티클 개수 또는 _vb 개수
	_totalPtcNum = totalPaticleNum;
	//if (totalPaticleNum == 0) { _totalPtcNum = OneTimePaticleNum * 50 * plusPtc; }	// + (OneTimePaticleNum * ->lifeTime);	//총 파티클 개수(임의로 수를 곱해줌)
	_onePtcNum = OneTimePaticleNum;				//한번에 나오는 파티클 개수

	HRESULT hr = NULL;
	/*hr = _device->CreateVertexBuffer(_vbSize * sizeof(tagDxParticle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		PARTICLE_FVF,
		D3DPOOL_DEFAULT,
		&_vb,
		0);*/

	//if (FAILED(hr))	return E_FAIL;


	//텍스쳐 불러오기
	_texture = *PTM->LoadImgPathAndName(textureFileName);
	if(_texture == NULL)	return E_FAIL;

	//hr = D3DXCreateTextureFromFile(_device, textureFileName.c_str(), &_texture);
	
	//if (FAILED(hr))	return E_FAIL;
	
	//hr = D3DXCreateTextureFromFile(_device, textureFileName.c_str(), &_testTex);
	//hr = D3DXCreateTextureFromFile(_device, textureFileName.c_str(), &_testTex2);

	//memcpy(_testTex2, _testTex, sizeof(LPDIRECT3DTEXTURE9));

	////텍스쳐 합성 시험

	//D3DSURFACE_DESC dsc;
	//D3DLOCKED_RECT	drc;
	//DWORD*	pColorSrc = NULL;
	//DWORD*	pColorDst = NULL;


	//// 원본 텍스처 정보 얻기
	//_testTex2->GetLevelDesc(0, &dsc);

	//int		texImgW = dsc.Width;
	//int		texImgH = dsc.Height;

	//// 임시 버퍼 생성
	//pColorSrc = new DWORD[texImgW * texImgH];


	//// 원본 텍스처 픽셀 값을 임시 버퍼에 복사
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


	// 임시 버퍼 해제
	//SAFE_DELETE_ARRAY(pColorSrc);

	////텍스쳐 세팅
	//_device->SetTexture(0, _testTex);
	//_device->SetTexture(1, _testTex2);
	//
	////텍스쳐
	//_device->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	//_device->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);

	////이미지 필터
	//_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//_device->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	////(스테이지 번호, 처리방법, 전달방식?)
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

	//픽셀칼러(RGB) * 픽셀알파값(100 % 로계산) * 원하는 알파값(100 % 로계산)
	/*_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);*/
	//m_pD3dD9->SetRenderState(D3DRS_TEXTUREFACTOR,  D3DCOLOR_ARGB(원하는 알파값, 255, 255, 255));



	/*_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	_device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);*/

	//_testTex

	//_device->SetTexture(0, NULL);
	 
	

	//파티클 사이즈 정함.
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

	//뿜어내기
	//if (_spawnTime <= _spawnCurrentTime)
	//{
	//	_spawnCurrentTime = 0.0f;

	//	int num = 0;
	//	//_vb->Lock(0, 0, (void**)&ptcVtx, 0);
	//	for (iter = _ptcList.begin(); iter != _ptcList.end(); ++iter)
	//	{
	//		if (iter->isAlive == false)
	//		{
	//			//재활성화
	//			iter->size = _constPaticleSize;
	//			iter->isAlive = true;
	//			_module->InitUpdate(iter);
	//			_ptcVtx[num].position = iter->position;
	//			//_ptcVtx->position = iter->position;
	//			//ptcVtx->size = RandomFloatRange(1.0f,10.0f);->생각보다 느리다.
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
			//ptcVtx->position = iter->position;
		}

		

		//초기화부분
		if (_spawnTime <= _spawnCurrentTime)
		{
			if (iter->isAlive == false && checkNum < _onePtcNum)
			{
				//재활성화
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
				//ptcVtx->size = RandomFloatRange(1.0f,10.0f);->생각보다 느리다.
				//_ptcVtx->color = iter->color;
				_ptcVtx[InitNum].size = iter->size;
				_ptcVtx[InitNum].color = iter->color;

				checkNum++;
				//if (checkNum >= _onePtcNum) break;
			}

		}
		InitNum++;
		
		//활성화
		if (iter->isAlive)
		{
			//if (_realtimeTrackingPosOn) { iter->matPsRot = _psTrans->GetWorldRotateMatrix(); iter->psTransPos = _psTrans->GetWorldPosition();}
			_module->ActiveUpdate(iter);
			//ptcVtx->position = D3DXVECTOR3(sinf(angle),0.0f,cosf(angle));

			//이거 느림
			//_ptcVtx[ActiveNum].position += (-iter->preCircleSpeed) + iter->circleSpeed + iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta) / 2.0f) + iter->posDirectVel*_timeDelta;
			//이게 빠르다
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

			//나이 더하기
			iter->age += DeltaTime;

			_drawVtx[_drawPtcNum] = _ptcVtx[ActiveNum];
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


void dxPointEmitter::render()
{
	//시작시간 과 동작시간에 따른 렌더
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

	//거리에 따른 비율?
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

