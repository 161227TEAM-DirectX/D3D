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
	//�̰��� �ִϸ��̼��� ���� ������ �ƴϴ�. ���� �������� ������ ������ �ʿ����!!!(�������� ���´�!!!)


	//0----1
	//|   /|
	//|  / |
	//| /  |
	//|/   |
	//2----3

	//�̰� ����Ѵٰ� �İ��ߴ�...
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



	//�ִϸ��̼� ���ۺκ� ����κ� ���� ����
	if (_radPtc.aniSectionOn)
	{
		//U��꿡 �ʿ�
		_radPtc.totalFrameNum = (_radPtc.endFrameNum - _radPtc.startFrameNum) + 1; 
		//V��꿡 �ʿ�
		_radPtc.useFrameMaxNumY = (_radPtc.endFrameNum + _radPtc.frameMaxNumX) / _radPtc.frameMaxNumX - _radPtc.startFrameNum / _radPtc.frameMaxNumX;
	}

	//if (_radPtc.animationOn)
	//{
	//	//U�κ�
	//	iter->UV0.x = (1.0f / _radPtc.frameMaxNumX)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum) % _radPtc.frameMaxNumX);
	//	iter->UV2.x = iter->UV0.x;
	//	iter->UV1.x = (1.0f / _radPtc.frameMaxNumX)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum) % _radPtc.frameMaxNumX + 1);
	//	iter->UV3.x = iter->UV1.x;

	//	//V�κ�
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
		////U�κ�
		//iter->UV0.x = (1.0f / _radPtc.frameMaxNumX)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum) % _radPtc.frameMaxNumX);
		//iter->UV2.x = iter->UV0.x;
		//iter->UV1.x = (1.0f / _radPtc.frameMaxNumX)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum) % _radPtc.frameMaxNumX + 1);
		//iter->UV3.x = iter->UV1.x;

		////V�κ�
		//iter->UV0.y = (1.0f / _radPtc.frameMaxNumY)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.frameMaxNumY));
		//iter->UV1.y = iter->UV0.y;
		//iter->UV2.y = (1.0f / _radPtc.frameMaxNumY)*((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.frameMaxNumY + 1));
		//iter->UV3.y = iter->UV2.y;

		//�ִϸ��̼� ���ۺκа� ����κ� ����

	/*	_radPtc.startFrameNum = 1;
		_radPtc.endFrameNum = 2;
		_radPtc.totalFrameNum = (_radPtc.endFrameNum - _radPtc.startFrameNum) + 1;
		_radPtc.useFrameMaxNumY = (_radPtc.endFrameNum + _radPtc.frameMaxNumX) / _radPtc.frameMaxNumX - _radPtc.startFrameNum / _radPtc.frameMaxNumX;*/

		if (_radPtc.reverseImgU_On)
		{
			//����U
			iter->UV1.x = (1.0f / _radPtc.frameMaxNumX)*((_radPtc.startFrameNum + (int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum)) % _radPtc.frameMaxNumX);
			iter->UV3.x = iter->UV1.x;
			iter->UV0.x = (1.0f / _radPtc.frameMaxNumX)*((_radPtc.startFrameNum + (int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum)) % _radPtc.frameMaxNumX + 1);
			iter->UV2.x = iter->UV0.x;
		}
		else
		{
			//U�κ�
			iter->UV0.x = (1.0f / _radPtc.frameMaxNumX)*((_radPtc.startFrameNum + (int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum)) % _radPtc.frameMaxNumX);
			iter->UV2.x = iter->UV0.x;
			iter->UV1.x = (1.0f / _radPtc.frameMaxNumX)*((_radPtc.startFrameNum + (int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum)) % _radPtc.frameMaxNumX + 1);
			iter->UV3.x = iter->UV1.x;
		}

		if (_radPtc.reverseImgV_On)
		{

			//����V
			iter->UV2.y = (1.0f / _radPtc.frameMaxNumY)*(((_radPtc.startFrameNum + 1) / _radPtc.frameMaxNumX) + ((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.useFrameMaxNumY)));
			iter->UV3.y = iter->UV2.y;
			iter->UV0.y = (1.0f / _radPtc.frameMaxNumY)*(((_radPtc.startFrameNum + 1) / _radPtc.frameMaxNumX) + ((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.useFrameMaxNumY + 1)));
			iter->UV1.y = iter->UV0.y;

		}
		else
		{
			//V�κ�
			iter->UV0.y = (1.0f / _radPtc.frameMaxNumY)*(((_radPtc.startFrameNum + 1) / _radPtc.frameMaxNumX) + ((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.useFrameMaxNumY)));
			iter->UV1.y = iter->UV0.y;
			iter->UV2.y = (1.0f / _radPtc.frameMaxNumY)*(((_radPtc.startFrameNum + 1) / _radPtc.frameMaxNumX) + ((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.useFrameMaxNumY + 1)));
			iter->UV3.y = iter->UV2.y;
		}


	}
}


//====================================================================
//			## �ؽ��� Wrap ��� ##
//====================================================================
//�ݺ������� ���´� 1 �Ѿ�� UV ��ǥ�� 1�� ���� �ٽ� 0���� ����
//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

////�ݺ������� ���� ���´� 1�Ѿ�� UV ��ǥ�� 1���� 0���� ������ 0���Ϸ� ������ �ٽ� 1�� ���Ͽ� ����
//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
//
////�Ӹ������ ����� 1 �Ѿ�� UV ��ǥ�� �α׸� 1�� �����Ѵ�
//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
//
////�Ӹ������ ����� 1�Ѿ�� UV��ǥ ���õ� ���� �÷��� ĥ�Ѵ�
//_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
//_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
////UV ��ǥ�� 1 �Ѿ���� �׸� ������
//_device->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0xffff00ff); 
