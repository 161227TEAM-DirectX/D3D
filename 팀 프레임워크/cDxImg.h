#pragma once
class cDxImg
{
	SYNTHESIZE(bool, m_isDrawBoundingBox, DrawBoundingBox);		//바운딩박스 그리는지
	SYNTHESIZE(D3DCOLOR, m_dwBoundingColor, BoundingColor);		//바운딩박스 색깔

	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);				//좌표
	SYNTHESIZE(D3DXVECTOR3, m_vScale, Scale);					//크기
	SYNTHESIZE(ST_SIZEF, m_stSize, Size);						//가로세로
	SYNTHESIZE(LPDIRECT3DTEXTURE9, m_pTexture, Texture);		//텍스쳐
	SYNTHESIZE(D3DXIMAGE_INFO, m_stImageInfo, stImageInfo);		//텍스쳐 정보
	SYNTHESIZE(string, m_sFullPath, FullPath);					//텍스쳐 경로

	SYNTHESIZE(eImgLayer, m_eImgLayer, ImgLayer);				//레이어
	SYNTHESIZE(bool, m_isCenterDraw, CenterDraw);				//중점에서 그리는지

private:
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_matScale;
	D3DXMATRIXA16			m_matTrans;
	LPD3DXSPRITE			m_pSprite;

public:
	cDxImg();
	cDxImg(string sImgKey);
	~cDxImg();

	void render();
	void render(float cx, float cy, float angle = 0.0f);
	void renderCenter(float cx=0.0f, float cy=0.0f, float angle = 0.0f);
};

