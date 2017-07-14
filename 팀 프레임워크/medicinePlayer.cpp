#include "stdafx.h"
#include "medicinePlayer.h"
#include "inven.h"

HRESULT medicinePlayer::init(void)
{
	_HPdublePick = 0;
	_MPdublePick = 0;
	HB = false;
	MB = false;

	return S_OK;
}

void medicinePlayer::release(void)
{

}

void medicinePlayer::update(void)
{
	if (_vHPMedicinePlayerInforMation.size() != 0)
	{
		if (KEYMANAGER->isOnceKeyDown('O'))
		{
			if (_vHPMedicinePlayerInforMation[0].medicineCount <= 1)
			{
				this->removeInvenItem(0);
				this->removeInvenItemInformation(0);
			}
			else
			{
				int SUM = 0;

				if (_vHPMedicinePlayerInforMation[0].hpAbility + PLAYERMANAGER->GetHp() > PLAYERMANAGER->GetMaxHp())
				{
					SUM = PLAYERMANAGER->GetMaxHp();
				}
				else
				{
					SUM = _vHPMedicinePlayerInforMation[0].hpAbility + PLAYERMANAGER->GetHp();
				}

				PLAYERMANAGER->SetHp(SUM);
				
				_vHPMedicinePlayerInforMation[0].medicineCount--;
			}
		}
	}

	if (_vMPMedicinePlayerInforMation.size() != 0)
	{
		if (KEYMANAGER->isOnceKeyDown('P'))
		{
			if (_vMPMedicinePlayerInforMation[0].medicineCount <= 1)
			{
				this->removeInvenItem2(0);
				this->removeInvenItem2Information(0);
			}
			else
			{
				//여기다가 연동된 MP값 넣기
			    //MP는 스킬을 쓸댸 연동이 필요없어서 안했음.
				//HP만 있으면 된다고 판단
				_vMPMedicinePlayerInforMation[0].medicineCount--;
			}
		}
	}

	if (_vHPMedicinePlayerRender.size() != 0)
	{
		if (PtInRect(&_vHPMedicinePlayerRender[0].rc2, GetMousePos()))
		{
			RHtemp = _vHPMedicinePlayerRender[0];
			IHtemp = _vHPMedicinePlayerInforMation[0];

			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				_HPdublePick++;

				if (_HPdublePick >= 2)
				{
					this->removeInvenItem(0);
					this->removeInvenItemInformation(0);

					_HPdublePick = 0;

					HB = true;
				}
			}
		}
		else
		{
			_HPdublePick = 0;
		}
	}

	if (_vMPMedicinePlayerRender.size() != 0)
	{
		if (PtInRect(&_vMPMedicinePlayerRender[0].rc2, GetMousePos()))
		{
			RMtemp = _vMPMedicinePlayerRender[0];
			IMtemp = _vMPMedicinePlayerInforMation[0];

			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				_MPdublePick++;

				if (_MPdublePick >= 2)
				{
					this->removeInvenItem2(0);
					this->removeInvenItem2Information(0);

					_MPdublePick = 0;

					MB = true;
				}
			}
		}
		else
		{
			_MPdublePick = 0;
		}
	}

	if (HB == true)
	{
		RHtemp.rc2 = { 0,0,0,0 };
		_inven->setVinvenItemRender(RHtemp);
		_inven->setVinvenItem(IHtemp);
		HB = false;
	}

	if (MB == true)
	{
		RMtemp.rc2 = { 0,0,0,0 };
		_inven->setVinvenItemRender(RMtemp);
		_inven->setVinvenItem(IMtemp);
		MB = false;
	}

}

void medicinePlayer::render(void)
{
	if (_vHPMedicinePlayerRender.size() != 0)
	{
		for (int i = 0; i < _vHPMedicinePlayerRender.size(); i++)
		{
			_vHPMedicinePlayerRender[i].rc2 = { DXIMG_MANAGER->GetDxImg("quickSlotUI_back")->getRect().left + 528, DXIMG_MANAGER->GetDxImg("quickSlotUI_back")->getRect().top + 81, _vHPMedicinePlayerRender[i].rc2.left + 53,_vHPMedicinePlayerRender[i].rc2.top + 53 };
			SPRITEMANAGER->renderRectTexture(_vHPMedicinePlayerRender[i].tex, &_vHPMedicinePlayerRender[i].rc1, &_vHPMedicinePlayerRender[i].rc2, 0, 0, 64, 64, DXIMG_MANAGER->GetDxImg("quickSlotUI_back")->getRect().left + 528, DXIMG_MANAGER->GetDxImg("quickSlotUI_back")->getRect().top + 81);

			if (_vHPMedicinePlayerInforMation[i].medicineCount < 10)
			{
				FONTMANAGER->fontOut(to_string(_vHPMedicinePlayerInforMation[i].medicineCount), _vHPMedicinePlayerRender[i].rc2.left + 36, _vHPMedicinePlayerRender[i].rc2.top + 30, D3DCOLOR_XRGB(255, 255, 255));
			}
			else
			{
				FONTMANAGER->fontOut(to_string(_vHPMedicinePlayerInforMation[i].medicineCount), _vHPMedicinePlayerRender[i].rc2.left + 29, _vHPMedicinePlayerRender[i].rc2.top + 30, D3DCOLOR_XRGB(255, 255, 255));
			}
		}
	}

	if (_vMPMedicinePlayerRender.size() != 0)
	{
		for (int i = 0; i < _vMPMedicinePlayerRender.size(); i++)
		{
			_vMPMedicinePlayerRender[i].rc2 = { DXIMG_MANAGER->GetDxImg("quickSlotUI_back")->getRect().left + 578, DXIMG_MANAGER->GetDxImg("quickSlotUI_back")->getRect().top + 81, _vMPMedicinePlayerRender[i].rc2.left + 53,_vMPMedicinePlayerRender[i].rc2.top + 53 };
			SPRITEMANAGER->renderRectTexture(_vMPMedicinePlayerRender[i].tex, &_vMPMedicinePlayerRender[i].rc1, &_vMPMedicinePlayerRender[i].rc2, 0, 0, 64, 64, DXIMG_MANAGER->GetDxImg("quickSlotUI_back")->getRect().left + 578, DXIMG_MANAGER->GetDxImg("quickSlotUI_back")->getRect().top + 81);

			if (_vMPMedicinePlayerInforMation[i].medicineCount < 10)
			{
				FONTMANAGER->fontOut(to_string(_vMPMedicinePlayerInforMation[i].medicineCount), _vMPMedicinePlayerRender[i].rc2.left + 36, _vMPMedicinePlayerRender[i].rc2.top + 30, D3DCOLOR_XRGB(255, 255, 255));
			}
			else
			{
				FONTMANAGER->fontOut(to_string(_vMPMedicinePlayerInforMation[i].medicineCount), _vMPMedicinePlayerRender[i].rc2.left + 29, _vMPMedicinePlayerRender[i].rc2.top + 30, D3DCOLOR_XRGB(255, 255, 255));
			}
		}
	}

}

void medicinePlayer::removeInvenItem(int num)
{
	_vHPMedicinePlayerRender.erase(_vHPMedicinePlayerRender.begin() + num);
}

void medicinePlayer::removeInvenItemInformation(int num)
{
	_vHPMedicinePlayerInforMation.erase(_vHPMedicinePlayerInforMation.begin() + num);
}

void medicinePlayer::removeInvenItem2(int num)
{
	_vMPMedicinePlayerRender.erase(_vMPMedicinePlayerRender.begin() + num);
}

void medicinePlayer::removeInvenItem2Information(int num)
{
	_vMPMedicinePlayerInforMation.erase(_vMPMedicinePlayerInforMation.begin() + num);
}