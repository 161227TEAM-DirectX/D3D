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

		//U�κ�
		iter->UV0.x = (1.0f / _radPtc.frameMaxNumX)*((_radPtc.startFrameNum + (int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum)) % _radPtc.frameMaxNumX);
		iter->UV2.x = iter->UV0.x;
		iter->UV1.x = (1.0f / _radPtc.frameMaxNumX)*((_radPtc.startFrameNum + (int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.totalFrameNum)) % _radPtc.frameMaxNumX + 1);
		iter->UV3.x = iter->UV1.x;

		//V�κ�
		iter->UV0.y = (1.0f / _radPtc.frameMaxNumY)*(((_radPtc.startFrameNum + 1) / _radPtc.frameMaxNumX)+((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.useFrameMaxNumY)));
		iter->UV1.y = iter->UV0.y;
		iter->UV2.y = (1.0f / _radPtc.frameMaxNumY)*(((_radPtc.startFrameNum + 1) / _radPtc.frameMaxNumX)+((int)((iter->age / iter->lifeTime)*_radPtc.reactivateNum*_radPtc.useFrameMaxNumY + 1)));
		iter->UV3.y = iter->UV2.y;
	}
}
