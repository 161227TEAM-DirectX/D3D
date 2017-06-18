#include "stdafx.h"
#include "cUIObject.h"

cUIObject::cUIObject()
	: m_vPosition(0, 0, 0)
	, m_stSize(0, 0)
	, m_pParent(NULL)
	, m_isDrawBoundingBox(false)
	, m_nTag(0)
	, m_pSprite(NULL)
	, m_pUIDelegate(NULL)
{
	D3DXCreateSprite(_device, &m_pSprite);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matTrans);
	D3DXMatrixIdentity(&m_matWorld);
	m_vPosition = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_vScale = D3DXVECTOR3(0.f, 0.f, 0.f);
}


cUIObject::~cUIObject()
{
	for each(auto p in m_vecChild)
	{
		SAFE_RELEASE(p);
	}
	m_vecChild.clear();
	SAFE_RELEASE(m_pSprite);
}

void cUIObject::Setup()
{
}

void cUIObject::Update()
{
	D3DXVECTOR3 v = m_vPosition;
	if (m_pParent)
	{
		v += m_pParent->GetPosition();
	}

	D3DXMatrixTranslation(&m_matTrans, v.x, v.y, v.z);

	m_matWorld = m_matScale * m_matTrans;

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Update();
	}
}

void cUIObject::Render(LPD3DXSPRITE pSprite)
{
	if (m_isDrawBoundingBox)
	{
		DWORD dwPrev = 0;
		_device->SetTexture(0, NULL);
		_device->GetRenderState(D3DRS_LIGHTING, &dwPrev);
		_device->SetRenderState(D3DRS_LIGHTING, false);

		int nCnt = 0;
		ST_RHWC_VERTEX aVertex[5];

		aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42, 0, 1);
		aVertex[nCnt++].c = D3DCOLOR_XRGB(255, 0, 0);

		aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42 + m_stSize.fHeight, 0, 1);
		aVertex[nCnt++].c = D3DCOLOR_XRGB(255, 0, 0);

		aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + m_stSize.fWidth, m_matTrans._42 + m_stSize.fHeight, 0, 1);
		aVertex[nCnt++].c = D3DCOLOR_XRGB(255, 0, 0);

		aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41 + m_stSize.fWidth, m_matTrans._42, 0, 1);
		aVertex[nCnt++].c = D3DCOLOR_XRGB(255, 0, 0);

		aVertex[nCnt].p = D3DXVECTOR4(m_matTrans._41, m_matTrans._42, 0, 1);
		aVertex[nCnt++].c = D3DCOLOR_XRGB(255, 0, 0);

		_device->SetFVF(ST_RHWC_VERTEX::FVF);
		_device->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, aVertex, sizeof(ST_RHWC_VERTEX));

		_device->SetRenderState(D3DRS_LIGHTING, (bool)dwPrev);
	}

	for each(auto p in m_vecChild)
	{
		p->Render(pSprite);
	}
}

void cUIObject::AddChild(cUIObject * pChild)
{
	pChild->m_pParent = this;
	m_vecChild.push_back(pChild);
}

void cUIObject::Destroy()
{
}

cUIObject * cUIObject::GetChildByTag(int nTag)
{
	//자신의 태그랑 같은면 그냥 리턴
	if (m_nTag == nTag)
		return this;
	//자식 중에 있으면 리턴
	for each(auto p in m_vecChild)
	{
		cUIObject* pChild = p->GetChildByTag(nTag);
		if (pChild)
			return pChild;
	}
	//없으면 NULL리턴
	return NULL;
}

void cUIObject::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
