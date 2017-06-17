#pragma once
#include "iGameNode.h"

class mapObject : public iGameNode
{
private:
	lightDirection* _directionLight; //ºûÅ¬·¡½º
//	camera			_mainCamera;

public:
	mapObject();
	~mapObject();

	HRESULT objectinit();
	void objectUpdate();
	void objectSet(int objectNumber, baseObject * tempObect, D3DXMATRIX	matRotate, float m_fPickposX, float m_fPickposY, float m_fPickposZ, float mapScale, float mapRotation);
//	void objectRender(vector<baseObject>& object);
	void objectRenderTool(vector<baseObject*>& object, camera* _mainCamera);

	HRESULT init() { return S_OK; }
	void release() {}
	void update() {}
	void render() {}
};

