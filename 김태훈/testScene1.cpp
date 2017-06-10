#include "stdafx.h"
#include "testScene1.h"

HRESULT testScene1::init()
{
	_sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(90), 0, 0);
	_player = new xPlayer;
	_player->init();
	return S_OK;
}

void testScene1::update()
{
	_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);
	_player->update();
}

void testScene1::render()
{
	//if (KEYMANAGER->isStayKeyDown('1'))
	//{
	//	//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	//	//xMeshStatic::setTechniqueName("CreateShadow");
	//	
	//}
	//else
	//{
	//	//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	//	xMeshStatic::setTechniqueName("ReciveShadow");
	//}



	xMeshStatic::setCamera(_mainCamera);
	xMeshStatic::setTechniqueName("Toon");
	xMeshStatic::setBaseLight(this->_sceneBaseDirectionLight);

	xMeshSkinned::setCamera(_mainCamera);
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);
	//xMeshSkinned::setTechniqueName("ReciveShadow");
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resources/Testures/Ramp_1.png"));
	

	_player->render();

	RM_SKINNED->getResource("Resources/Player/FHUMAN_PLATE/FHUMAN.X")->ShowAnimationName(0, 0);

	
}

void testScene1::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
}
