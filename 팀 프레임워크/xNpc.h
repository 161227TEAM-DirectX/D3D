#pragma once
#include "gameNode.h"

class xNpc : public gameNode
{
private:
	string _name;
	float _posX;
	float _posZ;
	float _Tlerp;
	bool _playerTrace;

private:
	baseObject* _NpcObject;

	vector<baseObject*> _renderObjects;	
	terrain*			linkTerrain;

	dx::transform trans1;
	dx::transform trans2;

public:
	HRESULT init() { return S_OK; }
	HRESULT init(float posX, float poxZ, string name);
	void update();
	void render();
	void release(void);

	baseObject* getNpcObject() { return _NpcObject; }
	vector<baseObject*>& getRenderObject() { return _renderObjects; }
	void setlinkTerrain(terrain& land) { this->linkTerrain = &land; }
	void setlinkUi() {};
	void setCamera(camera* cc) { this->_mainCamera = cc; }

	xNpc() {};
	~xNpc() {};
};

