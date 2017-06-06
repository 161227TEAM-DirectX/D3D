#pragma once
/*������ ���� ����� �̰����� �߰��Ұ�!!!*/
#include "testScene.h"

class mainGame
{
private:
	void initManager();		//�Ŵ��� ����
	void releaseManager();	//�Ŵ��� ����

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	//���� ���ν���
	LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	mainGame() {}
	~mainGame() {}
};