#include "stdafx.h"
#include "rmTexture.h"

HRESULT rmTexture::init(void)
{
	return S_OK;
}

void rmTexture::release(void)
{
}

LPDIRECT3DTEXTURE9 rmTexture::loadResource(string filePath, void * pParam)
{
	//텍스쳐 로딩
	LPDIRECT3DTEXTURE9 texture = NULL;
	if (FAILED(D3DXCreateTextureFromFile(_device, filePath.c_str(), &texture))) return NULL;

	return texture;
}

void rmTexture::releaseResource(LPDIRECT3DTEXTURE9 data)
{
	SAFE_RELEASE(data);
}
