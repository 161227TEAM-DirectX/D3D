#include "stdafx.h"
#include "cDxImg.h"

cDxImg::cDxImg()
{
}

cDxImg::cDxImg(string sImgKey, D3DXVECTOR2 vecPos, bool _isCenter)
	: m_pTexture(NULL)						//�ؽ���
	, m_isDrawBoundingBox(false)			//�ٿ���ڽ� �׸�����
	, m_dwBoundingColor(BLACK)				//�ٿ���ڽ� ����
	, m_vPosition(vecPos.x, vecPos.y, 0.0f)	//��ǥ
	, m_vScale(1.0f, 1.0f, 1.0f)			//ũ��
	, m_stSize(0.0f, 0.0f)					//���μ���
	, m_pSprite(NULL)						//��������Ʈ
	, m_nImgAlpha(255)						//���İ�
	, m_eImgLayer(eImgLayer::E_NONE)		//���̾�
	, m_isCenterDraw(_isCenter)				//�������� �׸�����
	, m_fCurX(0)							//�ٿ��� ���� x��ġ
	, m_currentFrameX(0)					//���� ������ x
	, m_currentFrameY(0)					//���� ������ y
	, m_maxFrameX(1)						//�ִ� ������ x����
	, m_maxFrameY(1)						//�ִ� ������ y����
	, m_frameWidth(0)						//1������ ����ũ��
	, m_frameHeight(0)						//1������ ����ũ��
	, m_stImgAni(5)							//������ ��Ʈ�� ����ü
	, m_fMiniStartX(0.0f)					//�̴ϸ� ���� ��ǥx
	, m_fMiniStartY(0.0f)					//�̴ϸ� ���� ��ǥy
	, m_fMiniWidth(0.0f)					//�̴ϸ� ����
	, m_fMiniHeight(0.0f)					//�̴ϸ� ����
{
	ZeroMemory(&m_stImageInfo, sizeof(D3DXIMAGE_INFO));

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matTrans);

	D3DXCreateSprite(_device, &m_pSprite);

	m_sFullPath = sImgKey;
	m_pTexture = TEXTURE_MANAGER->GetTexture(m_sFullPath, &m_stImageInfo);
	m_stSize.fWidth = m_stImageInfo.Width;
	m_stSize.fHeight = m_stImageInfo.Height;
}

cDxImg::cDxImg(string sImgKey, int maxFrameX, int maxFrameY, int frameTime, bool _isCenter)
	: m_pTexture(NULL)					//�ؽ���
	, m_isDrawBoundingBox(false)		//�ٿ���ڽ� �׸�����
	, m_dwBoundingColor(BLACK)			//�ٿ���ڽ� ����
	, m_vPosition(0.0f, 0.0f, 0.0f)		//��ǥ
	, m_vScale(1.0f, 1.0f, 1.0f)		//ũ��
	, m_stSize(0.0f, 0.0f)				//���μ���
	, m_pSprite(NULL)					//��������Ʈ
	, m_nImgAlpha(255)					//���İ�
	, m_eImgLayer(eImgLayer::E_NONE)	//���̾�
	, m_isCenterDraw(_isCenter)			//�������� �׸�����
	, m_fCurX(0)						//�ٿ��� ���� x��ġ
	, m_currentFrameX(0)				//���� ������ x
	, m_currentFrameY(0)				//���� ������ y
	, m_maxFrameX(1)					//�ִ� ������ x����
	, m_maxFrameY(1)					//�ִ� ������ y����
	, m_frameWidth(0)					//1������ ����ũ��
	, m_frameHeight(0)					//1������ ����ũ��
	, m_stImgAni(5)						//������ ��Ʈ�� ����ü
	, m_fMiniStartX(0.0f)				//�̴ϸ� ���� ��ǥx
	, m_fMiniStartY(0.0f)				//�̴ϸ� ���� ��ǥy
	, m_fMiniWidth(0.0f)				//�̴ϸ� ����
	, m_fMiniHeight(0.0f)				//�̴ϸ� ����
{
	ZeroMemory(&m_stImageInfo, sizeof(D3DXIMAGE_INFO));

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matTrans);

	D3DXCreateSprite(_device, &m_pSprite);

	m_sFullPath = sImgKey;
	m_pTexture = TEXTURE_MANAGER->GetTexture(m_sFullPath, &m_stImageInfo);
	m_stSize.fWidth = m_stImageInfo.Width;
	m_stSize.fHeight = m_stImageInfo.Height;

	m_maxFrameX = maxFrameX;
	m_maxFrameY = maxFrameY;
	m_frameWidth = m_stImageInfo.Width / m_maxFrameX;
	m_frameHeight = m_stImageInfo.Height / m_maxFrameY;

	m_stImgAni.nAniTime = frameTime;
}


cDxImg::~cDxImg()
{
	SAFE_RELEASE(m_pSprite);
}


void cDxImg::render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc;
	SetRect(&rc, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);

	D3DXVECTOR3 v = m_vPosition;

	if (!m_isCenterDraw)
	{
		D3DXMatrixTranslation(&m_matTrans, v.x, v.y, v.z);
		m_matWorld = m_matScale * m_matTrans;

		m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(m_pTexture,
						&rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(m_nImgAlpha, 255, 255, 255));

		m_pSprite->End();

		if (m_isDrawBoundingBox)
		{
			RectMake(m_vPosition.x, m_vPosition.y, m_stSize.fWidth, m_stSize.fHeight, false, m_dwBoundingColor);
		}
	}
	else
	{
		v.x-=m_stImageInfo.Width / 2;
		v.y-=m_stImageInfo.Height / 2;

		D3DXMatrixTranslation(&m_matTrans, v.x, v.y, v.z);
		m_matWorld = m_matScale * m_matTrans;

		m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(m_pTexture,
						&rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(m_nImgAlpha, 255, 255, 255));

		m_pSprite->End();

		if (m_isDrawBoundingBox)
		{
			RectMakeCenter(m_vPosition.x, m_vPosition.y, m_stSize.fWidth, m_stSize.fHeight, false, m_dwBoundingColor);
		}
	}
}

void cDxImg::render(float srcX, float srcY, float srcWidth, float srcHeight, float moveX, float moveY)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	m_fMiniStartX = srcX - moveX;
	//if (m_fMiniStartX <= 0.0f)
	//	m_fMiniStartX = 0.0f;
	//if (m_fMiniStartX >= this->m_stSize.fWidth - srcWidth)
	//	m_fMiniStartX = this->m_stSize.fWidth - srcWidth;


	m_fMiniStartY = srcY - moveY;
	//if (m_fMiniStartY <= 0.0f)
	//	m_fMiniStartY = 0.0f;
	//if (m_fMiniStartY >= this->m_stSize.fHeight - srcHeight)
	//	m_fMiniStartY = this->m_stSize.fHeight - srcHeight;


	m_fMiniWidth = m_fMiniStartX + srcWidth;
	m_fMiniHeight = m_fMiniStartY + srcHeight;

	RECT rc;
	D3DXVECTOR3 v = m_vPosition;

	if (!m_isCenterDraw)
	{
		SetRect(&rc, m_fMiniStartX, m_fMiniStartY, m_fMiniWidth, m_fMiniHeight);
		//v.x -= srcWidth;
		//v.y -= srcHeight;
	}
	else
	{
		SetRect(&rc, m_fMiniStartX, m_fMiniStartY, m_fMiniWidth, m_fMiniHeight);
		v.x += srcX;
		v.y += srcY;
	}



	if (!m_isCenterDraw)
	{
		D3DXMatrixTranslation(&m_matTrans, v.x, v.y, v.z);
		m_matWorld = m_matScale * m_matTrans;

		m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(m_pTexture,
						&rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(m_nImgAlpha, 255, 255, 255));

		m_pSprite->End();

		if (m_isDrawBoundingBox)
		{
			RectMake(m_vPosition.x, m_vPosition.y, m_stSize.fWidth, m_stSize.fHeight, false, m_dwBoundingColor);
		}
	}
	else
	{
		v.x-=m_stImageInfo.Width / 2;
		v.y-=m_stImageInfo.Height / 2;

		D3DXMatrixTranslation(&m_matTrans, v.x, v.y, v.z);
		m_matWorld = m_matScale * m_matTrans;

		m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(m_pTexture,
						&rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(m_nImgAlpha, 255, 255, 255));

		m_pSprite->End();

		if (m_isDrawBoundingBox)
		{
			RectMakeCenter(m_vPosition.x, m_vPosition.y, m_stSize.fWidth, m_stSize.fHeight, false, m_dwBoundingColor);
		}
	}
}

void cDxImg::render(float cx, float cy, float angle)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	D3DXVECTOR3 v = m_vPosition;

	if (!m_isCenterDraw)
	{
		RECT rc;
		SetRect(&rc, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);

		//��� ��� - ũ���߾�(0) - ũ��ȸ��(0) - ũ��(0) - ȸ������ - ȸ������ - �׸���ġ(�»��)
		D3DXMatrixTransformation2D(&m_matWorld, NULL, 0, 0, &D3DXVECTOR2(0, 0), D3DXToRadian(angle), &D3DXVECTOR2(cx + v.x, cy + v.y));

		m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(m_pTexture,
						&rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(m_nImgAlpha, 255, 255, 255));

		m_pSprite->End();

		if (m_isDrawBoundingBox)
		{
			RectMake(m_vPosition.x, m_vPosition.y, m_stSize.fWidth, m_stSize.fHeight, false, m_dwBoundingColor);
		}
	}
	else
	{
		int _cx = v.x + cx - m_stImageInfo.Width / 2;
		int _cy = v.y + cy - m_stImageInfo.Height / 2;
		int _cxE = v.x + cx + m_stImageInfo.Width / 2;
		int _cyE = v.y + cy + m_stImageInfo.Height / 2;

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

		RECT rc;
		SetRect(&rc, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);

		//��� ��� - ũ���߾�(0) - ũ��ȸ��(0) - ũ��(0) - ȸ������ - ȸ������ - �׸���ġ(�»��)
		D3DXMatrixTransformation2D(&m_matWorld, NULL, 0, 0, &D3DXVECTOR2(m_stImageInfo.Width / 2, m_stImageInfo.Height / 2), D3DXToRadian(angle), &D3DXVECTOR2(_cx, _cy));

		m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(m_pTexture,
						&rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(m_nImgAlpha, 255, 255, 255));

		m_pSprite->End();

		if (m_isDrawBoundingBox)
		{
			RectMakeCenter(m_vPosition.x, m_vPosition.y, m_stSize.fWidth, m_stSize.fHeight, false, m_dwBoundingColor);
		}
	}
}

void cDxImg::renderFrame()
{
	//
	// �������� ������.
	//
	m_stImgAni.nAniCount++;
	if (m_stImgAni.nAniCount > m_stImgAni.nAniTime)
	{
		if (m_currentFrameX >= m_maxFrameX - 1)
		{
			m_stImgAni.nAniIndex = 0;
		}
		m_stImgAni.nAniIndex++;
		m_stImgAni.nAniCount = 0;
		m_currentFrameX = m_stImgAni.nAniIndex;
	}



	//
	// �׸���.
	//
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc;
	SetRect(&rc,
			m_currentFrameX * m_frameWidth,					//������ 1�� ���� ����
			0,
			(m_currentFrameX + 1) * m_frameWidth,
			m_stImageInfo.Height / m_maxFrameY);

	D3DXVECTOR3 v = m_vPosition;

	if (!m_isCenterDraw)
	{
		D3DXMatrixTranslation(&m_matTrans, v.x, v.y, v.z);
		m_matWorld = m_matScale * m_matTrans;

		m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(m_pTexture,
						&rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(m_nImgAlpha, 255, 255, 255));

		m_pSprite->End();
	}
	else
	{
		v.x-=m_frameWidth / 2;
		v.y-=m_frameHeight / 2;

		D3DXMatrixTranslation(&m_matTrans, v.x, v.y, v.z);
		m_matWorld = m_matScale * m_matTrans;

		m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(m_pTexture,
						&rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(m_nImgAlpha, 255, 255, 255));

		m_pSprite->End();
	}
}

void cDxImg::renderBarX()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc;
	SetRect(&rc, 0, 0, m_fCurX, m_stImageInfo.Height);

	D3DXVECTOR3 v = m_vPosition;

	if (!m_isCenterDraw)
	{
		D3DXMatrixTranslation(&m_matTrans, v.x, v.y, v.z);
		m_matWorld = m_matScale * m_matTrans;

		m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(m_pTexture,
						&rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(m_nImgAlpha, 255, 255, 255));

		m_pSprite->End();

		if (m_isDrawBoundingBox)
		{
			RectMake(m_vPosition.x, m_vPosition.y, m_stSize.fWidth, m_stSize.fHeight, false, m_dwBoundingColor);
		}
	}
	else
	{
		v.x-=m_stImageInfo.Width / 2;
		v.y-=m_stImageInfo.Height / 2;

		D3DXMatrixTranslation(&m_matTrans, v.x, v.y, v.z);
		m_matWorld = m_matScale * m_matTrans;

		m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(m_pTexture,
						&rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(m_nImgAlpha, 255, 255, 255));

		m_pSprite->End();

		if (m_isDrawBoundingBox)
		{
			RectMakeCenter(m_vPosition.x, m_vPosition.y, m_stSize.fWidth, m_stSize.fHeight, false, m_dwBoundingColor);
		}
	}
}

RECT cDxImg::getRect()
{
	RECT temp;

	if (!m_isCenterDraw)
	{
		temp.left = m_vPosition.x;
		temp.top = m_vPosition.y;
		temp.right = m_vPosition.x + m_stSize.fWidth;
		temp.bottom = m_vPosition.y + m_stSize.fHeight;
	}
	else
	{
		temp.left = m_vPosition.x - m_stSize.fWidth / 2;
		temp.top = m_vPosition.y - m_stSize.fHeight / 2;
		temp.right = m_vPosition.x + m_stSize.fWidth / 2;
		temp.bottom = m_vPosition.y + m_stSize.fHeight / 2;
	}

	return temp;
}
