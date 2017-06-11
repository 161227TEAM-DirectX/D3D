#pragma once
#include "iGameNode.h"
class cGameNodeTest : public iGameNode
{
private:
	camera* _mainCamera; //���� ī�޶�

private:
	vector<baseObject*>		_renderObjects;		//���� ��ġ�� ���� ������Ʈ �迭
	vector<baseObject*>		_cullObjects;		//�ø��� ������Ʈ

	terrain*				_terrain;			//����
	terrain*				_terrainShadow;		//���� �׸���

	lightDirection*			_sceneBaseDirectionLight;	//���� ��ġ�� �⺻������
	camera*					_directionLightCamera;		//���⼺ ������ ���� ī�޶�
	float					_shadowDistance;			//�׸��� �Ÿ�

public:
	cGameNodeTest();
	virtual ~cGameNodeTest();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	void readyShadowMap(vector<baseObject*>* renderObjects, terrain* pTerrain = NULL);

};

