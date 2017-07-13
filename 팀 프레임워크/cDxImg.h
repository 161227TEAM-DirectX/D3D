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
	SYNTHESIZE(int, m_nImgAlpha, ImgAlpha);						//알파값

	SYNTHESIZE(eImgLayer, m_eImgLayer, ImgLayer);				//레이어
	SYNTHESIZE(bool, m_isCenterDraw, CenterDraw);				//중점에서 그리는지
	SYNTHESIZE(float, m_fCurX, CurX);							//바에서 현재 x위치


																//프레임
	SYNTHESIZE(int, m_currentFrameX, CurrentFrameX);			//현재 프레임 x
	SYNTHESIZE(int, m_currentFrameY, CurrentFrameY);			//현재 프레임 y
	SYNTHESIZE(int, m_maxFrameX, MaxFrameX);					//최대 프레임 x개수
	SYNTHESIZE(int, m_maxFrameY, MaxFrameY);					//최대 프레임 y개수
	SYNTHESIZE(int, m_frameWidth, FrameWidth);					//1프레임 가로크기
	SYNTHESIZE(int, m_frameHeight, FrameHeight);				//1프레임 세로크기
	SYNTHESIZE(ST_DXIMGANI, m_stImgAni, ImgAni);				//프레임 컨트롤 구조체


																//미니맵
	SYNTHESIZE(float, m_fMiniStartX, MiniStartX);				//미니맵 시작좌표x
	SYNTHESIZE(float, m_fMiniStartY, MiniStartY);				//미니맵 시작좌표y
	SYNTHESIZE(float, m_fMiniWidth, MiniWidth);					//미니맵 그릴 가로길이
	SYNTHESIZE(float, m_fMiniHeight, MiniHeight);				//미니맵 그릴 세로길이

private:
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_matScale;
	D3DXMATRIXA16			m_matTrans;
	LPD3DXSPRITE			m_pSprite;

public:
	cDxImg();
	cDxImg(string sImgKey, D3DXVECTOR2 vecPos={ 0,0 }, bool _isCenter=false);
	cDxImg(string sImgKey, int maxFrameX, int maxFrameY, int frameTime = 5, bool _isCenter=true);
	~cDxImg();

	void render();
	void render(float srcX, float srcY, float srcWidth, float srcHeight, float moveX = 0.0f, float moveY = 0.0f);
	void render(float cx, float cy, float angle = 0.0f);
	void renderFrame();
	void renderBarX();

	RECT getRect();

	inline void setPos(float x, float y) { this->SetPosition(D3DXVECTOR3(x, y, 0)); }
	inline int getPosX()const { return this->GetPosition().x; }
	inline int getPosY()const { return this->GetPosition().y; }
	inline D3DXVECTOR2 getPos()const { return D3DXVECTOR2(getPosX(), getPosY()); }
};

