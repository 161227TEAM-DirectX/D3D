#include "stdafx.h"
#include "_2particleEmitter.h"
#include "particleEmitter.h"

HRESULT _2particleEmitter::init(void)
{
	//����ī�޶� ��ġ ����
	_mainCamera->SetWorldPosition(0, 1, -5);

	//��ƼŬ Ŭ���� ����
	_pParticle = new particleEmitter();
	_pParticle->setActive(true);
	
	//
	//������ ����~
	//

	//�迭�� 2���̻�
	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));

	VEC_SCALE scales;
	scales.push_back(1.0f);
	scales.push_back(1.0f);
	scales.push_back(1.0f);

	LPDIRECT3DTEXTURE9 pTex = RM_TEXTURE->getResource("Resources/Textures/particle_0.png");

	//��ƼŬ ������ ����
 	_pParticle->init(
	1000,						//�ִ� ��ƼŬ��
	200.0f,						//�ʴ� ��ƼŬ �߻� ��
	5,							//�ϳ��� ��ƼŬ ���� ������ �ּҰ�
	5,							//�ϳ��� ��ƼŬ ���� ������ �ִ밪
	D3DXVECTOR3(0, 0, 5),		//��ƼŬ ���� �ӵ� �ּҰ�(���ñ���)
	D3DXVECTOR3(0, 0, 5),		//��ƼŬ ���� �ӵ� �ִ밪(���ñ���)
	D3DXVECTOR3(0, 0, 0),		//��ƼŬ ���� ���� �ּҰ�(���ñ���)
	D3DXVECTOR3(0, 0, 0),		//��ƼŬ ���� ���� �ִ밪(���ñ���)
	colors,						//�÷� �迭
	scales,						//������ �迭
	1.0f,						//����ũ�� �ּҰ�
	1.0f,						//����ũ�� �ִ밪
	pTex,						//�ؽ���
	true						//�����̴�? �ƴϴ�?
	);
	

	/*
	//
	//��������
	//
	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 0.1f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 0.1f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));

	VEC_SCALE scales;
	scales.push_back(3.0f);
	scales.push_back(2.0f);
	scales.push_back(1.0f);
	scales.push_back(0.5f);
	scales.push_back(0.1f);

	LPDIRECT3DTEXTURE9 pTex = RM_TEXTURE->getResource("Resources/Textures/particle_0.png");

	//��ƼŬ ������ ����
	_pParticle->init(
		1000,						//�ִ� ��ƼŬ��
		200.0f,						//�ʴ� ��ƼŬ �߻� ��
		3,							//�ϳ��� ��ƼŬ ���� ������ �ּҰ�
		5,							//�ϳ��� ��ƼŬ ���� ������ �ִ밪
		D3DXVECTOR3(0, 0, 0),		//��ƼŬ ���� �ӵ� �ּҰ�(���ñ���)
		D3DXVECTOR3(0, 0, 0),		//��ƼŬ ���� �ӵ� �ִ밪(���ñ���)
		D3DXVECTOR3(1, 1, 1),		//��ƼŬ ���� ���� �ּҰ�(���ñ���)
		D3DXVECTOR3(-1, -1, -1),	//��ƼŬ ���� ���� �ִ밪(���ñ���)
		colors,						//�÷� �迭
		scales,						//������ �迭
		0.1f,						//����ũ�� �ּҰ�
		0.5f,						//����ũ�� �ִ밪
		pTex,						//�ؽ���
		false						//�����̴�? �ƴϴ�?
	);
	*/

	/*
	//
	//ȭ�� ����
	//
	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(0, 0, 1, 0));
	colors.push_back(D3DXCOLOR(1, 0, 1, 0.5f));
	colors.push_back(D3DXCOLOR(1, 1, 1, 1));
	colors.push_back(D3DXCOLOR(0, 1, 1, 1));
	colors.push_back(D3DXCOLOR(1, 1, 0, 1));
	colors.push_back(D3DXCOLOR(1, 1, 0, 0));

	VEC_SCALE scales;
	scales.push_back(0.1f);
	scales.push_back(0.5f);
	scales.push_back(1.0f);
	scales.push_back(2.0f);
	scales.push_back(4.0f);

	LPDIRECT3DTEXTURE9 pTex = RM_TEXTURE->getResource("Resources/Textures/particle_0.png");

	//��ƼŬ ������ ����
	_pParticle->init(
	1000,							//�ִ� ��ƼŬ��
	100.0f,							//�ʴ� ��ƼŬ �߻� ��
	3,								//�ϳ��� ��ƼŬ ���� ������ �ּҰ�
	3.5f,							//�ϳ��� ��ƼŬ ���� ������ �ִ밪
	D3DXVECTOR3(0, 0, 3),			//��ƼŬ ���� �ӵ� �ּҰ�(���ñ���)
	D3DXVECTOR3(0, 0, 3),			//��ƼŬ ���� �ӵ� �ִ밪(���ñ���)
	D3DXVECTOR3(0, 0.2f, -0.5f),	//��ƼŬ ���� ���� �ּҰ�(���ñ���)
	D3DXVECTOR3(0, 0.4f, -1.0f),	//��ƼŬ ���� ���� �ִ밪(���ñ���)
	colors,							//�÷� �迭
	scales,							//������ �迭
	2.1f,							//����ũ�� �ּҰ�
	4.5f,							//����ũ�� �ִ밪
	pTex,							//�ؽ���
	false							//�����̴�? �ƴϴ�?
	);
	*/
	
	/*
	//
	//����
	//
	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 0.9f));
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 0.1f));
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(0.1f);
	scales.push_back(0.5f);
	scales.push_back(1.0f);
	scales.push_back(2.0f);
	scales.push_back(3.0f);

	LPDIRECT3DTEXTURE9 pTex = RM_TEXTURE->getResource("Resources/Textures/particle_0.png");
	
	//��ƼŬ ������ ����
	_pParticle->init(
	1000,						//�ִ� ��ƼŬ��
	200.0f,						//�ʴ� ��ƼŬ �߻� ��
	3,							//�ϳ��� ��ƼŬ ���� ������ �ּҰ�
	5,							//�ϳ��� ��ƼŬ ���� ������ �ִ밪
	D3DXVECTOR3(0, 0, 0),		//��ƼŬ ���� �ӵ� �ּҰ�(���ñ���)
	D3DXVECTOR3(0, 0, 0),		//��ƼŬ ���� �ӵ� �ִ밪(���ñ���)
	D3DXVECTOR3(1,1,1),			//��ƼŬ ���� ���� �ּҰ�(���ñ���)
	D3DXVECTOR3(-1,-1,-1),		//��ƼŬ ���� ���� �ִ밪(���ñ���)
	colors,						//�÷� �迭
	scales,						//������ �迭
	1.1f,						//����ũ�� �ּҰ�
	3.5f,						//����ũ�� �ִ밪
	pTex,						//�ؽ���
	false						//�����̴�? �ƴϴ�?
	);
	*/

	return S_OK;
}

void _2particleEmitter::release(void)
{
	_pParticle->release();
	SAFE_DELETE(_pParticle);
}

void _2particleEmitter::update(void)
{
	_pParticle->update();
	_pParticle->_transform->DefaultMyControl(_timeDelta);

	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		_pParticle->StartEmission();
	}
	else
	{
		_pParticle->StopEmission();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_pParticle->Burst(100, 1.4f, 2.7f, 0.1f, 0.5f);
	}
}

void _2particleEmitter::render(void)
{
	_pParticle->render();
	_pParticle->_transform->RenderGimozo();

	FONTMANAGER->fontOut("ParticleEmitter", 0, 100, 0xffff0000);
}
