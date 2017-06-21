#pragma once
class Text
{
protected:
	D3DXVECTOR3			pos;
	D3DXMATRIX			matBillBoard;
	LPD3DXMESH			str;
	int					strLength;
public:
	Text();
	~Text();

	void init(string str);
	void update(void);
	void render(void);
};

