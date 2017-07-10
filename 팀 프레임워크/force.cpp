#include "stdafx.h"
#include "force.h"
#include "inven.h"

HRESULT force::init(void)
{
	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword1").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword1")[i]->SetPosition(D3DXVECTOR3(380, 290, 0));
		DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword1")[i]->SetCenterDraw(false);
	}
	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword2").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword2")[i]->SetPosition(D3DXVECTOR3(380, 290, 0));
		DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword2")[i]->SetCenterDraw(false);
	}
	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword3").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword3")[i]->SetPosition(D3DXVECTOR3(380, 290, 0));
		DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword3")[i]->SetCenterDraw(false);
	}
	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword4").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword4")[i]->SetPosition(D3DXVECTOR3(380, 290, 0));
		DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword4")[i]->SetCenterDraw(false);
	}
	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword5").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword5")[i]->SetPosition(D3DXVECTOR3(380, 290, 0));
		DXIMGANI_MANAGER->GetDxImgAni("Ani_Sword5")[i]->SetCenterDraw(false);
	}

	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("force").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("force")[i]->SetPosition(D3DXVECTOR3(390, 310, 0));
		DXIMGANI_MANAGER->GetDxImgAni("force")[i]->SetCenterDraw(false);
	}

	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("force2").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("force2")[i]->SetPosition(D3DXVECTOR3(600, 310, 0));
		DXIMGANI_MANAGER->GetDxImgAni("force2")[i]->SetCenterDraw(false);
	}



	_forceV.tex = RM_TEXTURE->getResource("Resource/Maptool/sword/소드1/1.png");
	_forceShop.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/실험용.png");
	_foceGage.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/강화게이지.png");
	_forcePlus.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/강화게이지.png");
	_forceS.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/강화알림.png");
	_forceF.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/강화알림.png");
	_forceB.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/확인취소.png");

	for (int i = 0; i < 3; i++)
	{
		_forceButton[i].check = false;
		_forceButton[i].tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/강화버튼.png");
	}
	_forcePlus.check = false;
	_forceS.check = false;
	_forceF.check = false;

	_forceMoney = 1000;
	_forceGaege = 0;
	forceNumber = 0;

	return S_OK;
}

void force::release(void)
{

}

void force::update(void)
{
	//강화
	if (PtInRect(&_forceButton[0].rc2, GetMousePos()))
	{
		_forceButton[0].check = true;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
		{
			if (_forceInformation.size() != 0)
			{
				_forcePlus.check = true;
			}

			pair<bool, POINT> temp;
			temp.first = false;

			_inven->setPick(temp);
		}
	}
	else
	{
		_forceButton[0].check = false;
	}
	//분리
	if (PtInRect(&_forceButton[1].rc2, GetMousePos()))
	{
		_forceButton[1].check = true;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
		{
			if (_forceInformation.size() != 0 && _forcePlus.check == false)
			{
				//인벤으로 대입
				_inven->setVinvenItemRender(_forceRender[0]);
				_inven->setVinvenItem(_forceInformation[0]);

				//대장간에서 삭제
				_forceRender.erase(_forceRender.begin());
				_forceInformation.erase(_forceInformation.begin());

				forceNumber = 0;

			}

			_forceButton[1].check = false;

			pair<bool, POINT> temp;
			temp.first = false;

			_inven->setPick(temp);
		}
	}
	else
	{
		_forceButton[1].check = false;
	}

	//장착
	if (_inven->getPick().first == true)
	{
		if (PtInRect(&_forceButton[2].rc2, GetMousePos()))
		{
			_forceButton[2].check = true;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				if (_forceRender.size() < 1 && _inven->getTempInformation().type == ITEMKIND::WEAPON)
				{
					//벡터정보 넣기
					_forceInformation.push_back(_inven->getTempInformation());
					//인벤벡터정보 삭제
					_inven->removeInvenItemInformation(_inven->getTempItem());
					//렌더 벡터정보 넣기
					_forceRender.push_back(_inven->getTempRender());
					//인벤렌더 정보 삭제
					_inven->removeInvenItem(_inven->getTempItem());

					forceNumber = _inven->getTempInformation().number;
				}

				_forceButton[2].check = false;

				pair<bool, POINT> temp;
				temp.first = false;

				_inven->setPick(temp);
			}
		}
		else
		{
			_forceButton[2].check = false;
		}
	}

	//랜덤으로 값돌리기
	_rand = RandomFloatRange(1, 3);

	//게이지 순서 
	if (_forcePlus.check == true)
	{
		if (_forceGaege >= 314)
		{
			if (_rand == 1)
			{
				_forceS.check = true;
				_forceInformation[0].force++;
			}
			else
			{
				_forceF.check = true;
			}

			_forcePlus.check = false;
			_forceGaege = 0;
		}
		else
		{
			_forceGaege++;
		}
	}

	//성공할떄 버튼
	if (_forceS.check == true)
	{
		if (PtInRect(&_forceB.rc2, GetMousePos()))
		{
			_forceB.check = true;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				_forceS.check = false;
				_forceB.check = false;
			}
		}
		else
		{
			_forceB.check = false;
		}
	}

	//실패할때 버튼
	if (_forceF.check == true)
	{
		if (PtInRect(&_forceB.rc2, GetMousePos()))
		{
			_forceB.check = true;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				_forceF.check = false;
				_forceB.check = false;
			}
		}
		else
		{
			_forceB.check = false;
		}
	}
}

void force::render(void)
{
	//대장간바탕UI
	_forceShop.rc2 = { 350,150,862,662 };
	SPRITEMANAGER->renderRectTexture(_forceShop.tex, &_forceShop.rc1, &_forceShop.rc2, 0, 0, 1024, 1024, 350, 150);

	if (_forcePlus.check == true)
	{
		SPRITEMANAGER->renderRectTexture(_forcePlus.tex, &_forcePlus.rc1, &_forcePlus.rc2, 0, 31, _forceGaege, 64, _forceShop.rc2.left + 86, _forceShop.rc2.top + 321);
	}

	SPRITEMANAGER->renderRectTexture(_foceGage.tex, &_foceGage.rc1, &_foceGage.rc2, 0, 0, 512, 31, _forceShop.rc2.left + 86, _forceShop.rc2.top + 321);

	if (_forcePlus.check == true)
	{
		FONTMANAGER->fontOut("강 화 중", _forceShop.rc2.left + 200, _forceShop.rc2.top + 326, D3DCOLOR_XRGB(255, 255, 255));
		DXIMGANI_MANAGER->render("force");
	}

	_forceButton[0].rc2 = { _forceShop.rc2.left + 280,_forceShop.rc2.top + 365 ,_forceButton[0].rc2.left + 96,_forceButton[0].rc2.top + 37 };
	_forceButton[1].rc2 = { _forceShop.rc2.left + 280,_forceShop.rc2.top + 400 ,_forceButton[1].rc2.left + 96,_forceButton[1].rc2.top + 37 };
	_forceButton[2].rc2 = { _forceShop.rc2.left + 280,_forceShop.rc2.top + 435 ,_forceButton[2].rc2.left + 96,_forceButton[2].rc2.top + 37 };

	//무기렌더
	for (int i = 0; i < _forceRender.size(); i++)
	{
		SPRITEMANAGER->renderRectTexture(_forceRender[i].tex, &_forceRender[i].rc1, &_forceRender[i].rc2, 0, 0, 64, 64, _forceShop.rc2.left + 32, _forceShop.rc2.top + 314);
	}
	//대장간UI버튼
	//강화버튼
	if (_forceButton[0].check == true)
	{
		SPRITEMANAGER->renderRectTexture(_forceButton[0].tex, &_forceButton[0].rc1, &_forceButton[0].rc2, 0, 0, 96, 37, _forceShop.rc2.left + 280, _forceShop.rc2.top + 365);
	}
	else
	{
		SPRITEMANAGER->renderRectTexture(_forceButton[0].tex, &_forceButton[0].rc1, &_forceButton[0].rc2, 0, 37, 96, 74, _forceShop.rc2.left + 280, _forceShop.rc2.top + 365);
	}
	//분리버튼
	if (_forceButton[1].check == true)
	{
		SPRITEMANAGER->renderRectTexture(_forceButton[1].tex, &_forceButton[1].rc1, &_forceButton[1].rc2, 0, 74, 96, 111, _forceShop.rc2.left + 280, _forceShop.rc2.top + 400);
	}
	else
	{
		SPRITEMANAGER->renderRectTexture(_forceButton[1].tex, &_forceButton[1].rc1, &_forceButton[1].rc2, 0, 111, 96, 148, _forceShop.rc2.left + 280, _forceShop.rc2.top + 400);
	}
	//장착버튼
	if (_forceButton[2].check == true)
	{
		SPRITEMANAGER->renderRectTexture(_forceButton[2].tex, &_forceButton[2].rc1, &_forceButton[1].rc2, 0, 148, 96, 185, _forceShop.rc2.left + 280, _forceShop.rc2.top + 435);
	}
	else
	{
		SPRITEMANAGER->renderRectTexture(_forceButton[2].tex, &_forceButton[2].rc1, &_forceButton[1].rc2, 0, 185, 96, 222, _forceShop.rc2.left + 280, _forceShop.rc2.top + 435);
	}

	if (_forceInformation.size() != 0)
	{
		FONTMANAGER->fontOut("+" + to_string(_forceInformation[0].force), _forceShop.rc2.left + 120, _forceShop.rc2.top + 375, D3DCOLOR_XRGB(255, 255, 255));

		FONTMANAGER->fontOut(to_string(_forceMoney * _forceInformation[0].force), _forceShop.rc2.left + 110, _forceShop.rc2.top + 430, D3DCOLOR_XRGB(255, 255, 255));
	}

	switch (forceNumber)
	{
	case 0:
		SPRITEMANAGER->renderRectTexture(_forceV.tex, &_forceV.rc1, &_forceV.rc2, 0, 0, 512, 512, 380, 290);
		break;
	case 1:
		DXIMGANI_MANAGER->render("Ani_Sword1");
		break;
	case 2:
		DXIMGANI_MANAGER->render("Ani_Sword2");
		break;
	case 3:
		DXIMGANI_MANAGER->render("Ani_Sword3");
		break;
	case 4:
		DXIMGANI_MANAGER->render("Ani_Sword4");
		break;
	case 5:
		DXIMGANI_MANAGER->render("Ani_Sword5");
		break;
	}

	if (_forcePlus.check == true)
	{
		DXIMGANI_MANAGER->render("force");
		DXIMGANI_MANAGER->render("force2");
	}


	//성공
	if (_forceS.check == true)
	{
		SPRITEMANAGER->renderRectTexture(_forceS.tex, &_forceS.rc1, &_forceS.rc2, 0, 0, 512, 89, _forceShop.rc2.left + 330, _forceShop.rc2.top + 150);

		_forceB.rc2 = { _forceShop.rc2.left + 400, _forceShop.rc2.top + 200 ,_forceB.rc2.left + 96 , _forceB.rc2.top + 37 };

		if (_forceB.check == true)
		{
			SPRITEMANAGER->renderRectTexture(_forceB.tex, &_forceB.rc1, &_forceB.rc2, 0, 0, 256, 37, _forceShop.rc2.left + 400, _forceShop.rc2.top + 200);
		}
		else
		{
			SPRITEMANAGER->renderRectTexture(_forceB.tex, &_forceB.rc1, &_forceB.rc2, 0, 37, 256, 74, _forceShop.rc2.left + 400, _forceShop.rc2.top + 200);
		}
	}
	//실패
	if (_forceF.check == true)
	{
		SPRITEMANAGER->renderRectTexture(_forceF.tex, &_forceF.rc1, &_forceF.rc2, 0, 89, 512, 178, _forceShop.rc2.left + 330, _forceShop.rc2.top + 150);

		_forceB.rc2 = { _forceShop.rc2.left + 400, _forceShop.rc2.top + 200 ,_forceB.rc2.left + 96 , _forceB.rc2.top + 37 };

		if (_forceB.check == true)
		{
			SPRITEMANAGER->renderRectTexture(_forceB.tex, &_forceB.rc1, &_forceB.rc2, 0, 0, 256, 37, _forceShop.rc2.left + 400, _forceShop.rc2.top + 200);
		}
		else
		{
			SPRITEMANAGER->renderRectTexture(_forceB.tex, &_forceB.rc1, &_forceB.rc2, 0, 37, 256, 74, _forceShop.rc2.left + 400, _forceShop.rc2.top + 200);
		}
	}
}
