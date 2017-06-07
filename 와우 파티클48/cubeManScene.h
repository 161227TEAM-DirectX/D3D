#pragma once
#include "gameNode.h"

class gameObject;
class characterController;

class cubeManScene : public gameNode
{
private:
	gameObject* _root;
	characterController* _cc;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	cubeManScene() : _root(NULL), _cc(NULL) {}
	~cubeManScene() {}
};

