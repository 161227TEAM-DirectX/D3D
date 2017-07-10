#include "stdafx.h"
#include "medicineShop.h"
#include "inven.h"

HRESULT medicineShop::init(void)
{
	_medicine = new medicine;

	for (int i = 0; i < _medicine->getVmedicineRender().size(); i++)
	{
		_medicineRender[i].tex = _medicine->getVmedicineRender()[i].tex;
		_medicineRender[i].kind = _medicine->getVmedicineRender()[i].kind;
		_medicineRender[i].check = false;
		_medicineRender[i].number = 0;
	}

	//사기,팔기 버튼
	for (int i = 0; i < 2; i++)
	{
		_medicineButton[i].tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/상점버튼.png");
		_medicineButton[i].check = false;

		_medicineSellButton[i].tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/확인취소.png");
		_medicineSellButton[i].check = false;

		_medicinePMSellButton[i].tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/물약업.png");
		_medicinePMSellButton[i].check = false;
	}
	//플,마 버튼
	for (int i = 0; i < 3; i++)
	{
		_medicinePMbutton[i].tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/물약업.png");
		_medicinePMbutton[i].check = false;
	}

	_medicineSellMenu.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/알림.png");
	_medicineSellMenu.check = false;

	for (int i = 0; i < _medicine->getVmedicene().size(); i++)
	{
		_vmidicine.push_back(_medicine->getVmedicene()[i]);
	}

	_countStrart = false;
	_pick.first = false;
	_tempTemp = false;
	_pick.second = { 0,0 };

	return S_OK;
}

void medicineShop::release(void)
{
}

void medicineShop::update(void)
{
	for (int i = 0; i < MENUMBER; i++)
	{
		if (PtInRect(&_medicineRender[i].rc2, GetMousePos()))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				//선택하면 테두리
				_pick.second = { _medicineRender[i].rc2.left,_medicineRender[i].rc2.top };
				_pick.first = true;

				//렌더이미지 템프에 담기
				_medicineTemp = _medicineRender[i];

				_tempInfomation = _vmidicine[i];

				pair<bool, POINT> temp;
				temp.first = false;
				_inven->setPick(temp);
			}
		}
	}

	//픽이 선택 되었을 때
	if (_pick.first == true)
	{
		//마이너스 버튼
		if (PtInRect(&_medicinePMbutton[0].rc2, GetMousePos()))
		{
			_medicinePMbutton[0].check = true;

			if (_tempInfomation.medicineCount <= 1) _tempInfomation.medicineCount = 1;
			else _tempInfomation.medicineCount--;
		}
		else
		{
			_medicinePMbutton[0].check = false;
		}

		//플러스 버튼
		if (PtInRect(&_medicinePMbutton[1].rc2, GetMousePos()))
		{
			_medicinePMbutton[1].check = true;

			if (_tempInfomation.medicineCount >= 99) _tempInfomation.medicineCount = 99;
			else _tempInfomation.medicineCount++;
		}
		else
		{
			_medicinePMbutton[1].check = false;
		}

		//사기버튼
		if (PtInRect(&_medicineButton[0].rc2, GetMousePos()))
		{
			_medicineButton[0].check = true;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				_inven->setVinvenItemRender(_medicineTemp);
				_inven->setVinvenItem(_tempInfomation);

				_medicineButton[0].check = false;
				_pick.first = false;
			}

		}
		else
		{
			_medicineButton[0].check = false;
		}
	}


	//팔기버튼
	if (PtInRect(&_medicineButton[1].rc2, GetMousePos()))
	{
		_medicineButton[1].check = true;

		if (_inven->getPick().first == true)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				_medicineSellMenu.check = true;
			}
		}
		else
		{
			_medicineButton[1].check = false;
		}
	}

	if (_medicineSellMenu.check == true)
	{
		if (_countStrart == false)
		{
			_countTemp = _inven->getTempInformation();
			_count2Temp = _inven->getTempInformation();
			_countStrart = true;
		}
		//마이너스버튼
		if (PtInRect(&_medicinePMSellButton[0].rc2, GetMousePos()))
		{
			_medicinePMSellButton[0].check = true;

			if (_countTemp.medicineCount <= 1) _countTemp.medicineCount = 1;
			else _countTemp.medicineCount--;
		}
		else
		{
			_medicinePMSellButton[0].check = false;
		}

		//플러스 버튼
		if (PtInRect(&_medicinePMSellButton[1].rc2, GetMousePos()))
		{
			_medicinePMSellButton[1].check = true;

			if (_countTemp.medicineCount >= _count2Temp.medicineCount) _countTemp.medicineCount = _count2Temp.medicineCount;
			else _countTemp.medicineCount++;
		}
		else
		{
			_medicinePMSellButton[1].check = false;
		}

		//확인버튼
		if (PtInRect(&_medicineSellButton[0].rc2, GetMousePos()))
		{
			_medicineSellButton[0].check = true;

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				if (_countTemp.medicineCount == _inven->getTempInformation().medicineCount)
				{
					_inven->removeInvenItem(_inven->getTempItem());
					_inven->removeInvenItemInformation(_inven->getTempItem());
				}
				else
				{
					_countTemp.medicineCount = _count2Temp.medicineCount - _countTemp.medicineCount;
					_tempTemp = true;
					_inven->setTempInformation(_countTemp);
				}

				_medicineSellMenu.check = false;
				_medicineButton[1].check = false;
				_countStrart = false;

				pair<bool, POINT> temp;
				temp.first = false;
				_inven->setPick(temp);
			}
		}
		else
		{
			_medicineSellButton[0].check = false;
		}

		//취소버튼
		if (PtInRect(&_medicineSellButton[1].rc2, GetMousePos()))
		{
			_medicineSellButton[1].check = true;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON, false))
			{
				_medicineSellButton[1].check = false;
				_medicineSellMenu.check = false;
				_countStrart = false;

				_medicineButton[1].check = false;
				pair<bool, POINT> temp;
				temp.first = false;
				_inven->setPick(temp);
			}
		}
		else
		{
			_medicineSellButton[1].check = false;
		}
	}


}

void medicineShop::render(void)
{
	//상점바탕UI
	_medicineShop.tex = RM_TEXTURE->getResource("ResourceUI/inven/shop/물약상점.png");
	_medicineShop.rc2 = { 350,150,862,662 };
	SPRITEMANAGER->renderRectTexture(_medicineShop.tex, &_medicineShop.rc1, &_medicineShop.rc2, 0, 0, 1024, 1024, 350, 150);

	//무기 아이템
	for (int i = 0; i < _medicine->getVmedicineRender().size(); i++)
	{
		_medicineRender[i].rc2 = { _medicineShop.rc2.left + 108, (_medicineShop.rc2.top + 150) + i * 62 ,_medicineRender[i].rc2.left + 33,_medicineRender[i].rc2.top + 51 };
		SPRITEMANAGER->renderRectTexture(_medicineRender[i].tex, &_medicineRender[i].rc1, &_medicineRender[i].rc2, 0, 0, 64, 64, _medicineShop.rc2.left + 108, (_medicineShop.rc2.top + 150) + i * 62);
	}

	//선택버튼
	if (_pick.first == true)
	{
		LPDIRECT3DTEXTURE9 temp = RM_TEXTURE->getResource("ResourceUI/inven/shop/픽1.png");
		for (int i = 0; i < MENUMBER; i++)
		{
			SPRITEMANAGER->renderRectTexture(temp, &_medicineRender[i].rc1, &_medicineRender[i].rc2, 0, 0, 64, 64, _pick.second.x, _pick.second.y);
		}
	}

	//사기,팔기 버튼
	if (_medicineButton[0].check == true)
	{
		_medicineButton[0].rc2 = { _medicineShop.rc2.left + 195, _medicineShop.rc2.top + 445 ,_medicineButton[0].rc2.left + 96,_medicineButton[0].rc2.top + 37 };
		SPRITEMANAGER->renderRectTexture(_medicineButton[0].tex, &_medicineButton[0].rc1, &_medicineButton[0].rc2, 0, 0, 96, 37, _medicineShop.rc2.left + 195, _medicineShop.rc2.top + 445);
	}
	else
	{
		_medicineButton[0].rc2 = { _medicineShop.rc2.left + 195, _medicineShop.rc2.top + 445 ,_medicineButton[0].rc2.left + 96,_medicineButton[0].rc2.top + 37 };
		SPRITEMANAGER->renderRectTexture(_medicineButton[0].tex, &_medicineButton[0].rc1, &_medicineButton[0].rc2, 0, 37, 96, 74, _medicineShop.rc2.left + 195, _medicineShop.rc2.top + 445);
	}

	if (_medicineButton[1].check == true)
	{
		_medicineButton[1].rc2 = { _medicineShop.rc2.left + 300, _medicineShop.rc2.top + 445 ,_medicineButton[1].rc2.left + 96,_medicineButton[1].rc2.top + 37 };
		SPRITEMANAGER->renderRectTexture(_medicineButton[1].tex, &_medicineButton[1].rc1, &_medicineButton[1].rc2, 0, 74, 96, 111, _medicineShop.rc2.left + 300, _medicineShop.rc2.top + 445);
	}
	else
	{
		_medicineButton[1].rc2 = { _medicineShop.rc2.left + 300, _medicineShop.rc2.top + 445 ,_medicineButton[1].rc2.left + 96,_medicineButton[1].rc2.top + 37 };
		SPRITEMANAGER->renderRectTexture(_medicineButton[1].tex, &_medicineButton[1].rc1, &_medicineButton[1].rc2, 0, 111, 96, 148, _medicineShop.rc2.left + 300, _medicineShop.rc2.top + 445);
	}

	//상점바탕UI
	SPRITEMANAGER->renderRectTexture(_medicinePMbutton[2].tex, &_medicinePMbutton[2].rc1, &_medicinePMbutton[2].rc2, 0, 74, 74, 109, _medicineShop.rc2.left + 63, _medicineShop.rc2.top + 445);


	if (_pick.first == true)
	{
		//물약 갯수 정보
		FONTMANAGER->fontOut(to_string(_tempInfomation.medicineCount), _medicineShop.rc2.left + 90, _medicineShop.rc2.top + 454, D3DCOLOR_XRGB(255, 255, 255));
	}

	//물약 마이너스 버튼
	if (_medicinePMbutton[0].check == true)
	{
		_medicinePMbutton[0].rc2 = { _medicineShop.rc2.left + 15, _medicineShop.rc2.top + 445 ,_medicinePMbutton[0].rc2.left + 37,_medicinePMbutton[0].rc2.top + 37 };
		SPRITEMANAGER->renderRectTexture(_medicinePMbutton[0].tex, &_medicinePMbutton[0].rc1, &_medicinePMbutton[0].rc2, 37, 0, 74, 37, _medicineShop.rc2.left + 15, _medicineShop.rc2.top + 445);
	}
	else
	{
		_medicinePMbutton[0].rc2 = { _medicineShop.rc2.left + 15, _medicineShop.rc2.top + 445 ,_medicinePMbutton[0].rc2.left + 37,_medicinePMbutton[0].rc2.top + 37 };
		SPRITEMANAGER->renderRectTexture(_medicinePMbutton[0].tex, &_medicinePMbutton[0].rc1, &_medicinePMbutton[0].rc2, 37, 37, 74, 74, _medicineShop.rc2.left + 15, _medicineShop.rc2.top + 445);
	}

	//물약 플러스 버튼
	if (_medicinePMbutton[1].check == true)
	{
		_medicinePMbutton[1].rc2 = { _medicineShop.rc2.left + 150, _medicineShop.rc2.top + 445 ,_medicinePMbutton[1].rc2.left + 37,_medicinePMbutton[1].rc2.top + 37 };
		SPRITEMANAGER->renderRectTexture(_medicinePMbutton[1].tex, &_medicinePMbutton[1].rc1, &_medicinePMbutton[1].rc2, 0, 0, 37, 37, _medicineShop.rc2.left + 150, _medicineShop.rc2.top + 445);
	}
	else
	{
		_medicinePMbutton[1].rc2 = { _medicineShop.rc2.left + 150, _medicineShop.rc2.top + 445 ,_medicinePMbutton[1].rc2.left + 37,_medicinePMbutton[1].rc2.top + 37 };
		SPRITEMANAGER->renderRectTexture(_medicinePMbutton[1].tex, &_medicinePMbutton[1].rc1, &_medicinePMbutton[1].rc2, 0, 37, 37, 74, _medicineShop.rc2.left + 150, _medicineShop.rc2.top + 445);
	}

	if (_medicineSellMenu.check == true)
	{
		_medicineSellMenu.rc2 = { 500,300, 670,415 };
		SPRITEMANAGER->renderRectTexture(_medicineSellMenu.tex, &_medicineSellMenu.rc1, &_medicineSellMenu.rc2, 0, 0, 512, 512, 500, 300);

		LPDIRECT3DTEXTURE9 temp = RM_TEXTURE->getResource("ResourceUI/inven/shop/물약업.png");
		SPRITEMANAGER->renderRectTexture(temp, &_medicineSellMenu.rc1, &_medicineSellMenu.rc2, 0, 74, 74, 109, (_medicineSellMenu.rc2.left + _medicineSellMenu.rc2.right) / 2 + 13, _medicineSellMenu.rc2.top + 30);

		FONTMANAGER->fontOut(to_string(_countTemp.medicineCount), _medicineSellMenu.rc2.left + 123, _medicineSellMenu.rc2.top + 40, D3DCOLOR_XRGB(255, 255, 255));

		if (_medicineSellButton[0].check == true)
		{
			_medicineSellButton[0].rc2 = { _medicineSellMenu.rc2.left + 10, _medicineSellMenu.rc2.top + 72 ,_medicineSellButton[0].rc2.left + 96,_medicineSellButton[0].rc2.top + 37 };
			SPRITEMANAGER->renderRectTexture(_medicineSellButton[0].tex, &_medicineSellButton[0].rc1, &_medicineSellButton[0].rc2, 0, 0, 96, 37, _medicineSellMenu.rc2.left + 10, _medicineSellMenu.rc2.top + 72);
		}
		else
		{
			_medicineSellButton[0].rc2 = { _medicineSellMenu.rc2.left + 10, _medicineSellMenu.rc2.top + 72 ,_medicineSellButton[0].rc2.left + 96,_medicineSellButton[0].rc2.top + 37 };
			SPRITEMANAGER->renderRectTexture(_medicineSellButton[0].tex, &_medicineSellButton[0].rc1, &_medicineSellButton[0].rc2, 0, 37, 96, 74, _medicineSellMenu.rc2.left + 10, _medicineSellMenu.rc2.top + 72);
		}
		if (_medicineSellButton[1].check == true)
		{
			_medicineSellButton[1].rc2 = { _medicineSellMenu.rc2.left + 165, _medicineSellMenu.rc2.top + 72 ,_medicineSellButton[1].rc2.left + 96,_medicineSellButton[1].rc2.top + 37 };
			SPRITEMANAGER->renderRectTexture(_medicineSellButton[1].tex, &_medicineSellButton[1].rc1, &_medicineSellButton[1].rc2, 0, 74, 96, 111, _medicineSellMenu.rc2.left + 165, _medicineSellMenu.rc2.top + 72);
		}
		else
		{
			_medicineSellButton[1].rc2 = { _medicineSellMenu.rc2.left + 165, _medicineSellMenu.rc2.top + 72 ,_medicineSellButton[1].rc2.left + 96,_medicineSellButton[1].rc2.top + 37 };
			SPRITEMANAGER->renderRectTexture(_medicineSellButton[1].tex, &_medicineSellButton[1].rc1, &_medicineSellButton[1].rc2, 0, 111, 96, 148, _medicineSellMenu.rc2.left + 165, _medicineSellMenu.rc2.top + 72);
		}

		if (_medicinePMSellButton[0].check == true)
		{
			_medicinePMSellButton[0].rc2 = { _medicineSellMenu.rc2.left + 55, _medicineSellMenu.rc2.top + 30 ,_medicinePMSellButton[0].rc2.left + 37,_medicinePMSellButton[0].rc2.top + 37 };
			SPRITEMANAGER->renderRectTexture(_medicinePMSellButton[0].tex, &_medicinePMSellButton[0].rc1, &_medicinePMSellButton[0].rc2, 37, 0, 74, 37, _medicineSellMenu.rc2.left + 55, _medicineSellMenu.rc2.top + 30);
		}
		else
		{
			_medicinePMSellButton[0].rc2 = { _medicineSellMenu.rc2.left + 55, _medicineSellMenu.rc2.top + 30 ,_medicinePMSellButton[0].rc2.left + 37,_medicinePMSellButton[0].rc2.top + 37 };
			SPRITEMANAGER->renderRectTexture(_medicinePMSellButton[0].tex, &_medicinePMSellButton[0].rc1, &_medicinePMSellButton[0].rc2, 37, 37, 74, 74, _medicineSellMenu.rc2.left + 55, _medicineSellMenu.rc2.top + 30);
		}
		if (_medicinePMSellButton[1].check == true)
		{
			_medicinePMSellButton[1].rc2 = { _medicineSellMenu.rc2.left + 180, _medicineSellMenu.rc2.top + 30 ,_medicinePMSellButton[1].rc2.left + 37,_medicinePMSellButton[1].rc2.top + 37 };
			SPRITEMANAGER->renderRectTexture(_medicinePMSellButton[1].tex, &_medicinePMSellButton[1].rc1, &_medicinePMSellButton[1].rc2, 0, 0, 37, 37, _medicineSellMenu.rc2.left + 180, _medicineSellMenu.rc2.top + 30);
		}
		else
		{
			_medicinePMSellButton[1].rc2 = { _medicineSellMenu.rc2.left + 180, _medicineSellMenu.rc2.top + 30 ,_medicinePMSellButton[1].rc2.left + 37,_medicinePMSellButton[1].rc2.top + 37 };
			SPRITEMANAGER->renderRectTexture(_medicinePMSellButton[1].tex, &_medicinePMSellButton[1].rc1, &_medicinePMSellButton[1].rc2, 0, 37, 37, 74, _medicineSellMenu.rc2.left + 180, _medicineSellMenu.rc2.top + 30);
		}

	}



}
