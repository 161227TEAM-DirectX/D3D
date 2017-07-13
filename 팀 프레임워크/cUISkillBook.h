#pragma once
class cUISkillBook
{
	SYNTHESIZE(string, m_sSkillBook, SkillBook); //���� �ִϸ��̼� �̸�
	SYNTHESIZE(bool, m_isAct, IsAct);			 //��ų���� �۵��ϴ���
	SYNTHESIZE(int, m_nCount, Count);			 //��ų�� ī��Ʈ
	SYNTHESIZE(int, m_nMaxCount, MaxCount);		 //��ų�� �ƽ�ī��Ʈ
	SYNTHESIZE(int, m_nActStart, ActStart);		 //�ִ� ���� ������
	SYNTHESIZE(int, m_nActEnd, ActEnd);			 //�ִ� ���� ������
	SYNTHESIZE(int, m_nPosX, PosX);				 //��ų�� ��ġX
	SYNTHESIZE(int, m_nPosY, PosY);				 //��ų�� ��ġY

	vector<cDxImg*>	m_vecSkill;

public:
	cUISkillBook(string sSkillBook);
	~cUISkillBook();

	void update();
	void render();
};

