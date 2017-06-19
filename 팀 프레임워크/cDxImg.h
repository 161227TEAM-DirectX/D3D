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

