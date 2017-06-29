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

	_realTimeTrackingOn = false;

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
	D3DXMATRIXA16 matPos;
	D3DXMATRIXA16 matRot;
	D3DXMATRIXA16 matFin;

	D3DXMatrixIdentity(&matPos);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matFin);

	D3DXMatrixTranslation(&matPos, iter->position.x, iter->position.y, iter->position.z);

	//iter->allRotAngle.x = 60.0f;

	//사원수 준비
	D3DXQUATERNION quatRot;
	D3DXQuaternionRotationYawPitchRoll(&quatRot, D3DXToRadian(iter->allRotAngle.y), D3DXToRadian(iter->allRotAngle.x), D3DXToRadian(iter->allRotAngle.z));

	//사원수에 의한 행렬준비
	D3DXMatrixRotationQuaternion(&matRot, &quatRot);		//사원수에 의한 회전값으로 회전행렬이 만들어진다.

															//역행렬 방향을 바꾸기 위해 일부러
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

	_posMD->ActiveUpdate(iter);			//위치
	_velMD->ActiveUpdate(iter);			//속도
	_accelMD->ActiveUpdate(iter);		//가속도
	_colorMD->ActiveUpdate(iter);		//색깔
	_sizeMD->ActiveUpdate(iter);		//사이즈
	_lifeMD->ActiveUpdate(iter);		//생명력
	_circleMD->ActiveUpdate(iter);		//원회전

	_rotateMD->ActiveUpdate(iter);		//일반 회전

	_uvMD->ActiveUpdate(iter);			//uv



	//사이즈 및 중심 위치 종합계산
	iter->scaleHV0 = D3DXVECTOR2(iter->size*iter->lengthHV0.x, iter->size*iter->lengthHV0.y);
	iter->scaleHV1 = D3DXVECTOR2(iter->size*iter->lengthHV1.x, iter->size*iter->lengthHV1.y);
	iter->scaleHV2 = D3DXVECTOR2(iter->size*iter->lengthHV2.x, iter->size*iter->lengthHV2.y);
	iter->scaleHV3 = D3DXVECTOR2(iter->size*iter->lengthHV3.x, iter->size*iter->lengthHV3.y);


	//최종계산
	float DeltaTime = _timeDelta*iter->emitterNum;

	iter->vectorDir = (-iter->preCircleSpeed) + iter->circleSpeed + iter->velocity*DeltaTime + (iter->acceleration*(iter->age*DeltaTime)*(iter->age*DeltaTime) / 2.0f) + iter->posDirectVel*DeltaTime + iter->attractPos*DeltaTime;
	//iter->vectorDir = iter->attractPos*DeltaTime*_timeDelta;

	//방향 돌리기 계산
	D3DXMATRIXA16 matPos;
	D3DXMATRIXA16 matRot;
	D3DXMATRIXA16 matFin;

	D3DXMatrixIdentity(&matPos);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matFin);

	D3DXMatrixTranslation(&matPos, iter->vectorDir.x, iter->vectorDir.y, iter->vectorDir.z);

	//iter->allRotAngle.x = 60.0f;

	//사원수 준비
	D3DXQUATERNION quatRot;
	D3DXQuaternionRotationYawPitchRoll(&quatRot, D3DXToRadian(iter->allRotAngle.y), D3DXToRadian(iter->allRotAngle.x), D3DXToRadian(iter->allRotAngle.z));

	//사원수에 의한 회전값으로 회전행렬로 만듬
	D3DXMatrixRotationQuaternion(&matRot, &quatRot);

	//역행렬 방향을 바꾸기 위해 일부러
	D3DXMatrixInverse(&matRot, NULL, &matRot);

	matFin = matPos*matRot*(iter->matPsRot);

	iter->FinalDir = D3DXVECTOR3(matFin._41, matFin._42, matFin._43);


	//평면용
	iter->posCenter += iter->FinalDir;

	////실시간 추적 사용시
	//if (_realTimeTrackingOn)
	//{
	//	
	//	D3DXMatrixIdentity(&matPos);
	//	D3DXMatrixIdentity(&matRot);
	//	D3DXMatrixIdentity(&matFin);


	//	iter->FinalPos += iter->FinalDir;

	//	D3DXMatrixTranslation(&matPos, iter->FinalPos.x, iter->FinalPos.y, iter->FinalPos.z);

	//	matFin = matPos*(iter->matPsRot);

	//	//실시간 추격용
	//	iter->TrackingPos = D3DXVECTOR3(matFin._41, matFin._42, matFin._43);

	//}

	//평면용
	//iter->posCenter += anglePos*_timeDelta;

	//평면용
	//iter->posCenter += iter->FinalPos;
}

