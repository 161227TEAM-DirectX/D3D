#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	return S_OK;
}

void loadingScene::release()
{
}

void loadingScene::update()
{
}

void loadingScene::render()
{
	FONTMANAGER->fontOut("로딩씬입니다!", WINSIZEX / 2, WINSIZEY / 2, D3DCOLOR_XRGB(255, 255, 255));
}
