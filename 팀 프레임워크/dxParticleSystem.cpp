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
			else if (_vTempEmitter[i]->GetType() == ET_PLANE)
			{
				tempEMT = new dxPlaneEmitter;
				*(dynamic_cast<dxPlaneEmitter*>(tempEMT)) = *(dynamic_cast<dxPlaneEmitter*>(_vTempEmitter[i]));
			}
			else if (_vTempEmitter[i]->GetType() == ET_BOARD)
			{
				tempEMT = new dxBoardEmitter;
				*(dynamic_cast<dxBoardEmitter*>(tempEMT)) = *(dynamic_cast<dxBoardEmitter*>(_vTempEmitter[i]));
			}
			else if (_vTempEmitter[i]->GetType() == ET_MESH)
			{
				tempEMT = new dxMeshEmitter;
				*(dynamic_cast<dxMeshEmitter*>(tempEMT)) = *(dynamic_cast<dxMeshEmitter*>(_vTempEmitter[i]));
			}

			//tempEMT->reset();
			_vEmitter.push_back(tempEMT);
		}
	}


	return S_OK;
}

void dxParticleSystem::release()
{
	SAFE_DELETE(_trans);
	for (int i = 0; i < _vEmitter.size(); i++)
	{
		_vEmitter[i]->release();
	}
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
	_isActive = true;
	_currentTime = 0.0f;
	_EmitterCountNum = 0;
}

void dxParticleSystem::update()
{
	//파티클 시스템 활성화 여부 판단
	if (_isActive == FALSE) return;

	//이미터 업데이트
	if (_vEmitter.empty() == FALSE)
	{

		//실패함
		/*for (int i = 0; i < _vEmitter.size(); i++)
		{
			_vEmitter[i]->preUpdate();
		}*/

		if (_vEmitter[_EmitterCountNum]->getRealtimeTrackingPosOn() == FALSE && _AllRealTimeTrackingOn == FALSE)
		{
			//실시간 추적이 아니면
			_vEmitter[_EmitterCountNum]->setParticleSystemTrans(_trans);
		}
		else
		{
			//실시간 추적이면 빌보드를 위해 행렬용 트랜스폼 세팅
			if (_vEmitter[_EmitterCountNum]->GetType() == ET_BOARD)
			{
				_vEmitter[_EmitterCountNum]->setPsBoardTrans(_trans);
			}
			//실시간 추적이면 빌보드를 위해 행렬용 트랜스폼 세팅
			if (_vEmitter[_EmitterCountNum]->GetType() == ET_MESH)
			{
				_vEmitter[_EmitterCountNum]->setParticleSystemTrans(_trans);
			}
		}

		//사이즈 세팅->시간 맞추기용
		_vEmitter[_EmitterCountNum]->setEmitterNum(_vEmitter.size());

		//업데이트
		_vEmitter[_EmitterCountNum]->update();
		_EmitterCountNum++;
		if (_EmitterCountNum >= _vEmitter.size()) { _EmitterCountNum = 0; }
	}

}

void dxParticleSystem::render()
{
	//파티클 시스템 활성화 여부 판단
	if (_isActive == FALSE) return;

	//_device->SetTexture(0, NULL);

	D3DXMATRIXA16 matInitWorld;
	D3DXMatrixIdentity(&matInitWorld);

	//이미터 작동
	if (_vEmitter.empty() == FALSE)
	{
		for (int i = 0; i < _vEmitter.size(); i++)
		{
			//트렌스폼 업데이트->트루일 때
			if ((_vEmitter[i]->getRealtimeTrackingPosOn() || _AllRealTimeTrackingOn))
			{
				_trans->SetDeviceWorld();
			}
			else
			{
				_device->SetTransform(D3DTS_WORLD,&matInitWorld);
			}

			//이미터 렌더
			_vEmitter[i]->render();
		}

	}
	_device->SetTransform(D3DTS_WORLD, &matInitWorld);

	//_device->SetTexture(0, NULL);

}

bool dxParticleSystem::autoTimeReset(bool ResetFunOn)
{
	if (_limitTime <= _currentTime)
	{
		//_currentTime = 0.0f;
		if (ResetFunOn) { this->reset(); this->_isActive = FALSE; }
		return TRUE;
	}
	_currentTime += _timeDelta;
	return FALSE;
}

