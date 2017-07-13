#pragma once

class cUIYouDied
{
	SYNTHESIZE(int, m_nAlpha, Alpha);
	SYNTHESIZE(int, m_nAlphaMax, AlphaMax);
	SYNTHESIZE(int, m_nAlphaSpeed,AlphaSpeed);
	SYNTHESIZE(bool, m_isDied, IsDied);

public:
	cUIYouDied();
	~cUIYouDied();

	void render();
};

