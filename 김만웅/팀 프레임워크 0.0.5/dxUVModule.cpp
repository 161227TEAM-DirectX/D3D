#include "stdafx.h"
#include "dxUVModule.h"

HRESULT dxUVModule::init()
{
	return E_NOTIMPL;
}

void dxUVModule::relese()
{
}

void dxUVModule::InitUpdate(vector<tagDxAttribute>::iterator iter)
{
	//0----1
	//|   /|
	//|  / |
	//| /  |
	//|/   |
	//2----3

	//이거 계산한다고 식겁했다...
	//U0,2 (1.0f / frameMaxNumX)*(float)((int)((age / lifeTime)*FrameMaxNum) % frameMaxNumX);
	//U1,3 (1.0f / frameMaxNumX)*(float)((int)((age / lifeTime)*FrameMaxNum) % frameMaxNumX + 1);

	//V0,1 (1.0f / frameMaxNumY)*(float)((int)((age / lifeTime)*FrameMaxNumY));
	//V2,3 (1.0f / frameMaxNumY)*(float)((int)((age / lifeTime)*FrameMaxNumY + 1));



	

	if (_radPtc.animationOn)
	{
		//U부분
		iter->UV0.x = (1.0f / _radPtc.frameMaxNumX)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum) % _radPtc.frameMaxNumX);
		iter->UV2.x = iter->UV0.x;
		iter->UV1.x = (1.0f / _radPtc.frameMaxNumX)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum) % _radPtc.frameMaxNumX + 1);
		iter->UV3.x = iter->UV1.x;

		//V부분
		iter->UV0.y = (1.0f / _radPtc.frameMaxNumY)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.frameMaxNumY));
		iter->UV1.y = iter->UV0.y;
		iter->UV2.y = (1.0f / _radPtc.frameMaxNumY)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.frameMaxNumY + 1));
		iter->UV3.y = iter->UV2.y;
	}


}

void dxUVModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
	if (_radPtc.animationOn)
	{
		//U부분
		iter->UV0.x = (1.0f / _radPtc.frameMaxNumX)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum) % _radPtc.frameMaxNumX);
		iter->UV2.x = iter->UV0.x;
		iter->UV1.x = (1.0f / _radPtc.frameMaxNumX)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum) % _radPtc.frameMaxNumX + 1);
		iter->UV3.x = iter->UV1.x;

		//V부분
		iter->UV0.y = (1.0f / _radPtc.frameMaxNumY)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.frameMaxNumY));
		iter->UV1.y = iter->UV0.y;
		iter->UV2.y = (1.0f / _radPtc.frameMaxNumY)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.frameMaxNumY + 1));
		iter->UV3.y = iter->UV2.y;
	}
}
