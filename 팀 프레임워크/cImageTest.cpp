#include "stdafx.h"
#include "cImageTest.h"
//
#include "cUIImageView.h"

cImageTest::cImageTest()
{
}


cImageTest::~cImageTest()
{
	SAFE_DELETE(pImage);
}

HRESULT cImageTest::init()
{
	//pImage = new cUIImageView;
	//pImage->SetTexture(FILEPATH_MANAGER->GetFilepath("�̹���_���ڸ�"));
	//pImage->SetPosition(D3DXVECTOR3(0, 0, 0));
	
	
	cDxImg* temp;

	temp = new cDxImg(FILEPATH_MANAGER->GetFilepath("�̹���_�źϿ�"));
	temp->SetCenterDraw(true);
	temp->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2 + 200, 0));
	temp->SetImgLayer(eImgLayer::E_NONE3);
	m_vecImg.push_back(temp);
	DXIMG_MANAGER->AddDxImg("�źϿ�", temp);

	temp = new cDxImg(FILEPATH_MANAGER->GetFilepath("�̹���_�̻��ز�"));
	temp->SetCenterDraw(true);
	temp->SetPosition(D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2 + 400, 0));
	temp->SetImgLayer(eImgLayer::E_NONE2);
	m_vecImg.push_back(temp);
	DXIMG_MANAGER->AddDxImg("�̻��ز�", temp);

	temp = new cDxImg(FILEPATH_MANAGER->GetFilepath("�̹���_���ڸ�"));
	temp->SetCenterDraw(true);
	temp->SetPosition(D3DXVECTOR3(WINSIZEX/2, WINSIZEY/2, 0));
	temp->SetImgLayer(eImgLayer::E_NONE);
	m_vecImg.push_back(temp);
	DXIMG_MANAGER->AddDxImg("���ڸ�", temp);






	sort(m_vecImg.begin(), m_vecImg.end(), [](const cDxImg* a, const cDxImg* b)
	{
		return a->GetImgLayer() > b->GetImgLayer();
	});

	return S_OK;
}

void cImageTest::release()
{
	m_vecImg.clear();

	//pImage->Release();
}

void cImageTest::update()
{
	_camera.updateBase();
	//pImage->Update();

	/*if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rt, GetMousePos()))
		{
			exit(0);
		}
	}*/

}

void cImageTest::render()
{
	//pImage->Render(m_pSprite);

	char str[STR_LEN];
	sprintf(str, "%d %d", GetMousePos().x, GetMousePos().y);

	FONTMANAGER->fontOut(str, 100, 500, BLACK);


	for (int i=0; i < m_vecImg.size(); i++)
	{
		//m_vecImg[i]->render();
	}

	RectMakeCenter(WINSIZEX/2,WINSIZEY/2,300,300,true);

	//DXIMG_MANAGER->render();

	//DXIMG_MANAGER->GetDxImg("���ڸ�")->render();
	//DXIMG_MANAGER->GetDxImg("�źϿ�")->render();
	//DXIMG_MANAGER->GetDxImg("�̻��ز�")->render();

	//m_pImg->SetDrawBoundingBox(true);
	//m_pImg->SetBoundingColor(GREEN);
	//m_pImg->render(WINSIZEX/2,WINSIZEY/2,45);
	//m_pImg->renderCenter(WINSIZEX / 2, WINSIZEY / 2);

	//IMAGE_MANAGER->RectMakeCenter(100, 0, 100, 300, true, SKY);

	//RectMake(100, 100, 100, 100);
	//RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
}
