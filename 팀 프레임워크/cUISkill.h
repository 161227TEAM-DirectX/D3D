#pragma once
#include "cDxImgUI.h"

class cUISkill : public cDxImgUI
{
	SYNTHESIZE(cDxImg*, m_pOffImg, OffImg);			//��ų ��Ÿ���϶� �̹���(���)
	SYNTHESIZE(float, m_fSkillMaxX, SkillMaxX);		//��ų��� �̹��� ���� ����
	SYNTHESIZE(float, m_fSkillMaxY, SkillMaxY);		//��ų��� �̹��� ���� ����
	SYNTHESIZE(float, m_fSkillGauge, SkillGauge);	//��Ÿ�� ������
	SYNTHESIZE(float, m_fSkillCool, SkillCool);		//��Ÿ�� ���� �ӵ�
	SYNTHESIZE(bool, m_isCoolTime, IsCoolTime);		//��Ÿ��
	SYNTHESIZE(bool, m_isOnSkill, IsOnSkill);		//��ų�� ����ߴ���
	SYNTHESIZE(int, m_nSkillKey, SkillKey);			//� Ű�� ��ų�� ����� ����
	SYNTHESIZE(bool, m_isSkillCool, IsSkillCool);	//��Ÿ�� ������
	SYNTHESIZE(cDxImg*, m_pCoolTimeImg, CoolTimeImg);	//��Ÿ�� ��� �̹���
	SYNTHESIZE(int, m_nCoolAlpha, CoolAlpha);			//��Ÿ�Ӱ�� �̹��� ���İ�

	SYNTHESIZE(int,n,N);
	
public:
	cUISkill(string sUIon, string sUIoff, float posX, float posY, bool isCenter);
	cUISkill(string sUIon, string sUIoff,string sCool, int nSkillKey, float posX, float posY, bool isCenter);
	virtual ~cUISkill();

	virtual void update();
	virtual void render();

	void changePos(float x, float y, bool isCenter = false);
};

