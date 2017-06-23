#pragma once
#include "iGameNode.h"
class loadingScene : public iGameNode
{
private:
	cDxImgBar* m_pLoadingBar;
	static bool m_isChange;

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
	static void AniLoading();
	static void XMeshStaticLoading();
	static void XMeshSkinnedLoading();
	static void SoundLoading();
};

