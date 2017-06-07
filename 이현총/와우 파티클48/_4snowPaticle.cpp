#include "stdafx.h"
#include "_4snowPaticle.h"


HRESULT _4snowPaticle::init(void)
{
	_particle = new particleEmitter;
	_particle->setActive(true);

	//배열을 2개 이상 
	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1, 0.5f, 0, 1));
	colors.push_back(D3DXCOLOR(1, 0.8f, 0, 1));

	VEC_SCALE scales;
	scales.push_back(0.1f);
	scales.push_back(0.1f);

	LPDIRECT3DTEXTURE9  pTex = RM_TEXTURE->getResource("Resources/textures/Paticle_Snow.tga");

	//파티클 랜더러 생성
	_particle->init(
		5000,							//최대 파티클 수
		1000,							//초당 파티클 발생 량
		1,								//하나의 파티클 입자 라이프 최소값
		10,								//하나의 파티클 입자 라이프 최대값
		D3DXVECTOR3(0, 1.0f, 0),		//파티클 입자 속도 최소값(로컬 기준)
		D3DXVECTOR3(0, 2.0f, 0),		//파티클 입자 속도 최대값(로컬 기준)
		D3DXVECTOR3(0, 1, 0),			//파티클 입자 가속도 최소값(로컬 기준)
		D3DXVECTOR3(0, 2, 0),			//파티클 입자 가속도 최대값(로컬 기준)
		colors,							//컬러배열
		scales,							//스케일 배열
		3.1f,							//입자크기 최소값
		5.2f,							//최대 값
		pTex,							//텍스쳐
		false							//로컬이니???
	);

	//////////////////////////////////////////////////
	////눈
	_particle->EmissionType = PATICLE_EMISSION_TYPE::BOX;
	_particle->MinEmissionRangeX = -10.0f;
	_particle->MaxEmissionRangeX = 10.0f;
	_particle->MinEmissionRangeY = 0.0f;
	_particle->MaxEmissionRangeY = 10.0f;
	_particle->MinEmissionRangeZ = -10.0f;
	_particle->MaxEmissionRangeZ = 10.0f;

	////////////////////////////////////////////////
	//원
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
	FONTMANAGER->fontOut("<스노우파티클 테스트>", 0, 100, 0xffff0000);
}
