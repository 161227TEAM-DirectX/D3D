#pragma once
class damageText
{
private:
	D3DXVECTOR3			pos;
	D3DXMATRIX			matBillBoard;
	LPD3DXMESH			str;
	string				nameStr;
	int					strLength;
public:
	damageText();
	~damageText();

	inline D3DXVECTOR3& getPos(void) { return pos; }
	inline void setPos(const D3DXVECTOR3& temp) { this->pos = temp; }

	inline string& getName(void) { return nameStr; }

	void init(string str, D3DXCOLOR color);
	void update(void);
	void render(void);
};

