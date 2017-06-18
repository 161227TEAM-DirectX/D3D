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
	temp = RM_TEXTURE->getResource("Resource/UI/로딩화면.png");
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
	temp->
	FONTMANAGER->fontOut("로딩씬입니다!", WINSIZEX / 2, WINSIZEY / 2, D3DCOLOR_XRGB(255, 255, 255));
}
