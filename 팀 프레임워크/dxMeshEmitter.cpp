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

	//�ؽ��� �ҷ�����
	//hr = D3DXCreateTextureFromFile(_device, textureFileName.c_str(), &_texture);

	/*D3DXMATRIXA16 matMesh;

	D3DXMatrixIdentity(&matMesh);*/

	//_mesh = RM_XMESH->loadResource(textureFileName);

	//this->filePath = filePath;
	LPD3DXBUFFER pAdjacency = NULL;	//���� ����
	LPD3DXBUFFER pMaterial = NULL;	//���� ����

	//XFile �� ���� �޽��� �ҷ����� �Լ�
	hr = D3DXLoadMeshFromX(
		xFileName.c_str(),			//X ���� �ε� ���...
		D3DXMESH_MANAGED,			//�޽� �ɼ� �ϴ� D3DXMESH_MANAGED ��....
		_device,					//����̽�
		&pAdjacency,				//���� �������� ����
		&pMaterial,					//���� �������� ����
		NULL,						//Effect 
		&_materialsNum,				//�޽����� ���Ǵ� ���� ����
		&_mesh						//�޽�
	);

	if (FAILED(hr))
	{

		SAFE_RELEASE(pAdjacency);
		SAFE_RELEASE(pMaterial);

		return E_FAIL;
	}



	//�ε� ��ο��� ���ϸ� �����ϰ� ��θ� �޴´�.
	string path;
	int lastPathIndex = 0;		//������ \ �� ��ġ

								//filePath.find_first_of( 'A' ); filePath ���ڿ��� 'A' �� ����ִ� ��ġ ���� (�տ��� ���� �˻�)
	lastPathIndex = xFileName.find_last_of('/'); //�ڿ��� ���� �˻�
	if (lastPathIndex == -1)
	{	//��ã���� -1 �� ����
		lastPathIndex = xFileName.find_last_of('\\'); //��� ������ �ϴ� / �� ��ã���� \ �� ã�´�.
	}
	//��� ������ �ִٸ�...
	if (lastPathIndex != -1)
	{
		//filePath.substr( /*������ġ*/, /*����*/ );
		path = xFileName.substr(0, lastPathIndex + 1);
	}

	//Texture �ε��� �ʿ��� ���ڿ���..
	string texFilePath;		//���� ���...
	string texExp;			//���� Ȯ���� ��
	string texFile;			//���� ��	


	_meshMaterial = new D3DMATERIAL9[_materialsNum];
	_meshTexture = new LPDIRECT3DTEXTURE9[_materialsNum];


	//���� ���� ���
	LPD3DXMATERIAL	pMaterials = (LPD3DXMATERIAL)pMaterial->GetBufferPointer();

	for (DWORD i = 0; i < _materialsNum; i++)
	{
		//�ε�� ���͸���
		_meshMaterial[i] = pMaterials[i].MatD3D;

		//�޽��� ���͸��󿡴� Ambient ������ ������
		//Diffuse ������ �����ϰ� ����..
		_meshMaterial[i].Ambient = _meshMaterial[i].Diffuse;

		//���׸��� ������ �ִٸ�
		if (pMaterials[i].pTextureFilename != NULL)
		{
			//tex ���ϰ�δ� Mesh ���ϰ�� + texture �����̸�
			texFilePath = path + pMaterials[i].pTextureFilename;

			////���� �̸��� Ȯ���� ��ġ
			//int dotIndex = texFilePath.find_last_of(".");

			////���� ��� Ȯ���ڸ� ������.
			//texFile = texFilePath.substr(0, dotIndex);
			//texExp = texFilePath.substr(dotIndex + 1, xFileName.length());

			HRESULT hr = NULL;

			hr = D3DXCreateTextureFromFile(_device, texFilePath.c_str(), &_meshTexture[i]);

			if (FAILED(hr)) return E_FAIL;
		}

	}

	//���� ���� ������ �� ����Ͽ� ������ Texture �� �ε� �߱⶧���� 
	//���̻� pMaterial ���� ���۴� �ʿ� ���� �� �޸� ���縦 ���־�� �Ѵ�.
	SAFE_RELEASE(pMaterial);

	//�޽� ����ȭ (���� ���۸� �̿��Ͽ� �޽��� ����ȭ �Ѵ�)
	_mesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |		//�޽� ����¼������ ���� (DrawSubset ȿ���� ���δ� 
		D3DXMESHOPT_COMPACT |		//�޽����� ������ �ʴ� ������ �ε��� ����
		D3DXMESHOPT_VERTEXCACHE,	//���� Cache ��Ʈ�� ������.
		(DWORD*)pAdjacency->GetBufferPointer(),	//�������� �Ѱܾ� �Ѵ�.
		NULL,			//����ȭ�� ������ ����� ��� �������� (���̻� �ʿ������ NULL)
		NULL,			//����ȭ�� �ε��� ����
		NULL			//����ȭ�� ���� ���� ���� 
	);

	//����ȭ�� �������� ����
	SAFE_RELEASE(pAdjacency);

	//���� ���� ���
	//D3DVERTEXELEMENT9 pVtxElement[MAX_FVF_DECL_SIZE];

	////���ؽ� ����
	//DWORD vtxNum = _mesh->GetNumVertices();

	//

	////�ٿ�� MinMax ����� ���� �ʱ�ȭ
	//_vtxPosMin = D3DXVECTOR3(0, 0, 0);
	//_vtxPosMax = D3DXVECTOR3(0, 0, 0);

	////������ ũ��
	//DWORD verSize = D3DXGetFVFVertexSize(_mesh->GetFVF());

	////�޽��� ���ؽ� ���۸� Lock �Ѵ�
	//void* pVtx = NULL;
	//
	//_mesh->LockVertexBuffer(0, &pVtx);


	////���� ��ġũ�� �ּҰ� �ִ밪 ���ϱ�
	//for (DWORD i = 0; i < vtxNum; i++)
	//{
	//	//���ؽ� ���� �ּ�
	//	char* pVertex = ((char*)pVtx + (i * verSize));

	//
	//		D3DXVECTOR3* pos = (D3DXVECTOR3*)(pVertex + positionOffset);

	//		D3DXVec3TransformCoord(pos, pos, matCorrection);

	//		//���� �ּ� ������
	//		if (_vtxPosMin.x > pos->x)		_vtxPosMin.x = pos->x;
	//		if (_vtxPosMin.y > pos->y)		_vtxPosMin.y = pos->y;
	//		if (_vtxPosMin.z > pos->z)		_vtxPosMin.z = pos->z;

	//		//���� �ִ� ������
	//		if (_vtxPosMax.x < pos->x)		_vtxPosMax.x = pos->x;
	//		if (_vtxPosMax.y < pos->y)		_vtxPosMax.y = pos->y;
	//		if (_vtxPosMax.z < pos->z)		_vtxPosMax.z = pos->z;

	//}



	_vMesh.resize(_totalPtcNum, _mesh);


	//��ƼŬ ������ ����.
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
		}


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

				//������
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



		//Ȱ��ȭ
		if (iter->isAlive)
		{
			_module->ActiveUpdate(iter);

			//���� ����
			/*for (DWORD i = 0; i < _materialsNum; i++)
			{
				iter->color.a = 0.0f;
				_meshMaterial[i].Ambient = _meshMaterial[i].Diffuse = (D3DCOLORVALUE)iter->color;
			}*/

			//Ʈ������ ������Ʈ
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

	//�ð� �ʱ�ȭ
	if (_spawnTime <= _spawnCurrentTime)
	{
		_spawnCurrentTime = 0.0f;
	}

	//���� �ð� ��
	_spawnCurrentTime += DeltaTime;


}

void dxMeshEmitter::render()
{
	//���۽ð� �� ���۽ð��� ���� ����
	if (_startRenderOn == FALSE) return;
	if (_activeRenderOn == FALSE) return;


	//D3DXMATRIXA16 getView;
	//_device->GetTransform(D3DTS_VIEW, &getView);
	////D3DXMatrixInverse(&getView, NULL, &getView);
	//D3DXVECTOR3 cameraPos = D3DXVECTOR3(getView._41, getView._42, getView._43);

	//_meshCamera.SetWorldPosition(cameraPos);

	//_mesh->setCamera(&_meshCamera);

	//_mesh->render(_trans);


	_device->SetRenderState(D3DRS_LIGHTING, false);		//�������� ����.
	//_device->SetRenderState(D3DRS_ZWRITEENABLE, false);	//z ������ ���⸦ ���´�.
	//_device->SetRenderState(D3DRS_ZWRITEENABLE, true);	//z ������ ���⸦ ���´�.

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	////���� ���� ����
	//_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	////_device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	////_device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	//_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Texture �� ���� Diffuse ���⼭�� �����÷��� ���İ� �� ���� ���� ����� �Ѵ�.
	/*_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);*/


	////ī�޶� ��� ��������
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

	////��ƼŬ Texture ����
	//_device->SetTexture(0, _texture);

	////��ƼŬ ���� ���
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


	////��ƼŬ �׸��� ���� ��ó��
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

					//_mesh->QueryInterface(�����!!!!)

					//�޽� ���
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


