#pragma once
#include "cDxImgUI.h"

class cUIShopSlot : public cDxImgUI
{
	enum eUIBtnState
	{
		E_UIBTN_NONE,
		E_UIBTN_GO,
		E_UIBTN_SHOP,
		E_UIBTN_BACK
	};

	SYNTHESIZE(bool, m_isBtnSetting, IsBtnSetting);
	SYNTHESIZE(RECT, m_rtBtn, RtBtn);
	SYNTHESIZE(int, m_nBtnX, BtnX);
	SYNTHESIZE(int, m_nBtnY, BtnY);
	SYNTHESIZE(int, m_nBtnWidth, BtnWidth);
	SYNTHESIZE(int, m_nBtnHeight, BtnHeight);

	SYNTHESIZE(eUIBtnState,m_eUIBtnState,UIBtnState);

	SYNTHESIZE(bool, m_isBtnCheck, IsBtnCheck);
	SYNTHESIZE(bool, m_isBtnCheckBack, IsBtnCheckBack);
	SYNTHESIZE(int, m_nBtnSpeed, BtnSpeed);
	SYNTHESIZE(int, m_nCountMax, CountMax);

	SYNTHESIZE(int, m_nCount,Count);
	
public:
	cUIShopSlot(string sUI, int nBtnX, int nBtnY, int nBtnWidth, int nBtnHeight);
	~cUIShopSlot();

	virtual void update();
	virtual void render();
};

