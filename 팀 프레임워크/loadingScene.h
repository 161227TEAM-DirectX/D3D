#pragma once
#include "iGameNode.h"
class loadingScene : public iGameNode
{
private:
	int i = 0;

public:
	loadingScene();
	virtual ~loadingScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:
	static HRESULT ThreadInit(LPVOID lpVod);

	static void UILoading();
	static void XMeshStaticLoading();
	static void XMeshSkinnedLoading();
};

