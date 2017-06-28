#include "stdafx.h"
#include "damageText.h"


damageText::damageText()
{
}


damageText::~damageText()
{
}

void damageText::init(string str, D3DXCOLOR color)
{
	nameStr = str;
	strLength = str.length();

	HDC hdc = CreateCompatibleDC(nullptr);

	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));

	lf.lfHeight = 2;						//�۲��� ���̰�(���밪�̶� ���� ����)
	lf.lfWidth = 1;							//�۰��� ���ΰ�
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

	strcpy_s(lf.lfFaceName, "HY�߰��");	//��Ʈ ��Ÿ��.

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

	switch (color)
	{

	}

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

void damageText::update(void)
{
}

void damageText::render(void)
{
}
