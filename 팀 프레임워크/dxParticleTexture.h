#pragma once
class dxParticleTexture
{
private:
	string				_path;			//파일경로
	D3DXIMAGE_INFO		_texInfo;		//텍스쳐 정보
	LPDIRECT3DTEXTURE9	_texture;		//

public:
	//이미지 세팅
	LPDIRECT3DTEXTURE9* LoadImg(string inPath, bool grayScaleOn = false);
	

	LPDIRECT3DTEXTURE9* getTexture(void) { return &_texture; }
	D3DXIMAGE_INFO		getInfo(void) { return _texInfo; }
	string				getPath(void) { return _path; }

	UINT getWidth() { return _texInfo.Width; }
	UINT getHeight() { return _texInfo.Height; }

	

public:
	dxParticleTexture() {};
	~dxParticleTexture() {};
};

