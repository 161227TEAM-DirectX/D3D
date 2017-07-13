#pragma once
#include "cDxImgUI.h"

class cUIQuest : public cDxImgUI
{
	SYNTHESIZE(RECT, m_rtBtn, RtBtn);
	SYNTHESIZE(int, m_nBtnX, BtnX);
	SYNTHESIZE(int, m_nBtnY, BtnY);
	SYNTHESIZE(int, m_nBtnWidth, BtnWidth);
	SYNTHESIZE(int, m_nBtnHeight, BtnHeight);
	SYNTHESIZE(bool, m_isSure, IsSure);			//����Ʈ�� �³��ߴ���
	SYNTHESIZE(bool, m_isBtnOver, IsBtnOver);	//��ư���� ���콺�� �÷ȴ���
	

public:
	cUIQuest(string sUI, int nBtnX, int nBtnY, int nBtnWidth, int nBtnHeight);
	virtual ~cUIQuest();

	virtual void update();
	virtual void render();
};

