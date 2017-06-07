#pragma once

class cUIObject;

class cUIDelegate
{
public:
	virtual void OnUIFinished(cUIObject* pUI) = 0;
};

class cUIObject : public cObject
{
protected:
	vector<cUIObject*> m_vecChild;
	cUIObject*		   m_pParent;

public:
	enum eUIType
	{
		E_NONE
	};

protected:
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_matScale;
	D3DXMATRIXA16			m_matTrans;
	LPD3DXSPRITE			m_pSprite;
	SYNTHESIZE(int, m_nTag, Tag);
	SYNTHESIZE(bool, m_isDrawBoundingBox, DrawBoundingBox);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vScale, Scale);
	SYNTHESIZE(ST_SIZEF, m_stSize, Size);
	SYNTHESIZE(eUIType, m_eUItype, UItype);
	SYNTHESIZE(cUIDelegate*, m_pUIDelegate, UIDelegate);

public:
	cUIObject();
	virtual ~cUIObject();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void AddChild(cUIObject* pChild);
	virtual void Destroy();
	virtual cUIObject* GetChildByTag(int nTag);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

