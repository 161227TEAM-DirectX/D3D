#pragma once
class cDxImgUI
{
	SYNTHESIZE(cDxImg*, m_pUI, UI);
	SYNTHESIZE(bool, m_isMove, IsMove);
	SYNTHESIZE(float, m_fSaveX, SaveX);
	SYNTHESIZE(float, m_fSaveY, SaveY);
	SYNTHESIZE(eImgLayer, m_eUILayer, UILayer);

public:
	cDxImgUI(string sUI);
	~cDxImgUI();

	void update();
	void render();
};

