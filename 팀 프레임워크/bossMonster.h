#pragma once
#include "monster.h"
class bossMonster : public monster
{
private:
	int Frequency;								//����
	
	dx::transform rightTrans;
	dx::transform leftTrans;
	dx::transform fieldTrans;
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
};

