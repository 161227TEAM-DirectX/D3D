#include "stdafx.h"
#include "dxEffect.h"


HRESULT dxEffect::init()
{
	return S_OK;
}

void dxEffect::update()
{
	//if (_limitTime <= _currentTime)
	//{
	//	//����
	//	if (_vPS.empty() == FALSE)
	//	{
	//		for (int i = 0; i < _vPS.size(); i++)
	//		{
	//			_vPS.erase(_vPS.begin() + i);
	//		}
	//		_vPS.clear();
	//		//Ÿ�� ����
	//		_currentTime = 0;

	//		_oneSettingOn = true;
	//		_startOn = true;
	//	}
	//}

	if (_startOn == FALSE) return;

	//�����ǰ� ������� ������~
	if (_vPos.empty() == FALSE)
	{
		//�ѹ� ����
		if (_oneSettingOn)
		{
			//dxParticleSystem* _ps;
			//for (int i = 0; i < _vPos.size(); i++)
			//{
			//	_ps = NULL;
			//	_ps = new dxParticleSystem;
			//	*_ps = *PSM->findPS(_psName);
			//	_ps->init();

			//	//PSM->initPS(_ps,_psName);
			//	//������ ����
			//	_vPS.push_back(_ps);

			//	_ps = NULL;
			//}

			PSM->initArrayPS(_vPS, _vPosTrans.size(), _psName);
			_oneSettingOn = false;

			for (int i = 0; i < _vPS.size(); i++)
			{

				_vPS[i]->Transform()->SetWorldMatrix(_vPosTrans[i]->GetFinalMatrix());
			}

		}

		for (int i = 0; i < _vPS.size(); i++)
		{

			//_vPS[i]->Transform()->SetWorldPosition(*_vPos[i]);

			//if (_vDir.empty() == FALSE)
			//{
			//	//���� ����
			//	_vPS[i]->Transform()->LookDirection(_vDir[i]);
			//}

			_vPS[i]->update();
		}
	}

	//Ÿ�� ��
	_currentTime += _timeDelta;
}

void dxEffect::render()
{
	if (_startOn == FALSE) return;


	//�����ض�~
	if (_vPS.empty() == FALSE)
	{
		for (int i = 0; i < _vPS.size(); i++)
		{
			_vPS[i]->render();
		}
	}

	//�����ϱ�
	/*if (_vPos.empty() == FALSE)
	{
		for (int i = 0; i < _vPos.size(); i++)
		{
			_vPos.erase(_vPos.begin() + i);

			if (_vDir.empty() == FALSE)
			{
				_vDir.erase(_vDir.begin() + i);
			}
		}
	}*/

}





