#include "stdafx.h"
#include "Environment.h"

HRESULT Environment::init(void)
{
	_environmentEffect =  RM_SHADERFX->loadResource("Resource/Maptool/_Prev/FX/EnvironmentCUBE.fx");

	D3DXCreateCubeTextureFromFile(_device, "Resource/Maptool/TextureCUBE/fire.dds", &_temp);
	_environmentTexture.push_back(_temp);

	D3DXCreateCubeTextureFromFile(_device, "Resource/Maptool/TextureCUBE/autumnday1.dds", &_temp);
	_environmentTexture.push_back(_temp);

	D3DXCreateCubeTextureFromFile(_device, "Resource/Maptool/TextureCUBE/deserted.dds", &_temp);
	_environmentTexture.push_back(_temp);

	D3DXCreateCubeTextureFromFile(_device, "Resource/Maptool/TextureCUBE/freeskymatter.dds", &_temp);
	_environmentTexture.push_back(_temp);

	D3DXCreateCubeTextureFromFile(_device, "Resource/Maptool/TextureCUBE/ZORL.dds", &_temp);
	_environmentTexture.push_back(_temp);

	D3DXCreateCubeTextureFromFile(_device, "Resource/Maptool/TextureCUBE/desert.dds", &_temp);
	_environmentTexture.push_back(_temp);

	return S_OK;
}

void Environment::release(void)
{
	for (int i = 0; i < _environmentTexture.size(); i++)
	{
		SAFE_RELEASE(_environmentTexture[i]);
	}

	SAFE_RELEASE(_environmentCubeMesh);
	SAFE_RELEASE(_environmentEffect);
}

void Environment::update()
{
	_mainCamera->DefaultControl(_timeDelta, 1);
}

void Environment::render(void)
{
}

void Environment::renderEnvironment(int number)
{
	for (int i = 0; i < _environmentTexture.size(); i++)
	{
		if (_environmentTexture[i] == NULL)return;
	}

	if (number == 1) _environmentEffect->SetTexture("MyCube_Tex", _environmentTexture[0]);
	if (number == 2) _environmentEffect->SetTexture("MyCube_Tex", _environmentTexture[1]);
	if (number == 3) _environmentEffect->SetTexture("MyCube_Tex", _environmentTexture[2]);
	if (number == 4) _environmentEffect->SetTexture("MyCube_Tex", _environmentTexture[3]);
	if (number == 5) _environmentEffect->SetTexture("MyCube_Tex", _environmentTexture[4]);
	if (number == 6) _environmentEffect->SetTexture("MyCube_Tex", _environmentTexture[5]);

	if (_environmentCubeMesh == NULL)
	{
		D3DXCreateSphere(_device, 256.0f, 20, 20, &_environmentCubeMesh, NULL);
	}

	D3DXMATRIX matWorld = _mainCamera->GetFinalMatrix();
	D3DXMATRIX matViewProj = _mainCamera->getViewProjectionMatrix();
	D3DXMATRIX matWVP = matWorld * matViewProj;

	_environmentEffect->SetMatrix("matWVP", &matWVP);
	_environmentEffect->SetMatrix("matWorld", &matWorld);


	UINT iPassNum = 0;

	_environmentEffect->Begin(&iPassNum, 0);

	_mainCamera->updateCamToDevice();
	for (UINT i = 0; i < iPassNum; i++)
	{
		_environmentEffect->BeginPass(i);

		_environmentCubeMesh->DrawSubset(0);

		_environmentEffect->EndPass();
	}

	_environmentEffect->End();
}
