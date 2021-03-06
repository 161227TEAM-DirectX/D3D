#pragma once

class cUIButton;

class iUIButtonDelegate
{
public:
	virtual void OnClick(cUIButton* pSender) = 0;
};

class cUIButton : public cUIObject
{
protected:
	enum eButtonState
	{
		E_NORMAL,
		E_MOVER,
		E_SELECTED,
		E_COUNT,
	};
	eButtonState		m_eButtonState;
	LPDIRECT3DTEXTURE9	m_aTexture[E_COUNT];
	SYNTHESIZE(iUIButtonDelegate*, m_pDelegate, Delegate);

public:
	cUIButton();
	virtual ~cUIButton();

	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
	virtual void SetButtonImage(string sNor, string sOvr, string sSel);
public:
	void OnClick(cUIButton* pUIButton);
};

