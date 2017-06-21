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
	//애니메이션 세팅
	void InitAnimation(int inFrameMaxX, int inFrameMaxY, int inTotalFrame)
	{
		_radPtc.animationOn = true;
		_radPtc.frameMaxNumX = inFrameMaxX;
		_radPtc.frameMaxNumY = inFrameMaxY;
		_radPtc.useFrameMaxNumY = _radPtc.frameMaxNumY;
		_radPtc.totalFrameNum = inTotalFrame;
		if (inTotalFrame == 0) { _radPtc.totalFrameNum = inFrameMaxX*inFrameMaxY; }
	};
	//애니메이션 재생수
	void InitConstAniReactivateNum(int inReactiveateNum) { _radPtc.reactivateNum = inReactiveateNum; };

	//애니메이션 재생구간
	void InitAniPlaySection(int inStartFrameNum, int inEndFrameNum)
	{
		_radPtc.startFrameNum = inStartFrameNum;
		_radPtc.endFrameNum = inEndFrameNum;	//1더하기는 개수를 위해
	};

	//void InitStartAnimation(int startFrameX, int startFrameY, bool reverseOn = FALSE) {};

public:
	dxUVModule() {};
	~dxUVModule() {};
};

