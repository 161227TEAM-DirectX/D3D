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

	inline D3DXVECTOR3& getPos(void) { return pos; }
	inline void setPos(const D3DXVECTOR3& temp) { this->pos = temp; }

	void init(string str);
	void update(void);
	void render(void);
};

