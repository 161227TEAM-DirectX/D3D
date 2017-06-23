#pragma once

class cDxImg;

class cDxImgButton
{
	SYNTHESIZE(string, m_sBtnName, BtnName);

private:
	cDxImg* m_pOff;
	cDxImg* m_pOver;
	bool	m_isOver;

public:
	cDxImgButton(cDxImg* off, cDxImg* over, D3DXVECTOR2 vecPos, string sBtnName, bool isCenter = false, bool isBoundingBox = false);
	~cDxImgButton();

	void render();
	bool click();
};

