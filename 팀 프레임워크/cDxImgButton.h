#pragma once

class cDxImg;

class cDxImgButton
{
private:
	cDxImg* m_pDxImg;
	bool	m_isCenter;

public:
	cDxImgButton(cDxImg* dxImg, D3DXVECTOR2 vecPos, bool isCenter, bool isBoundingBox = false);
	~cDxImgButton();

	void render();
	bool click();
};

