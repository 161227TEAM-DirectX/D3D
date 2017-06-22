#pragma once
#include "dxParticleTexture.h"
#include "singletonBase.h"

class dxParticleTextureManager : public singletonBase<dxParticleTextureManager>
{
private:
	map<string, dxParticleTexture*> _mapTex;
	map<string, dxParticleTexture*>::iterator _iter;

public:
	//이미지 등록 초기화
	void LoadImgInit(void);
public:
	//경로인지 이름인지 판단
	LPDIRECT3DTEXTURE9* LoadImgPathAndName(string inDecName, bool grayScaleAlphaOn = FALSE)
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
				return this->LoadImg(inDecName, inDecName, grayScaleAlphaOn);
			//}
		}
	};

	LPDIRECT3DTEXTURE9* AdjusteGrayScaleOn(string inName)
	{
		//경로 찾기
		string path = findTexInfo(inName)->getPath();
		//그레이스케일 변경 후 재 등록
		return this->LoadImg(inName + "_GrayScaleAlpha", path, TRUE);
	}

	//파티클 텍스쳐 로드
	LPDIRECT3DTEXTURE9* LoadImg(string texName, string inPath, bool grayScaleAlphaOn = FALSE)
	{
		//있는지 확인
		if (checkName(texName)) return NULL;

		dxParticleTexture* newTex = new dxParticleTexture;
		newTex->LoadImg(inPath, grayScaleAlphaOn);

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
	//파티클 텍스쳐 찾기2
	dxParticleTexture* findPtcTex(LPDIRECT3DTEXTURE9& inTex)
	{
		/*_iter = _mapPS.begin();
		
		}*/
		_iter = _mapTex.begin();
		for (_iter; _iter != _mapTex.end(); ++_iter)
		{
			if (*(_iter->second->getTexture()) == inTex)
			{
				return _iter->second;
			}

		}
		return NULL;
	}

	//파티클 텍스쳐 찾기2
	string findPtcTexName(LPDIRECT3DTEXTURE9& inTex)
	{
		/*_iter = _mapPS.begin();

		}*/
		_iter = _mapTex.begin();
		for (_iter; _iter != _mapTex.end(); ++_iter)
		{
			if (*(_iter->second->getTexture()) == inTex)
			{
				return _iter->first;
			}

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

	//그레이 스케일 알파로 체인지
	void ChangeGrayScaleAlpha(LPDIRECT3DTEXTURE9& inAndOutTex)
	{
		dxParticleTexture* changePtcTex = findPtcTex(inAndOutTex);

		if (changePtcTex != NULL)
		{
			if (changePtcTex->getGrayScaleAlpha()) return;

			string newTexName = findPtcTexName(inAndOutTex) + "_GrayScaleAlpha";
			string inPath = findPtcTex(inAndOutTex)->getPath();

			dxParticleTexture* newTex = new dxParticleTexture;
			newTex->LoadImg(inPath, TRUE);

			//등록
			_mapTex.insert(pair<string, dxParticleTexture*>(newTexName, newTex));

			inAndOutTex = *this->findTex(newTexName);
			
		}
	}

public:
	dxParticleTextureManager() {};
	~dxParticleTextureManager() {};
	
};

