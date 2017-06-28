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

	lf.lfHeight = 2;						//글꼴의 높이값(절대값이라 음수 가능)
	lf.lfWidth = 1;							//글골의 세로값
	lf.lfEscapement = 0;					//문자열의 기울기
	lf.lfOrientation = 0;					//글자의 각도를 0.1단위로 명시
	lf.lfWeight = 1000;						//글꼴의 굵기
	lf.lfItalic = false;					//이테릭체
	lf.lfUnderline = false;					//밑줄
	lf.lfStrikeOut = false;					//문자 가운데 줄
	lf.lfCharSet = DEFAULT_CHARSET;			//문자집합을 명시(국가 마다 다를 수 있다.)
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = 0;
	lf.lfPitchAndFamily = 0;

	strcpy_s(lf.lfFaceName, "HY견고딕");	//폰트 스타일.

	HFONT hFont = CreateFontIndirect(&lf);
	HFONT hFontOld = (HFONT)SelectObject(hdc, hFont);

	//장치 문맥에 관련지을 수 있는 폰트를 사용해, 지정한 텍스트를 포함한 메쉬를 생성 한다.
	/*HRESULT D3DXCreateText(
	LPDIRECT3DDEVICE9 pDevice,				[in] 메쉬를 생성 한 장치의 포인터.
	HDC hDC,								[in] 출력용의 폰트를 저장 하고 있는 장치의 문맥. 장치의 문맥에 의해 선택되는 폰트는, TrueType 폰트가 아니면 안된다.
	LPCTSTR pText,							[in] 생성하는 텍스트를 지정하는 캐릭터 라인의 포인터. 컴파일러의 설정이 Unicode 를 요구하고 있는 경우, 데이터 타입 LPCTSTR 는 LPCWSTR 가 된다. 그 이외의 경우는, 이 캐릭터 라인의 데이터 타입은 LPCSTR 가 된다. 「주의」를 참조할것.
	FLOAT Deviation,						[in] TrueType 폰트 아우트라인으로부터의 최대 코드 편차.
	FLOAT Extrusion,						[in] z 축의 부의 방향으로 밀어 내지는 텍스트의 양.
	LPD3DXMESH *ppMesh,						[out] 돌려주어진 메쉬의 포인터.
	LPD3DXBUFFER *ppAdjacency,				[out] 인접 천성보를 포함한 버퍼의 포인터.
	LPGLYPHMETRICSFLOAT pGlyphMetrics		[out] 그리후메트릭크데이타를 포함한 LPGLYPHMETRICSFLOAT 구조체의 배열의 포인터
	);*/
	wchar_t temp[_MAX_PATH] = { 0, };
	char temp2[_MAX_PATH] = { 0, };
	strcpy(temp2, str.c_str());

	MultiByteToWideChar(CP_ACP, 0, temp2, -1, temp, strlen(str.c_str()) + 1);

	LPD3DXMESH pMesh = nullptr;

	D3DXCreateTextW(_device, hdc, temp, 0.001f, 0.001f, &pMesh, nullptr, nullptr);

	//	D3DXMESH_MANAGED
	//메쉬를 복사한다. str에
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
