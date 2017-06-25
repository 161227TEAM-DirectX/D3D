#pragma once

class cDxImg;

class cDxImgButton
{
	SYNTHESIZE(string, m_sBtnName, BtnName);	//버튼의 이름을 가진다.
	SYNTHESIZE(cDxImg*, m_pOff, Off);			//오프 버튼 이미지
	SYNTHESIZE(cDxImg*, m_pOver, Over);			//오버 버튼 이미지
	SYNTHESIZE(bool, m_isOver, IsOver);			//오버되었는지

public:
	cDxImgButton(cDxImg* off, cDxImg* over, D3DXVECTOR2 vecPos, string sBtnName, bool isCenter = false, bool isBoundingBox = false);
	~cDxImgButton();

	void render();
	bool click();
};

