#include "stdafx.h"
#include "skinnedAniTest.h"

HRESULT skinnedAniTest::init(void)
{
	D3DXMATRIXA16 matCorrection;
	D3DXMatrixScaling(&matCorrection, 0.1f, 0.1f, 0.1f);

	xMeshSkinned* pSkinned = 
		RM_SKINNED->getResource("Resources/Meshes/Witch/WitchApprentice.X", &matCorrection);

	//위에서 로딩괸 SkinnedMesh 인스턴스를 만든다.
	this->_pSkinned1 = new skinnedAnimation;
	this->_pSkinned2 = new skinnedAnimation;
	this->_pSkinned1->init(pSkinned);
	this->_pSkinned2->init(pSkinned);

	this->_pSkinnedTrans1 = new transform;
	this->_pSkinnedTrans2 = new transform;
	this->_pSkinnedTrans2->SetWorldPosition(5, 0, 0);

	this->_pBoxTrans1 = new transform;
	this->_pBoxTrans2 = new transform;
	this->_pBox1 = new boundBox();
	this->_pBox1->setBound(&D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1));

	//this->_pSkinned2->AddBoneTransform( "Bip01-HeadNub", _pBoxTrans1);
	//this->_pSkinned1->AddBoneTransform("Bip01-R-Hand", _pBoxTrans2);

	//this->_pApplyTrans = new transform();
	//this->_pSkinned1->AddApplyTransform( "Bip01-Spine1", this->_pApplyTrans);


	//라이트 푸쉬
	lightDirection* light1 = new lightDirection;
	light1->_color = D3DXCOLOR(1, 1, 1, 1);
	light1->_intensity = 1.0f;

	lightPoint* light2 = new lightPoint;
	light2->_color = D3DXCOLOR(1, 1, 1, 0);
	light2->_minRange = 5.0f;
	light2->_maxRange = 10.0f;
	light2->_distancePow = 10.0f;

	lightPoint* light3 = new lightPoint;
	light3->_color = D3DXCOLOR(1, 1, 1, 0);
	light3->_minRange = 5.0f;
	light3->_maxRange = 10.0f;
	light3->_distancePow = 10.0f;
	light3->_transform->SetWorldPosition(3, 3, 0);
	light3->_intensity = 0.5f;

	_lights.push_back(light1);
	_lights.push_back(light2);
	_lights.push_back(light3);

	return S_OK;
}

void skinnedAniTest::release(void)
{
	SAFE_DELETE(_pSkinnedTrans1);
	SAFE_DELETE(_pSkinnedTrans2);

	_pSkinned1->release();
	_pSkinned2->release();

	SAFE_DELETE(_pSkinned1);
	SAFE_DELETE(_pSkinned2);
	SAFE_DELETE(_pBoxTrans1);
	SAFE_DELETE(_pBox1);
}

void skinnedAniTest::update(void)
{
	_pSkinned1->update();
	_pSkinned2->update();

	if (KEYMANAGER->isStayKeyDown(VK_LCONTROL))
	{
		if (KEYMANAGER->isOnceKeyDown('1'))
		{
			_pSkinned1->Play("Idle", 0.3f);
		}
		if (KEYMANAGER->isOnceKeyDown('2'))
		{
			_pSkinned1->Play("Walk", 0.3f);
		}
		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			_pSkinned1->Play("run", 0.3f);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_pSkinned1->PlayOneShot("Atk01", 0.3, 0.3);
		}
		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			_pSkinned1->PlayOneShotAfterHold("Death", 0.3);
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('1'))
		{
			_pSkinned2->Play("Idle", 0.3f);
		}
		if (KEYMANAGER->isOnceKeyDown('2'))
		{
			_pSkinned2->Play("Walk", 0.3f);
		}
		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			_pSkinned2->Play("run", 0.3f);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_pSkinned2->PlayOneShot("Atk01", 0.3, 0.3);
		}
		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			_pSkinned2->PlayOneShotAfterHold("Death", 0.3);
		}
	}

	//this->_pApplyTrans->DefaultMyControl(_timeDelta);
	
	static float speed = 1.0f;

	if( KEYMANAGER->isStayKeyDown( VK_UP ))
	{
		speed += _timeDelta;
		if( speed >= 5.0f ) speed = 5.0f;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		speed -= _timeDelta;
		if (speed <= -5.0f) speed = -5.0f;
	}
	//애니메이션 속도
	_pSkinned1->SetPlaySpeed(speed);
	
}

void skinnedAniTest::render(void)
{
	//적용되는 LightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < _lights.size(); i++)
	{
		matLights[i] = _lights[i]->getLightMatrix();
	}

	//셰이더에 라이팅 세팅
	xMeshSkinned::_sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	xMeshSkinned::_sSkinnedMeshEffect->SetInt("LightNum", _lights.size());
	xMeshSkinned::setCamera(_mainCamera);
	_pSkinned1->render(_pSkinnedTrans1);
	_pSkinned2->render(_pSkinnedTrans2);

	this->_pSkinned1->renderBoneName(_mainCamera, _pSkinnedTrans1);
	//this->_pSkinned2->renderBoneName(_mainCamera, _pSkinnedTrans2);

	//가지고 있는 Animation 을출력해보자..
	RM_SKINNED->getResource("Resources/Meshes/Witch/WitchApprentice.X")->ShowAnimationName(0, 100);
}
