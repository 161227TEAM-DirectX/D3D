#pragma once
#include "gameNode.h"
class testScene : public gameNode
{
private:
	DWORD  m_dwThread[2];
	HANDLE m_hThread[2];

public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render();

public:
	static void ThreadSetup(LPVOID lpVod);
};

