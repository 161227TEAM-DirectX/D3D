#pragma once

class cUICinema
{
private:
	float m_fCutscnGauge;		//컷씬 게이지
	float m_fCutscnMaxGauge;	//컷씬 맥스게이지(높을수록 많이 움직인다.)
	float m_fCutscnSpeed;		//컷씬 속도
	int   m_nCutscnDir;			//컷씬 방향(내려오는지 올라가는지)

	float m_fCutscnUp;			//위 컷씬검정 이미지 시작좌표(y축)
	float m_fCutscnDown;		//아래 컷씬검정 이미지 시작좌표(y축)
	float m_fCutscnUpEnd;		//위 컷씬검정 이미지 끝좌표(y축)
	float m_fCutscnDownEnd;		//아래 컷씬검정 이미지 끝좌표(y축)

	vector<string> m_vecString;	//자막을 한줄씩 저장하는 벡터
	int m_nStrCount;			//자막 인덱스(한줄씩 읽어온다.)
	int m_nTimeCount;			//이걸로 세어서 m_nTimeMax와 같거나 커지면 다음 자막으로
	int m_nTimeMax;				//카운트 맥스

	bool m_isCutStart;			//컷씬이 시작했는지 여부

public:
	cUICinema();
	~cUICinema();

	void init();
	void update();
	void render();
};

