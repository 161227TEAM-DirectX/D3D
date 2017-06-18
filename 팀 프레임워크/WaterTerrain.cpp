#include "stdafx.h"
#include "WaterTerrain.h"


WaterTerrain::WaterTerrain()
{
}


WaterTerrain::~WaterTerrain()
{
}

HRESULT WaterTerrain::init()
{
	return S_OK;
}

HRESULT WaterTerrain::init(float cellSize, int tileNum)
{
	_cellScale = cellSize;

	//가로세로 정점 수를 구한다.
	_verNumX = tileNum + 1;	//가로 정점갯수는 높이 맵에 가로 해상도 + 1 과 같다. (이유는 쿼드트리쓰려면 정점갯수가 2의N승 + 1 이여야 하기 때문에)
	_verNumZ = tileNum + 1;	//세로 정점잿수는 높이 맵에 세로 해상도 + 1 과 같다. (이유는 쿼드트리쓰려면 정점갯수가 2의N승 + 1 이여야 하기 때문에)
	_totalVerNum = _verNumX * _verNumZ;	//총 정점 갯수

										//가로세로 셀수
	_cellNumX = _verNumX - 1;
	_cellNumZ = _verNumZ - 1;
	_totalCellNum = _cellNumX * _cellNumZ;
	//총 삼각형수는
	_totalTriangle = _totalCellNum * 2;

	//정점버퍼 만들기
	_device->CreateVertexBuffer(
		sizeof(WATERVERTEX) * _totalVerNum,
		D3DUSAGE_WRITEONLY,
		WATERVERTEX::FVF_Flags,
		D3DPOOL_MANAGED,
		&_terrainVb,
		0);

	//지형 생성
	//지형 정점 가지고 있어야 한다.
	_terrainVertices = new WATERVERTEX[_totalVerNum];

	//정정위치를 계산하기
	for (int z = 0; z < _verNumZ; z++)
	{
		for (int x = 0; x < _verNumX; x++)
		{
			D3DXVECTOR3 pos;

			//정점의 x, z 위치 계산
			pos.x = (x - (_cellNumX * 0.5)) * _cellScale;
			pos.z = (-z + (_cellNumZ * 0.5)) * _cellScale;
			pos.y = 0;/*cosf(_flowAngle + x*100.0f)*/

					   //버텍스 배열인덱스 계산
			int idx = z * _verNumX + x;

			_terrainVertices[idx].pos = pos;

			_terrainVertices[idx].tu = ((float)x / (_verNumX - 1));
			_terrainVertices[idx].tv = ((float)z / (_verNumZ - 1));
		}
	}

	//만들어진 정점 버퍼를 Lock 하여 지형 정점 값을 쓴다.
	void* p = NULL;
	_terrainVb->Lock(0, 0, &p, 0);
	memcpy(p, _terrainVertices, sizeof(WATERVERTEX) * _totalVerNum);
	_terrainVb->Unlock();

	//인덱스 버퍼 만들기
	_device->CreateIndexBuffer(
		sizeof(WATERTRI) * _totalTriangle,
		D3DUSAGE_WRITEONLY,	//D3DUSAGE_WRITEONLY 예는 락안하고 고정정으로 버퍼내용이 유지될때 최고성능을 발휘, D3DUSAGE_DYNAMIC 락 을 자주하여 버퍼 내용이 바뀌는 경우
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,	//D3DUSAGE_DYNAMIC 을 쓰려면 무조건 D3DPOOL_DEFAULT
		&_terrainIb,
		0);


	// 정점 인덱스를 구한다
	LPWATERTRI pIndices = new tagWATERTRI[_totalTriangle];
	//인덱스 배열 인덱스
	int idx = 0;

	for (DWORD z = 0; z < _cellNumZ; z++)
	{
		for (DWORD x = 0; x < _cellNumX; x++)
		{
			// lt-----rt
			//  |    /|
			//  |   / |
			//  |  /  |
			//  | /   |
			//  |/    |
			// lb-----rb

			//해당 셀에 대한 정점 인덱스를 얻자
			DWORD lt = z * _verNumX + x;
			DWORD rt = z * _verNumX + x + 1;
			DWORD lb = ((z + 1)* _verNumX) + x;
			DWORD rb = ((z + 1)* _verNumX) + x + 1;

			//셀의 삼각형 하나
			pIndices[idx].dw0 = lt;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = lb;
			idx++;

			//셀의 삼각형 하나
			pIndices[idx].dw0 = lb;
			pIndices[idx].dw1 = rt;
			pIndices[idx].dw2 = rb;
			idx++;
		}
	}

	//인덱스 버퍼에 값을 쓴다.
	_terrainIb->Lock(0, 0, &p, 0);
	memcpy(p, pIndices, sizeof(WATERTRI) * _totalTriangle);
	_terrainIb->Unlock();

	_flowAngle = 0.0f;

	D3DXCreateTextureFromFile(_device, "Resource/Maptool/Textures/water/1.jpg", &temp);
	m_pWaterBump.push_back(temp);
	D3DXCreateTextureFromFile(_device, "Resource/Maptool/Textures/water/5.jpg", &temp);
	m_pWaterBump.push_back(temp);
	D3DXCreateTextureFromFile(_device, "Resource/Maptool/Textures/water/4.jpg", &temp);
	m_pWaterBump.push_back(temp);
	D3DXCreateTextureFromFile(_device, "Resource/Maptool/Textures/water/3.jpg", &temp);
	m_pWaterBump.push_back(temp);
	D3DXCreateTextureFromFile(_device, "Resource/Maptool/Textures/water/2.jpg", &temp);
	m_pWaterBump.push_back(temp);
	D3DXCreateTextureFromFile(_device, "Resource/Maptool/Textures/water/1.jpg", &temp);
	m_pWaterBump.push_back(temp);

	m_pReflectionMap = NULL;
	m_Effect_Water = NULL;
	m_timer = 0.0f;

	D3DXCreateCubeTextureFromFile(_device, "cubemap.dds", &m_pReflectionMap);

	HRESULT hr;
	LPD3DXBUFFER pBufferErrors = NULL;

	hr = D3DXCreateEffectFromFile(_device,
		"water.fx",
		NULL,
		NULL,
		D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY,
		NULL,
		&m_Effect_Water,
		&pBufferErrors);
	return S_OK;
}

void WaterTerrain::release()
{
	SAFE_RELEASE(_terrainVb);
	SAFE_RELEASE(_terrainIb);
	SAFE_DELETE_ARRAY(_terrainVertices);
}

void WaterTerrain::update(int number)
{
	if (number == 1)
	{
		waterOption.AlphaLayer = true;                                    //알파 레이어
		waterOption.BumpScale = 0.2f;                                      //범프 스케일
		waterOption.bumpSpeed = D3DXVECTOR2(0.015f, 0.015f);
		waterOption.deepColor = D3DXVECTOR4(0.3f, 0.4f, 0.4f, 1.0f);     //멀리서바지는 깊은색상인듯
		waterOption.fresnelBias = 0.328f; //프레 넬 바이어스
		waterOption.fresnelPower = 3.0f;   //프레 넬 파워
		waterOption.hdrMultiplier = 0.471f; //hdr 곱셈기
		waterOption.reflectionAmount = 1.0f; //얕은색상 옆에 흰색상 // 반사 양
		waterOption.reflectionBlur = 0.0f; //반사 흐림
		waterOption.reflectionColor = D3DXVECTOR4(0.95f, 1.0f, 1.0f, 1.0f); //반사색상
		waterOption.shallowColor = D3DXVECTOR4(0, 1, 1, 1.0f);    //얕은색상(바로맨위 색상)
		waterOption.textureScale = D3DXVECTOR2(1, 2); //텍스쳐를 나누너서 하는것
		waterOption.waterAmount = 0.3f;                  //바닥을 더욱더 파랗게 만드는거 같다
		waterOption.waveAmp = 0.3f;                      //웨이브 앰프 // 지형 왓다갓다하게 하는거같음
		waterOption.waveFreq = 0.028f;                     //파 주파수 //정확히모르겠음
		waterOption._using = true;
	}

	if (number == 2)
	{
		waterOption.AlphaLayer = true;                                    //알파 레이어
		waterOption.BumpScale = 0.2f;                                      //범프 스케일
		waterOption.bumpSpeed = D3DXVECTOR2(0.015f, 0.015f);
		waterOption.deepColor = D3DXVECTOR4(0.3f, 0.4f, 0.4f, 1.0f);     //멀리서바지는 깊은색상인듯
		waterOption.fresnelBias = 0.328f; //프레 넬 바이어스
		waterOption.fresnelPower = 3.0f;   //프레 넬 파워
		waterOption.hdrMultiplier = 0.471f; //hdr 곱셈기
		waterOption.reflectionAmount = 1.0f; //얕은색상 옆에 흰색상 // 반사 양
		waterOption.reflectionBlur = 0.0f; //반사 흐림
		waterOption.reflectionColor = D3DXVECTOR4(0.95f, 1.0f, 1.0f, 0.55f); //반사색상
		waterOption.shallowColor = D3DXVECTOR4(0, 1, 1, 1.0f);    //얕은색상(바로맨위 색상)
		waterOption.textureScale = D3DXVECTOR2(1, 2); //텍스쳐를 나누너서 하는것
		waterOption.waterAmount = 0.3f;                  //바닥을 더욱더 파랗게 만드는거 같다
		waterOption.waveAmp = 0.3f;                      //웨이브 앰프 // 지형 왓다갓다하게 하는거같음
		waterOption.waveFreq = 0.028f;                     //파 주파수 //정확히모르겠음
		waterOption._using = true;
	}

	if (number == 3)
	{
		waterOption.AlphaLayer = true;                                    //알파 레이어
		waterOption.BumpScale = 1.5f;                                      //범프 스케일
		waterOption.bumpSpeed = D3DXVECTOR2(0.015f, 0.015f);
		waterOption.deepColor = D3DXVECTOR4(1.0 / 255 * 160, 1.0 / 255 * 20, 1.0 / 255 * 170, 1.0f);    //멀리서바지는 깊은색상인듯
		waterOption.fresnelBias = 0.328f; //프레 넬 바이어스
		waterOption.fresnelPower = 3.0f;   //프레 넬 파워
		waterOption.hdrMultiplier = 0.471f; //hdr 곱셈기
		waterOption.reflectionAmount = 1.0f; //얕은색상 옆에 흰색상 // 반사 양
		waterOption.reflectionBlur = 0.0f; //반사 흐림
		waterOption.reflectionColor = D3DXVECTOR4(1.0 / 255 * 255, 1.0 / 255 * 255, 1.0 / 255 * 0, 0.55f); //반사색상
		waterOption.shallowColor = D3DXVECTOR4(1.0 / 255 * 80, 1.0 / 255 * 180, 1.0 / 255 * 60, 1.0f);    //얕은색상(바로맨위 색상)
		waterOption.textureScale = D3DXVECTOR2(1, 2); //텍스쳐를 나누너서 하는것
		waterOption.waterAmount = 0.3f;                  //바닥을 더욱더 파랗게 만드는거 같다
		waterOption.waveAmp = 0.8f;                      //웨이브 앰프 // 지형 왓다갓다하게 하는거같음
		waterOption.waveFreq = 0.528f;                     //파 주파수 //정확히모르겠음
		waterOption._using = true;
	}

	if (number == 4)
	{
		waterOption.AlphaLayer = true;                                    //알파 레이어
		waterOption.BumpScale = 0.2f;                                      //범프 스케일
		waterOption.bumpSpeed = D3DXVECTOR2(0.015f, 0.015f);
		waterOption.deepColor = D3DXVECTOR4(1.0f / 50 * 0, 1.0f / 255 * 150, 1.0f / 255 * 20, 0.6f);     //멀리서바지는 깊은색상인듯
		waterOption.fresnelBias = 0.328f; //프레 넬 바이어스
		waterOption.fresnelPower = 3.0f;   //프레 넬 파워
		waterOption.hdrMultiplier = 0.471f; //hdr 곱셈기
		waterOption.reflectionAmount = 1.0f; //얕은색상 옆에 흰색상 // 반사 양
		waterOption.reflectionBlur = 0.0f; //반사 흐림
		waterOption.reflectionColor = D3DXVECTOR4(1.0f / 255 * 190, 1.0f / 255 * 220, 1.0f / 255 * 70, 0.6f); //반사색상
		waterOption.shallowColor = D3DXVECTOR4(0, 1, 1, 1.0f);    //얕은색상(바로맨위 색상)
		waterOption.textureScale = D3DXVECTOR2(1, 2); //텍스쳐를 나누너서 하는것
		waterOption.waterAmount = 0.3f;                  //바닥을 더욱더 파랗게 만드는거 같다
		waterOption.waveAmp = 1.8f;                      //웨이브 앰프 // 지형 왓다갓다하게 하는거같음
		waterOption.waveFreq = 0.028f;                     //파 주파수 //정확히모르겠음
		waterOption._using = true;
	}

	if (number == 5)
	{
		waterOption.AlphaLayer = true;                                    //알파 레이어
		waterOption.BumpScale = 0.2f;                                      //범프 스케일
		waterOption.bumpSpeed = D3DXVECTOR2(0.015f, 0.015f);
		waterOption.deepColor = D3DXVECTOR4(0.3f, 0.7f, 0.3f, 1.0f);     //멀리서바지는 깊은색상인듯
		waterOption.fresnelBias = 0.328f; //프레 넬 바이어스
		waterOption.fresnelPower = 3.0f;   //프레 넬 파워
		waterOption.hdrMultiplier = 0.471f; //hdr 곱셈기
		waterOption.reflectionAmount = 1.0f; //얕은색상 옆에 흰색상 // 반사 양
		waterOption.reflectionBlur = 0.0f; //반사 흐림
		waterOption.reflectionColor = D3DXVECTOR4(0.7f, 0.3f, 0.1f, 0.55f); //반사색상
		waterOption.shallowColor = D3DXVECTOR4(0, 1, 1, 1.0f);    //얕은색상(바로맨위 색상)
		waterOption.textureScale = D3DXVECTOR2(1, 2); //텍스쳐를 나누너서 하는것
		waterOption.waterAmount = 0.3f;                  //바닥을 더욱더 파랗게 만드는거 같다
		waterOption.waveAmp = 1.8f;                      //웨이브 앰프 // 지형 왓다갓다하게 하는거같음
		waterOption.waveFreq = 0.028f;                     //파 주파수 //정확히모르겠음
		waterOption._using = true;
	}

	if (number == 6)
	{
		waterOption.AlphaLayer = true;                                    //알파 레이어
		waterOption.BumpScale = 2.2f;                                      //범프 스케일
		waterOption.bumpSpeed = D3DXVECTOR2(0.015f, 0.015f);
		waterOption.deepColor = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);     //멀리서바지는 깊은색상인듯
		waterOption.fresnelBias = 0.328f; //프레 넬 바이어스
		waterOption.fresnelPower = 3.0f;   //프레 넬 파워
		waterOption.hdrMultiplier = 0.471f; //hdr 곱셈기
		waterOption.reflectionAmount = 1.0f; //얕은색상 옆에 흰색상 // 반사 양
		waterOption.reflectionBlur = 0.0f; //반사 흐림
		waterOption.reflectionColor = D3DXVECTOR4(0.7f, 0.2f, 0.2f, 0.55f); //반사색상
		waterOption.shallowColor = D3DXVECTOR4(0.7f, 0.4f, 0.8f, 1.0f);    //얕은색상(바로맨위 색상)
		waterOption.textureScale = D3DXVECTOR2(1, 2); //텍스쳐를 나누너서 하는것
		waterOption.waterAmount = 0.5f;                  //바닥을 더욱더 파랗게 만드는거 같다
		waterOption.waveAmp = 0.6f;                      //웨이브 앰프 // 지형 왓다갓다하게 하는거같음
		waterOption.waveFreq = 0.028f;                     //파 주파수 //정확히모르겠음
		waterOption._using = true;
	}

	m_timer += 0.02f;

	_flowAngle += D3DXToRadian(2.0f);

	if (_flowAngle > D3DXToRadian(360.0f))
	{
		D3DXToRadian(0.0f);
	}
}

void WaterTerrain::render(int number)
{
	D3DXMATRIX				mat_WorldViewProj;
	D3DXMATRIX				mat_World;

	D3DXMatrixIdentity(&mat_WorldViewProj);
	D3DXMatrixIdentity(&mat_World);

	D3DXMATRIX				mat_View = _mainCamera.getViewMatrix(); /*= _mainCamera.getViewMatrix()*/;
	D3DXMATRIX				mat_Proj = _mainCamera.getProjectionMatrix();/* = _mainCamera.getProjectionMatrix()*/;

	_device->GetTransform(D3DTS_WORLD, &mat_World);
	_device->GetTransform(D3DTS_VIEW, &mat_View);
	_device->GetTransform(D3DTS_PROJECTION, &mat_Proj);

	mat_WorldViewProj = mat_World * mat_View * mat_Proj;

	//이쪽부분에 나중에 카메라 위치
	D3DXVECTOR4 eye(_mainCamera.GetWorldPosition(), 1.0f);

	//이펙트파일 적용 하는부분
	if (number == 1) 	m_Effect_Water->SetTexture("texture0", m_pWaterBump[0]);
	if (number == 2) m_Effect_Water->SetTexture("texture0", m_pWaterBump[1]);
	if (number == 3) m_Effect_Water->SetTexture("texture0", m_pWaterBump[2]);
	if (number == 4) m_Effect_Water->SetTexture("texture0", m_pWaterBump[3]);
	if (number == 5) m_Effect_Water->SetTexture("texture0", m_pWaterBump[4]);
	if (number == 6) m_Effect_Water->SetTexture("texture0", m_pWaterBump[5]);

	m_Effect_Water->SetTexture("texture1", m_pReflectionMap);


	m_Effect_Water->SetMatrix("WorldViewProj", &mat_WorldViewProj);

	m_Effect_Water->SetVector("eyePosition", &eye);


	m_Effect_Water->SetFloat("time", m_timer);

	m_Effect_Water->SetValue("textureScale", waterOption.textureScale, sizeof(D3DXVECTOR2));
	m_Effect_Water->SetFloat("waveFreq", waterOption.waveFreq);
	m_Effect_Water->SetFloat("waveAmp", waterOption.waveAmp);

	m_Effect_Water->SetFloat("BumpScale", waterOption.BumpScale);

	m_Effect_Water->SetValue("bumpSpeed", waterOption.bumpSpeed, sizeof(D3DXVECTOR2));
	m_Effect_Water->SetVector("deepColor", &waterOption.deepColor);
	m_Effect_Water->SetVector("shallowColor", &waterOption.shallowColor);
	m_Effect_Water->SetFloat("waterAmount", waterOption.waterAmount);

	m_Effect_Water->SetVector("reflectionColor", &waterOption.reflectionColor);
	m_Effect_Water->SetFloat("reflectionAmount", waterOption.reflectionAmount);
	m_Effect_Water->SetFloat("reflectionBlur", waterOption.reflectionBlur);

	m_Effect_Water->SetFloat("fresnelPower", waterOption.fresnelPower);
	m_Effect_Water->SetFloat("fresnelBias", waterOption.fresnelBias);
	m_Effect_Water->SetFloat("hdrMultiplier", waterOption.hdrMultiplier);



	if (waterOption.AlphaLayer)
	{
		// 텍스쳐 사용 준비. 
		DWORD alpha = 175;
		_device->SetRenderState(D3DRS_TEXTUREFACTOR, (0x00ffffff) + (alpha << 24));
		_device->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

		// 알파 채널을 넣어서 반투명하게 하자.
		_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
		_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	m_Effect_Water->SetTechnique("water");



	UINT uPasses;
	m_Effect_Water->Begin(&uPasses, 0);

	for (UINT uPass = 0; uPass < uPasses; ++uPass)
	{
		m_Effect_Water->BeginPass(uPass);

		//정점렌더
		_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		_device->SetFVF(WATERVERTEX::FVF_Flags);
		_device->SetStreamSource(0, _terrainVb, 0, sizeof(WATERVERTEX));
		_device->SetIndices(_terrainIb);
		_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _totalVerNum, 0, _totalTriangle);
		_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		m_Effect_Water->EndPass();
	}

	m_Effect_Water->End();


	if (waterOption.AlphaLayer)
		_device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}