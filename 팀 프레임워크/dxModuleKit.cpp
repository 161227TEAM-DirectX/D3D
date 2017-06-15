#include "stdafx.h"
#include "dxModuleKit.h"

HRESULT dxModuleKit::init()
{
	//���� �Ҵ�
	_posMD = new dxPositionModule;
	_velMD = new dxVelocityModule;
	_accelMD = new dxAccelerationModule;
	_colorMD = new dxColorModule;
	_sizeMD = new dxSizeModule;
	_lifeMD = new dxLifeTimeModule;
	_circleMD = new dxCircleModule;

	_rotateMD = new dxRotationModule;
	_uvMD = new dxUVModule;

	//�ʱ�ȭ
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
	//����
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
	_posMD->InitUpdate(iter);			//��ġ
	_velMD->InitUpdate(iter);			//�ӵ�
	_accelMD->InitUpdate(iter);			//���ӵ�
	_colorMD->InitUpdate(iter);			//����
	_sizeMD->InitUpdate(iter);			//������
	_lifeMD->InitUpdate(iter);			//�����
	_circleMD->InitUpdate(iter);		//��ȸ��

	_rotateMD->InitUpdate(iter);		//�Ϲ� ȸ��

	_uvMD->InitUpdate(iter);			//uv

	//�������
	//iter->FinalPos = iter->position;
	iter->posCenter = iter->position;
}

void dxModuleKit::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
	_posMD->ActiveUpdate(iter);			//��ġ
	_velMD->ActiveUpdate(iter);			//�ӵ�
	_accelMD->ActiveUpdate(iter);		//���ӵ�
	_colorMD->ActiveUpdate(iter);		//����
	_sizeMD->ActiveUpdate(iter);		//������
	_lifeMD->ActiveUpdate(iter);		//�����
	_circleMD->ActiveUpdate(iter);		//��ȸ��

	_rotateMD->ActiveUpdate(iter);		//�Ϲ� ȸ��

	_uvMD->ActiveUpdate(iter);			//uv

	//�������
	//iter->FinalPos = iter->position;
	iter->FinalPos = (-iter->preCircleSpeed) + iter->circleSpeed + iter->velocity*_timeDelta + (iter->acceleration*(iter->age*_timeDelta)*(iter->age*_timeDelta) / 2.0f) + iter->posDirectVel*_timeDelta + iter->attractPos*_timeDelta;

	

	//����
	//iter->posCenter += anglePos*_timeDelta;

	//����
	iter->posCenter += iter->FinalPos;
}

