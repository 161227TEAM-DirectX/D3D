#pragma once

#define DXIMGANI_MANAGER cDxImgAniManager::GetInstance()

class cDxImg;

class cDxImgAniManager
{
	SINGLETONE(cDxImgAniManager);

private:
	map<string, vector<cDxImg*>>	m_mapDxImgAni;			//�ִϸ��̼� �̹���
	map<string, ST_DXIMGANI>		m_mapDxImgST;			//�ִϸ��̼� ����ü
	map<string, int>				m_mapDxImgNum;			//�ߺ� �ִϸ��̼� ����

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

	inline int getSize()const { return m_mapDxImgAni.size(); }	//�ִϸ��̼� �� � ����ִ���

																//�ߺ� �ִϸ��̼�
	inline void setAniOverlap(string sKey) { m_mapDxImgNum[sKey]+=1; }	//�ߺ� ���� ����
	int getAniSize(string sKey);	//Ư�� �ִϸ��̼��� �ߺ� ������?


	void render(string sKey);
};

