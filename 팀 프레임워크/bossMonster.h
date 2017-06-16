#pragma once
#include "monster.h"
//class bossActionControl;
class bossMonster : public monster
{
private:
	int Frequency;								//빈도율
//	bossActionControl* control;
public:
	bossMonster();
	~bossMonster();

	//override로 필요하면 재정의 해서 사용하기
	void baseObjectEnable() override;			//BaseObject가 활성화 될때 실행
	void baseObjectDisable() override;			//BaseObject가 비활성화 될때 실행
	void baseObjectUpdate() override;			//BaseObject가 Update 때 실행
	void baseObjectNoActiveUpdate() override;	//BaseObject가 비활성화시 업데이트 실행
	void baseObjectRender() override;			//BaseObject를 그릴때 실행

	void switchState(void);
};

