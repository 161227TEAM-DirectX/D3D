#include "stdafx.h"
#include "cubeManScene.h"
#include "cube.h"
#include "characterController.h"

HRESULT cubeManScene::init(void)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixTranslation(&mat, 0, -1.5f, 0);
	
	cube* body = new cube;
	body->init(D3DXVECTOR3(2, 3, 1));
	_root = body;
	
	cube* head = new cube;
	head->init(D3DXVECTOR3(2, 2, 2));
	head->setLocalTranslation(D3DXVECTOR3(0, 2.5, 0));
	_root->addChild(head);

	cube* pLArm = new cube;
	pLArm->init(D3DXVECTOR3(1, 3, 1), &mat);
	pLArm->setLocalTranslation(D3DXVECTOR3(-1.5, 1.5, 0));
	pLArm->setAngleSpeed(0.1f);
	_root->addChild(pLArm);

	cube* pRArm = new cube;
	pRArm->init(D3DXVECTOR3(1, 3, 1), &mat);
	pRArm->setLocalTranslation(D3DXVECTOR3(1.5, 1.5, 0));
	pRArm->setAngleSpeed(-0.1f);
	_root->addChild(pRArm);

	cube* pLLeg = new cube;
	pLLeg->init(D3DXVECTOR3(1, 3, 1), &mat);
	pLLeg->setLocalTranslation(D3DXVECTOR3(-0.5, -1, 0));
	pLLeg->setAngleSpeed(-0.1f);
	_root->addChild(pLLeg);

	cube* pRLeg = new cube;
	pRLeg->init(D3DXVECTOR3(1, 3, 1), &mat);
	pRLeg->setLocalTranslation(D3DXVECTOR3(0.5, -1, 0));
	pRLeg->setAngleSpeed(0.1f);
	_root->addChild(pRLeg);
	
	_cc = new characterController;
	_cc->init();

	//카메라 타겟 세팅(없어도 세팅해줘야 카메라가 세팅된다)
	//CAMAERAMANAGER->setTarget(_cc->GetPosition());
	//CAMAERAMANAGER->setTarget(&D3DXVECTOR3(0, 0, 0));
	
	return S_OK;
}

void cubeManScene::release(void)
{
	if (_root) _root->destroy();
}

void cubeManScene::update(void)
{
	_cc->update();
	_root->update(_cc->GetWorldTM());
}

void cubeManScene::render(void)
{
	GIZMOMANAGER->WorldGrid(1, 15);
	_root->render();
}
