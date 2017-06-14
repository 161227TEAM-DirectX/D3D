#include "stdafx.h"
#include "dxEmitter.h"

void dxEmitter::release()
{
	 _module->relese();
	 SAFE_DELETE(_module);
}

bool dxEmitter::autoActiveTimeCheck(void)
{
	if (_activeTimeCheckOn == FALSE) return FALSE;

	if (_activeLimitTime <= _activeCurrentTime)
	{
		//_activeCurrentTime = 0.0f;
		return TRUE;
	}
	_activeCurrentTime += _timeDelta;

	return FALSE;
}

bool dxEmitter::autoActiveTimeCheck(float timeDelta)
{
	if (_activeTimeCheckOn == FALSE) return FALSE;

	if (_activeLimitTime <= _activeCurrentTime)
	{
		//_activeCurrentTime = 0.0f;
		return TRUE;
	}
	_activeCurrentTime += timeDelta;

	return FALSE;
}