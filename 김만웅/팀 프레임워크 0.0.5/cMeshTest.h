#pragma once
#include "iGameNode.h"
class cMeshTest : public iGameNode
{
private:
	camera* _mainCamera; //메인 카메라

private:
	vector<baseObject*>		_renderObjects;		//씬에 배치된 랜더 오브젝트 배열
	vector<baseObject*>		_cullObjects;		//컬링된 오브젝트
	vector<skinnedAnimation*> _aniObjects;		//스키드메쉬


	lightDirection*			_sceneBaseDirectionLight;	//씬에 배치된 기본라이팅
	camera*					_directionLightCamera;		//방향성 광원에 따른 카메라
	float					_shadowDistance;			//그림자 거리
	
	skinnedAnimation*		_pSkinned1;
	dx::transform*			_pSkinnedTrans1;

public:
	cMeshTest();
	virtual ~cMeshTest();
	
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);
};

