#include "stdafx.h"
#include "dxEffect.h"


HRESULT dxEffect::init()
{
	//dxParticleSystem* _ps;
	//for (int i = 0; i < _vPos.size(); i++)
	//{
	//	_ps = NULL;
	//	_ps = new dxParticleSystem;
	//	*_ps = *PSM->findPS(_psName);
	//	_ps->init();
	//	//_ps->SetActive();
	//	//PSM->initPS(_ps,_psName);
	//	//포지션 세팅
	//	_vPS.push_back(_ps);

	//	_ps = NULL;
	//}

	return S_OK;
}

void dxEffect::release()
{
	/*if (_vPS.empty() == FALSE)
	{
		_vPos
	}*/
}

void dxEffect::update()
{
	//if (_startOn == FALSE) return;

	if (_vPS.empty() == FALSE)
	{
		for (int i = 0; i < _vPS.size(); i++)
		{
			_vPS[i]->SetLimitTime(_limitTime);
			if (_vPS[i]->autoTimeReset())
			{
				//_vPS[i]->release();
				_vPS.erase(_vPS.begin() + i);
			}
		}
	}

	////있다면 비어있지 않으면~
	if (_vPS.empty() == FALSE)
	{
		for (int i = 0; i < _vPS.size(); i++)
		{
			//_vPS[i]->SetLimitTime(_limitTime);
			//_vPS[i]->Transform()->SetWorldPosition(*(_vPos[i]));
			_vPS[i]->Transform()->SetWorldPosition(_vPosTrans[i]->GetWorldPosition());
			//_vPS[i]->Transform()->SetWorldMatrix(_vPosTrans[i]->GetFinalMatrix());
			if (_vDir.empty() == FALSE)
			{
				_vPS[i]->Transform()->LookDirection(_vDirTrans[i]->GetForward());
				//_vPS[i]->Transform()->LookDirection(*_vDir[i]);
			}
			_vPS[i]->update();
		}
	}
}

void dxEffect::render()
{
	if (_startOn == FALSE) return;


	//렌더해라~
	if (_vPS.empty() == FALSE)
	{
		for (int i = 0; i < _vPS.size(); i++)
		{
			_vPS[i]->render();
		}
	}

	//해제하기
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
//
//void dxEffect::setPositoin(D3DXVECTOR3* pos)
//{
//	this->_vPos.push_back(pos);
//	dxParticleSystem* _ps;
//	_ps = NULL;
//	_ps = new dxParticleSystem;
//	*_ps = *PSM->findPS(_psName);
//	_ps->init();
//	//_ps->Transform()->SetWorldPosition(pos);
//	//_ps->SetActive();
//	//PSM->initPS(_ps,_psName);
//	//포지션 세팅
//	this->_vPS.push_back(_ps);
//}
//
//void dxEffect::setPosTrans(dx::transform * posTrans)
//{
//	this->_vPosTrans.push_back(posTrans);
//
//}
//
//void dxEffect::Start(D3DXVECTOR3 * pos, D3DXVECTOR3 * dir)
//{
//	_startOn = true;
//	//위치 넣기
//	//this->_vPos.push_back(pos);
//	//방향 넣기
//	this->_vDir.push_back(dir);
//	dxParticleSystem* _ps;
//	_ps = NULL;
//	_ps = new dxParticleSystem;
//	*_ps = *PSM->findPS(_psName);
//	_ps->init();
//	//_ps->Transform()->SetWorldPosition(pos);
//	//_ps->SetActive();
//	//PSM->initPS(_ps,_psName);
//	//포지션 세팅
//	this->_vPS.push_back(_ps);
//
//}

void dxEffect::Start(dx::transform * posTrans, dx::transform * dirTrans)
{
	_startOn = true;

	this->_vPosTrans.push_back(posTrans);
	this->_vDirTrans.push_back(dirTrans);
	dxParticleSystem* _ps;
	_ps = NULL;
	_ps = new dxParticleSystem;
	*_ps = *PSM->findPS(_psName);
	_ps->init();
	//_ps->Transform()->SetWorldPosition(pos);
	//_ps->SetActive();
	//PSM->initPS(_ps,_psName);
	//포지션 세팅
	this->_vPS.push_back(_ps);
}





