#include "stdafx.h"
#include "dxParticleTextureManager.h"

void dxParticleTextureManager::LoadImgInit(void)
{
	//this->LoadImg("�׽�Ʈ",);
}

//�̹��� ����
void dxParticleTextureManager::ImgRelease(void)
{
	_iter = _mapTex.begin();
	for (_iter; _iter != _mapTex.end(); ++_iter)
	{
		SAFE_DELETE(_iter->second);
	}
	_mapTex.clear();
}
