#pragma once
#include "iScene.h"
class cSceneTest : public iScene
{
public:
	cSceneTest();
	virtual ~cSceneTest();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

