#include "stdafx.h"
#include "_2particleEmitter.h"
#include "particleEmitter.h"

HRESULT _2particleEmitter::init(void)
{
	//메인카메라 위치 세팅
	_mainCamera->SetWorldPosition(0, 1, -5);

	//파티클 클래스 생성
	_pParticle = new particleEmitter();
	_pParticle->setActive(true);
	
	//
	//레이저 세팅~
	//

	//배열을 2개이상
	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));

	VEC_SCALE scales;
	scales.push_back(1.0f);
	scales.push_back(1.0f);
	scales.push_back(1.0f);

	LPDIRECT3DTEXTURE9 pTex = RM_TEXTURE->getResource("Resources/Textures/particle_0.png");

	//파티클 렌더러 세팅
 	_pParticle->init(
	1000,						//최대 파티클수
	200.0f,						//초당 파티클 발생 량
	5,							//하나의 파티클 입자 라이프 최소값
	5,							//하나의 파티클 입자 라이프 최대값
	D3DXVECTOR3(0, 0, 5),		//파티클 입자 속도 최소값(로컬기준)
	D3DXVECTOR3(0, 0, 5),		//파티클 입자 속도 최대값(로컬기준)
	D3DXVECTOR3(0, 0, 0),		//파티클 입자 가속 최소값(로컬기준)
	D3DXVECTOR3(0, 0, 0),		//파티클 입자 가속 최대값(로컬기준)
	colors,						//컬러 배열
	scales,						//스케일 배열
	1.0f,						//입자크기 최소값
	1.0f,						//입자크기 최대값
	pTex,						//텍스쳐
	true						//로컬이니? 아니니?
	);
	

	/*
	//
	//간지세팅
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

	//파티클 렌더러 세팅
	_pParticle->init(
		1000,						//최대 파티클수
		200.0f,						//초당 파티클 발생 량
		3,							//하나의 파티클 입자 라이프 최소값
		5,							//하나의 파티클 입자 라이프 최대값
		D3DXVECTOR3(0, 0, 0),		//파티클 입자 속도 최소값(로컬기준)
		D3DXVECTOR3(0, 0, 0),		//파티클 입자 속도 최대값(로컬기준)
		D3DXVECTOR3(1, 1, 1),		//파티클 입자 가속 최소값(로컬기준)
		D3DXVECTOR3(-1, -1, -1),	//파티클 입자 가속 최대값(로컬기준)
		colors,						//컬러 배열
		scales,						//스케일 배열
		0.1f,						//입자크기 최소값
		0.5f,						//입자크기 최대값
		pTex,						//텍스쳐
		false						//로컬이니? 아니니?
	);
	*/

	/*
	//
	//화염 방사기
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

	//파티클 렌더러 세팅
	_pParticle->init(
	1000,							//최대 파티클수
	100.0f,							//초당 파티클 발생 량
	3,								//하나의 파티클 입자 라이프 최소값
	3.5f,							//하나의 파티클 입자 라이프 최대값
	D3DXVECTOR3(0, 0, 3),			//파티클 입자 속도 최소값(로컬기준)
	D3DXVECTOR3(0, 0, 3),			//파티클 입자 속도 최대값(로컬기준)
	D3DXVECTOR3(0, 0.2f, -0.5f),	//파티클 입자 가속 최소값(로컬기준)
	D3DXVECTOR3(0, 0.4f, -1.0f),	//파티클 입자 가속 최대값(로컬기준)
	colors,							//컬러 배열
	scales,							//스케일 배열
	2.1f,							//입자크기 최소값
	4.5f,							//입자크기 최대값
	pTex,							//텍스쳐
	false							//로컬이니? 아니니?
	);
	*/
	
	/*
	//
	//폭발
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
	
	//파티클 렌더러 세팅
	_pParticle->init(
	1000,						//최대 파티클수
	200.0f,						//초당 파티클 발생 량
	3,							//하나의 파티클 입자 라이프 최소값
	5,							//하나의 파티클 입자 라이프 최대값
	D3DXVECTOR3(0, 0, 0),		//파티클 입자 속도 최소값(로컬기준)
	D3DXVECTOR3(0, 0, 0),		//파티클 입자 속도 최대값(로컬기준)
	D3DXVECTOR3(1,1,1),			//파티클 입자 가속 최소값(로컬기준)
	D3DXVECTOR3(-1,-1,-1),		//파티클 입자 가속 최대값(로컬기준)
	colors,						//컬러 배열
	scales,						//스케일 배열
	1.1f,						//입자크기 최소값
	3.5f,						//입자크기 최대값
	pTex,						//텍스쳐
	false						//로컬이니? 아니니?
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
