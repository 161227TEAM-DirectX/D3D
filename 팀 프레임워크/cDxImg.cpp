#include "stdafx.h"
#include "cDxImg.h"

cDxImg::cDxImg()
{
}

cDxImg::cDxImg(string sImgKey)
	: m_pTexture(NULL)
	, m_isDrawBoundingBox(false)
	, m_dwBoundingColor(BLACK)
	, m_vPosition(0.0f, 0.0f, 0.0f)
	, m_vScale(1.0f, 1.0f, 1.0f)
	, m_stSize(0.0f, 0.0f)
	, m_pSprite(NULL)
	, m_eImgLayer(eImgLayer::E_NONE)
	, m_isCenterDraw(false)
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
						D3DCOLOR_XRGB(255, 255, 255));

		m_pSprite->End();

		if (m_isDrawBoundingBox)
		{
			DWORD dwPrev = 0;
			_device->SetTexture(0, NULL);
			_device->GetRenderState(D3DRS_LIGHTING, &dwPrev);
			_device->SetRenderState(D3DRS_LIGHTING, false);

			int nCnt = 0;
			ST_RHWC_VERTEX aVertex[5];

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42 + m_stSize.fHeight, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + m_stSize.fWidth, m_matTrans._42 + m_stSize.fHeight, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + m_stSize.fWidth, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			_device->SetFVF(ST_RHWC_VERTEX::FVF);
			_device->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, aVertex, sizeof(ST_RHWC_VERTEX));

			_device->SetRenderState(D3DRS_LIGHTING, (bool)dwPrev);
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
						D3DCOLOR_XRGB(255, 255, 255));

		m_pSprite->End();

		if (m_isDrawBoundingBox)
		{
			DWORD dwPrev = 0;
			_device->SetTexture(0, NULL);
			_device->GetRenderState(D3DRS_LIGHTING, &dwPrev);
			_device->SetRenderState(D3DRS_LIGHTING, false);

			int nCnt = 0;
			ST_RHWC_VERTEX aVertex[5];

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42 + m_stSize.fHeight, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + m_stSize.fWidth, m_matTrans._42 + m_stSize.fHeight, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + m_stSize.fWidth, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			_device->SetFVF(ST_RHWC_VERTEX::FVF);
			_device->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, aVertex, sizeof(ST_RHWC_VERTEX));

			_device->SetRenderState(D3DRS_LIGHTING, (bool)dwPrev);
		}
	}
}

void cDxImg::render(float cx, float cy, float angle)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	D3DXVECTOR3 v = m_vPosition;

	if(!m_isCenterDraw)
	{
		RECT rc;
		SetRect(&rc, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);

		//출력 행렬 - 크기중앙(0) - 크기회전(0) - 크기(0) - 회전중점 - 회전각도 - 그림위치(좌상단)
		D3DXMatrixTransformation2D(&m_matWorld, NULL, 0, 0, &D3DXVECTOR2(0, 0), D3DXToRadian(angle), &D3DXVECTOR2(cx + v.x, cy + v.y));

		m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(m_pTexture,
						&rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_XRGB(255, 255, 255));

		m_pSprite->End();

		if (m_isDrawBoundingBox)
		{
			DWORD dwPrev = 0;
			_device->SetTexture(0, NULL);
			_device->GetRenderState(D3DRS_LIGHTING, &dwPrev);
			_device->SetRenderState(D3DRS_LIGHTING, false);

			int nCnt = 0;
			ST_RHWC_VERTEX aVertex[5];

			aVertex[nCnt].p = D3DXVECTOR4(m_matWorld._41, m_matWorld._42, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matWorld._41, m_matWorld._42 + m_stSize.fHeight, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matWorld._41 + m_stSize.fWidth, m_matWorld._42 + m_stSize.fHeight, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matWorld._41 + m_stSize.fWidth, m_matWorld._42, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(m_matWorld._41, m_matWorld._42, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			_device->SetFVF(ST_RHWC_VERTEX::FVF);
			_device->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, aVertex, sizeof(ST_RHWC_VERTEX));

			_device->SetRenderState(D3DRS_LIGHTING, (bool)dwPrev);
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

		//출력 행렬 - 크기중앙(0) - 크기회전(0) - 크기(0) - 회전중점 - 회전각도 - 그림위치(좌상단)
		D3DXMatrixTransformation2D(&m_matWorld, NULL, 0, 0, &D3DXVECTOR2(m_stImageInfo.Width / 2, m_stImageInfo.Height / 2), D3DXToRadian(angle), &D3DXVECTOR2(_cx, _cy));

		m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(m_pTexture,
						&rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_XRGB(255, 255, 255));

		m_pSprite->End();

		if (m_isDrawBoundingBox)
		{
			DWORD dwPrev = 0;
			_device->SetTexture(0, NULL);
			_device->GetRenderState(D3DRS_LIGHTING, &dwPrev);
			_device->SetRenderState(D3DRS_LIGHTING, false);

			int nCnt = 0;
			ST_RHWC_VERTEX aVertex[5];

			aVertex[nCnt].p = D3DXVECTOR4(_cx, _cy, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(_cx, _cyE, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(_cxE, _cyE, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(_cxE, _cy, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			aVertex[nCnt].p = D3DXVECTOR4(_cx, _cy, 0, 1);
			aVertex[nCnt++].c = m_dwBoundingColor;

			_device->SetFVF(ST_RHWC_VERTEX::FVF);
			_device->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, aVertex, sizeof(ST_RHWC_VERTEX));

			_device->SetRenderState(D3DRS_LIGHTING, (bool)dwPrev);
		}
	}	
}

void cDxImg::renderCenter(float cx, float cy, float angle)
{
	D3DXVECTOR3 v = m_vPosition;

	
}
