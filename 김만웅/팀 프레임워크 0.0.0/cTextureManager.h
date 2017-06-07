#pragma once

#define TEXTURE_MANAGER cTextureManager::GetInstance()

class cTextureManager
{
private:
	SINGLETONE(cTextureManager);

private:
	map<string, LPDIRECT3DTEXTURE9> m_mapTexture;
	map<string, D3DXIMAGE_INFO>		m_mapImageInfo;

public:
	LPDIRECT3DTEXTURE9 GetTexture(string sFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(string sFullPath, OUT D3DXIMAGE_INFO* pImageInfo);
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath, OUT D3DXIMAGE_INFO* pImageInfo);
	void GetTexture(OUT LPDIRECT3DTEXTURE9* pOutTexture, OUT D3DXIMAGE_INFO* pImageInfo, char* szFullPath);
	void GetTexture(OUT LPDIRECT3DTEXTURE9* pOutTexture, OUT D3DXIMAGE_INFO* pImageInfo, string sFullPath);

	void Destroy();
};

