#pragma once
class dxParticleTexture
{
private:
	string				_path;				//���ϰ��
	D3DXIMAGE_INFO		_texInfo;			//�ؽ��� ����
	LPDIRECT3DTEXTURE9	_texture;			//�ؽ���
	bool				_isGrayScaleAlpha;	//���뿩��

public:
	//�̹��� ����
	LPDIRECT3DTEXTURE9* LoadImg(string inPath, bool grayScaleAlphaOn = false);

	//�̹��� �׷��̽����� ���İ� ����� �̹�����
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

