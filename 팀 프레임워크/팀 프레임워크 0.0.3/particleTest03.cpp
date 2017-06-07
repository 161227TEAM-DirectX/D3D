#include "stdafx.h"
#include "particleTest03.h"

HRESULT particleTest03::init(void)
{
	//시스템 초기화
	_testPS = new dxParticleSystem;


	_testEmitter = new dxPointEmitter;
	_testEmitter->init("PaticleResources/Texture/Light02.png", 1, 1.5f);
	//_testEmitter->InitRandomPositionX(-2.0f, 2.0f);
	//_testEmitter->InitRandomPositionY(0.0f, 0.0f);
	//_testEmitter->InitRandomPositionZ(-2.0f, 2.0f);

	//_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	//_testEmitter->InitRandomVelocityY(5.0f, 8.0f);
	//_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	/*_testEmitter->InitRandomVelocityX(0.0f, 0.0f);
	_testEmitter->addVelocityGraphX(0.25f, 1.0f, 1.0f);
	_testEmitter->addVelocityGraphX(0.5f, -2.0f, -2.0f);
	_testEmitter->addVelocityGraphX(0.75f, 2.0f, 2.0f);
	_testEmitter->addVelocityGraphX(1.0f, -1.0f, -1.0f);*/

	_testEmitter->InitRandomVelocityY(1.0f, 1.0f);

	//_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);
	/*_testEmitter->addVelocityGraphZ(0.25f, 1.0f, 1.0f);
	_testEmitter->addVelocityGraphZ(0.5f, -2.0f, -2.0f);
	_testEmitter->addVelocityGraphZ(0.75f, 2.0f, 2.0f);
	_testEmitter->addVelocityGraphZ(1.0f, -1.0f, -1.0f);*/

	//_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	//_testEmitter->InitRandomAccelerationY(-90.0f,-90.0f);
	//_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	//_testEmitter->InitRandomColorR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorB(0.1f, 1.0f);

	//_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeB(0.1f, 1.0f);

	_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.25f, 1.0f, 1.0f);
	_testEmitter->addAlphaGraph(0.3f, 1.0f, 1.0f);
	_testEmitter->addAlphaGraph(0.6f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.75f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(1.0f, 0.2f, 0.2f);

//	_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	_testEmitter->InitRandomLifeTime(6.0f, 6.0f);
	//_testEmitter->InitConstSize(1.0f);
	_testEmitter->InitRandomSize(2.0f, 2.0f);
	_testEmitter->addSizeGraph(0.25f, 0.5f, 0.5f);
	_testEmitter->addSizeGraph(0.5f, 6.0f, 6.0f);
	_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);
	_testEmitter->addSizeGraph(1.0f, 2.0f, 2.0f);
	//_testEmitter->addSizeGraph(0.25f, 3.0f, 3.0f);
	//_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);



	//_testEmitter->InitRandomSizeEnd(0.1f,2.0f);





	//
	//_testPS->addEmitter(_testEmitter);

	_testEmitter = NULL;
	_testEmitter = new dxPointEmitter;
	_testEmitter->init("PaticleResources/Texture/Light02.png", 3, 0.2f);
	_testEmitter->InitRandomPositionX(-8.0f, 8.0f);
	_testEmitter->InitRandomPositionY(0.0f, 0.0f);
	_testEmitter->InitRandomPositionZ(-8.0f, 8.0f);

	//_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	//_testEmitter->InitRandomVelocityY(5.0f, 8.0f);
	//_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);
	//_testEmitter->InitRandomPositionX(1.0f, 1.0f);
	//_testEmitter->InitRandomPositionY(0.0f, 20.0f);
	//_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);

	//_testEmitter->InitRandomRadiusX(10.0f, 10.0f);
	//_testEmitter->InitRandomRadiusY(5.0f, 5.0f);
	//_testEmitter->InitRandomRadiusZ(10.0f, 10.0f);
//	_testEmitter->InitRandomRadiusEndY(10.0f, 10.0f);
	//_testEmitter->InitRandomAngleSpeedX(50.0f,50.0f);
	//_testEmitter->InitRandomAngleSpeedY(-200.0f, -210.0f);
	//_testEmitter->InitRandomAngleSpeedZ(50.0f, 50.0f);


	_testEmitter->InitRandomVelocityX(0.0f, 0.0f);
	/*_testEmitter->addVelocityGraphX(0.25f, 1.0f, 1.0f);
	_testEmitter->addVelocityGraphX(0.5f, -2.0f, -2.0f);
	_testEmitter->addVelocityGraphX(0.75f, 2.0f, 2.0f);
	_testEmitter->addVelocityGraphX(1.0f, -1.0f, -1.0f);*/

	_testEmitter->InitRandomVelocityY(1.0f, 1.0f);

	_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);
	/*_testEmitter->addVelocityGraphZ(0.25f, 1.0f, 1.0f);
	_testEmitter->addVelocityGraphZ(0.5f, -2.0f, -2.0f);
	_testEmitter->addVelocityGraphZ(0.75f, 2.0f, 2.0f);
	_testEmitter->addVelocityGraphZ(1.0f, -1.0f, -1.0f);*/

	//_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	_testEmitter->InitRandomAccelerationY(180.0f,180.0f);
	//_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	//_testEmitter->InitRandomColorR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorB(0.1f, 1.0f);

	//_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeB(0.1f, 1.0f);

	_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.25f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.3f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.75f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(1.0f, 0.0f, 0.0f);

	//_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	_testEmitter->InitRandomLifeTime(8.0f, 8.0f);
	//_testEmitter->InitConstSize(1.0f);
	_testEmitter->InitRandomSize(3.0f, 3.0f);
	//_testEmitter->addSizeGraph(0.25f, 3.0f, 3.0f);
	//_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);



	//_testEmitter->InitRandomSizeEnd(0.1f,2.0f);

	//
	//_testPS->addEmitter(_testEmitter);

	_testEmitter = NULL;
	_testEmitter = new dxPointEmitter;
	_testEmitter->init("PaticleResources/Texture/Light02.png", 100, 8.0f);
	_testEmitter->InitRandomPositionX(-1.0f, 1.0f);
	_testEmitter->InitRandomPositionY(-1.0f, 1.0f);
	_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);
	_testEmitter->SetPositionType(PTC_SPHERE);
	_testEmitter->InitRandomPosSphereRadius(3.0f,3.0f);
	_testEmitter->InitRandomPosDirectionVelocity(0.0f,0.0f);
	_testEmitter->addPosDirectVelGraph(0.2f,0.0f,0.0f);
	_testEmitter->addPosDirectVelGraph(0.6f, 10.0f, 10.0f);
	_testEmitter->addPosDirectVelGraph(1.0f, -10.0f, -10.0f);
	//_testEmitter->InitStartDelayTime(5.0f);
	//_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	//_testEmitter->InitRandomVelocityY(5.0f, 8.0f);
	//_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);
	//_testEmitter->InitRandomPositionX(1.0f, 1.0f);
	//_testEmitter->InitRandomPositionY(0.0f, 20.0f);
	//_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);

	//_testEmitter->InitRandomRadiusX(10.0f, 10.0f);
	//_testEmitter->InitRandomRadiusY(2.0f, -2.0f);
	//_testEmitter->InitRandomRadiusZ(10.0f, 10.0f);
	//_testEmitter->InitRandomRadiusEndY(10.0f, 10.0f);
	//_testEmitter->InitRandomAngleSpeedX(50.0f,50.0f);
	//_testEmitter->InitRandomAngleSpeedY(-200.0f, -210.0f);
	//_testEmitter->InitRandomAngleSpeedZ(50.0f, 50.0f);


	//_testEmitter->InitRandomVelocityX(5.0f, 5.0f);
	/*_testEmitter->addVelocityGraphX(0.25f, 1.0f, 1.0f);
	_testEmitter->addVelocityGraphX(0.5f, -2.0f, -2.0f);
	_testEmitter->addVelocityGraphX(0.75f, 2.0f, 2.0f);
	_testEmitter->addVelocityGraphX(1.0f, -1.0f, -1.0f);*/

	//_testEmitter->InitRandomVelocityY(10.0f, 10.0f);
	_testEmitter->InitRandomVelocityY(0.0f, 0.0f);

	//_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);
	/*_testEmitter->addVelocityGraphZ(0.25f, 1.0f, 1.0f);
	_testEmitter->addVelocityGraphZ(0.5f, -2.0f, -2.0f);
	_testEmitter->addVelocityGraphZ(0.75f, 2.0f, 2.0f);
	_testEmitter->addVelocityGraphZ(1.0f, -1.0f, -1.0f);*/

	//_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	//_testEmitter->InitRandomAccelerationY(180.0f, 180.0f);
	//_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	//_testEmitter->InitRandomColorR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorB(0.1f, 1.0f);

	//_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeB(0.1f, 1.0f);

	_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.25f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.3f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.75f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(1.0f, 0.0f, 0.0f);

	//_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	_testEmitter->InitRandomLifeTime(8.0f, 8.0f);
	//_testEmitter->InitConstSize(1.0f);
	_testEmitter->InitRandomSize(3.0f, 3.0f);
	//_testEmitter->addSizeGraph(0.25f, 3.0f, 3.0f);
	//_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);



	//_testEmitter->InitRandomSizeEnd(0.1f,2.0f);

	//
	_testPS->addEmitter(_testEmitter);
	


	_testEmitter = NULL;
	_testEmitter = new dxPointEmitter;
	_testEmitter->init("PaticleResources/Texture/Light.png", 1, 0.1f);
	//_testEmitter->InitRandomPositionX(1.0f, 1.0f);
	_testEmitter->InitRandomPositionY(10.0f, 10.0f);
	//_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);
	
	//_testEmitter->InitRandomRadiusX(10.0f, 10.0f);
	_testEmitter->InitRandomRadiusX(1.0f, 1.0f);
	//_testEmitter->InitRandomRadiusZ(10.0f, 10.0f);
	_testEmitter->InitRandomRadiusEndX(12.0f, 12.0f);

	//_testEmitter->InitRandomAngleSpeedX(50.0f,50.0f);
	_testEmitter->InitCircleAngleSpeedX(360.0f, 360.0f);
	//_testEmitter->InitRandomAngleSpeedZ(50.0f, 50.0f);


	//_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	//_testEmitter->InitRandomVelocityY(5.0f, 8.0f);
	//_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	_testEmitter->InitRandomVelocityX(0.0f, 0.0f);
	_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);
	/*_testEmitter->addVelocityGraphX(0.25f, -1.0f, -1.0f);
	_testEmitter->addVelocityGraphX(0.5f, 2.0f, 2.0f);
	_testEmitter->addVelocityGraphX(0.75f, -2.0f, -2.0f);
	_testEmitter->addVelocityGraphX(1.0f, 1.0f, 1.0f);*/

	_testEmitter->InitRandomVelocityX(20.0f, 20.0f);

	/*_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);
	_testEmitter->addVelocityGraphZ(0.25f, -1.0f,-1.0f);
	_testEmitter->addVelocityGraphZ(0.5f, 2.0f, 2.0f);
	_testEmitter->addVelocityGraphZ(0.75f, -2.0f, -2.0f);d
	_testEmitter->addVelocityGraphZ(1.0f, 1.0f, 1.0f);*/

	_testEmitter->InitRandomAccelerationX(-980.0f,-980.0f);
	//_testEmitter->InitRandomAccelerationY(-90.0f,-90.0f);
	//_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	//_testEmitter->InitRandomColorR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorB(0.1f, 1.0f);

	//_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeB(0.1f, 1.0f);

	_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.25f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.5f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.75f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(1.0f, 0.0f, 0.0f);

	_testEmitter->InitRandomAlphaFade(0.5f, 0.5f);

	_testEmitter->InitRandomLifeTime(8.0f, 8.0f);
	//_testEmitter->InitConstSize(1.0f);
	_testEmitter->InitRandomSize(5.0f, 5.0f);
	//_testEmitter->addSizeGraph(0.25f, 3.0f, 3.0f);
	//_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);



	//_testEmitter->InitRandomSizeEnd(0.1f,2.0f);

	//
	//_testPS->addEmitter(_testEmitter);



	_testEmitter = NULL;
	_testEmitter = new dxPointEmitter;
	_testEmitter->init("PaticleResources/Texture/magic.png", 1, 0.1f);
	//_testEmitter->InitRandomPositionX(1.0f, 1.0f);
	_testEmitter->InitRandomPositionY(8.0f, 8.0f);
	//_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);

	//_testEmitter->InitRandomRadiusX(10.0f, 10.0f);
	_testEmitter->InitRandomRadiusY(16.0f, 16.0f);
	//_testEmitter->InitRandomRadiusZ(10.0f, 10.0f);
	//_testEmitter->InitRandomRadiusEndY(1.0f, 1.0f);

	//_testEmitter->InitRandomAngleSpeedX(50.0f,50.0f);
	_testEmitter->InitCircleAngleSpeedY(90.0f, 90.0f);
	//_testEmitter->InitRandomAngleSpeedZ(50.0f, 50.0f);


	//_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	//_testEmitter->InitRandomVelocityY(5.0f, 8.0f);
	//_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	_testEmitter->InitRandomVelocityX(0.0f, 0.0f);
	_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);
	/*_testEmitter->addVelocityGraphX(0.25f, -1.0f, -1.0f);
	_testEmitter->addVelocityGraphX(0.5f, 2.0f, 2.0f);
	_testEmitter->addVelocityGraphX(0.75f, -2.0f, -2.0f);
	_testEmitter->addVelocityGraphX(1.0f, 1.0f, 1.0f);*/

	_testEmitter->InitRandomVelocityY(0.0f, 0.0f);

	/*_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);
	_testEmitter->addVelocityGraphZ(0.25f, -1.0f,-1.0f);
	_testEmitter->addVelocityGraphZ(0.5f, 2.0f, 2.0f);
	_testEmitter->addVelocityGraphZ(0.75f, -2.0f, -2.0f);d
	_testEmitter->addVelocityGraphZ(1.0f, 1.0f, 1.0f);*/

	//_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	//_testEmitter->InitRandomAccelerationY(-90.0f,-90.0f);
	//_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	//_testEmitter->InitRandomColorR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorB(0.1f, 1.0f);

	//_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	//_testEmitter->InitRandomColorFadeB(0.1f, 1.0f);

	_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.25f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.5f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.75f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(1.0f, 0.0f, 0.0f);

	_testEmitter->InitRandomAlphaFade(0.5f, 0.5f);

	_testEmitter->InitRandomLifeTime(4.0f, 4.0f);
	//_testEmitter->InitConstSize(1.0f);
	_testEmitter->InitRandomSize(2.0f, 2.0f);
	//_testEmitter->addSizeGraph(0.25f, 3.0f, 3.0f);
	//_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);



	//_testEmitter->InitRandomSizeEnd(0.1f,2.0f);

	//
	_testPS->addEmitter(_testEmitter);

//=================================================================================================

	////시스템 초기화
	//_testPS = new dxPaticleSystem;


	//_testEmitter = new dxPointEmitter;
	//_testEmitter->init("PaticleResources/Texture/Light05.png", 8, 0.1f);
	////_testEmitter->InitRandomPositionX(-2.0f, 2.0f);
	//_testEmitter->InitRandomPositionY(-0.5f, 0.5f);
	//_testEmitter->InitRandomPositionZ(-0.5f, 0.5f);

	////_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	////_testEmitter->InitRandomVelocityY(5.0f, 8.0f);
	////_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	//_testEmitter->InitRandomVelocityX(-3.0f, -3.0f);
	///*_testEmitter->addVelocityGraphX(0.25f, -2.0f, -2.0f);
	//_testEmitter->addVelocityGraphX(0.5f, -2.0f, -1.0f);
	//_testEmitter->addVelocityGraphX(0.75f, 1.0f, 1.0f);
	//_testEmitter->addVelocityGraphX(1.0f, -1.0f, -1.0f);*/

	//_testEmitter->InitRandomVelocityY(0.0f, 0.0f);
	//_testEmitter->addVelocityGraphY(0.166f, -4.0f, -4.0f);
	//_testEmitter->addVelocityGraphY(0.332f, 4.0f, 4.0f);
	//_testEmitter->addVelocityGraphY(0.5f, -3.0f, -3.0f);
	//_testEmitter->addVelocityGraphY(0.666f, 3.0f, 3.0f);
	//_testEmitter->addVelocityGraphY(0.832f, -2.0f, -2.0f);
	//_testEmitter->addVelocityGraphY(1.0f, 2.0f, 2.0f);

	//_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);
	///*_testEmitter->addVelocityGraphZ(0.25f, 1.0f, 1.0f);
	//_testEmitter->addVelocityGraphZ(0.5f, -2.0f, -2.0f);
	//_testEmitter->addVelocityGraphZ(0.75f, 2.0f, 2.0f);
	//_testEmitter->addVelocityGraphZ(1.0f, -1.0f, -1.0f);*/

	////_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	////_testEmitter->InitRandomAccelerationY(-90.0f,-90.0f);
	////_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	////_testEmitter->InitRandomColorR(0.1f, 1.0f);
	////_testEmitter->InitRandomColorG(0.1f, 1.0f);
	////_testEmitter->InitRandomColorB(0.1f, 1.0f);

	////_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	////_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	////_testEmitter->InitRandomColorFadeB(0.1f, 1.0f);

	//_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	////_testEmitter->addAlphaGraph(0.25f, 1.0f, 1.0f);
	////_testEmitter->addAlphaGraph(0.5f, 1.0f, 1.0f);
	////_testEmitter->addAlphaGraph(0.75f, 1.0f, 1.0f);
	////_testEmitter->addAlphaGraph(1.0f, 0.2f, 0.2f);

	//_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	//_testEmitter->InitRandomLifeTime(8.0f, 8.0f);
	////_testEmitter->InitConstSize(1.0f);
	///*_testEmitter->InitRandomSize(2.0f, 2.0f);
	//_testEmitter->addSizeGraph(0.25f, 0.5f, 0.5f);
	//_testEmitter->addSizeGraph(0.5f, 4.0f, 4.0f);
	//_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);
	//_testEmitter->addSizeGraph(1.0f, 2.0f, 2.0f);*/
	////_testEmitter->addSizeGraph(0.25f, 3.0f, 3.0f);
	////_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);


	//_testPS->addEmitter(_testEmitter);

	//_testEmitter = new dxPointEmitter;
	//_testEmitter->init("PaticleResources/Texture/Light.png", 8, 0.1f);
	////_testEmitter->InitRandomPositionX(-2.0f, 2.0f);
	//_testEmitter->InitRandomPositionY(-0.5f, 0.5f);
	//_testEmitter->InitRandomPositionZ(-0.5f, 0.5f);

	////_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	////_testEmitter->InitRandomVelocityY(5.0f, 8.0f);
	////_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	//_testEmitter->InitRandomVelocityX(3.0f, 3.0f);
	///*_testEmitter->addVelocityGraphX(0.25f, -2.0f, -2.0f);
	//_testEmitter->addVelocityGraphX(0.5f, -2.0f, -1.0f);
	//_testEmitter->addVelocityGraphX(0.75f, 1.0f, 1.0f);
	//_testEmitter->addVelocityGraphX(1.0f, -1.0f, -1.0f);*/

	//_testEmitter->InitRandomVelocityY(0.0f, 0.0f);
	//_testEmitter->addVelocityGraphY(0.166f, -4.0f, -4.0f);
	//_testEmitter->addVelocityGraphY(0.332f, 4.0f, 4.0f);
	//_testEmitter->addVelocityGraphY(0.5f, -3.0f, -3.0f);
	//_testEmitter->addVelocityGraphY(0.666f, 3.0f, 3.0f);
	//_testEmitter->addVelocityGraphY(0.832f, -2.0f, -2.0f);
	//_testEmitter->addVelocityGraphY(1.0f, 2.0f, 2.0f);

	//_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);
	///*_testEmitter->addVelocityGraphZ(0.25f, 1.0f, 1.0f);
	//_testEmitter->addVelocityGraphZ(0.5f, -2.0f, -2.0f);
	//_testEmitter->addVelocityGraphZ(0.75f, 2.0f, 2.0f);
	//_testEmitter->addVelocityGraphZ(1.0f, -1.0f, -1.0f);*/

	////_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	////_testEmitter->InitRandomAccelerationY(-90.0f,-90.0f);
	////_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	////_testEmitter->InitRandomColorR(0.1f, 1.0f);
	////_testEmitter->InitRandomColorG(0.1f, 1.0f);
	////_testEmitter->InitRandomColorB(0.1f, 1.0f);

	////_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	////_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	////_testEmitter->InitRandomColorFadeB(0.1f, 1.0f);

	//_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	////_testEmitter->addAlphaGraph(0.25f, 1.0f, 1.0f);
	////_testEmitter->addAlphaGraph(0.5f, 1.0f, 1.0f);
	////_testEmitter->addAlphaGraph(0.75f, 1.0f, 1.0f);
	////_testEmitter->addAlphaGraph(1.0f, 0.2f, 0.2f);

	//_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	//_testEmitter->InitRandomLifeTime(8.0f, 8.0f);
	////_testEmitter->InitConstSize(1.0f);
	///*_testEmitter->InitRandomSize(2.0f, 2.0f);
	//_testEmitter->addSizeGraph(0.25f, 0.5f, 0.5f);
	//_testEmitter->addSizeGraph(0.5f, 4.0f, 4.0f);
	//_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);
	//_testEmitter->addSizeGraph(1.0f, 2.0f, 2.0f);*/
	////_testEmitter->addSizeGraph(0.25f, 3.0f, 3.0f);
	////_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);


	//_testPS->addEmitter(_testEmitter);

	//_testEmitter = NULL;
	//_testEmitter = new dxPointEmitter;
	//_testEmitter->init("PaticleResources/Texture/Light02.png", 8, 0.1f);
	//_testEmitter->InitRandomPositionX(-1.0f, 1.0f);
	////_testEmitter->InitRandomPositionY(-0.5f, 0.5f);
	//_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);

	////_testEmitter->InitRandomVelocityX(-3.0f, 3.0f);
	////_testEmitter->InitRandomVelocityY(5.0f, 8.0f);
	////_testEmitter->InitRandomVelocityZ(-3.0f, 3.0f);

	////_testEmitter->InitRandomVelocityX(3.0f, 3.0f);
	///*_testEmitter->addVelocityGraphX(0.25f, -2.0f, -2.0f);
	//_testEmitter->addVelocityGraphX(0.5f, -2.0f, -1.0f);
	//_testEmitter->addVelocityGraphX(0.75f, 1.0f, 1.0f);
	//_testEmitter->addVelocityGraphX(1.0f, -1.0f, -1.0f);*/

	//_testEmitter->InitRandomVelocityY(2.0f, 2.0f);
	///*_testEmitter->addVelocityGraphY(0.166f, -4.0f, -4.0f);
	//_testEmitter->addVelocityGraphY(0.332f, 4.0f, 4.0f);
	//_testEmitter->addVelocityGraphY(0.5f, -3.0f, -3.0f);
	//_testEmitter->addVelocityGraphY(0.666f, 3.0f, 3.0f);
	//_testEmitter->addVelocityGraphY(0.832f, -2.0f, -2.0f);
	//_testEmitter->addVelocityGraphY(1.0f, 2.0f, 2.0f);*/

	//_testEmitter->InitRandomVelocityZ(0.0f, 0.0f);
	///*_testEmitter->addVelocityGraphZ(0.25f, 1.0f, 1.0f);
	//_testEmitter->addVelocityGraphZ(0.5f, -2.0f, -2.0f);
	//_testEmitter->addVelocityGraphZ(0.75f, 2.0f, 2.0f);
	//_testEmitter->addVelocityGraphZ(1.0f, -1.0f, -1.0f);*/

	////_testEmitter->InitRandomAccelerationX(0.0f,0.0f);
	////_testEmitter->InitRandomAccelerationY(-90.0f,-90.0f);
	////_testEmitter->InitRandomAccelerationZ(0.0f,0.0f);

	////_testEmitter->InitRandomColorR(0.1f, 1.0f);
	////_testEmitter->InitRandomColorG(0.1f, 1.0f);
	////_testEmitter->InitRandomColorB(0.1f, 1.0f);

	////_testEmitter->InitRandomColorFadeR(0.1f, 1.0f);
	////_testEmitter->InitRandomColorFadeG(0.1f, 1.0f);
	////_testEmitter->InitRandomColorFadeB(0.1f, 1.0f);

	//_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.25f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.5f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.75f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(1.0f, 0.2f, 0.2f);

	//_testEmitter->InitRandomAlphaFade(0.0f, 0.0f);

	//_testEmitter->InitRandomLifeTime(8.0f, 8.0f);
	////_testEmitter->InitConstSize(1.0f);
	///*_testEmitter->InitRandomSize(2.0f, 2.0f);
	//_testEmitter->addSizeGraph(0.25f, 0.5f, 0.5f);
	//_testEmitter->addSizeGraph(0.5f, 4.0f, 4.0f);
	//_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);
	//_testEmitter->addSizeGraph(1.0f, 2.0f, 2.0f);*/
	////_testEmitter->addSizeGraph(0.25f, 3.0f, 3.0f);
	////_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);


	//_testPS->addEmitter(_testEmitter);


	//_testEmitter = NULL;
	//_testEmitter = new dxPointEmitter;
	//_testEmitter->init("PaticleResources/Texture/Light06.png", 1, 1.0f);
	////_testEmitter->InitRandomPositionX(-1.0f, 1.0f);
	////_testEmitter->InitRandomPositionY(-0.5f, 0.5f);
	////_testEmitter->InitRandomPositionZ(-1.0f, 1.0f);
	//_testEmitter->InitRandomVelocityY(0.0f, 0.0f);


	//_testEmitter->InitRandomAlpha(1.0f, 1.0f);
	////_testEmitter->addAlphaGraph(0.25f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(0.5f, 0.6f, 0.6f);
	////_testEmitter->addAlphaGraph(0.75f, 1.0f, 1.0f);
	//_testEmitter->addAlphaGraph(1.0f, 1.0f, 1.0f);

	//_testEmitter->InitRandomSize(3.0f, 3.0f);
	////_testEmitter->addSizeGraph(0.25f, 0.5f, 0.5f);
	//_testEmitter->addSizeGraph(0.5f, 8.0f, 8.0f);
	////_testEmitter->addSizeGraph(0.75f, 0.5f, 0.5f);
	//_testEmitter->addSizeGraph(1.0f, 3.0f, 3.0f);

	//_testEmitter->InitRandomLifeTime(4.0f, 4.0f);

	//_testPS->addEmitter(_testEmitter);

	return S_OK;
}

void particleTest03::release(void)
{
	//SAFE_DELETE(_testEmitter);
}

void particleTest03::update(void)
{
	_testPS->update();
}

void particleTest03::render(void)
{
	_testPS->render();
}
