#include "stdafx.h"
#include "_3quadParticleEmitter.h"

HRESULT _3quadParticleEmitter::init(void)
{
	//����ī�޶� ��ġ ����
	_mainCamera->SetWorldPosition(-1, 3, -7);

	//��ƼŬ ����
	_particle = new quadParticleEmitter;
	_particle->setActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(1.0f);
	scales.push_back(5.0f);

	_particle->init(
		100,
		10.0f,
		3.5f,
		4.0f,
		D3DXVECTOR3(0, 5, 0),
		D3DXVECTOR3(0, 6, 0),
		D3DXVECTOR3(0, 0.5, 0),
		D3DXVECTOR3(0, 0.8, 0),
		D3DXVECTOR3(D3DXToRadian(-90), 0, D3DXToRadian(90)),	//�ʱ���۽� ȸ��Min
		D3DXVECTOR3(D3DXToRadian(-90), 0, 0),					//�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0.5),									//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0.5),									//�ʴ� ȸ���� ȭ�� �� Max
		D3DXVECTOR3(0, 0, 1),									//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 2),									//�ʴ� ȸ�� ���� Max
		colors, scales,
		3.0f, 3.0f,
		RM_TEXTURE->getResource("Resources/Textures/FireExplosionBlurred.png"),
		true);

	_particle->StartEmission();


	//ī�޶� ����
	_particle->SetCameraSort(_mainCamera, true);

	return S_OK;
}

void _3quadParticleEmitter::release(void)
{
	_particle->release();
	SAFE_DELETE(_particle);
}

void _3quadParticleEmitter::update(void)
{
	_particle->update();
	_particle->_transform->DefaultMyControl(_timeDelta);

	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		_particle->StartEmission();
	}
	else
	{
		_particle->StopEmission();
	}
}

void _3quadParticleEmitter::render(void)
{
	_particle->render();
	_particle->_transform->RenderGimozo(_device);

	FONTMANAGER->fontOut("<��ƼŬ3 �׽�Ʈ>", 0, 100, 0xffff0000);
}
