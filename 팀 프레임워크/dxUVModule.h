#pragma once
#include "dxModule.h"
class dxUVModule :public dxModule
{
private:

public:
	virtual HRESULT init();
	virtual void relese();
	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);

public:
	//�ִϸ��̼� ����
	void InitAnimation(int inFrameMaxX, int inFrameMaxY, int inTotalFrame)
	{
		_radPtc.animationOn = true;
		_radPtc.frameMaxNumX = inFrameMaxX;
		_radPtc.frameMaxNumY = inFrameMaxY;
		_radPtc.useFrameMaxNumY = _radPtc.frameMaxNumY;
		_radPtc.totalFrameNum = inTotalFrame;
		if (inTotalFrame == 0) { _radPtc.totalFrameNum = inFrameMaxX*inFrameMaxY; }
	};
	//�ִϸ��̼� �����
	void InitConstAniReactivateNum(int inReactiveateNum) { _radPtc.reactivateNum = inReactiveateNum; };

	//�ִϸ��̼� �������
	void InitAniPlaySection(int inStartFrameNum, int inEndFrameNum)
	{
		_radPtc.aniSectionOn = true;
		_radPtc.startFrameNum = inStartFrameNum;
		_radPtc.endFrameNum = inEndFrameNum;	//1���ϱ�� ������ ����
	};

	//UV�̹��� ����
	void uvReverseImgU() { _radPtc.reverseImgU_On = true; };
	void uvReverseImgV() { _radPtc.reverseImgV_On = true; };

	//void InitStartAnimation(int startFrameX, int startFrameY, bool reverseOn = FALSE) {};

public:
	dxUVModule() {};
	~dxUVModule() {};
};

