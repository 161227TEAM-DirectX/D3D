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
	int HP;										//체력
	int gold;									//돈
	int soul;									//소울 - 몬스터를 잡아서 나오는 특수 숫자
	int att;									//공격력
	int def;									//방어력
	int mana;									//마력
	int dieCount;								//죽고 나서 다시 태어나기 위한 시간
	int startTime;								//죽은 시간
	D3DXVECTOR3 regenPosition;					//최초 설치 위치 - 몬스터가 다시 젠되는 위치
	boundBox range;								//탐색범위
	boundBox hitBox;							//공격용탐색박스
	LHS::ACTIONRESULT result;					//액션을 위한 입력값
	Text*	name;								//몬스터의 이름
	string	prefixName;							//몬스터 접두사
	string	lastName;							//몬스터 이름
	D3DXCOLOR nameColor;						//몬스터 이름 컬러

protected:
	Action*					CurrAction;				//현재 활성화된 행동 클래스
	Action*					NextAction;				//다음 활성화될 행동 클래스
public:
//	monster();
	monster(string Name = "이름을입력해주세요");
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

	//override로 필요하면 재정의 해서 사용하기
 	virtual void baseObjectEnable() override;			//BaseObject가 활성화 될때 실행
	virtual void baseObjectDisable() override;			//BaseObject가 비활성화 될때 실행
	virtual void baseObjectUpdate() override;			//BaseObject가 Update 때 실행
	virtual void baseObjectNoActiveUpdate() override;	//BaseObject가 비활성화시 업데이트 실행
	virtual void baseObjectRender() override;			//BaseObject를 그릴때 실행

	//상태 분류 함수
	void stateSwitch(void);
	// 특수 명칭 부여 함수
	void authorizeName(void);
};

