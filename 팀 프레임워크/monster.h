#pragma once
#include "Action.h"
#include "Text.h"

const int MAXHM = 40000;
const int MINHM = 10000;
const int MAXGS = 10000;
const int MINGS = 500;
const int MAXATT = 300;
const int MINATT = 50;
const int MAXDEF = 200;
const int MINDEF = 50;
const float RANGE = 5.0f;
const float BOSSRANGE = 2.5f;

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
	int dieCount;								//�װ� ���� �ٽ� �¾�� ���� �ð�
	int startTime;								//���� �ð�
	D3DXVECTOR3 regenPosition;					//���� ��ġ ��ġ - ���Ͱ� �ٽ� ���Ǵ� ��ġ
	boundBox range;								//Ž������
	boundBox hitBox;							//���ݿ�Ž���ڽ�
	LHS::ACTIONRESULT result;					//�׼��� ���� �Է°�
	Text*	name;								//������ �̸�
	string	prefixName;							//���� ���λ�
	string	lastName;							//���� �̸�
	D3DXCOLOR nameColor;						//���� �̸� �÷�

protected:
	Action*					CurrAction;				//���� Ȱ��ȭ�� �ൿ Ŭ����
	Action*					NextAction;				//���� Ȱ��ȭ�� �ൿ Ŭ����
public:
//	monster();
	monster(string Name = "�̸����Է����ּ���");
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

	inline Text& getText(void) { return *name; }

	//override�� �ʿ��ϸ� ������ �ؼ� ����ϱ�
 	virtual void baseObjectEnable() override;			//BaseObject�� Ȱ��ȭ �ɶ� ����
	virtual void baseObjectDisable() override;			//BaseObject�� ��Ȱ��ȭ �ɶ� ����
	virtual void baseObjectUpdate() override;			//BaseObject�� Update �� ����
	virtual void baseObjectNoActiveUpdate() override;	//BaseObject�� ��Ȱ��ȭ�� ������Ʈ ����
	virtual void baseObjectRender() override;			//BaseObject�� �׸��� ����

	//���� �з� �Լ�
	void stateSwitch(void);
	// Ư�� ��Ī �ο� �Լ�
	void authorizeName(void);
};

