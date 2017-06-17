#pragma once
#include "baseObject.h"
#include "Action.h"
#include "ActionAttack.h"
#include "ActionDie.h"
#include "ActionMove.h"
#include "ActionReMove.h"
#include "ActionSeq.h"
#include "ActionStanding.h"
#include "terrain.h"

const int MAXHM = 40000;
const int MINHM = 10000;
const int MAXGS = 10000;
const int MINGS = 500;
const int DEFAULTATT = 200;
const int DEFAULTDEF = 50;
const float RANGE = 50.0f;
const float BOSSRANGE = 45.0f;

class monster : public baseObject
{
private:
protected:
	int HP;										//ü��
	int gold;									//��
	int soul;									//�ҿ� - ���͸� ��Ƽ� ������ Ư�� ����
	int att;									//���ݷ�
	int def;									//����
	int mana;									//����
	D3DXVECTOR3 regenPosition;					//���� ��ġ ��ġ - ���Ͱ� �ٽ� ���Ǵ� ��ġ
	boundBox range;								//Ž������
	boundBox hitBox;							//���ݿ�Ž���ڽ�
	LHS::ACTIONRESULT result;					//�׼��� ���� �Է°�
protected:
	Action*					CurrAction;				//���� Ȱ��ȭ�� �ൿ Ŭ����
	Action*					NextAction;				//���� Ȱ��ȭ�� �ൿ Ŭ����
public:
	monster();
	virtual ~monster();

	inline int& getHP(void) { return HP; }
	inline void setHP(const int& temp) { HP = temp; }

	inline int& getGold(void) { return gold; }
	inline void setGold(const int& temp) { gold = temp; }

	inline int& getSoul(void) { return soul; }
	inline void setSoul(const int& temp) { soul = temp; }

	inline int& getAtt(void) { return att; }
	inline void setAtt(const int& temp) { att = temp; }

	inline int& getDef(void) { return def; }
	inline void setDef(const int& temp) { def = temp; }

	inline int& getMana(void) { return mana; }
	inline void setMana(const int& temp) { mana = temp; }

	inline D3DXVECTOR3& getRegenPosition(void) { return regenPosition; }
	inline void setRegenPosition(const D3DXVECTOR3& temp) { this->regenPosition = temp; }
	inline void setRegenPosition(const float& x, const float& y, const float& z) { setRegenPosition(D3DXVECTOR3(x, y, z)); }

	inline boundBox& getRange(void) { return range; }
	inline boundBox& getHitBox(void) { return hitBox; }

	inline LHS::ACTIONRESULT& getResult(void) { return result; }

	//override�� �ʿ��ϸ� ������ �ؼ� ����ϱ�
 	virtual void baseObjectEnable() override;			//BaseObject�� Ȱ��ȭ �ɶ� ����
	virtual void baseObjectDisable() override;			//BaseObject�� ��Ȱ��ȭ �ɶ� ����
	virtual void baseObjectUpdate() override;			//BaseObject�� Update �� ����
	virtual void baseObjectNoActiveUpdate() override;	//BaseObject�� ��Ȱ��ȭ�� ������Ʈ ����
	virtual void baseObjectRender() override;			//BaseObject�� �׸��� ����

	void stateSwitch(void);
};

