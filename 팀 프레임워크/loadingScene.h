#pragma once
#include "iGameNode.h"
class loadingScene : public iGameNode
{
private:
	cDxImgBar* m_pLoadingBar;
	static bool m_isChange;
	static bool m_isChangeScene1;
	static bool m_isChangeScene2;
	static bool m_isChangeScene3;
	static bool m_isChangeScene4;

public:
	loadingScene();
	virtual ~loadingScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:
	static HRESULT ThreadInit(LPVOID lpVod);
	static HRESULT ThreadInitScene1(LPVOID lpVod);
	static HRESULT ThreadInitScene2(LPVOID lpVod);
	static HRESULT ThreadInitScene3(LPVOID lpVod);
	static HRESULT ThreadInitScene4(LPVOID lpVod);


	static void UILoading();
	static void AniLoading();
	static void PtcLoading();
	static void XMeshStaticLoading();
	static void XMeshSkinnedLoading();
	static void SoundLoading();
};

