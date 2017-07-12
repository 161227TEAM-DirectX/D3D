#include "stdafx.h"
#include "dxParticleTexture.h"

LPDIRECT3DTEXTURE9* dxParticleTexture::LoadImg(string inPath, bool grayScaleAlphaOn)
{

	HRESULT hr = NULL;

	hr = D3DXCreateTextureFromFileEx
	(
		_device, 				//디바이스 세팅
		inPath.c_str(), 		//파일경로
		D3DX_DEFAULT, 			//가로 크기(자동)
		D3DX_DEFAULT, 			//세로 크기(자동)
		4,
		//D3DX_DEFAULT, 			//밉맵 설정(자동)->일부러 많이 사용했다.(메모리는 많이 차지하지만 파티클의 프레임 드랍을 많이 줄여줄 거라 예상)
		NULL,
		//D3DFMT_FROM_FILE,		//파일에서 포맷(자동)
		D3DFMT_A8B8G8R8,		//파일 포맷 세팅
		D3DPOOL_MANAGED, 		//메모리풀
		D3DX_DEFAULT, 			//필터(D3DX_FILTER_NONE을 쓰지 말자 이상하게 나온다.)
		D3DX_DEFAULT, 			//밉맵필터
		NULL,
		&_texInfo, 				//텍스쳐 정보
		NULL,
		&_texture
	);

	if (FAILED(hr))	return NULL;

	if (grayScaleAlphaOn == TRUE)
	{
		D3DSURFACE_DESC dsc;
		D3DLOCKED_RECT	drc;
		DWORD*	pColorSrc = NULL;
		DWORD*	pColorDst = NULL;


		// 원본 텍스처 정보 얻기
		_texture->GetLevelDesc(0, &dsc);

		int		texImgW = dsc.Width;
		int		texImgH = dsc.Height;

		// 임시 버퍼 생성
		pColorSrc = new DWORD[texImgW * texImgH];


		// 원본 텍스처 픽셀 값을 임시 버퍼에 복사
		_texture->LockRect(0, &drc, NULL, 0);
		memcpy(pColorSrc, drc.pBits, texImgW * texImgH * sizeof(DWORD));
		pColorDst = (DWORD*)drc.pBits;
		_texture->UnlockRect(0);

		D3DXCOLOR texColor;
		float grayScale;

		for (int y = 0; y < texImgH; ++y)
		{
			for (int x = 0; x < texImgW; ++x)
			{
				int nIdx = y*texImgW + x;

				texColor = pColorSrc[nIdx];

				//I = 0.30R + 0.59G + 0.11B
				grayScale = texColor.r * 0.2126f + texColor.g * 0.7152f + texColor.b * 0.0722f;

				//pColorDst[nIdx] = D3DXCOLOR(grayScale, grayScale, grayScale, texColor.a);
				pColorDst[nIdx] = D3DXCOLOR(texColor.r, texColor.g, texColor.b, grayScale);
			}
		}
	}
	/*else
	{
		hr = D3DXCreateTextureFromFile(_device, inPath.c_str(), &_texture);
		if (FAILED(hr))	return NULL;
	}*/

	//경로 저장
	_path = inPath;
	//알파 여부
	_isGrayScaleAlpha = grayScaleAlphaOn;

	return &_texture;
}

void dxParticleTexture::ChangeGrayScaleAlpha()
{
	D3DSURFACE_DESC dsc;
	D3DLOCKED_RECT	drc;
	DWORD*	pColorSrc = NULL;
	DWORD*	pColorDst = NULL;


	// 원본 텍스처 정보 얻기
	_texture->GetLevelDesc(0, &dsc);

	int		texImgW = dsc.Width;
	int		texImgH = dsc.Height;

	// 임시 버퍼 생성
	pColorSrc = new DWORD[texImgW * texImgH];


	// 원본 텍스처 픽셀 값을 임시 버퍼에 복사
	_texture->LockRect(0, &drc, NULL, 0);
	memcpy(pColorSrc, drc.pBits, texImgW * texImgH * sizeof(DWORD));
	pColorDst = (DWORD*)drc.pBits;
	_texture->UnlockRect(0);

	D3DXCOLOR texColor;
	float grayScale;

	for (int y = 0; y < texImgH; ++y)
	{
		for (int x = 0; x < texImgW; ++x)
		{
			int nIdx = y*texImgW + x;

			texColor = pColorSrc[nIdx];

			//I = 0.30R + 0.59G + 0.11B
			grayScale = texColor.r * 0.2126f + texColor.g * 0.7152f + texColor.b * 0.0722f;

			//pColorDst[nIdx] = D3DXCOLOR(grayScale, grayScale, grayScale, texColor.a);
			pColorDst[nIdx] = D3DXCOLOR(texColor.r, texColor.g, texColor.b, grayScale);
		}
	}
}


