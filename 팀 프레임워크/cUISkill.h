#pragma once
#include "cDxImgUI.h"

class cUISkill : public cDxImgUI
{
	SYNTHESIZE(cDxImg*, m_pOffImg, OffImg);			//스킬 쿨타임일때 이미지(흑백)
	SYNTHESIZE(float, m_fSkillMaxX, SkillMaxX);		//스킬흑백 이미지 가로 길이
	SYNTHESIZE(float, m_fSkillMaxY, SkillMaxY);		//스킬흑백 이미지 세로 길이
	SYNTHESIZE(float, m_fSkillGauge, SkillGauge);	//쿨타임 게이지
	SYNTHESIZE(float, m_fSkillCool, SkillCool);		//쿨타임 차는 속도
	SYNTHESIZE(bool, m_isCoolTime, IsCoolTime);		//쿨타임
	SYNTHESIZE(bool, m_isOnSkill, IsOnSkill);		//스킬을 사용했는지
	SYNTHESIZE(int, m_nSkillKey, SkillKey);			//어떤 키로 스킬을 사용할 건지
	SYNTHESIZE(bool, m_isSkillCool, IsSkillCool);	//쿨타임 중인지
	SYNTHESIZE(cDxImg*, m_pCoolTimeImg, CoolTimeImg);	//쿨타임 경고 이미지
	SYNTHESIZE(int, m_nCoolAlpha, CoolAlpha);			//쿨타임경고 이미지 알파값

	SYNTHESIZE(int,n,N);
	
public:
	cUISkill(string sUIon, string sUIoff, float posX, float posY, bool isCenter);
	cUISkill(string sUIon, string sUIoff,string sCool, int nSkillKey, float posX, float posY, bool isCenter);
	virtual ~cUISkill();

	virtual void update();
	virtual void render();

	void changePos(float x, float y, bool isCenter = false);
};

