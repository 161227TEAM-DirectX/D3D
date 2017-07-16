#pragma once
#include "monster.h"

class bossMonster : public monster
{
private:
	dx::transform rightTrans;
	dx::transform leftTrans;
	dx::transform fieldTrans;
	dx::transform tailTrans;
	dx::transform breathTrans;
	dx::transform oxPattern;
private:
	cDxImgBar* m_pBar;

public:
	bossMonster();
	~bossMonster();

	//override�� �ʿ��ϸ� ������ �ؼ� ����ϱ�
	void baseObjectEnable() override;			//BaseObject�� Ȱ��ȭ �ɶ� ����
	void baseObjectDisable() override;			//BaseObject�� ��Ȱ��ȭ �ɶ� ����
	void baseObjectUpdate() override;			//BaseObject�� Update �� ����
	void baseObjectNoActiveUpdate() override;	//BaseObject�� ��Ȱ��ȭ�� ������Ʈ ����
	void baseObjectRender() override;			//BaseObject�� �׸��� ����

	void switchState(void);
	void testKeyAI(void);

	inline dx::transform& getrightTrans(void) { return rightTrans; }
	inline void setrightTrans(dx::transform& temp) { this->rightTrans = temp; }

	inline dx::transform& getleftTrans(void) { return leftTrans; }
	inline void setleftTrans(dx::transform& temp) { this->leftTrans = temp; }

	inline dx::transform& getfieldTrans(void) { return fieldTrans; }
	inline void setfieldTrans(dx::transform& temp) { this->fieldTrans = temp; }

	inline dx::transform& gettailTrans(void) { return tailTrans; }
	inline void settailTrans(dx::transform& temp) { this->tailTrans = temp; }

	inline dx::transform& getbreathTrans(void) { return breathTrans; }
	inline void setbreathTrans(dx::transform& temp) { this->breathTrans = temp; }

	inline dx::transform& getOXPattern(void) { return oxPattern; }
	inline void setOXPattern(dx::transform& temp) { this->oxPattern = temp; }
};

