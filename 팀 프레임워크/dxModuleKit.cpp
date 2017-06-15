#include "stdafx.h"
#include "dxModuleKit.h"

HRESULT dxModuleKit::init()
{
	//동적 할당
	_posMD = new dxPositionModule;
	_velMD = new dxVelocityModule;
	_accelMD = new dxAccelerationModule;
	_colorMD = new dxColorModule;
	_sizeMD = new dxSizeModule;
	_lifeMD = new dxLifeTimeModule;
	_circleMD = new dxCircleModule;

	_rotateMD = new dxRotationModule;
	_uvMD = new dxUVModule;

	//초기화
	_posMD->init();
	_velMD->init();
	_accelMD->init();
	_colorMD->init();
	_sizeMD->init();
	_lifeMD->init();
	_circleMD->init();

	_rotateMD->init();
	_uvMD->init();

	return S_OK;
}

void dxModuleKit::relese()
{
	//해제
	SAFE_DELETE(_posMD);
	SAFE_DELETE(_velMD);
	SAFE_DELETE(_accelMD);
	SAFE_DELETE(_colorMD);
	SAFE_DELETE(_sizeMD);
	SAFE_DELETE(_lifeMD);
	SAFE_DELETE(_circleMD);

	SAFE_DELETE(_rotateMD);
	SAFE_DELETE(_uvMD);
}

void dxModuleKit::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	_posMD->InitUpdate(iter);			//위치
	_velMD->InitUpdate(iter);			//속도
	_accelMD->InitUpdate(iter);			//가속도
	_colorMD->InitUpdate(iter);			//색깔
	_sizeMD->InitUpdate(iter);			//사이즈
	_lifeMD->InitUpdate(iter);			//생명력
	_circleMD->InitUpdate(iter);		//원회전

	_rotateMD->InitUpdate(iter);		//일반 회전

	_uvMD->InitUpdate(iter);			//uv

	//최종계산
	//iter->FinalPos = iter->position;
	iter->posCenter = iter->position;
}

void dxModuleKit::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
	_posMD->ActiveUpdate(iter);			//위치
	_velMD->ActiveUpdate(iter);			//속도
	_accelMD->ActiveUpdate(iter);		//가속도
	_colorMD->ActiveUpdate(iter);		//색깔
	_sizeMD->ActiveUpdate(iter);		//사이즈
	_lifeMD->ActiveUpdate(iter);		//생명력
	_circleMD->ActiveUpdate(iter);		//원회전

	_rotateMD->ActiveUpdate(iter);		//일반 회전

	_uvMD->ActiveUpdate(iter);			//uv

	//최종계산
	//iter->FinalPos = iter->position;
	iter->FinalPos = (-iter->preCircleSpeed) + iter->circleSpeed + iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta) / 2.0f) + iter->posDirectVel*_timeDelta + iter->attractPos*_timeDelta;

	

	//평면용
	//iter->posCenter += anglePos*_timeDelta;

	//평면용
	iter->posCenter += iter->FinalPos;
}

