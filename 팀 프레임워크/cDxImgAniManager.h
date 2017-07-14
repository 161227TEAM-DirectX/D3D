#pragma once

#define DXIMGANI_MANAGER cDxImgAniManager::GetInstance()

class cDxImg;

class cDxImgAniManager
{
	SINGLETONE(cDxImgAniManager);

private:
	map<string, vector<cDxImg*>>	m_mapDxImgAni;			//애니메이션 이미지
	map<string, ST_DXIMGANI>		m_mapDxImgST;			//애니메이션 구조체
	map<string, int>				m_mapDxImgNum;			//중복 애니메이션 개수

public:
	bool AddDxImgAni(string sKey,
					 vector<cDxImg*> dxImg,
					 ST_DXIMGANI dxImgAni,
					 D3DXVECTOR2 vPos ={ WINSIZEX / 2,WINSIZEY / 2 },
					 bool isCenter = true);

	void setDxImgAniPosition(string sKey, D3DXVECTOR2 vecPos);

	void setDxAniTime(string sKey, int aniTime);
	void setDxAniIsOnce(string sKey, bool isOnce);
	void setDxAniIsReverse(string sKey, bool isReverse);
	void setDxAniIsSection(string sKey, bool isSection, int start, int end);
	void setDxAniType(string sKey, eAniState aniType);

	ST_DXIMGANI getDxAniST(string sKey);
	vector<cDxImg*> GetDxImgAni(string sKey);

	inline int getSize()const { return m_mapDxImgAni.size(); }	//애니메이션 총 몇개 들어있는지

																//중복 애니메이션
	inline void setAniOverlap(string sKey) { m_mapDxImgNum[sKey]+=1; }	//중복 개수 증가
	int getAniSize(string sKey);	//특정 애니메이션의 중복 개수는?


	void render(string sKey);
};

