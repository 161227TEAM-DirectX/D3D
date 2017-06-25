#pragma once

class cDxImgBar
{
	enum eBarType
	{
		E_BTN0,		//초기화
		E_BTN2,		//이미지 2개를 사용하는 바
		E_BTN3		//이미지 3개를 사용하는 바
	};

	SYNTHESIZE(eBarType, m_eBarType, BarType);
	SYNTHESIZE(cDxImg*, m_pCover, Cover);
	SYNTHESIZE(cDxImg*, m_pBack, Back);
	SYNTHESIZE(cDxImg*, m_pMove, Move);
	SYNTHESIZE(int, m_nTimeCount, TimeCount);

	SYNTHESIZE(int, m_fGaugeSpeed, GaugeSpeed);
	SYNTHESIZE(int, m_fGaugeInterval, GaugeInterval);

public:
	cDxImgBar(string sBack, string sMove, D3DXVECTOR2 vecPos, bool isCenter = false);
	cDxImgBar(string sCover, string sBack, string sMove, D3DXVECTOR2 vecPos, bool isCenter = false);
	~cDxImgBar();

	void setMoveGauge(int nGauge);

	void updateLoading();
	void moveBar(int nCurX);
	void movePos(int cx, int cy);

	void render();

	bool IsFullBar();
};

