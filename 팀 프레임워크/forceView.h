#pragma once
#include "iGameNode.h"

class forceView : public iGameNode
{
private:
	lightDirection* _directionLight; //ºûÅ¬·¡½º
	baseObject _sword[5];
	camera	   _mainCamera;

	float speed;
	int number;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	forceView() {}
	~forceView() {}
};

