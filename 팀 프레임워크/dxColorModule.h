#pragma once
#include "dxModule.h"
class dxColorModule : public dxModule
{
private:
	//색
	vector<tagDxGraph*> _grpColorR;
	vector<tagDxGraph*> _grpColorG;
	vector<tagDxGraph*> _grpColorB;
	bool _grpColorR_On;
	bool _grpColorG_On;
	bool _grpColorB_On;

	//알파
	vector<tagDxGraph*> _grpAlpha;
	bool _grpAlphaOn;

public:
	virtual HRESULT init();
	virtual void relese();
	//virtual void InitUpdate(list<tagDxAttribute>::iterator iter);
	//virtual void ActiveUpdate(list<tagDxAttribute>::iterator iter);

	virtual void InitUpdate(vector<tagDxAttribute>::iterator iter);
	virtual void ActiveUpdate(vector<tagDxAttribute>::iterator iter);
public:
	//초기색
	void InitRandomColorR(float min, float max) { _radPtc.colorInitR = tagMaxMin(min, max); _radPtc.radColorOn = true; }
	void InitRandomColorG(float min, float max) { _radPtc.colorInitG = tagMaxMin(min, max); _radPtc.radColorOn = true; }
	void InitRandomColorB(float min, float max) { _radPtc.colorInitB = tagMaxMin(min, max); _radPtc.radColorOn = true; }

	//소멸색
	void InitRandomColorFadeR(float min, float max) { _radPtc.colorFadeR = tagMaxMin(min, max); _radPtc.radColorFadeOn = true; }
	void InitRandomColorFadeG(float min, float max) { _radPtc.colorFadeG = tagMaxMin(min, max); _radPtc.radColorFadeOn = true; }
	void InitRandomColorFadeB(float min, float max) { _radPtc.colorFadeB = tagMaxMin(min, max); _radPtc.radColorFadeOn = true; }

	//색 그래프
	void addColorGraphR(float point, float min, float max) { GraphCheck(_grpColorR, point, min, max); _grpColorR_On = true; }
	void addColorGraphG(float point, float min, float max) { GraphCheck(_grpColorG, point, min, max); _grpColorG_On = true; }
	void addColorGraphB(float point, float min, float max) { GraphCheck(_grpColorB, point, min, max); _grpColorB_On = true; }

	//알파 초기 및 소멸
	void InitRandomAlpha(float min, float max) { _radPtc.alphaInit = tagMaxMin(min, max); _radPtc.radAlphaInitOn = true; }
	void InitRandomAlphaFade(float min, float max) { _radPtc.alphaFade = tagMaxMin(min, max); _radPtc.radAlphaFadeOn = true; }

	//알파 그래프
	void addAlphaGraph(float point, float min, float max) { GraphCheck(_grpAlpha, point, min, max); _grpAlphaOn = true; }

public:
	dxColorModule() {};
	~dxColorModule() {};
};

