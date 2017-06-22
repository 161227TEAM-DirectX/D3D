#include "stdafx.h"
#include "Text.h"


Text::Text()
	:strLength(0)
{
	D3DXMatrixIdentity(&matBillBoard);
}


Text::~Text()
{
}

void Text::init(string str)
{
	strLength = str.length();

	HDC hdc = CreateCompatibleDC(nullptr);

	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));

	lf.lfHeight = 2;						//�۲��� ���̰�(���밪�̶� ���� ����)
	lf.lfWidth = 1;						//�۰��� ���ΰ�
	lf.lfEscapement = 0;					//���ڿ��� ����
	lf.lfOrientation = 0;					//������ ������ 0.1������ ���
	lf.lfWeight = 1000;						//�۲��� ����
	lf.lfItalic = false;					//���׸�ü
	lf.lfUnderline = false;					//����
	lf.lfStrikeOut = false;					//���� ��� ��
	lf.lfCharSet = DEFAULT_CHARSET;			//���������� ���(���� ���� �ٸ� �� �ִ�.)
	lf.lfOutPrecision = 0;					
	lf.lfClipPrecision = 0;
	lf.lfQuality = 0;
	lf.lfPitchAndFamily = 0;

	strcpy_s(lf.lfFaceName, "����ü");	//��Ʈ ��Ÿ��.

	HFONT hFont = CreateFontIndirect(&lf);
	HFONT hFontOld = (HFONT)SelectObject(hdc, hFont);

	//��ġ ���ƿ� �������� �� �ִ� ��Ʈ�� �����, ������ �ؽ�Ʈ�� ������ �޽��� ���� �Ѵ�.
	/*HRESULT D3DXCreateText(
		LPDIRECT3DDEVICE9 pDevice,				[in] �޽��� ���� �� ��ġ�� ������.
		HDC hDC,								[in] ��¿��� ��Ʈ�� ���� �ϰ� �ִ� ��ġ�� ����. ��ġ�� ���ƿ� ���� ���õǴ� ��Ʈ��, TrueType ��Ʈ�� �ƴϸ� �ȵȴ�.
		LPCTSTR pText,							[in] �����ϴ� �ؽ�Ʈ�� �����ϴ� ĳ���� ������ ������. �����Ϸ��� ������ Unicode �� �䱸�ϰ� �ִ� ���, ������ Ÿ�� LPCTSTR �� LPCWSTR �� �ȴ�. �� �̿��� ����, �� ĳ���� ������ ������ Ÿ���� LPCSTR �� �ȴ�. �����ǡ��� �����Ұ�.
		FLOAT Deviation,						[in] TrueType ��Ʈ �ƿ�Ʈ�������κ����� �ִ� �ڵ� ����.
		FLOAT Extrusion,						[in] z ���� ���� �������� �о� ������ �ؽ�Ʈ�� ��.
		LPD3DXMESH *ppMesh,						[out] �����־��� �޽��� ������.
		LPD3DXBUFFER *ppAdjacency,				[out] ���� õ������ ������ ������ ������.
		LPGLYPHMETRICSFLOAT pGlyphMetrics		[out] �׸��ĸ�Ʈ��ũ����Ÿ�� ������ LPGLYPHMETRICSFLOAT ����ü�� �迭�� ������
	);*/
	wchar_t temp[_MAX_PATH] = { 0, };
	char temp2[_MAX_PATH] = { 0, };
	strcpy(temp2, str.c_str());

	MultiByteToWideChar(CP_ACP, 0, temp2, -1, temp, strlen(str.c_str()) + 1);

	LPD3DXMESH pMesh = nullptr;

	D3DXCreateTextW(_device, hdc, temp, 0.001f, 0.001f, &pMesh, nullptr, nullptr);
	
//	D3DXMESH_MANAGED
	//�޽��� �����Ѵ�. str��
	pMesh->CloneMeshFVF(pMesh->GetOptions(), VERTEX_PND::FVF, _device, &this->str);
	
	LPVERTEX_PND pV2;
	
	this->str->LockVertexBuffer(0, (LPVOID*)&pV2);
	
	for (int i = 0; i < pMesh->GetNumVertices(); ++i)
	{
		pV2[i].color = D3DCOLOR_XRGB(0, 255, 0);
	}
	
	this->str->UnlockVertexBuffer();
	
	SAFE_RELEASE(pMesh);
	SAFE_DELETE(pMesh);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);
}

void Text::update(void)
{
	D3DXVECTOR3 vPos = this->pos;
	D3DXMATRIX matScaling;
	//������(��� �ʿ�)
	D3DXMatrixTranslation(&matBillBoard, vPos.x, vPos.y, vPos.z);
	D3DXMatrixScaling(&matScaling, 0.1f, 0.1f, 0.1f);
	
	D3DXMATRIX matView, matInvView;
	
	_device->GetTransform(D3DTS_VIEW, &matView);
	
	D3DXMatrixInverse(&matInvView, 0, &matView);
	
	matBillBoard._11 = matInvView._11; matBillBoard._21 = matInvView._21; matBillBoard._31 = matInvView._31;
	matBillBoard._12 = matInvView._12; matBillBoard._22 = matInvView._22; matBillBoard._32 = matInvView._32;
	matBillBoard._13 = matInvView._13; matBillBoard._23 = matInvView._23; matBillBoard._33 = matInvView._33;
	
	D3DXMATRIX matT;
	float x = (strLength / 2) * -0.05f;
	D3DXMatrixTranslation(&matT, x, 0, 0);
	matBillBoard = matScaling * matT * matBillBoard;
}

void Text::render(void)
{
	D3DXMATRIX matS, matWorld;
	//D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);

	matWorld = matBillBoard;

	_device->SetTransform(D3DTS_WORLD, &matWorld);
	_device->SetRenderState(D3DRS_LIGHTING, false);
	this->str->DrawSubset(0);
	_device->SetRenderState(D3DRS_LIGHTING, true);
}
