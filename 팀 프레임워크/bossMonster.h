#pragma once
#include "monster.h"
class bossMonster : public monster
{
private:

public:
	bossMonster();
	~bossMonster();

	//override�� �ʿ��ϸ� ������ �ؼ� ����ϱ�
	virtual void baseObjectEnable() override;			//BaseObject�� Ȱ��ȭ �ɶ� ����
	virtual void baseObjectDisable() override;			//BaseObject�� ��Ȱ��ȭ �ɶ� ����
	virtual void baseObjectUpdate() override;			//BaseObject�� Update �� ����
	virtual void baseObjectNoActiveUpdate() override;	//BaseObject�� ��Ȱ��ȭ�� ������Ʈ ����
	virtual void baseObjectRender() override;			//BaseObject�� �׸��� ����
};

