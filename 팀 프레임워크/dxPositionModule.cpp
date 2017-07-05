#include "stdafx.h"
#include "dxPositionModule.h"

HRESULT dxPositionModule::init()
{
	_grpPosExprosionVelOn = false;

	PositionType = PTC_DEFAULT;
	return S_OK;
}

void dxPositionModule::relese()
{
}

void dxPositionModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	//위치
	if (_radPtc.radPosOn)
	{
		iter->position.x = RandomFloatRange(_radPtc.positionX.Min, _radPtc.positionX.Max);
		iter->position.y = RandomFloatRange(_radPtc.positionY.Min, _radPtc.positionY.Max);
		iter->position.z = RandomFloatRange(_radPtc.positionZ.Min, _radPtc.positionZ.Max);
	}
	else
	{
		iter->position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}

	//스피어 위치 설정
	if (PositionType == PTC_SPHERE)
	{
		//0값을 제거하자!!
		if(iter->dirSphere.x != 0.0f) iter->dirSphere.x = RandomFloatRange(-_radPtc.dirSphere.x, _radPtc.dirSphere.x) + 0.000001;
		if(iter->dirSphere.y != 0.0f) iter->dirSphere.y = RandomFloatRange(-_radPtc.dirSphere.y, _radPtc.dirSphere.y) + 0.000001;
		if(iter->dirSphere.z != 0.0f) iter->dirSphere.z = RandomFloatRange(-_radPtc.dirSphere.z, _radPtc.dirSphere.z) + 0.000001;


		D3DXVec3Normalize(&iter->dirSphere, &iter->dirSphere);

		//랜덤거리
		float radDistance = RandomFloatRange(_radPtc.posSphereRadius.Min, _radPtc.posSphereRadius.Max);

		//추가위치
		iter->position = iter->position + iter->dirSphere * radDistance;

	}

	//위치 회전
	if (_radPtc.posRotateOn)
	{
		//거리 뽑기

		//float radDistanceX = D3DXVec3Length(&D3DXVECTOR3());
		//float radDistanceY = D3DXVec3Length(&D3DXVECTOR3(iter->position.x, 0.0f, iter->position.z));
		//float radDistanceZ = D3DXVec3Length(&D3DXVECTOR3());
		

		iter->posRotAngleSpeed.x = RandomFloatRange(_radPtc.posRotAngleSpeedX.Min, _radPtc.posRotAngleSpeedX.Max);
		iter->posRotAngleSpeed.y = RandomFloatRange(_radPtc.posRotAngleSpeedY.Min, _radPtc.posRotAngleSpeedY.Max);
		iter->posRotAngleSpeed.z = RandomFloatRange(_radPtc.posRotAngleSpeedZ.Min, _radPtc.posRotAngleSpeedZ.Max);

	}

	//iter->posRotAngleSpeed.y = 10.0f;

	//폭발
	if (_radPtc.radPosExprosionVelOn)
	{
		//방향만 뽑기
		//D3DXVECTOR3 posDirtion;
		D3DXVec3Normalize(&iter->posDirection, &iter->position);
		//속도
		iter->posDirectSpeed = RandomFloatRange(_radPtc.posExprosionVel.Min, _radPtc.posExprosionVel.Max);
		iter->posDirectVel = iter->posDirection* iter->posDirectSpeed;

//		iter->posDirectVel = iter->posDirection* iter->posDirectSpeed;


		if (_grpPosExprosionVelOn) { _grpPosExprosionVel[0]->value = iter->posDirectSpeed; }

	}

	//익스플로
	if (_grpPosExprosionVelOn) { this->SetGraph(_grpPosExprosionVel); }

	//끌림 초기화
	if (_radPtc.attractOn)
	{
		iter->attractCenter.x = RandomFloatRange(_radPtc.attractX.Min, _radPtc.attractX.Max);
		iter->attractCenter.y = RandomFloatRange(_radPtc.attractY.Min, _radPtc.attractY.Max);
		iter->attractCenter.z = RandomFloatRange(_radPtc.attractZ.Min, _radPtc.attractZ.Max);

		//iter->attractStrartPos = iter->psTransPos+iter->position; 
		iter->attractStrartPos = iter->position;

		iter->attractPos = (iter->attractCenter - iter->attractStrartPos) /iter->lifeTime;
		//iter->attractPos = VecLerp(iter->attractCenter, iter->attractStrartPos, _timeDelta*iter->emitterNum);
	}

}

void dxPositionModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{

	float DeltaTime = _timeDelta*iter->emitterNum;

	D3DXVECTOR3 newPos = iter->FinalPos - iter->psTransPos;

	//폭발
	if (_grpPosExprosionVelOn)
	{
		//방향만 뽑기
		D3DXVec3Normalize(&iter->posDirection, &newPos);

		this->GraphVelocityUpdate(_grpPosExprosionVel, iter, iter->posDirectSpeed);
		iter->posDirectVel = iter->posDirection*iter->posDirectSpeed;
		//iter->position += iter->posDirectVel*DeltaTime;
	}

	else if (_radPtc.radPosExprosionVelOn)
	{
		D3DXVec3Normalize(&iter->posDirection, &newPos);
		iter->posDirectVel = iter->posDirection* iter->posDirectSpeed;
		//iter->position += iter->posDirectVel*DeltaTime;
	}

	if (_radPtc.posRotateOn)
	{
		//최종계산

		//iter->vectorDir = iter->attractPos*DeltaTime*_timeDelta;


		iter->posRotateAngle = iter->posRotAngleSpeed*DeltaTime;

		//방향 돌리기 계산
		D3DXMATRIXA16 matPos;
		D3DXMATRIXA16 matRot;
		D3DXMATRIXA16 matFin;

		D3DXMatrixIdentity(&matPos);
		D3DXMatrixIdentity(&matRot);
		D3DXMatrixIdentity(&matFin);

		

		D3DXMatrixTranslation(&matPos, newPos.x, newPos.y, newPos.z);
		//D3DXMatrixTranslation(&matPos, iter->position.x, iter->position.y, iter->position.z);

		//iter->allRotAngle.x = 60.0f;

		//사원수 준비
		D3DXQUATERNION quatRot;
		D3DXQuaternionRotationYawPitchRoll(&quatRot, D3DXToRadian(iter->posRotateAngle.y), D3DXToRadian(iter->posRotateAngle.x), D3DXToRadian(iter->posRotateAngle.z));

		//사원수에 의한 회전값으로 회전행렬로 만듬
		D3DXMatrixRotationQuaternion(&matRot, &quatRot);

		//역행렬 방향을 바꾸기 위해 일부러
		D3DXMatrixInverse(&matRot, NULL, &matRot);

		matFin = matPos*matRot;

		D3DXVECTOR3 finalRotPos = D3DXVECTOR3(matFin._41, matFin._42, matFin._43);

		iter->InitPos = finalRotPos + iter->psTransPos;
		iter->posCenter = iter->InitPos;
		iter->FinalPos = iter->InitPos;

	}

	




	//끌림
	//if (_radPtc.attractOn)
	//{
		//iter->attractPos = VecLerp(iter->attractStrartPos, iter->attractCenter, (iter->age / iter->lifeTime));

	//}

}
