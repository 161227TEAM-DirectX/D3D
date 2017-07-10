#pragma once
#include "singletonBase.h"
#include "dxParticleSystem.h"
#include "dxParticleSystemSet.h"
#include "psBossSet00.h"
#include "psEffectSet00.h"

#include "psPlayerSet00.h"

class dxParticleSystemManager :public singletonBase<dxParticleSystemManager>
{
private:
	map<string, dxParticleSystem*> _mapPS;
	map<string, dxParticleSystem*>::iterator _iter;

private:
	psBossSet00* _bossSet00;
	psEffectSet00* _effectSet00;
	psPlayerSet00* _playerSet00;


public:
	//��ƼŬ ���
	void addPS(string psName, dxParticleSystem* inPS, bool allRealTimeTrackingOn = false)
	{
		//�ִ��� Ȯ��
		if (checkName(psName)) return;
		//_mapPS.insert(pair<string, dxParticleSystem*>(psName,inPS));
		inPS->setAllRealTimeTrackingOn(allRealTimeTrackingOn);
		_mapPS.insert(pair<string, dxParticleSystem*>(psName, inPS));
		

	}

	//��ƼŬ ã��
	dxParticleSystem* findPS(string psName)
	{
		/*_iter = _mapPS.begin();
		for (_iter; _iter != _mapPS.end(); ++_iter)
		{
			if (_iter->first == psName)
			{
				return _iter->second;
			}
		}*/

		_iter = _mapPS.find(psName);
		if (_iter != _mapPS.end())
		{
			return _iter->second;
		}

		return NULL;
	}
	
	bool checkName(string psName)
	{
		_iter = _mapPS.find(psName);
		if (_iter != _mapPS.end())
		{
			return TRUE;
		}
		return FALSE;
	}

	//�ʱ�ȭ��
	void initPS(dxParticleSystem*& inPS, string psName)
	{
		inPS = NULL;
		//dxParticleSystem* PS = new dxParticleSystem;
		inPS = new dxParticleSystem;
		*inPS = *this->findPS(psName);
		inPS->init();
	}

	void initArrayPS(vector<dxParticleSystem*>& inPS, int particleNum, string psName)
	{
		dxParticleSystem* newPS;

		for (int i = 0; i < particleNum; i++)
		{
			newPS = NULL;
			newPS = new dxParticleSystem;
			*newPS = *this->findPS(psName);
			newPS->init();
			inPS.push_back(newPS);
		}


		//inPS->resize(particleNum, this->findPS(psName));
	}
	
	//��� �ʱ�ȭ��
	//void initArrayPS(dxParticleSystem*& inPS, int arrayNum, string psName)
	//{
	//	inPS = NULL;
	//	//dxParticleSystem* PS = new dxParticleSystem;
	//	inPS = new dxParticleSystem[arrayNum];
	//	for (int i = 0; i < arrayNum; i++)
	//	{
	//		inPS[i] = *this->findPS(psName);
	//	}

	//	//memcpy(inPS, this->findPS(psName) + 5, sizeof(dxParticleSystem)*arrayNum);
	//	//memset(inPS,);
	//	//inPS = this->findPS(psName);
	//}

	


public:
	//��ƼŬ �� �����
	void ParticleSystemSetInit();
	void ParticleSystemSetRelease();

public:
	dxParticleSystemManager() {};
	~dxParticleSystemManager() {};
};

