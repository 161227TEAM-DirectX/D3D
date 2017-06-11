#include "stdafx.h"
#include "cLoading.h"


cLoading::cLoading()
{
	SetRandomSeed();					//랜덤시드 초기화
	CreateDevice();						//디바이스 초기화
	KEYMANAGER->init();					//키매니져 초기화
	TIMEMANAGER->init();				//타임매니져 초기화
	SCENEMANAGER->init();				//씬매니져 초기화
	FONTMANAGER->init();				//폰트매니져 초기화
	GIZMOMANAGER->init();				//기즈모매니져 초기화
	RM_TEXTURE->init();					//RM텍스쳐 초기화
	RM_SHADERFX->init();				//RM셰이더FX 초기화
	RM_XMESH->init();					//RM스태틱X메쉬 초기화
	RM_SKINNED->init();					//RM스킨드X메쉬 초기화
	PHYSICSMANAGER->init();				//피직스매니져 초기화
	SPRITEMANAGER->init();				//스프라이트매니져 초기화
	PSM->ParticleSystemSetInit();		//파티클시스템매니져 초기화
}


cLoading::~cLoading()
{
	//키매니져 싱글톤 해제
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
	//타임매니져 싱글톤 해제
	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();
	//씬매니져 싱글톤 해제
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();
	//폰트매니져 싱글톤 해제
	FONTMANAGER->release();
	FONTMANAGER->releaseSingleton();
	//기즈모매니져 싱글톤 해제
	GIZMOMANAGER->release();
	GIZMOMANAGER->releaseSingleton();
	//리소스매니져 싱글톤 해제
	RM_TEXTURE->clearResource();
	RM_TEXTURE->releaseSingleton();
	RM_SHADERFX->clearResource();
	RM_SHADERFX->releaseSingleton();
	RM_XMESH->clearResource();
	RM_XMESH->releaseSingleton();
	RM_SKINNED->clearResource();
	RM_SKINNED->releaseSingleton();
	//피직스매니져 싱글톤 해제
	PHYSICSMANAGER->release();
	PHYSICSMANAGER->releaseSingleton();
	//스프라이트매니져 싱글톤 해제
	SPRITEMANAGER->release();
	SPRITEMANAGER->releaseSingleton();
	//파티클시스템매니져 싱글톤 해제
	PSM->ParticleSystemSetRelease();
	PSM->releaseSingleton();

	//디바이스 해제
	ReleaseDevice();
}
