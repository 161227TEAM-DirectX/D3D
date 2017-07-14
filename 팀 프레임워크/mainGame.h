#pragma once
/*앞으로 씬의 헤더만 이곳에서 추가할것!!!*/

//===================================================================================
//이현총 씬 테스트 헤더파일
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
//이현수 씬 테스트 헤더파일
//===================================================================================
#include "terrainPickingTest.h"
#include "bossMonsterAITestScene.h"

//===================================================================================
//김만웅 씬 테스트 헤더파일
//===================================================================================
//#include "cLoadingBarTest.h"	//로딩바
//#include "cLoadingTest.h"		//로딩


//===================================================================================
//김태훈 씬 테스트 헤더파일
//===================================================================================
#include "kimsTestScene.h"
#include "kimsNewTest.h"
#include "cubeLight.h"

//===================================================================================
//김태승 씬 테스트 헤더파일
//===================================================================================

//===================================================================================
//게임 씬
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

	//메인 프로시져
	LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};