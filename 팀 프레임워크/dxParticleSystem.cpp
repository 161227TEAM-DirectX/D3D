#include "stdafx.h"
#include "dxParticleSystem.h"


HRESULT dxParticleSystem::init()
{
	/*if (_vEmitter.empty() == FALSE)
	{
		for (int i = 0; i < _vEmitter.size(); i++)
		{
			_vEmitter[i]->init();
		}
	}*/
	//���� ���縦 ���� �ʱ�ȭ ���(�����ڸ� �ҷ��� ������ �̸��� ���...)
	_trans = NULL;
	_trans = new dx::transform;
	_isActive = true;

	_limitTime = 0.0f;
	_currentTime = 0.0f;
	_EmitterCountNum = 0;

	//�̹��� ���� ����
	if (_vEmitter.empty() == FALSE)
	{
		dxEmitter* tempEMT;
		vector<dxEmitter*> _vTempEmitter;
		_vTempEmitter = _vEmitter;
		_vEmitter.clear();
		//_vEmitter.resize(_vTempEmitter.size());
		for (int i = 0; i < _vTempEmitter.size(); i++)
		{
			tempEMT = NULL;
			if (_vTempEmitter[i]->GetType() == ET_POINT)
			{
				tempEMT = new dxPointEmitter;
				//*tempEMT = *_vTempEmitter[i];
				//*(dxPointEmitter*)tempEMT = *(dxPointEmitter*)_vTempEmitter[i];
				//������ ����ȯ
				*(dynamic_cast<dxPointEmitter*>(tempEMT)) = *(dynamic_cast<dxPointEmitter*>(_vTempEmitter[i]));

				//tempEMT->CopyInit();
			}
			_vEmitter.push_back(tempEMT);
		}
	}


	return S_OK;
}

void dxParticleSystem::addEmitter(dxEmitter* emitter)
{
	_vEmitter.push_back(emitter);
}

void dxParticleSystem::reset()
{
	if (_vEmitter.empty() == FALSE)
	{
		for (int i = 0; i < _vEmitter.size(); i++)
		{
			_vEmitter[i]->reset();
		}
	}
	_trans->Reset();
}

void dxParticleSystem::update()
{
	//��ƼŬ �ý��� Ȱ��ȭ ���� �Ǵ�
	if (_isActive == FALSE) return;

	//�̹��� ������Ʈ
	if (_vEmitter.empty() == FALSE)
	{
		/*for (int i = 0; i < _vEmitter.size(); i++)
		{
			_vEmitter[i]->update();
		}*/
		_vEmitter[_EmitterCountNum]->update();
		_EmitterCountNum++;
		if (_EmitterCountNum >= _vEmitter.size()) { _EmitterCountNum = 0; }
	}
	
}

void dxParticleSystem::render()
{
	//��ƼŬ �ý��� Ȱ��ȭ ���� �Ǵ�
	if (_isActive == FALSE) return;
	
	//Ʈ������ ������Ʈ
	_trans->SetDeviceWorld();
	//�̹��� ������Ʈ
	
	if (_vEmitter.empty() == FALSE)
	{
		for (int i = 0; i < _vEmitter.size(); i++)
		{
			_vEmitter[i]->render();
		}
		
		//_vEmitter[_EmitterCountNum]->render();
		//_EmitterCountNum++;
		//if (_EmitterCountNum >= _vEmitter.size()) { _EmitterCountNum = 0; }
	}
}
