#pragma once
#include "dxParticleTexture.h"
#include "singletonBase.h"

class dxParticleTextureManager : public singletonBase<dxParticleTextureManager>
{
private:
	map<string, dxParticleTexture*> _mapTex;
	map<string, dxParticleTexture*>::iterator _iter;

public:
	void InitLoadImg(void);

public:
	//경로인지 이름인지 판단
	LPDIRECT3DTEXTURE9* LoadImgPathAndName(string inDecName, bool grayScaleOn = FALSE)
	{
		if (this->checkName(inDecName))
		{
			return this->findTex(inDecName);
		}
		else
		{
			/*if (inDecName.find(".") != -1)
			{
				return this->findTex(inDecName);
			}
			else
			{*/
				return this->LoadImg(inDecName, inDecName, grayScaleOn);
			//}
		}
	};

	LPDIRECT3DTEXTURE9* AdjusteGrayScaleOn(string inName)
	{
		//경로 찾기
		string path = findTexInfo(inName)->getPath();
		//그레이스케일 변경 후 재 등록
		return this->LoadImg(inName + "_GrayScale", path, TRUE);
	}

	//파티클 텍스쳐 로드
	LPDIRECT3DTEXTURE9* LoadImg(string texName, string inPath, bool grayScaleOn = FALSE)
	{
		//있는지 확인
		if (checkName(texName)) return NULL;

		dxParticleTexture* newTex = new dxParticleTexture;
		newTex->LoadImg(inPath, grayScaleOn);

		_mapTex.insert(pair<string, dxParticleTexture*>(texName, newTex));

		return this->findTex(texName);
	}
	//파티클 텍스쳐 정보 찾기
	dxParticleTexture* findTexInfo(string texName)
	{
		
		_iter = _mapTex.find(texName);
		if (_iter != _mapTex.end())
		{
			return _iter->second;
		}

		return NULL;
	}

	//파티클 텍스쳐 찾기
	LPDIRECT3DTEXTURE9* findTex(string texName)
	{

		_iter = _mapTex.find(texName);
		if (_iter != _mapTex.end())
		{
			return _iter->second->getTexture();
		}

		return NULL;
	}

	bool checkName(string texName)
	{
		_iter = _mapTex.find(texName);
		if (_iter != _mapTex.end())
		{
			return TRUE;
		}
		return FALSE;
	}


public:
	dxParticleTextureManager() {};
	~dxParticleTextureManager() {};
};

