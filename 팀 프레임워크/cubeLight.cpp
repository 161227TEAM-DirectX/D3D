#include "stdafx.h"
#include "cubeLight.h"


HRESULT cubeLight::init()
{
	_player = new xPlayer;
	_player->init();

	return S_OK;
}

void cubeLight::release()
{
}

void cubeLight::update()
{
	_player->update();
}

void cubeLight::render()
{
	_player->render();
}
