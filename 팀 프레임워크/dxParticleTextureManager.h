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
	//������� �̸����� �Ǵ�
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
		//��� ã��
		string path = findTexInfo(inName)->getPath();
		//�׷��̽����� ���� �� �� ���
		return this->LoadImg(inName + "_GrayScale", path, TRUE);
	}

	//��ƼŬ �ؽ��� �ε�
	LPDIRECT3DTEXTURE9* LoadImg(string texName, string inPath, bool grayScaleOn = FALSE)
	{
		//�ִ��� Ȯ��
		if (checkName(texName)) return NULL;

		dxParticleTexture* newTex = new dxParticleTexture;
		newTex->LoadImg(inPath, grayScaleOn);

		_mapTex.insert(pair<string, dxParticleTexture*>(texName, newTex));

		return this->findTex(texName);
	}
	//��ƼŬ �ؽ��� ���� ã��
	dxParticleTexture* findTexInfo(string texName)
	{
		
		_iter = _mapTex.find(texName);
		if (_iter != _mapTex.end())
		{
			return _iter->second;
		}

		return NULL;
	}

	//��ƼŬ �ؽ��� ã��
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

