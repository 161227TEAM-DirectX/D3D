#include "stdafx.h"
#include "startScene.h"

startScene::startScene()
{
}

startScene::~startScene()
{
}

HRESULT startScene::init()
{
	SOUNDMANAGER->play("시작", 0.1f);

	for (int i=0; i < DXIMGANI_MANAGER->getAniSize("Ani_Fire01"); i++)
	{
		DXIMGANI_MANAGER->setDxImgAniPosition("Ani_Fire01_" + to_string(i), D3DXVECTOR2(i * 50, 800));
	}

	cDxImgButton* temp;

	temp = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_exit_off"),
							DXIMG_MANAGER->GetDxImg("btn_exit_over"),
							D3DXVECTOR2(25, 25), "종료버튼");
	m_vecBtn.push_back(temp);


	temp = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_option_off"),
							DXIMG_MANAGER->GetDxImg("btn_option_over"),
							D3DXVECTOR2(130, 25), "맵툴버튼");
	m_vecBtn.push_back(temp);


	temp = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_gameStart_off"),
							DXIMG_MANAGER->GetDxImg("btn_gameStart_over"),
							D3DXVECTOR2(1200, 750), "시작버튼");
	m_vecBtn.push_back(temp);


	//temp = new cDxImgButton(DXIMG_MANAGER->GetDxImg("btn_mapTool_off"),
	//						DXIMG_MANAGER->GetDxImg("btn_mapTool_over"),
	//						D3DXVECTOR2(1200, 750), "맵툴버튼");
	//m_vecBtn.push_back(temp);

	return S_OK;
}

void startScene::release()
{
	for (int i = 0; i<m_vecBtn.size(); i++)
	{
		SAFE_DELETE(m_vecBtn[i]);
	}
	m_vecBtn.clear();
}

void startScene::update()
{
	for (int i = 0; i < m_vecBtn.size(); i++)
	{
		if (m_vecBtn[i]->click())
		{
			if (m_vecBtn[i]->GetBtnName() == "종료버튼")
			{
				exit(0);
			}
			if (m_vecBtn[i]->GetBtnName() == "설정버튼")
			{

			}
			if (m_vecBtn[i]->GetBtnName() == "시작버튼")
			{
				SCENEMANAGER->changeScene("gameSceneOne");
			}
			if (m_vecBtn[i]->GetBtnName() == "맵툴버튼")
			{
				g_eSelectMode = E_MAPTOOL;
				SCENEMANAGER->changeScene("maptool");
			}
		}
	}
}

void startScene::render()
{
	DXIMG_MANAGER->GetDxImg("시작화면")->render();

	for (int i=0; i < DXIMGANI_MANAGER->getAniSize("Ani_Fire01"); i++)
	{
		DXIMGANI_MANAGER->render("Ani_Fire01_" + to_string(i));
	}

	for (int i=0; i<m_vecBtn.size(); i++)
	{
		m_vecBtn[i]->render();
	}
}