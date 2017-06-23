#include "stdafx.h"
#include "dxEmitter.h"

void dxEmitter::preUpdate()
{
	if (_preUpdateOn == FALSE)	return;
	//미리 조금씩 계산하자
	//_preInitPtcMaxNum = 0;

	if (_preOneSettingOn)
	{
		//한 프레임당 파티클 초기화 수
		_oneFramePtcNum = ((int)(_spawnTime / _timeDelta)) - 1;	//1프레임을 빼는 이유는 일반 업데이트와 겹치지 않기 위함임(안전용)
		_preLimitTime = _oneFramePtcNum*_timeDelta;
		_preInitPtcCurrentNum = 0;
		_preOneSettingOn = FALSE;
	}
	//float limitTime;
	vector<tagDxAttribute>::iterator iter;


	if (_oneFramePtcNum <= 0)
	{
		_oneFramePtcNum = _onePtcNum;

	}
	else
	{
		//시간 누적
		_accrueTime += _timeDelta;

		if (_preLimitTime <= _accrueTime)
		{
			_oneFramePtcNum = _onePtcNum - _preInitPtcCurrentNum;
			//누적시간 초기화
			_accrueTime = 0.0f;
		}
		else
		{
			//마지막 나머지 계산
			if ((_onePtcNum - _preInitPtcCurrentNum) < _oneFramePtcNum)
			{
				_oneFramePtcNum = _onePtcNum - _preInitPtcCurrentNum;
			}
		}
	}

	//현재 초기화한 프레임 파티클 수 초기화
	_oneFramePtcCurrentNum = 0;

	for (iter = _ptcList.begin(); iter != _ptcList.end(); ++iter)
	{
		if (iter->isAlive == false)
		{
			//재활성화
			iter->isInit = true;
			iter->emitterNum = _emitterNum;
			if (_psTrans != NULL)
			{
				iter->psTransPos = _psTrans->GetWorldPosition();
				iter->matPsRot = _psTrans->GetWorldRotateMatrix();
			}
			_module->InitUpdate(iter);

			//한 프레임당 업데이트한 개수
			_oneFramePtcCurrentNum++;
			//초기화한 총 개수
			_preInitPtcCurrentNum++;

			if (_oneFramePtcNum > _oneFramePtcCurrentNum) break;

		}
	}

	//파티클 초기화 완료조건
	if (_onePtcNum <= _preInitPtcCurrentNum)
	{
		_preUpdateOn = FALSE;
		_preOneSettingOn = FALSE;
	}

}

void dxEmitter::release()
{
	 _module->relese();
	 SAFE_DELETE(_module);
}

void dxEmitter::setGrayScaleAlphaOn()
{
	PTM->ChangeGrayScaleAlpha(this->_texture);
}

bool dxEmitter::autoActiveTimeCheck(float timeDelta)
{
	if (_activeTimeCheckOn == FALSE) return FALSE; 

	if (_activeLimitTime <= _activeCurrentTime)
	{
		//_activeCurrentTime = 0.0f;
		if (_activeRenderControlOn) { _activeRenderOn = false; }
		return TRUE;
	}
	_activeCurrentTime += timeDelta;

	return FALSE;
}

bool dxEmitter::autoStartTimeCheck(float timeDelta)
{
	if (_startTimeCheckOn == FALSE) return FALSE;

	if (_startLimitTime <= _startCurrentTime)
	{
		//_activeCurrentTime = 0.0f;
		_startRenderOn = TRUE;
		//_startTimeCheckOn = FALSE;
		return FALSE;
	}
	_startCurrentTime += timeDelta;

	return TRUE;
}
