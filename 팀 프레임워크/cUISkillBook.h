#pragma once
class cUISkillBook
{
	SYNTHESIZE(string, m_sSkillBook, SkillBook); //돌릴 애니메이션 이름
	SYNTHESIZE(bool, m_isAct, IsAct);			 //스킬북이 작동하는지
	SYNTHESIZE(int, m_nCount, Count);			 //스킬북 카운트
	SYNTHESIZE(int, m_nMaxCount, MaxCount);		 //스킬북 맥스카운트
	SYNTHESIZE(int, m_nActStart, ActStart);		 //애니 시작 프레임
	SYNTHESIZE(int, m_nActEnd, ActEnd);			 //애니 종료 프레임
	SYNTHESIZE(int, m_nPosX, PosX);				 //스킬북 위치X
	SYNTHESIZE(int, m_nPosY, PosY);				 //스킬북 위치Y

	vector<cDxImg*>	m_vecSkill;

public:
	cUISkillBook(string sSkillBook);
	~cUISkillBook();

	void update();
	void render();
};

