#pragma once

class cUICinema
{
private:
	float m_fCutscnGauge;		//�ƾ� ������
	float m_fCutscnMaxGauge;	//�ƾ� �ƽ�������(�������� ���� �����δ�.)
	float m_fCutscnSpeed;		//�ƾ� �ӵ�
	int   m_nCutscnDir;			//�ƾ� ����(���������� �ö󰡴���)

	float m_fCutscnUp;			//�� �ƾ����� �̹��� ������ǥ(y��)
	float m_fCutscnDown;		//�Ʒ� �ƾ����� �̹��� ������ǥ(y��)
	float m_fCutscnUpEnd;		//�� �ƾ����� �̹��� ����ǥ(y��)
	float m_fCutscnDownEnd;		//�Ʒ� �ƾ����� �̹��� ����ǥ(y��)

	vector<string> m_vecString;	//�ڸ��� ���پ� �����ϴ� ����
	int m_nStrCount;			//�ڸ� �ε���(���پ� �о�´�.)
	int m_nTimeCount;			//�̰ɷ� ��� m_nTimeMax�� ���ų� Ŀ���� ���� �ڸ�����
	int m_nTimeMax;				//ī��Ʈ �ƽ�

	bool m_isCutStart;			//�ƾ��� �����ߴ��� ����

public:
	cUICinema();
	~cUICinema();

	void init();
	void update();
	void render();
};

