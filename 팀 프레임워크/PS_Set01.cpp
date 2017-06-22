#include "stdafx.h"
#include "PS_Set00.h"

HRESULT PS_Set01::init()
{
	//파티클 이름이 잘 보이게 일부러 이름 넣는 인자값을 준다.
	this->set00_00("테스트");
	this->set00_01("타겟");

	return S_OK;
}

void PS_Set01::release()
{
	dxParticleSystemSet::release();
}

void PS_Set01::set00_00(string psName)
{
	dxParticleSystemSet::init();

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/Light.png", 36, 0.5f, 200);
	_pointEMT->InitRandomLifeTime(1.0f, 1.0f);
	_pointEMT->SetPositionType();
	_pointEMT->InitDirSphere(1.0f,0.0f,1.0f);
	_pointEMT->InitRandomPosSphereRadius(3.0f, 3.0f);
	_pointEMT->InitConstAttractCenter(0.0f,6.0f, 0.0f);
	//_pointEMT->InitRandomColorR(0.2126, 0.2126f);
	//_pointEMT->InitRandomColorG(0.07152f, 0.7152f);
	//_pointEMT->InitRandomColorB(0.0722f, 0.0722f);
	//_pointEMT->InitConstSize(2.4f);

	_PS->addEmitter(_pointEMT);

	PSM->addPS(psName, _PS);
}

void PS_Set01::set00_01(string psName)
{
	dxParticleSystemSet::init();

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/Light06.png", 1, 1.0f , 1);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);
	
	_pointEMT->InitRandomSize(2.5f, 2.5f);
	_pointEMT->InitRandomSizeEnd(7.0f,7.0f);

	_pointEMT->InitRandomAlpha(0.4f, 0.4f);
	_pointEMT->addAlphaGraph(0.8, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.7f, 0.7f);
//	_pointEMT->InitRandomAlphaFade(.0f, 10.0f);
	//_pointEMT->addSizeGraph(0.5f, 3.5f, 3.5f);
	//_pointEMT->addSizeGraph(1.0f, 2.5f, 2.5f);
	

	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/explosion.png", 1, 1.0f,1);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);
	_pointEMT->InitRandomSize(2.2f,2.2f);
	_pointEMT->addSizeGraph(0.5f,4.5f,4.5f);
	_pointEMT->addSizeGraph(1.0f,1.5f,1.5f);
	_pointEMT->InitRandomAlpha(1.0f, 1.0f);
	_pointEMT->addAlphaGraph(0.6, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.3f, 0.3f);

	_PS->addEmitter(_pointEMT);

	_pointEMT = NULL;
	_pointEMT = new dxPointEmitter;
	_pointEMT->init("PaticleResources/Texture/Light02.png", 1, 1.0f,1);
	_pointEMT->InitRandomLifeTime(0.2f, 0.2f);
	_pointEMT->InitRandomSize(2.0f, 2.0f);
	_pointEMT->addSizeGraph(0.7f, 2.5f, 2.5f);
	_pointEMT->addSizeGraph(1.0f, 7.5f, 7.5f);
	_pointEMT->InitRandomAlpha(0.2f, 0.2f);
	_pointEMT->addAlphaGraph(0.7, 1.0f, 1.0f);
	_pointEMT->addAlphaGraph(1.0, 0.8f, 0.8f);

	_PS->addEmitter(_pointEMT);

	PSM->addPS(psName, _PS);
}
