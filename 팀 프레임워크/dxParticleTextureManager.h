#pragma once
#include "dxParticleTexture.h"
#include "singletonBase.h"

class dxParticleTextureManager : public singletonBase<dxParticleTextureManager>
{
private:
	map<string, dxParticleTexture*> _mapTex;
	map<string, dxParticleTexture*>::iterator _iter;

public:
	//�̹��� ��� �ʱ�ȭ
	void LoadImgInit(void);
public:
	//������� �̸����� �Ǵ�
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
		//��� ã��
		string path = findTexInfo(inName)->getPath();
		//�׷��̽����� ���� �� �� ���
		return this->LoadImg(inName + "_GrayScaleAlpha", path, TRUE);
	}

	//��ƼŬ �ؽ��� �ε�
	LPDIRECT3DTEXTURE9* LoadImg(string texName, string inPath, bool grayScaleAlphaOn = FALSE)
	{
		//�ִ��� Ȯ��
		if (checkName(texName)) return NULL;

		dxParticleTexture* newTex = new dxParticleTexture;
		newTex->LoadImg(inPath, grayScaleAlphaOn);

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
	//��ƼŬ �ؽ��� ã��2
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

	//��ƼŬ �ؽ��� ã��2
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

	//�׷��� ������ ���ķ� ü����
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

			//���
			_mapTex.insert(pair<string, dxParticleTexture*>(newTexName, newTex));

			inAndOutTex = *this->findTex(newTexName);
			
		}
	}

public:
	dxParticleTextureManager() {};
	~dxParticleTextureManager() {};
	
};

