#include "stdafx.h"
#include "dxParticleTextureManager.h"

void dxParticleTextureManager::LoadImgInit(void)
{
	//this->LoadImg("테스트",);
}

//이미지 해제
void dxParticleTextureManager::ImgRelease(void)
{
	_iter = _mapTex.begin();
	for (_iter; _iter != _mapTex.end(); ++_iter)
	{
		SAFE_DELETE(_iter->second);
	}
	_mapTex.clear();
}
