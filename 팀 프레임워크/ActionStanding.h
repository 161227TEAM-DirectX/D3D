#pragma once
#include "Action.h"
#include "dijkstra.h"
#include "terrain.h"
#include "monster.h"

class ActionStanding : public Action
{
private:
	float PassedTime;
protected:
	float actionTime;
public:
	ActionStanding();
	virtual ~ActionStanding();

	inline float getActionTime(void) { return actionTime; }
	inline void setActionTime(float time) {
		this->actionTime = time;
	}

	void setTerrain(terrain* temp) { this->rand = temp; }

	virtual int Start() override;
	virtual int Update() override;
};

