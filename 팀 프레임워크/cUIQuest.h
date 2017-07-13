#pragma once
#include "cDxImgUI.h"

class cUIQuest : public cDxImgUI
{
	SYNTHESIZE(RECT, m_rtBtn, RtBtn);
	SYNTHESIZE(int, m_nBtnX, BtnX);
	SYNTHESIZE(int, m_nBtnY, BtnY);
	SYNTHESIZE(int, m_nBtnWidth, BtnWidth);
	SYNTHESIZE(int, m_nBtnHeight, BtnHeight);
	SYNTHESIZE(bool, m_isSure, IsSure);			//퀘스트를 승낙했는지
	SYNTHESIZE(bool, m_isBtnOver, IsBtnOver);	//버튼위에 마우스를 올렸는지
	

public:
	cUIQuest(string sUI, int nBtnX, int nBtnY, int nBtnWidth, int nBtnHeight);
	virtual ~cUIQuest();

	virtual void update();
	virtual void render();
};

