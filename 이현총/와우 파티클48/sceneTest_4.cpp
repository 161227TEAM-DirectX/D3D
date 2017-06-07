#include "stdafx.h"
#include "sceneTest_4.h"

HRESULT sceneTest_4::init(void)
{
	//�׸��� Ŭ���� ���� �� �ʱ�ȭ
	_grid = new grid;
	_grid->init();

	//���� ���� �����
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 3,		//������� ���������� ũ��(�ﰢ���� ���� 3�� �ʿ�)
		D3DUSAGE_WRITEONLY,			//��������� ���������� �Ӽ�(�ϴ� writeonly�� ������ ������, �Ŀ� �������ۿ� ������ ���� �Ͼ�ٸ� ���̳������� ��������)
		MYVERTEX::FVF,				//FVF����
		D3DPOOL_DEFAULT,			//�޸�Ǯ �������
		&_vb,						//������ ���ع���
		NULL);						//�׳� ������ �������� ���� NULL

	//D3DPOOL_DEFAULT => ���������� �޸𸮴� �ý��ۻ�翡 ���� �˾Ƽ� ������ �Ǵµ�, �Ϲ������� �׷���ī��޸𸮿� �����̵ȴ�
	//D3DPOOl_MANAGED => ���������� �޸𸮴� �ý����� �޸𸮿����� ������ �ǰ� �׷���ī�带 ����Ѵٸ� �׷���ī��޸𸮿� �����̵ȴ�
	//�� ������ ���������� �ý��۸޸𸮿� ������ �� ���¿��� �׷���ī��޸𸮿� �װſ� �Ȱ��� �纻�� ����� ����ϴ� ���
	//�̴� ����̽��� ���� �Ǿ ������ ������ �ٽ� ������ �� �ִ� ������ �ִ�

	//���� �迭�غ�
	MYVERTEX vertices[8];
	vertices[0].pos = D3DXVECTOR3(-2.3f, -2.3f, -2.3f);
	vertices[0].color = 0xffffff00;
	vertices[1].pos = D3DXVECTOR3(-2.3f, -2.3f, 2.3f);
	vertices[1].color = 0xffffff00;
	vertices[2].pos = D3DXVECTOR3(2.3f, -2.3f, 2.3f);
	vertices[2].color = 0xffffff00;
	vertices[3].pos = D3DXVECTOR3(2.3f, -2.3f, -2.3f);
	vertices[3].color = 0xffffff00;
	vertices[4].pos = D3DXVECTOR3(-2.3f, 2.3f, -2.3f);
	vertices[4].color = 0xffffff00;
	vertices[5].pos = D3DXVECTOR3(-2.3f, 2.3f, 2.3f);
	vertices[5].color = 0xffffff00;
	vertices[6].pos = D3DXVECTOR3(2.3f, 2.3f, 2.3f);
	vertices[6].color = 0xffffff00;
	vertices[7].pos = D3DXVECTOR3(2.3f, 2.3f, -2.3f);
	vertices[7].color = 0xffffff00;

	//���� ��
	void* pVertices = NULL;
	_vb->Lock(0, 0, &pVertices, 0);
	//�޸� ����
	memcpy(pVertices, vertices, sizeof(MYVERTEX) * 8);
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
	
	WORD indices[24] = {
		0, 4, 4, 7, 7, 3, 3, 0,
		1, 5, 5, 6, 6, 2, 2, 1,
		0, 1, 4, 5, 7, 6, 3, 2 };

	//�ε��� ��
	void* pIndices = NULL;
	_ib->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, indices, sizeof(WORD) * 24);
	_ib->Unlock();

	//������ �÷� ������ ����ϱ� ���ؼ��� ����̽��� �⺻ ����Ʈ ����� �����ؾ� �Ѵ�
	//��а� ����Ʈ ����� ����� ���� ������ ������
	_device->SetRenderState(
		D3DRS_LIGHTING,			//�������Ҳ���?
		FALSE					//���ð��� ��� �ǳ�?
	);

	//�����̽� �ø�(��������)
	//_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);	//�ð���� �ȱ׸��ڴ�(�ݽð���� �׷�����)
	//_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//�ݽð���� �ȱ׸��ڴ� (�ð���� �׷�����) => ����Ʈ
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//�ø����� (����� ��� �׷�����)
	_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //���̾�������
																//�����ʱ�ȭ
	_angle = 0.0f;

	return S_OK;
}

void sceneTest_4::release(void)
{
	//�׸��� Ŭ���� ����
	SAFE_DELETE(_grid);
	//��������
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
}

void sceneTest_4::update(void)
{
	//�ʴ� 90�� ȸ��
	_angle += D3DXToRadian(90) * _timeDelta;

	//���� �࿡���� ȸ�����
	D3DXMATRIXA16 matRotation;
	//D3DXMatrixRotationX(&matRotation, _angle);	//x�� �������� ȸ�����
	D3DXMatrixRotationY(&matRotation, _angle);		//y�� �������� ȸ�����
	//D3DXMatrixRotationZ(&matRotation, _angle);	//z�� �������� ȸ�����
	//������ �࿡ ���� ȸ�����
	//D3DXMatrixRotationAxis(&matRotation, &D3DXVECTOR3(0, 1, 0), _angle);

	//�������
	_matWorld = matRotation;
}

void sceneTest_4::render(void)
{
	//�׸��� Ŭ���� ����
	_grid->render();

//====================================================================
//			## ���� �����̽� ##
//====================================================================
	//Ư����ü�� �׸������� ��ü�� �ش�Ǵ� ��������� �����ϰ� �׸���!!!
	_device->SetTransform(D3DTS_WORLD, &_matWorld);

//====================================================================
//			## �� �����̽� ##
//====================================================================
	//����� �� �交�� �غ�
	D3DXMATRIXA16 matView;
	D3DXVECTOR3	lookAtPos(0, 0, 0);			//0,0,0��ġ�� �ٶ󺻴�
	D3DXVECTOR3 eyePos(0, 1, -10);			//ī�޶� ���� ��ġ
	D3DXVECTOR3 up(0, 1, 0);				//��溤�� �׳� 0,1,0

	//D3DXMatrixLookAtLH(�����, ����ġ, �ٶ���ġ, ������)
	D3DXMatrixLookAtLH(&matView, &eyePos, &lookAtPos, &up);

	//����� ����
	_device->SetTransform(D3DTS_VIEW, &matView);

//====================================================================
//			## ���� ##
//====================================================================
	//������� �غ�
	D3DXMATRIXA16 matProjection;

	D3DXMatrixPerspectiveFovLH(
		&matProjection,		//�������
		D3DXToRadian(60),	//ȭ�� 60��
		(float)(WINSIZEX) / static_cast<float>(WINSIZEY), //ȭ�� ��Ⱦ��
		0.001f,				//�ٰŸ� ��� �Ÿ�(0�϶� ������ ���δ�)
		100.0f);			//���Ÿ� ��� �Ÿ�

							//������� ����
	_device->SetTransform(D3DTS_PROJECTION, &matProjection);

//============================================================================

	//SetStreamSource => ���� �̾߱� �ϸ� ���ؽ� ���� ����
	_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX));

	//�ε������� ����
	_device->SetIndices(_ib);

	//���� �׸��� ������ ���� ���� ���� �÷��� ����
	_device->SetFVF(MYVERTEX::FVF);

	_device->DrawIndexedPrimitive(
		D3DPT_LINELIST,	 //���α׸���			
		0,				//���� ���ؽ��迭 �ε���				
		0,							
		8,				//���� ����			
		0,				//���� �ε����迭 �ε���		
		12				//�׸��� ��ü�� ������ 12��
		);				
}
