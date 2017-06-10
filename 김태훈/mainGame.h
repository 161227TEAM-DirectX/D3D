#pragma once
/*������ ���� ����� �̰����� �߰��Ұ�!!!*/
#include "shadowTest1.h"
#include "shadowTest2.h"
#include "testScene1.h"

class mainGame
{
private:
	//�Ŵ��� ����
	void initManager(void);
	//�Ŵ��� ����
	void releaseManager(void);

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	//���� ���ν���
	LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	mainGame() {}
	~mainGame() {}
};