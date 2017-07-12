#include "stdafx.h"
#include "skPlayer_FireMagic.h"


HRESULT skPlayer_FireMagic::init()
{

	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(2);
	setMaxNumActionPS(2);
	setMaxNumFinishPS(1);

	setPvActionPS(0, "È­¿°±ËÀû", 1);
	setPvActionPS(1, "È­¿°È¸¿À¸®", 1);

	_pvActionPS[0][0]->SetLimitTime(2.0f);

	//for (int i = 0; i < _pvActionPS[0].size(); i++)
	//{
	//	_pvActionPS[0][i]->SetLimitTime(8.0f);
	//}

	//_OneActionSettingOn = true;

	_pvActionPS[1][0]->SetActive(FALSE);

	_actionAtiveNum = 0;

	_limitShootTime = 0.3f;
	_currentCollisionTime = 0.0f;


	_oneSettingOn = true;

	_collisonSphere[0].setBound(&D3DXVECTOR3(0.0f,0.0f,0.0f), &D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	_collisonSphere[1].setBound(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.1f, 0.1f, 0.1f));

	return S_OK;
}

void skPlayer_FireMagic::release()
{

}

bool skPlayer_FireMagic::Prepare()
{
	//D3DXVECTOR3 playerPos = _skillPosTrans->GetWorldPosition();

	//playerPos.y += 0.01;

	//_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(playerPos);
	//_pvPrepaerPS[1][0]->Transform()->SetWorldPosition(playerPos);

	//_pvPrepaerPS[0][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());


	//_pvPrepaerPS[0][0]->Transform()->LookDirection(_skillPosTrans->GetForward());


	//_pvPrepaerPS[1][0]->Transform()->SetWorldMatrix(_skillPosTrans->GetFinalMatrix());
	//_pvPrepaerPS[1][0]->Transform()->SetWorldPosition(_oneTagerTrans->GetWorldPosition());
	//_pvPrepaerPS[1][0]->update();


	_skillActionOn = true;



	return false;
}

bool skPlayer_FireMagic::Action()
{
	D3DXVECTOR3 playerPos = _skillPosTrans->GetWorldPosition();
	D3DXVECTOR3 tagretPos = _oneTargetTrans->GetWorldPosition();

	if (_oneSettingOn)
	{

		_pvActionPS[0][0]->Transform()->SetWorldPosition(playerPos);
		

		_oneSettingOn = false;
	}

	

	if (PHYSICSMANAGER->isOverlap(_oneTargetTrans, &_collisonSphere[0],_pvActionPS[0][0]->Transform(), &_collisonSphere[1]))
	{
		_pvActionPS[1][0]->Transform()->SetWorldPosition(_pvActionPS[0][0]->Transform()->GetWorldPosition());
		_pvActionPS[1][0]->SetActive(TRUE);

		if (_pvActionPS[0][0]->autoTimeReset(false))
		{
			//_skillPrepareOn = false;
			//_skillActionOn = true;
			_skillResetOn = true;
		}
	}
	else
	{
		_pvActionPS[0][0]->Transform()->LookPosition(tagretPos);
		_pvActionPS[0][0]->Transform()->MovePositionSelf(0.0f, 0.0f, 20.0f*_timeDelta);
	}

	for (int i = 0; i < _pvActionMaxNum; i++)
	{

		_pvActionPS[i][0]->update();
	}


	return false;
}


void skPlayer_FireMagic::Finsh()
{


}

void skPlayer_FireMagic::Reset()
{
	_oneSettingOn = true;

	_pvActionPS[1][0]->SetActive(FALSE);

	_actionAtiveNum = 0;

	_limitShootTime = 0.3f;
	_currentCollisionTime = 0.0f;
}