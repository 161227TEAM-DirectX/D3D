#include "stdafx.h"
#include "cUIStart.h"
//
#include "cUIImageView.h"

cUIStart::cUIStart() : m_eMenu(eMenuType::E_START)
{
}

cUIStart::cUIStart(string sStartScreen) : m_eMenu(eMenuType::E_START)
{
	cUIImageView* pImage = new cUIImageView;
	pImage->SetTexture(sStartScreen);
	pImage->SetPosition(D3DXVECTOR3(0, 0, 0));
	AddChild(pImage);
}

cUIStart::~cUIStart()
{
}

void cUIStart::Setup()
{
}

void cUIStart::Update()
{
	cUIObject::Update();
}

void cUIStart::Render()
{
	cUIObject::Render(m_pSprite);
	g_pPicking->Update();
}

void cUIStart::OnClick(cUIButton * pButton)
{
	switch(pButton->GetTag())
	{
	case eMenuType::E_START:
		SCENEMANAGER->changeScene("loading");
		break;
	case eMenuType::E_MAPTOOL:
		g_eSelectMode = eSelectMode::E_MAPTOOL;
		SCENEMANAGER->changeScene("maptool");
		break;
	case eMenuType::E_SETTING:
		break;
	case eMenuType::E_EXIT:
		exit(0);
		break;
	}
}

void cUIStart::addButton(string sNorButton, string sButtonMov, string sButtonSel, float px, float py, int nTag)
{
	cUIButton* pButton = new cUIButton;
	pButton->SetButtonImage(sNorButton, sButtonMov, sButtonSel);
	pButton->SetPosition(D3DXVECTOR3(px, py, 0));
	pButton->SetTag(nTag);
	pButton->SetDelegate(this);
	AddChild(pButton);
}

