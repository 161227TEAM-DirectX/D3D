#pragma once
/*������ ���� ����� �̰����� �߰��Ұ�!!!*/

//===================================================================================
//������ �� �׽�Ʈ �������
//===================================================================================
#include "particleTest04.h"
#include "particleTest05.h"
#include "particleTest06.h"
#include "particleTest07.h"
#include "particleTest08.h"
#include "particleTest09.h"
#include "particleTest10.h"
#include "particleTest11.h"
#include "particleTest13.h"


//===================================================================================
//������ �� �׽�Ʈ �������
//===================================================================================
#include "terrainPickingTest.h"
#include "bossMonsterAITestScene.h"

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

//===================================================================================
//���� ��
//===================================================================================
//#include "stageOne.h"
//#include "stageTwo.h"
//#include "stageThree.h"
//#include "stageFour.h"

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