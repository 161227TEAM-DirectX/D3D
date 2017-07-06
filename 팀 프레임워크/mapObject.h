#pragma once
#include "iGameNode.h"
#include "Tportal.h"

class mapObject : public iGameNode
{
private:
	vector<Tportal*> _tportal;
	int portalNumber;
	bool temp;

public:
	mapObject();
	~mapObject();

	HRESULT objectinit();

	void objectSet(int objectNumber, baseObject * tempObect, D3DXMATRIX	matRotate, float m_fPickposX, float m_fPickposY, float m_fPickposZ, float mapScale, float mapRotation);

	void objectRenderTool2(vector<baseObject*>& object, camera* _mainCamera, lightDirection* _directionLight);
	void objectRenderTool(vector<baseObject*>& object, camera* _mainCamera, lightDirection* _directionLight);

	void potralErase(int objectNumber, int number);

	void deletePortal();

	void portalRender(camera * _mainCamera);
	void portal(vector<baseObject*>& tempObectr);

	HRESULT init() { return S_OK; }
	void release() {}
	void update() {}
	void render() {}
};

