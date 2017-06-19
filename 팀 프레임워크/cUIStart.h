#pragma once
#include "cUIObject.h"
#include "cUIButton.h"

class cUIObject;
class cUIImageView;
class cUIButton;

class cUIStart
	: public cUIObject
	, public iUIButtonDelegate
{
private:
	enum eMenuType
	{
		E_START,
		E_MAPTOOL,
		E_SETTING,
		E_EXIT
	};
	eMenuType m_eMenu;

public:
	cUIStart();
	cUIStart(string sStartScreen);
	virtual ~cUIStart();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void OnClick(cUIButton* pButton);

	void addButton(string sNorButton, string sButtonMov, string sButtonSel, float px,float py, int nTag);
};



