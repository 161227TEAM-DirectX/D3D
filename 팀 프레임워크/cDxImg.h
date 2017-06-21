#pragma once
class cDxImg
{
	SYNTHESIZE(bool, m_isDrawBoundingBox, DrawBoundingBox);		//�ٿ���ڽ� �׸�����
	SYNTHESIZE(D3DCOLOR, m_dwBoundingColor, BoundingColor);		//�ٿ���ڽ� ����

	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);				//��ǥ
	SYNTHESIZE(D3DXVECTOR3, m_vScale, Scale);					//ũ��
	SYNTHESIZE(ST_SIZEF, m_stSize, Size);						//���μ���
	SYNTHESIZE(LPDIRECT3DTEXTURE9, m_pTexture, Texture);		//�ؽ���
	SYNTHESIZE(D3DXIMAGE_INFO, m_stImageInfo, stImageInfo);		//�ؽ��� ����
	SYNTHESIZE(string, m_sFullPath, FullPath);					//�ؽ��� ���

	SYNTHESIZE(eImgLayer, m_eImgLayer, ImgLayer);				//���̾�
	SYNTHESIZE(bool, m_isCenterDraw, CenterDraw);				//�������� �׸�����

	//������
	SYNTHESIZE(int, m_currentFrameX, CurrentFrameX);			//���� ������ x
	SYNTHESIZE(int, m_currentFrameY, CurrentFrameY);			//���� ������ y
	SYNTHESIZE(int, m_maxFrameX, MaxFrameX);					//�ִ� ������ x����
	SYNTHESIZE(int, m_maxFrameY, MaxFrameY);					//�ִ� ������ y����
	SYNTHESIZE(int, m_frameWidth, FrameWidth);					//1������ ����ũ��
	SYNTHESIZE(int, m_frameHeight, FrameHeight);				//1������ ����ũ��
	SYNTHESIZE(ST_DXIMGANI, m_stImgAni, ImgAni);				//������ ��Ʈ�� ����ü


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

