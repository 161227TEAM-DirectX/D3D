#pragma once
/*������ ���� ����� �̰����� �߰��Ұ�!!!*/

//===================================================================================
//������ �� �׽�Ʈ �������
//===================================================================================
#include "particleTest.h"
#include "particleTest02.h"
#include "particleTest03.h"
#include "particleTest04.h"
#include "particleTest05.h"
#include "particleTest06.h"
#include "particleTest07.h"
#include "particleTest08.h"
#include "particleTest09.h"
#include "particleTest10.h"
#include "particleTest13.h"


//===================================================================================
//������ �� �׽�Ʈ �������
//===================================================================================
#include "terrainPickingTest.h"


//===================================================================================
//�踸�� �� �׽�Ʈ �������
//===================================================================================
//#include "cLoadingBarTest.h"	//�ε���
//#include "cLoadingTest.h"		//�ε�


//===================================================================================
//������ �� �׽�Ʈ �������
//===================================================================================
#include "kimsTestScene.h"
#include "kimsNewTest.h"
#include "cubeLight.h"

//===================================================================================
//���½� �� �׽�Ʈ �������
//===================================================================================

class mainGame
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	mainGame();
	~mainGame();

	//���� ���ν���
	LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};