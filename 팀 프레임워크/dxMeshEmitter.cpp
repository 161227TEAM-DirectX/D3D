#include "stdafx.h"
#include "dxMeshEmitter.h"


HRESULT dxMeshEmitter::init(string xFileName, int OneTimePaticleNum, float spawnTime, int totalPaticleNum)
{
	_onePtcNum = OneTimePaticleNum;
	_totalPtcNum = totalPaticleNum;
	_spawnTime = spawnTime;
	_spawnCurrentTime = _spawnTime;

	//_ptcVertex = new tagDxParticleEX[_totalPtcNum * 4];
	//_ptcIndex = new DWORD[_totalPtcNum * 6];

	_trans = new dx::transform[_totalPtcNum];

	//_trans = new dx::transform;
	//_trans->SetWorldPosition(0.0f, 0.0f, 0.0f);

	HRESULT hr = NULL;

	//텍스쳐 불러오기
	//hr = D3DXCreateTextureFromFile(_device, textureFileName.c_str(), &_texture);

	/*D3DXMATRIXA16 matMesh;

	D3DXMatrixIdentity(&matMesh);*/

	//_mesh = RM_XMESH->loadResource(textureFileName);

	//this->filePath = filePath;
	LPD3DXBUFFER pAdjacency = NULL;	//인접 버퍼
	LPD3DXBUFFER pMaterial = NULL;	//재질 버퍼

	//XFile 로 부터 메쉬를 불러오는 함수
	hr = D3DXLoadMeshFromX(
		xFileName.c_str(),			//X 파일 로딩 경로...
		D3DXMESH_MANAGED,			//메쉬 옵션 일단 D3DXMESH_MANAGED 로....
		_device,					//디바이스
		&pAdjacency,				//얻어올 인접정보 버퍼
		&pMaterial,					//얻어올 재질정보 버퍼
		NULL,						//Effect 
		&_materialsNum,				//메쉬에서 사용되는 재질 갯수
		&_mesh						//메쉬
	);

	if (FAILED(hr))
	{

		SAFE_RELEASE(pAdjacency);
		SAFE_RELEASE(pMaterial);

		return E_FAIL;
	}



	//로딩 경로에서 파일명만 제거하고 경로만 받는다.
	string path;
	int lastPathIndex = 0;		//마지막 \ 의 위치

								//filePath.find_first_of( 'A' ); filePath 문자열에 'A' 가 들어있는 위치 리턴 (앞에서 부터 검색)
	lastPathIndex = xFileName.find_last_of('/'); //뒤에서 부터 검색
	if (lastPathIndex == -1)
	{	//못찾으면 -1 을 리턴
		lastPathIndex = xFileName.find_last_of('\\'); //경로 구분을 하는 / 을 못찾으면 \ 를 찾는다.
	}
	//경로 구분이 있다면...
	if (lastPathIndex != -1)
	{
		//filePath.substr( /*시작위치*/, /*갯수*/ );
		path = xFileName.substr(0, lastPathIndex + 1);
	}

	//Texture 로딩시 필요한 문자열들..
	string texFilePath;		//최종 경로...
	string texExp;			//파일 확장자 명
	string texFile;			//파일 명	


	_meshMaterial = new D3DMATERIAL9[_materialsNum];
	_meshTexture = new LPDIRECT3DTEXTURE9[_materialsNum];


	//재질 정보 얻기
	LPD3DXMATERIAL	pMaterials = (LPD3DXMATERIAL)pMaterial->GetBufferPointer();

	for (DWORD i = 0; i < _materialsNum; i++)
	{
		//로드된 메터리얼
		_meshMaterial[i] = pMaterials[i].MatD3D;

		//메쉬의 메터리얼에는 Ambient 정보가 없으니
		//Diffuse 정보와 동일하게 하자..
		_meshMaterial[i].Ambient = _meshMaterial[i].Diffuse;

		//마테리얼 정보가 있다면
		if (pMaterials[i].pTextureFilename != NULL)
		{
			//tex 파일경로는 Mesh 파일경로 + texture 파일이름
			texFilePath = path + pMaterials[i].pTextureFilename;

			////파일 이름과 확장자 위치
			//int dotIndex = texFilePath.find_last_of(".");

			////파일 명과 확장자를 나눈다.
			//texFile = texFilePath.substr(0, dotIndex);
			//texExp = texFilePath.substr(dotIndex + 1, xFileName.length());

			HRESULT hr = NULL;

			hr = D3DXCreateTextureFromFile(_device, texFilePath.c_str(), &_meshTexture[i]);

			if (FAILED(hr)) return E_FAIL;
		}

	}

	//얻어온 재질 정보를 다 사용하여 재질과 Texture 를 로딩 했기때문에 
	//더이상 pMaterial 재질 버퍼는 필요 없어 꼭 메모리 해재를 해주어야 한다.
	SAFE_RELEASE(pMaterial);

	//메쉬 최적화 (인접 버퍼를 이용하여 메쉬를 최적화 한다)
	_mesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |		//메쉬 서브셋순서대로 정렬 (DrawSubset 효율을 높인다 
		D3DXMESHOPT_COMPACT |		//메쉬에서 사용되지 않는 정점과 인덱스 해제
		D3DXMESHOPT_VERTEXCACHE,	//정점 Cache 히트율 높힌다.
		(DWORD*)pAdjacency->GetBufferPointer(),	//인접버퍼 넘겨야 한다.
		NULL,			//최적화를 마지고 결과로 얻는 인접정보 (더이상 필요없으면 NULL)
		NULL,			//최적화된 인덱스 정보
		NULL			//최적화된 정점 버퍼 정보 
	);

	//최적화가 끝났으니 해재
	SAFE_RELEASE(pAdjacency);

	//정점 정보 얻기
	//D3DVERTEXELEMENT9 pVtxElement[MAX_FVF_DECL_SIZE];

	////버텍스 갯수
	//DWORD vtxNum = _mesh->GetNumVertices();

	//

	////바운드 MinMax 계산을 위한 초기화
	//_vtxPosMin = D3DXVECTOR3(0, 0, 0);
	//_vtxPosMax = D3DXVECTOR3(0, 0, 0);

	////정점의 크기
	//DWORD verSize = D3DXGetFVFVertexSize(_mesh->GetFVF());

	////메쉬의 버텍스 버퍼를 Lock 한다
	//void* pVtx = NULL;
	//
	//_mesh->LockVertexBuffer(0, &pVtx);


	////정점 위치크기 최소값 최대값 구하기
	//for (DWORD i = 0; i < vtxNum; i++)
	//{
	//	//버텍스 시작 주소
	//	char* pVertex = ((char*)pVtx + (i * verSize));

	//
	//		D3DXVECTOR3* pos = (D3DXVECTOR3*)(pVertex + positionOffset);

	//		D3DXVec3TransformCoord(pos, pos, matCorrection);

	//		//정점 최소 값갱신
	//		if (_vtxPosMin.x > pos->x)		_vtxPosMin.x = pos->x;
	//		if (_vtxPosMin.y > pos->y)		_vtxPosMin.y = pos->y;
	//		if (_vtxPosMin.z > pos->z)		_vtxPosMin.z = pos->z;

	//		//정점 최대 값갱신
	//		if (_vtxPosMax.x < pos->x)		_vtxPosMax.x = pos->x;
	//		if (_vtxPosMax.y < pos->y)		_vtxPosMax.y = pos->y;
	//		if (_vtxPosMax.z < pos->z)		_vtxPosMax.z = pos->z;

	//}



	_vMesh.resize(_totalPtcNum, _mesh);


	//파티클 사이즈 정함.
	_ptcList.resize(_totalPtcNum);




	/*lightDirection* lightDir = new lightDirection;
	lightDir->_color = D3DXCOLOR(1, 1, 1, 1);
	lightDir->_intensity = 1.0f;*/
	//lightDir->_transform()_;

	//_mesh->setBaseLight(lightDir);
	//_device->GetTexture();

	return S_OK;
}

void dxMeshEmitter::relese()
{
	//dxEmitter::release();

	SAFE_DELETE_ARRAY(_ptcVertex);
	SAFE_DELETE_ARRAY(_ptcIndex);
	SAFE_DELETE_ARRAY(_trans);
}

void dxMeshEmitter::update()
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
		}


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

				//색상세팅
				/*for (DWORD i = 0; i < _materialsNum; i++)
				{
					iter->color.a = 0.0f;
					_meshMaterial[i].Ambient = _meshMaterial[i].Diffuse = (D3DCOLORVALUE)iter->color;
				}*/
				//this->InitCreatePlane(&_ptcVertex[InitNum * 4], &_ptcIndex[InitNum * 6], iter, InitNum);

				_trans[InitNum].SetScale(iter->size, iter->size, iter->size);
				_trans[InitNum].SetRotateLocal(iter->rotateAngle.x, iter->rotateAngle.y, iter->rotateAngle.z);
				_trans[InitNum].SetWorldPosition(iter->FinalPos);

				checkNum++;
				//if (checkNum >= _onePtcNum) break;
			}
			//_ptcVtx++;

		}
		InitNum++;



		//활성화
		if (iter->isAlive)
		{
			_module->ActiveUpdate(iter);

			//색상 세팅
			/*for (DWORD i = 0; i < _materialsNum; i++)
			{
				iter->color.a = 0.0f;
				_meshMaterial[i].Ambient = _meshMaterial[i].Diffuse = (D3DCOLORVALUE)iter->color;
			}*/

			//트랜스폼 업데이트
			_trans[ActiveNum].SetScale(iter->size, iter->size, iter->size);
			_trans[ActiveNum].SetRotateLocal(iter->rotateAngle.x, iter->rotateAngle.y, iter->rotateAngle.z);
			_trans[ActiveNum].SetWorldPosition(_trans[ActiveNum].GetWorldPosition() + (iter->FinalDir));

			iter->age += DeltaTime;
			//_drawVtx[_drawPtcNum] = _ptcVtx[ActiveNum];
			_drawPtcNum++;
		}
		ActiveNum++;
		//_ptcVtx++;
	}

	//시간 초기화
	if (_spawnTime <= _spawnCurrentTime)
	{
		_spawnCurrentTime = 0.0f;
	}

	//스폰 시간 업
	_spawnCurrentTime += DeltaTime;


}

void dxMeshEmitter::render()
{
	//시작시간 과 동작시간에 따른 렌더
	if (_startRenderOn == FALSE) return;
	if (_activeRenderOn == FALSE) return;


	//D3DXMATRIXA16 getView;
	//_device->GetTransform(D3DTS_VIEW, &getView);
	////D3DXMatrixInverse(&getView, NULL, &getView);
	//D3DXVECTOR3 cameraPos = D3DXVECTOR3(getView._41, getView._42, getView._43);

	//_meshCamera.SetWorldPosition(cameraPos);

	//_mesh->setCamera(&_meshCamera);

	//_mesh->render(_trans);


	_device->SetRenderState(D3DRS_LIGHTING, false);		//라이팅을 끈다.
	//_device->SetRenderState(D3DRS_ZWRITEENABLE, false);	//z 버퍼의 쓰기를 막는다.
	//_device->SetRenderState(D3DRS_ZWRITEENABLE, true);	//z 버퍼의 쓰기를 막는다.

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	////알파 블렌딩 셋팅
	//_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	////_device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	////_device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	//_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Texture 의 값과 Diffuse 여기서는 정점컬러의 알파값 을 섞어 최종 출력을 한다.
	/*_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);*/


	////카메라 행렬 가져오기
	///*D3DXMATRIXA16 getView;
	//_device->GetTransform(D3DTS_VIEW, &getView);
	//D3DXVECTOR3 cameraPos = D3DXVECTOR3(getView._41, getView._42, getView._43);*/

	////Trans.LookPosition(cameraPos);

	//D3DXMATRIXA16 matWorld;

	///*if (_bLocal == false)
	//{
	//D3DXMatrixIdentity(&matWorld);
	//}
	//else
	//{
	//matWorld = this->_transform->GetFinalMatrix();
	//}*/
	////_device->SetTransform(D3DTS_WORLD, &matWorld);

	////파티클 Texture 셋팅
	//_device->SetTexture(0, _texture);

	////파티클 정점 출력
	//_device->SetFVF(ParticleExFVF);
	//_device->DrawIndexedPrimitiveUP(
	//	D3DPT_TRIANGLELIST,
	//	0,
	//	_drawPtcNum * 4,
	//	_drawPtcNum * 2,
	//	_ptcIndex,
	//	D3DFMT_INDEX32,
	//	_ptcVertex,
	//	sizeof(tagDxParticleEX));

	////for (int i = 0; i < _totalPtcNum; i++)
	////{
	////	_device->DrawIndexedPrimitiveUP(
	////		D3DPT_TRIANGLELIST,
	////		i,
	////		4,
	////		2,
	////		_ptcIndex,
	////		D3DFMT_INDEX32,
	////		_ptcVertex,
	////		sizeof(tagDxParticleEX));
	////}


	////파티클 그리고 난후 후처리
	//_device->SetRenderState(D3DRS_LIGHTING, true);
	//_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	//_device->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//_device->SetTexture(0, NULL);

	//_device->SetFVF(ParticleExFVF);

	if (_vMesh.empty() == FALSE)
	{
		for (int i = 0; i < _vMesh.size(); i++)
		{
			if (_ptcList[i].isAlive == TRUE)
			{
				_trans[i].SetDeviceWorld();
				for (DWORD i = 0; i < _materialsNum; i++)
				{

					_device->SetMaterial(&_meshMaterial[i]);
					_device->SetTexture(0, _meshTexture[i]);

					//_mesh->QueryInterface(기모찌!!!!)

					//메쉬 출력
					_mesh->DrawSubset(i);
				}
			}
		}

	}

	_device->SetTexture(0, NULL);
	_device->SetRenderState(D3DRS_LIGHTING, TRUE);
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);


}


