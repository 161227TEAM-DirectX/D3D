#include "stdafx.h"
#include "dxParticleTexture.h"

LPDIRECT3DTEXTURE9* dxParticleTexture::LoadImg(string inPath, bool grayScaleAlphaOn)
{

	HRESULT hr = NULL;

	hr = D3DXCreateTextureFromFileEx
	(
		_device, 				//����̽� ����
		inPath.c_str(), 		//���ϰ��
		D3DX_DEFAULT, 			//���� ũ��(�ڵ�)
		D3DX_DEFAULT, 			//���� ũ��(�ڵ�)
		4,
		//D3DX_DEFAULT, 			//�Ӹ� ����(�ڵ�)->�Ϻη� ���� ����ߴ�.(�޸𸮴� ���� ���������� ��ƼŬ�� ������ ����� ���� �ٿ��� �Ŷ� ����)
		NULL,
		//D3DFMT_FROM_FILE,		//���Ͽ��� ����(�ڵ�)
		D3DFMT_A8B8G8R8,		//���� ���� ����
		D3DPOOL_MANAGED, 		//�޸�Ǯ
		D3DX_DEFAULT, 			//����(D3DX_FILTER_NONE�� ���� ���� �̻��ϰ� ���´�.)
		D3DX_DEFAULT, 			//�Ӹ�����
		NULL,
		&_texInfo, 				//�ؽ��� ����
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


		// ���� �ؽ�ó ���� ���
		_texture->GetLevelDesc(0, &dsc);

		int		texImgW = dsc.Width;
		int		texImgH = dsc.Height;

		// �ӽ� ���� ����
		pColorSrc = new DWORD[texImgW * texImgH];


		// ���� �ؽ�ó �ȼ� ���� �ӽ� ���ۿ� ����
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

	//��� ����
	_path = inPath;
	//���� ����
	_isGrayScaleAlpha = grayScaleAlphaOn;

	return &_texture;
}

void dxParticleTexture::ChangeGrayScaleAlpha()
{
	D3DSURFACE_DESC dsc;
	D3DLOCKED_RECT	drc;
	DWORD*	pColorSrc = NULL;
	DWORD*	pColorDst = NULL;


	// ���� �ؽ�ó ���� ���
	_texture->GetLevelDesc(0, &dsc);

	int		texImgW = dsc.Width;
	int		texImgH = dsc.Height;

	// �ӽ� ���� ����
	pColorSrc = new DWORD[texImgW * texImgH];


	// ���� �ؽ�ó �ȼ� ���� �ӽ� ���ۿ� ����
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


