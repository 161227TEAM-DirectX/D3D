#pragma once
#include "monster.h"
//class bossActionControl;
class bossMonster : public monster
{
private:
	int Frequency;								//����
//	bossActionControl* control;
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
};

