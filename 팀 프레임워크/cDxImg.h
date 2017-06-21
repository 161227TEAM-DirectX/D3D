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

	//프레임
	SYNTHESIZE(int, m_currentFrameX, CurrentFrameX);			//현재 프레임 x
	SYNTHESIZE(int, m_currentFrameY, CurrentFrameY);			//현재 프레임 y
	SYNTHESIZE(int, m_maxFrameX, MaxFrameX);					//최대 프레임 x개수
	SYNTHESIZE(int, m_maxFrameY, MaxFrameY);					//최대 프레임 y개수
	SYNTHESIZE(int, m_frameWidth, FrameWidth);					//1프레임 가로크기
	SYNTHESIZE(int, m_frameHeight, FrameHeight);				//1프레임 세로크기
	SYNTHESIZE(ST_DXIMGANI, m_stImgAni, ImgAni);				//프레임 컨트롤 구조체


private:
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_matScale;
	D3DXMATRIXA16			m_matTrans;
	LPD3DXSPRITE			m_pSprite;

public:
	cDxImg();
	cDxImg(string sImgKey, bool _isCenter=false);
	cDxImg(string sImgKey, int maxFrameX, int maxFrameY, int frameTime = 5, bool _isCenter=true);
	~cDxImg();

	void render();
	void render(float cx, float cy, float angle = 0.0f);
	void renderFrame();

	RECT getRect();
};

