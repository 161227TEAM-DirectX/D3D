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
	//깊은 복사를 위해 초기화 사용(생성자를 불러도 되지만 이름이 길다...)
	_trans = NULL;
	_trans = new dx::transform;
	_isActive = true;

	_limitTime = 0.0f;
	_currentTime = 0.0f;
	_EmitterCountNum = 0;

	//이미터 깊은 복사
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
				//안전한 형변환
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
	//파티클 시스템 활성화 여부 판단
	if (_isActive == FALSE) return;

	//이미터 업데이트
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
	//파티클 시스템 활성화 여부 판단
	if (_isActive == FALSE) return;
	
	//트렌스폼 업데이트
	_trans->SetDeviceWorld();
	//이미터 업데이트
	
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
