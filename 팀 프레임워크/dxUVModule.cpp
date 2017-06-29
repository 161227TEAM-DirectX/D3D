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
	//이곳의 애니메이션은 순수 수학이 아니다. 절대 수학적인 모으는 정리는 필요없다!!!(까먹을까봐 적는다!!!)


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


	if (_radPtc.reverseImgU_On)
	{
		iter->UV0.x = 1.0f;
		iter->UV1.x = 0.0f;
		iter->UV0.x = 1.0f;
		iter->UV0.x = 0.0f;
	}
	if (_radPtc.reverseImgV_On)
	{
		iter->UV0.y = 1.0f;
		iter->UV1.y = 1.0f;
		iter->UV0.y = 0.0f;
		iter->UV0.y = 0.0f;
	}



	//애니메이션 시작부분 종료부분 사용시 설정
	if (_radPtc.aniSectionOn)
	{
		//U계산에 필요
		_radPtc.totalFrameNum = (_radPtc.endFrameNum - _radPtc.startFrameNum) + 1; 
		//V계산에 필요
		_radPtc.useFrameMaxNumY = (_radPtc.endFrameNum + _radPtc.frameMaxNumX) / _radPtc.frameMaxNumX - _radPtc.startFrameNum / _radPtc.frameMaxNumX;
	}

	//if (_radPtc.animationOn)
	//{
	//	//U부분
	//	iter->UV0.x = (1.0f / _radPtc.frameMaxNumX)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum) % _radPtc.frameMaxNumX);
	//	iter->UV2.x = iter->UV0.x;
	//	iter->UV1.x = (1.0f / _radPtc.frameMaxNumX)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum) % _radPtc.frameMaxNumX + 1);
	//	iter->UV3.x = iter->UV1.x;

	//	//V부분
	//	iter->UV0.y = (1.0f / _radPtc.frameMaxNumY)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.frameMaxNumY));
	//	iter->UV1.y = iter->UV0.y;
	//	iter->UV2.y = (1.0f / _radPtc.frameMaxNumY)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.frameMaxNumY + 1));
	//	iter->UV3.y = iter->UV2.y;
	//}


}

void dxUVModule::ActiveUpdate(vector<tagDxAttribute>::iterator iter)
{
	//0----1
	//|   /|
	//|  / |
	//| /  |
	//|/   |
	//2----3
	

	if (_radPtc.animationOn)
	{
		////U부분
		//iter->UV0.x = (1.0f / _radPtc.frameMaxNumX)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum) % _radPtc.frameMaxNumX);
		//iter->UV2.x = iter->UV0.x;
		//iter->UV1.x = (1.0f / _radPtc.frameMaxNumX)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum) % _radPtc.frameMaxNumX + 1);
		//iter->UV3.x = iter->UV1.x;

		////V부분
		//iter->UV0.y = (1.0f / _radPtc.frameMaxNumY)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.frameMaxNumY));
		//iter->UV1.y = iter->UV0.y;
		//iter->UV2.y = (1.0f / _radPtc.frameMaxNumY)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.frameMaxNumY + 1));
		//iter->UV3.y = iter->UV2.y;

		//애니메이션 시작부분고 엔드부분 설정

	/*	_radPtc.startFrameNum = 1;
		_radPtc.endFrameNum = 2;
		_radPtc.totalFrameNum = (_radPtc.endFrameNum - _radPtc.startFrameNum) + 1;
		_radPtc.useFrameMaxNumY = (_radPtc.endFrameNum + _radPtc.frameMaxNumX) / _radPtc.frameMaxNumX - _radPtc.startFrameNum / _radPtc.frameMaxNumX;*/

		if (_radPtc.reverseImgU_On)
		{
			//반전U
			iter->UV1.x = (1.0f / _radPtc.frameMaxNumX)*((_radPtc.startFrameNum + (int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum)) % _radPtc.frameMaxNumX);
			iter->UV3.x = iter->UV1.x;
			iter->UV0.x = (1.0f / _radPtc.frameMaxNumX)*((_radPtc.startFrameNum + (int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum)) % _radPtc.frameMaxNumX + 1);
			iter->UV2.x = iter->UV0.x;
		}
		else
		{
			//U부분
			iter->UV0.x = (1.0f / _radPtc.frameMaxNumX)*((_radPtc.startFrameNum + (int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum)) % _radPtc.frameMaxNumX);
			iter->UV2.x = iter->UV0.x;
			iter->UV1.x = (1.0f / _radPtc.frameMaxNumX)*((_radPtc.startFrameNum + (int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum)) % _radPtc.frameMaxNumX + 1);
			iter->UV3.x = iter->UV1.x;
		}

		if (_radPtc.reverseImgV_On)
		{

			//반전V
			iter->UV2.y = (1.0f / _radPtc.frameMaxNumY)*(((_radPtc.startFrameNum + 1) / _radPtc.frameMaxNumX) + ((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.useFrameMaxNumY)));
			iter->UV3.y = iter->UV2.y;
			iter->UV0.y = (1.0f / _radPtc.frameMaxNumY)*(((_radPtc.startFrameNum + 1) / _radPtc.frameMaxNumX) + ((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.useFrameMaxNumY + 1)));
			iter->UV1.y = iter->UV0.y;

		}
		else
		{
			//V부분
			iter->UV0.y = (1.0f / _radPtc.frameMaxNumY)*(((_radPtc.startFrameNum + 1) / _radPtc.frameMaxNumX) + ((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.useFrameMaxNumY)));
			iter->UV1.y = iter->UV0.y;
			iter->UV2.y = (1.0f / _radPtc.frameMaxNumY)*(((_radPtc.startFrameNum + 1) / _radPtc.frameMaxNumX) + ((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.useFrameMaxNumY + 1)));
			iter->UV3.y = iter->UV2.y;
		}


	}
}


//====================================================================
//			## 텍스쳐 Wrap 모드 ##
//====================================================================
//반복적으로 나온다 1 넘어가는 UV 좌표는 1을 빼서 다시 0부터 시작
//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

////반복적으로 반전 나온다 1넘어가는 UV 좌표는 1부터 0으로 빠지고 0이하로 빠지면 다시 1을 향하여 증가
//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
//
////머리끄댕기 땡기듯 1 넘어가는 UV 좌표는 싸그리 1로 생각한다
//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
//
////머리끄댕기 땡기듯 1넘어가는 UV좌표 세팅된 보더 컬러로 칠한다
//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
////UV 좌표가 1 넘어갔을때 그릴 색상설정
//_device->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0xffff00ff); 
