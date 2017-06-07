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
		_radPtc.totalFrameNum = inTotalFrame;
		if (inTotalFrame == 0) { _radPtc.totalFrameNum = inFrameMaxX*inFrameMaxY; }
	};
	//애니메이션 재생수
	void InitConstAniReactivateNum(int inReactiveateNum) { _radPtc.reactivateNum = inReactiveateNum; };


	//void InitStartAnimation(int startFrameX, int startFrameY, bool reverseOn = FALSE) {};

public:
	dxUVModule() {};
	~dxUVModule() {};
};

