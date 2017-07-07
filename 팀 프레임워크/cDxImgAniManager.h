#pragma once

#define DXIMGANI_MANAGER cDxImgAniManager::GetInstance()

class cDxImg;

class cDxImgAniManager
{
	SINGLETONE(cDxImgAniManager);

private:
	map<string, vector<cDxImg*>>	m_mapDxImgAni;		//애니메이션 이미지
	map<string, ST_DXIMGANI>		m_mapDxImgST;		//애니메이션 돌릴 구조체
	map<string, bool>				m_mapDxAniIsOnce;	//애니메이션을 한번만 돌릴 건지

public:
	bool AddDxImgAni(string sKey,
					 vector<cDxImg*> dxImg,
					 ST_DXIMGANI dxImgAni,
					 D3DXVECTOR2 vPos ={ WINSIZEX / 2,WINSIZEY / 2 },
					 bool isCenter = true);

	void setDxImgAniPosition(string sKey, D3DXVECTOR2 vecPos);
	void setDxAniIsOnce(string sKey, bool isOnce);

	vector<cDxImg*> GetDxImgAni(string sKey);
	int getSize() { return m_mapDxImgAni.size(); }

	void render(string sKey);
};

