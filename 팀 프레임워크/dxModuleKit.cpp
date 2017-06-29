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

	_realTimeTrackingOn = false;

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
	D3DXMATRIXA16 matPos;
	D3DXMATRIXA16 matRot;
	D3DXMATRIXA16 matFin;

	D3DXMatrixIdentity(&matPos);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matFin);

	D3DXMatrixTranslation(&matPos, iter->position.x, iter->position.y, iter->position.z);

	//iter->allRotAngle.x = 60.0f;

	//����� �غ�
	D3DXQUATERNION quatRot;
	D3DXQuaternionRotationYawPitchRoll(&quatRot, D3DXToRadian(iter->allRotAngle.y), D3DXToRadian(iter->allRotAngle.x), D3DXToRadian(iter->allRotAngle.z));

	//������� ���� ����غ�
	D3DXMatrixRotationQuaternion(&matRot, &quatRot);		//������� ���� ȸ�������� ȸ������� ���������.

															//����� ������ �ٲٱ� ���� �Ϻη�
	D3DXMatrixInverse(&matRot, NULL, &matRot);

	matFin = matPos*matRot*(iter->matPsRot);

	iter->position = D3DXVECTOR3(matFin._41, matFin._42, matFin._43);


	iter->InitPos = iter->psTransPos + iter->position;
	iter->posCenter = iter->InitPos;
	iter->FinalPos = iter->InitPos;
	//iter->posCenter = D3DXVECTOR3(0.0f,0.0f,0.0f);



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



	//������ �� �߽� ��ġ ���հ��
	iter->scaleHV0 = D3DXVECTOR2(iter->size*iter->lengthHV0.x, iter->size*iter->lengthHV0.y);
	iter->scaleHV1 = D3DXVECTOR2(iter->size*iter->lengthHV1.x, iter->size*iter->lengthHV1.y);
	iter->scaleHV2 = D3DXVECTOR2(iter->size*iter->lengthHV2.x, iter->size*iter->lengthHV2.y);
	iter->scaleHV3 = D3DXVECTOR2(iter->size*iter->lengthHV3.x, iter->size*iter->lengthHV3.y);


	//�������
	float DeltaTime = _timeDelta*iter->emitterNum;

	iter->vectorDir = (-iter->preCircleSpeed) + iter->circleSpeed + iter->velocity*DeltaTime + (iter->acceleration*(iter->age*DeltaTime)*(iter->age*DeltaTime) / 2.0f) + iter->posDirectVel*DeltaTime + iter->attractPos*DeltaTime;
	//iter->vectorDir = iter->attractPos*DeltaTime*_timeDelta;

	//���� ������ ���
	D3DXMATRIXA16 matPos;
	D3DXMATRIXA16 matRot;
	D3DXMATRIXA16 matFin;

	D3DXMatrixIdentity(&matPos);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matFin);

	D3DXMatrixTranslation(&matPos, iter->vectorDir.x, iter->vectorDir.y, iter->vectorDir.z);

	//iter->allRotAngle.x = 60.0f;

	//����� �غ�
	D3DXQUATERNION quatRot;
	D3DXQuaternionRotationYawPitchRoll(&quatRot, D3DXToRadian(iter->allRotAngle.y), D3DXToRadian(iter->allRotAngle.x), D3DXToRadian(iter->allRotAngle.z));

	//������� ���� ȸ�������� ȸ����ķ� ����
	D3DXMatrixRotationQuaternion(&matRot, &quatRot);

	//����� ������ �ٲٱ� ���� �Ϻη�
	D3DXMatrixInverse(&matRot, NULL, &matRot);

	matFin = matPos*matRot*(iter->matPsRot);

	iter->FinalDir = D3DXVECTOR3(matFin._41, matFin._42, matFin._43);


	//����
	iter->posCenter += iter->FinalDir;

	////�ǽð� ���� ����
	//if (_realTimeTrackingOn)
	//{
	//	
	//	D3DXMatrixIdentity(&matPos);
	//	D3DXMatrixIdentity(&matRot);
	//	D3DXMatrixIdentity(&matFin);


	//	iter->FinalPos += iter->FinalDir;

	//	D3DXMatrixTranslation(&matPos, iter->FinalPos.x, iter->FinalPos.y, iter->FinalPos.z);

	//	matFin = matPos*(iter->matPsRot);

	//	//�ǽð� �߰ݿ�
	//	iter->TrackingPos = D3DXVECTOR3(matFin._41, matFin._42, matFin._43);

	//}

	//����
	//iter->posCenter += anglePos*_timeDelta;

	//����
	//iter->posCenter += iter->FinalPos;
}

