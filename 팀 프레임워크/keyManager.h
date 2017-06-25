#pragma once
#include "singletonBase.h"
//====================================================================
//			## keyManager ## (Ű �Ŵ���)
//====================================================================

#define KEYMAX 256
#define KEYSAME	100

class keyManager : public singletonBase <keyManager>
{
private:
	bool _keyUp[KEYMAX][KEYSAME];
	bool _keyDown[KEYMAX][KEYSAME];

public:
	//Ű�Ŵ��� �ʱ�ȭ
	HRESULT init();
	void release(void);

	//Ű�� �ѹ��� ���ȳ�?
	bool isOnceKeyDown(int key);
	//Ű�� �ѹ� ���ȴ� �����?
	bool isOnceKeyUp(int key);
	//Ű�� ��� ���� �ֳ�?
	bool isStayKeyDown(int key);
	//���Ű��?
	bool isToggleKey(int key);

	keyManager() {}
	~keyManager() {}
};