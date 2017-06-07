#include "stdafx.h"
#include "_4snowPaticle.h"


HRESULT _4snowPaticle::init(void)
{
	_particle = new particleEmitter;
	_particle->setActive(true);

	//�迭�� 2�� �̻� 
	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1, 0.5f, 0, 1));
	colors.push_back(D3DXCOLOR(1, 0.8f, 0, 1));

	VEC_SCALE scales;
	scales.push_back(0.1f);
	scales.push_back(0.1f);

	LPDIRECT3DTEXTURE9  pTex = RM_TEXTURE->getResource("Resources/textures/Paticle_Snow.tga");

	//��ƼŬ ������ ����
	_particle->init(
		5000,							//�ִ� ��ƼŬ ��
		1000,							//�ʴ� ��ƼŬ �߻� ��
		1,								//�ϳ��� ��ƼŬ ���� ������ �ּҰ�
		10,								//�ϳ��� ��ƼŬ ���� ������ �ִ밪
		D3DXVECTOR3(0, 1.0f, 0),		//��ƼŬ ���� �ӵ� �ּҰ�(���� ����)
		D3DXVECTOR3(0, 2.0f, 0),		//��ƼŬ ���� �ӵ� �ִ밪(���� ����)
		D3DXVECTOR3(0, 1, 0),			//��ƼŬ ���� ���ӵ� �ּҰ�(���� ����)
		D3DXVECTOR3(0, 2, 0),			//��ƼŬ ���� ���ӵ� �ִ밪(���� ����)
		colors,							//�÷��迭
		scales,							//������ �迭
		3.1f,							//����ũ�� �ּҰ�
		5.2f,							//�ִ� ��
		pTex,							//�ؽ���
		false							//�����̴�???
	);

	//////////////////////////////////////////////////
	////��
	_particle->EmissionType = PATICLE_EMISSION_TYPE::BOX;
	_particle->MinEmissionRangeX = -10.0f;
	_particle->MaxEmissionRangeX = 10.0f;
	_particle->MinEmissionRangeY = 0.0f;
	_particle->MaxEmissionRangeY = 10.0f;
	_particle->MinEmissionRangeZ = -10.0f;
	_particle->MaxEmissionRangeZ = 10.0f;

	////////////////////////////////////////////////
	//��
	//_particle->EmissionType = PATICLE_EMISSION_TYPE::SPHERE_OUTLINE;
	//_particle->SphereEmissionRange = 1;
	
	_particle->StartEmission();

	return S_OK;
}

void _4snowPaticle::release(void)
{
	_particle->release();
	SAFE_DELETE(_particle);
}

void _4snowPaticle::update(void)
{
	_particle->update();
	_particle->_transform->DefaultMyControl(_timeDelta);
}

void _4snowPaticle::render(void)
{
	_particle->render();
	_particle->_transform->RenderGimozo(_device);
	FONTMANAGER->fontOut("<�������ƼŬ �׽�Ʈ>", 0, 100, 0xffff0000);
}
