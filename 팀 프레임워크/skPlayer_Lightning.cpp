#include "stdafx.h"
#include "skPlayer_Lightning.h"


HRESULT skPlayer_Lightning::init()
{

	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(2);
	setMaxNumActionPS(1);
	setMaxNumFinishPS(1);
	
	setPvPreparePS(0, "번개준비", 1);
	setPvActionPS(0, "번개", 1);

	_pvPrepaerPS[0][0]->SetLimitTime(1.0f);
	_pvActionPS[0][0]->SetLimitTime(6.0f);

	/*for (int i = 0; i < _pvFinishPS[0].size(); i++)
	{
		_pvFinishPS[0][i]->SetLimitTime(10.0f);
	}*/

	//_OneActionSettingOn = true;

	_BP = new tagBezierPoint[6];

	for (int i = 0; i < 6; i++)
	{
		_bpTime[i] = 0.0f;
	}

	_actionAtiveNum = 0;

	_limitShootTime = 0.3f;
	_currentShootTime = 0.0f;

	return S_OK;
}

void skPlayer_Lightning::release()
{
}

bool skPlayer_Lightning::Prepare()
{
	//D3DXVECTOR3 playerPos = _skillPosTrans->GetWorldPosition();
	//
	//playerPos.y += 0.01;

	////_pvPrepaerPS[0][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
	_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(_skillPosTrans->GetLocalPosition());
	////_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillPosTrans->GetForward());
	_pvPrepaerPS[0][0]->update();

	////_pvPrepaerPS[1][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
	////_pvPrepaerPS[1][0]->Transform()->SetWorldPosition(_oneTagerTrans->GetWorldPosition());
	////_pvPrepaerPS[1][0]->update();


	if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{
		//_skillPrepareOn = false;
		_skillActionOn = true;
		//_skillResetOn = true;
	}

	

	return false;
}

bool skPlayer_Lightning::Action()
{
	D3DXVECTOR3 ActionPos = _skillPosTrans->GetWorldPosition();

	_pvActionPS[0][0]->Transform()->SetWorldPosition(_oneTargetTrans->GetWorldPosition());
	_pvActionPS[0][0]->update();

	if (_pvActionPS[0][0]->autoTimeReset())
	{
		_skillResetOn = true;
	}

	return false;
}


void skPlayer_Lightning::Finsh()
{
	
}

void skPlayer_Lightning::Reset()
{
	_OneActionSettingOn = true;

	_BP = new tagBezierPoint[6];

	for (int i = 0; i < 6; i++)
	{
		_bpTime[i] = 0.0f;
	}

	_actionAtiveNum = 0;

	_limitShootTime = 0.3f;
	_currentShootTime = 0.0f;
}