#include "stdafx.h"
#include "dxPositionModule.h"

HRESULT dxPositionModule::init()
{
	_grpPosDirectionVelOn = false;

	PositionType = PTC_DEFAULT;
	return S_OK;
}

void dxPositionModule::relese()
{
}

void dxPositionModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	//��ġ
	if (_radPtc.radPosOn)
	{
		iter->position.x = RandomFloatRange(_radPtc.positionX.Min, _radPtc.positionX.Max);
		iter->position.y = RandomFloatRange(_radPtc.positionY.Min, _radPtc.positionY.Max);
		iter->position.z = RandomFloatRange(_radPtc.positionZ.Min, _radPtc.positionZ.Max);

		iter->dirSphere.x = RandomFloatRange( -_radPtc.dirSphere.x, _radPtc.dirSphere.x);
		iter->dirSphere.y = RandomFloatRange( -_radPtc.dirSphere.y, _radPtc.dirSphere.y);
		iter->dirSphere.z = RandomFloatRange( -_radPtc.dirSphere.z, _radPtc.dirSphere.z);

		if (PositionType == PTC_SPHERE)
		{
			D3DXVec3Normalize(&iter->dirSphere, &iter->dirSphere);

			//�����Ÿ�
			float radDistance = RandomFloatRange(_radPtc.posSphereRadius.Min, _radPtc.posSphereRadius.Max);

			//�߰���ġ
			iter->position = iter->position + iter->dirSphere * radDistance;

		}

	}

	//��ġ ���⼺ �ӵ�
	if (_radPtc.radPosDirectionVelOn)
	{
		//���⸸ �̱�
		//D3DXVECTOR3 posDirtion;
		D3DXVec3Normalize(&iter->posDirection, &iter->position);
		//�ӵ�
		iter->posDirectSpeed = RandomFloatRange(_radPtc.posDirectionVel.Min, _radPtc.posDirectionVel.Max);
		//iter->posDirectVel = iter->posDirection* iter->posDirectSpeed;

		if (_grpPosDirectionVelOn) { _grpPosDirectionVel[0]->value = iter->posDirectSpeed; }

	}
	if (_grpPosDirectionVelOn) { this->SetGraph(_grpPosDirectionVel); }

	//���� �ʱ�ȭ
	if (_radPtc.attractOn)
	{
		iter->attractCenter.x = RandomFloatRange(_radPtc.attractX.Min, _radPtc.attractX.Max);
		iter->attractCenter.y = RandomFloatRange(_radPtc.attractY.Min, _radPtc.attractY.Max);
		iter->attractCenter.z = RandomFloatRange(_radPtc.attractZ.Min, _radPtc.attractZ.Max);

		iter->attractStrartPos = iter->position; 
	}

}

void dxPositionModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{

	//��ġ ���⼺ �ӵ�
	if (_grpPosDirectionVelOn)
	{
		this->GraphVelocityUpdate(_grpPosDirectionVel, iter, iter->posDirectSpeed);
		iter->posDirectVel = iter->posDirection*iter->posDirectSpeed;
	}

	//����
	if (_radPtc.attractOn)
	{
		//iter->attractPos = VecLerp(iter->attractStrartPos, iter->attractCenter, (iter->age / iter->lifeTime));
		iter->attractPos = (iter->attractCenter - iter->attractStrartPos)/iter->lifeTime;
	}

}
