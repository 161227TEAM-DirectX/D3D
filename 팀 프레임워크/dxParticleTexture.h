#pragma once
class dxParticleTexture
{
private:
	string				_path;				//파일경로
	D3DXIMAGE_INFO		_texInfo;			//텍스쳐 정보
	LPDIRECT3DTEXTURE9	_texture;			//텍스쳐
	bool				_isGrayScaleAlpha;	//적용여부

public:
	//이미지 세팅
	LPDIRECT3DTEXTURE9* LoadImg(string inPath, bool grayScaleAlphaOn = false);

	//이미지 그레이스케일 알파가 적용된 이미지로
	void ChangeGrayScaleAlpha();


	LPDIRECT3DTEXTURE9* getTexture(void) { return &_texture; }
	D3DXIMAGE_INFO		getInfo(void) { return _texInfo; }
	string				getPath(void) { return _path; }
	bool				getGrayScaleAlpha(void) { return _isGrayScaleAlpha; }

	UINT getWidth() { return _texInfo.Width; }
	UINT getHeight() { return _texInfo.Height; }

	

public:
	dxParticleTexture() {};
	~dxParticleTexture() {};
};

