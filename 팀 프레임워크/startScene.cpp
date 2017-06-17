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
	m_pUIStart = new cUIStart("Resource/UI/����ȭ��.png");
	
	m_pUIStart->addButton("Resource/UI/���۹�ư_����.png",
						  "Resource/UI/���۹�ư_����.png",
						  "Resource/UI/���۹�ư_����.png",
						  1200, 
						  WINSIZEY / 2, 
						  0);
	m_pUIStart->addButton("Resource/UI/���۹�ư_����.png",
						  "Resource/UI/���۹�ư_����.png",
						  "Resource/UI/���۹�ư_����.png",
						  1200,
						  WINSIZEY / 2+90, 
						  1);
	m_pUIStart->addButton("Resource/UI/���۹�ư_����.png",
						  "Resource/UI/���۹�ư_����.png",
						  "Resource/UI/���۹�ư_����.png",
						  1200,
						  WINSIZEY / 2+180, 
						  2);
	m_pUIStart->addButton("Resource/UI/���۹�ư_����.png",
						  "Resource/UI/���۹�ư_����.png",
						  "Resource/UI/���۹�ư_����.png",
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
