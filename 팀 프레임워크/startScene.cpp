#include "stdafx.h"
#include "startScene.h"

startScene::startScene()
{
}

startScene::~startScene()
{
}

HRESULT startScene::init()
{
	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
}

void startScene::render()
{
	DXIMG_MANAGER->GetDxImg("����ȭ��")->render();
}
