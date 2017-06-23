#pragma once

class cDxImgBar
{
private:
	cDxImg* m_pCover;
	cDxImg* m_pBack;
	cDxImg* m_Move;
	int m_timeCount;

	SYNTHESIZE(int, m_fGaugeSpeed, GaugeSpeed);
	SYNTHESIZE(int, m_fGaugeInterval, GaugeInterval);

public:
	cDxImgBar();
	cDxImgBar(string sCover, string sBack, string sMove, D3DXVECTOR2 vecPos, bool isCenter = false);
	~cDxImgBar();

	void update();
	void render();

	bool IsFullBar();
};

