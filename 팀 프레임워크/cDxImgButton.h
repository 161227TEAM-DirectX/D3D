#pragma once

class cDxImg;

class cDxImgButton
{
	SYNTHESIZE(string, m_sBtnName, BtnName);	//��ư�� �̸��� ������.
	SYNTHESIZE(cDxImg*, m_pOff, Off);			//���� ��ư �̹���
	SYNTHESIZE(cDxImg*, m_pOver, Over);			//���� ��ư �̹���
	SYNTHESIZE(bool, m_isOver, IsOver);			//�����Ǿ�����
	SYNTHESIZE(RECT, m_rtBtn, RtBtn);

public:
	cDxImgButton(cDxImg* off, cDxImg* over, D3DXVECTOR2 vecPos, string sBtnName, bool isCenter = false, bool isBoundingBox = false);
	~cDxImgButton();

	void render();
	bool click();

	void setPos(D3DXVECTOR2 vecPos);
};

