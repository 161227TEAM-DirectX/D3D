#include "stdafx.h"
#include "dxEmitter.h"

void dxEmitter::preUpdate()
{
	if (_preUpdateOn == FALSE)	return;
	//�̸� ���ݾ� �������
	//_preInitPtcMaxNum = 0;

	if (_preOneSettingOn)
	{
		//�� �����Ӵ� ��ƼŬ �ʱ�ȭ ��
		_oneFramePtcNum = ((int)(_spawnTime / _timeDelta)) - 1;	//1�������� ���� ������ �Ϲ� ������Ʈ�� ��ġ�� �ʱ� ������(������)
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
		//�ð� ����
		_accrueTime += _timeDelta;

		if (_preLimitTime <= _accrueTime)
		{
			_oneFramePtcNum = _onePtcNum - _preInitPtcCurrentNum;
			//�����ð� �ʱ�ȭ
			_accrueTime = 0.0f;
		}
		else
		{
			//������ ������ ���
			if ((_onePtcNum - _preInitPtcCurrentNum) < _oneFramePtcNum)
			{
				_oneFramePtcNum = _onePtcNum - _preInitPtcCurrentNum;
			}
		}
	}

	//���� �ʱ�ȭ�� ������ ��ƼŬ �� �ʱ�ȭ
	_oneFramePtcCurrentNum = 0;

	for (iter = _ptcList.begin(); iter != _ptcList.end(); ++iter)
	{
		if (iter->isAlive == false)
		{
			//��Ȱ��ȭ
			iter->isInit = true;
			iter->emitterNum = _emitterNum;
			if (_psTrans != NULL)
			{
				iter->psTransPos = _psTrans->GetWorldPosition();
				iter->matPsRot = _psTrans->GetWorldRotateMatrix();
			}
			_module->InitUpdate(iter);

			//�� �����Ӵ� ������Ʈ�� ����
			_oneFramePtcCurrentNum++;
			//�ʱ�ȭ�� �� ����
			_preInitPtcCurrentNum++;

			if (_oneFramePtcNum > _oneFramePtcCurrentNum) break;

		}
	}

	//��ƼŬ �ʱ�ȭ �Ϸ�����
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
