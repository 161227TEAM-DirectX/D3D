#pragma once
#include "iGameNode.h"
class cMeshTest : public iGameNode
{
private:
	camera* _mainCamera; //���� ī�޶�

private:
	vector<baseObject*>		_renderObjects;		//���� ��ġ�� ���� ������Ʈ �迭
	vector<baseObject*>		_cullObjects;		//�ø��� ������Ʈ
	vector<skinnedAnimation*> _aniObjects;		//��Ű��޽�


	lightDirection*			_sceneBaseDirectionLight;	//���� ��ġ�� �⺻������
	camera*					_directionLightCamera;		//���⼺ ������ ���� ī�޶�
	float					_shadowDistance;			//�׸��� �Ÿ�
	
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

