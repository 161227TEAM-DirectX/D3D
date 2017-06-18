#include "stdafx.h"
#include "startScene.h"
#include "cUIStart.h"

startScene::startScene()
{
}

startScene::~startScene()
{
}

HRESULT startScene::init()
{
	m_pUIStart = new cUIStart("Resource/UI/시작화면.png");
	
	m_pUIStart->addButton("Resource/UI/시작버튼_오버.png",
						  "Resource/UI/시작버튼_오프.png",
						  "Resource/UI/시작버튼_오프.png",
						  1200, 
						  WINSIZEY / 2, 
						  0);
	m_pUIStart->addButton("Resource/UI/시작버튼_오버.png",
						  "Resource/UI/시작버튼_오프.png",
						  "Resource/UI/시작버튼_오프.png",
						  1200,
						  WINSIZEY / 2+90, 
						  1);
	m_pUIStart->addButton("Resource/UI/시작버튼_오버.png",
						  "Resource/UI/시작버튼_오프.png",
						  "Resource/UI/시작버튼_오프.png",
						  1200,
						  WINSIZEY / 2+180, 
						  2);
	m_pUIStart->addButton("Resource/UI/시작버튼_오버.png",
						  "Resource/UI/시작버튼_오프.png",
						  "Resource/UI/시작버튼_오프.png",
						  1200,
						  WINSIZEY / 2+270, 
						  3);

	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
	m_pUIStart->Update();
}

void startScene::render()
{
	m_pUIStart->Render();
}
