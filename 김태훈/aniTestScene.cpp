#include "stdafx.h"
#include "aniTestScene.h"

HRESULT aniTestScene::init(void)
{
	//ť�����
	this->CreateCube();
	/*������*/

	//_mainCamera.SetWorldPosition(-2, 2, -12);
	_mainCamera.SetLocalPosition(-1, 3, -15);

	//��Ʈ���� ����
	_boneMap.insert(make_pair("Root", new transform));
	//�õ���
	_boneMap.insert(make_pair("LeftHip", new transform));
	_boneMap.insert(make_pair("RightHip", new transform));
	//�����
	_boneMap.insert(make_pair("LeftUpLeg", new transform));
	_boneMap.insert(make_pair("RightUpLeg", new transform));
	//���Ƹ�
	_boneMap.insert(make_pair("LeftDownLeg", new transform));
	_boneMap.insert(make_pair("RightDownLeg", new transform));
	//��
	_boneMap.insert(make_pair("LeftFoot", new transform));
	_boneMap.insert(make_pair("RightFoot", new transform));

	/*��������*/
	_boneMap["LeftHip"]->AttachTo(_boneMap["Root"]);
	_boneMap["RightHip"]->AttachTo(_boneMap["Root"]);
	_boneMap["LeftHip"]->SetLocalPosition(-1.0f, 0.0f, 0.0f);
	_boneMap["RightHip"]->SetLocalPosition(1.0f, 0.0f, 0.0f);

	_boneMap["LeftUpLeg"]->AttachTo(_boneMap["LeftHip"]);
	_boneMap["RightUpLeg"]->AttachTo(_boneMap["RightHip"]);
	_boneMap["LeftUpLeg"]->SetLocalPosition(0.0f, -0.5f, 0.0f);
	_boneMap["RightUpLeg"]->SetLocalPosition(0.0f, -0.5f, 0.0f);

	_boneMap["LeftDownLeg"]->AttachTo(_boneMap["LeftUpLeg"]);
	_boneMap["RightDownLeg"]->AttachTo(_boneMap["RightUpLeg"]);
	_boneMap["LeftDownLeg"]->SetLocalPosition(0.0f, -2.0f, 0.0f);
	_boneMap["RightDownLeg"]->SetLocalPosition(0.0f, -2.0f, 0.0f);

	_boneMap["LeftFoot"]->AttachTo(_boneMap["LeftDownLeg"]);
	_boneMap["RightFoot"]->AttachTo(_boneMap["RightDownLeg"]);
	_boneMap["LeftFoot"]->SetLocalPosition(0.0f, -2.0f, 0.0f);
	_boneMap["RightFoot"]->SetLocalPosition(0.0f, -2.0f, 0.0f);

	/*���� �ٴ� �޽�*/
	//��Ʈ �޽�
	_meshMap.insert(make_pair("Root", new transform));
	_meshMap["Root"]->AttachTo(_boneMap["Root"]);

	_meshMap.insert(make_pair("LeftHip", new transform));
	_meshMap["LeftHip"]->AttachTo(_boneMap["LeftHip"]);
	_meshMap["LeftHip"]->Reset();

	_meshMap.insert(make_pair("RightHip", new transform));
	_meshMap["RightHip"]->AttachTo(_boneMap["RightHip"]);
	_meshMap["RightHip"]->Reset();

	_meshMap.insert(make_pair("LeftUpLeg", new transform));
	_meshMap["LeftUpLeg"]->AttachTo(_boneMap["LeftUpLeg"]);
	_meshMap["LeftUpLeg"]->Reset();
	_meshMap["LeftUpLeg"]->SetScale(1, 2, 1);
	_meshMap["LeftUpLeg"]->SetLocalPosition(0, -1, 0);

	_meshMap.insert(make_pair("RightUpLeg", new transform));
	_meshMap["RightUpLeg"]->AttachTo(_boneMap["RightUpLeg"]);
	_meshMap["RightUpLeg"]->Reset();
	_meshMap["RightUpLeg"]->SetScale(1, 2, 1);
	_meshMap["RightUpLeg"]->SetLocalPosition(0, -1, 0);

	_meshMap.insert(make_pair("LeftDownLeg", new transform));
	_meshMap["LeftDownLeg"]->AttachTo(_boneMap["LeftDownLeg"]);
	_meshMap["LeftDownLeg"]->Reset();
	_meshMap["LeftDownLeg"]->SetScale(1, 2, 1);
	_meshMap["LeftDownLeg"]->SetLocalPosition(0, -1, 0);

	_meshMap.insert(make_pair("RightDownLeg", new transform));
	_meshMap["RightDownLeg"]->AttachTo(_boneMap["RightDownLeg"]);
	_meshMap["RightDownLeg"]->Reset();
	_meshMap["RightDownLeg"]->SetScale(1, 2, 1);
	_meshMap["RightDownLeg"]->SetLocalPosition(0, -1, 0);

	_meshMap.insert(make_pair("LeftFoot", new transform));
	_meshMap["LeftFoot"]->AttachTo(_boneMap["LeftFoot"]);
	_meshMap["LeftFoot"]->Reset();
	_meshMap["LeftFoot"]->SetScale(1, 0.5f, 1.5f);
	_meshMap["LeftFoot"]->SetLocalPosition(0, -0.25f, 0.25f);

	_meshMap.insert(make_pair("RightFoot", new transform));
	_meshMap["RightFoot"]->AttachTo(_boneMap["RightFoot"]);
	_meshMap["RightFoot"]->Reset();
	_meshMap["RightFoot"]->SetScale(1, 0.5f, 1.5f);
	_meshMap["RightFoot"]->SetLocalPosition(0, -0.25f, 0.25f);

	/*Ű������*/ //�뷫 �ʴ� 10�������� �����Ѵٰ� ����
	_boneMap["RightHip"]->SetRotateLocal(0.0f, 0.0f, 0.0f);
	_rightHipKeyFrames.push_back(new KEY_FRAME(0, *this->_boneMap["RightHip"]));

	_boneMap["RightHip"]->SetRotateLocal(D3DXToRadian(-90), 0.0f, 0.0f);
	_rightHipKeyFrames.push_back(new KEY_FRAME(10, *this->_boneMap["RightHip"]));

	_boneMap["RightHip"]->SetRotateLocal(D3DXToRadian(90), 0.0f, D3DXToRadian(90));
	_rightHipKeyFrames.push_back(new KEY_FRAME(20, *this->_boneMap["RightHip"]));

	_boneMap["RightHip"]->SetRotateLocal(0.0f, 0.0f, 0.0f);
	_rightHipKeyFrames.push_back(new KEY_FRAME(30, *this->_boneMap["RightHip"]));


	_nowFrame = 0.0f;

	//����Ʈ ����
	_device->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

void aniTestScene::release(void)
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);

	for (MAP_TRANS_ITER iter = _boneMap.begin(); iter != _boneMap.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

void aniTestScene::update(void)
{
	float deltaMove = 3.0f * _timeDelta;
	float deltaAngle = D3DXToRadian(90) * _timeDelta;

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) == FALSE)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_target.MovePositionSelf(-deltaMove, 0.0f, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_target.MovePositionSelf(deltaMove, 0.0f, 0.0f);
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_target.MovePositionSelf(0.0f, 0.0f, deltaMove);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_target.MovePositionSelf(0.0f, 0.0f, -deltaMove);
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_target.RotateSelf(0.0f, -deltaAngle, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_target.RotateSelf(0.0f, deltaAngle, 0.0f);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_target.RotateSelf(-deltaAngle, 0.0f, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_target.RotateSelf(deltaAngle, 0.0f, 0.0f);
		}
	}

	//������ ����
	_nowFrame += 10 * _timeDelta;
	if (_nowFrame > 30.0f) _nowFrame -= 30.0f;

	int frontIndex = 0;
	int backIndex = _rightHipKeyFrames.size() - 1;
	int centerIndex = (backIndex - frontIndex) / 2 + frontIndex;

	while (frontIndex < backIndex)
	{
		//�����ε����� ������ ���� ���� �����Ӻ��� ũ��?
		if (_rightHipKeyFrames[centerIndex]->frame >= _nowFrame)
		{
			backIndex = centerIndex;
			//���� ����
			centerIndex = (backIndex - frontIndex) / 2 + frontIndex;
		}
		else//�����ε����� ������ ���� ���� �����Ӻ��� �۳�?
		{
			frontIndex = centerIndex;
			//���� ����
			centerIndex = (backIndex - frontIndex) / 2 + frontIndex;
		}

		if (backIndex == frontIndex + 1) break;
	}

	//�����ؾ� �� ���ε����� ���� �ε����� ã�Ҵ�
	//���� �������� ����Ʈ�ε����� ���ε��� ���̿��� ��ŭ ����Ǿ��°��� 0 ~ 1�� ��´�
	//�������Լ��� ���� ��´�
	float t = InverseLerp(_rightHipKeyFrames[frontIndex]->frame,
		_rightHipKeyFrames[backIndex]->frame, _nowFrame);

	//������Ų��
	_boneMap["RightHip"]->Interpolate(
		_rightHipKeyFrames[frontIndex]->trans,
		_rightHipKeyFrames[backIndex]->trans,
		t);
		
	//ī�޶� ����Ʈ��Ʈ��
	_mainCamera.DefaultControl(_timeDelta);
	//ī�޶� ������Ʈ
	_mainCamera.updateCamToDevice();
}

void aniTestScene::render(void)
{
	for (MAP_TRANS_ITER iter = _boneMap.begin(); iter != _boneMap.end(); ++iter)
	{
		iter->second->RenderGimozo();
	}

	for (MAP_TRANS_ITER iter = _meshMap.begin(); iter != _meshMap.end(); ++iter)
	{
		iter->second->SetDeviceWorld();
		RenderCube();
	}

	_target.RenderGimozo();
}

void aniTestScene::CreateCube()
{
	//���� ���� �����
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 24,		//������� ���������� ũ��(�ﰢ���� ���� 3�� �ʿ�)
		D3DUSAGE_WRITEONLY,			//��������� ���������� �Ӽ�(�ϴ� writeonly�� ������ ������, �Ŀ� �������ۿ� ������ ���� �Ͼ�ٸ� ���̳������� ��������)
		MYVERTEX::FVF,				//FVF����
		D3DPOOL_DEFAULT,			//�޸�Ǯ �������
		&_vb,						//������ ���ع���
		NULL);						//�׳� ������ �������� ���� NULL

									//���� �÷� ����
	MYVERTEX quad[4];
	quad[0].pos = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	quad[1].pos = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
	quad[2].pos = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
	quad[3].pos = D3DXVECTOR3(0.5f, -0.5f, -0.5f);

	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationY(&matRot, D3DXToRadian(-90));

	//���� �迭 �غ�
	MYVERTEX vertices[24];

	//�ո�
	memcpy(vertices, quad, sizeof(MYVERTEX) * 4);
	vertices[0].color = 0xffff0000;
	vertices[1].color = 0xffff0000;
	vertices[2].color = 0xffff0000;
	vertices[3].color = 0xffff0000;

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//������ ����
	memcpy(vertices + 4, quad, sizeof(MYVERTEX) * 4);
	vertices[4].color = 0xff00ff00;
	vertices[5].color = 0xff00ff00;
	vertices[6].color = 0xff00ff00;
	vertices[7].color = 0xff00ff00;

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//�޸� ����
	memcpy(vertices + 8, quad, sizeof(MYVERTEX) * 4);
	vertices[8].color = 0xffff0000;
	vertices[9].color = 0xffff0000;
	vertices[10].color = 0xffff0000;
	vertices[11].color = 0xffff0000;

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//������ ����
	memcpy(vertices + 12, quad, sizeof(MYVERTEX) * 4);
	vertices[12].color = 0xff00ff00;
	vertices[13].color = 0xff00ff00;
	vertices[14].color = 0xff00ff00;
	vertices[15].color = 0xff00ff00;

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-90));

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//���� ����
	memcpy(vertices + 16, quad, sizeof(MYVERTEX) * 4);
	vertices[16].color = 0xff0000ff;
	vertices[17].color = 0xff0000ff;
	vertices[18].color = 0xff0000ff;
	vertices[19].color = 0xff0000ff;

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-180));

	//4�� ���� ������
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//�Ʒ��� ����
	memcpy(vertices + 20, quad, sizeof(MYVERTEX) * 4);
	vertices[20].color = 0xff0000ff;
	vertices[21].color = 0xff0000ff;
	vertices[22].color = 0xff0000ff;
	vertices[23].color = 0xff0000ff;

	//���� ��
	void* pVertices = NULL;
	_vb->Lock(0, 0, &pVertices, 0);
	//�޸� ����
	memcpy(pVertices, vertices, sizeof(MYVERTEX) * 24);
	_vb->Unlock();

	//�ε��� ���� ����
	_device->CreateIndexBuffer(
		sizeof(WORD) * 36,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&_ib,
		NULL);

	//		5--------6
	//     /|       /|
	//    4--------7 |
	//    | |      | | 
	//    | 1------| 2
	//    |/       |/
	//    0--------3

	WORD indices[36];
	for (int i = 0; i < 6; i++)
	{
		//���� ��ŸƮ �ε���
		WORD vertexIndex = i * 4;
		//�ε��� �迭 ��ŸƮ �ε���
		WORD indicesIndex = i * 6;

		indices[indicesIndex + 0] = vertexIndex + 0;
		indices[indicesIndex + 1] = vertexIndex + 1;
		indices[indicesIndex + 2] = vertexIndex + 2;
		indices[indicesIndex + 3] = vertexIndex + 0;
		indices[indicesIndex + 4] = vertexIndex + 2;
		indices[indicesIndex + 5] = vertexIndex + 3;
	}

	//�ε��� ��
	void* pIndices = NULL;
	_ib->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, indices, sizeof(WORD) * 36);
	_ib->Unlock();
}

void aniTestScene::RenderCube()
{
	//SetStreamSource => ���� �̾߱� �ϸ� ���ؽ� ���� ����
	_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX));

	//�ε������� ����
	_device->SetIndices(_ib);

	//���� �׸��� ������ ���� ���� ���� �÷��� ����
	_device->SetFVF(MYVERTEX::FVF);

	_device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,	 //���α׸���			
		0,				//���� ���ؽ��迭 �ε���				
		0,
		24,				//���� ����			
		0,				//���� �ε����迭 �ε���		
		12				//�׸��� ��ü�� ������ 12��
	);
}
