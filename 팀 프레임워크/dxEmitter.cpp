#include "stdafx.h"
#include "dxEmitter.h"

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
