#pragma once
class damageText
{
private:
	D3DXVECTOR3			pos;
	D3DXMATRIX			matBillBoard;
	LPD3DXMESH			str;
	LHS::FONTCOLOR		color;
private:
	string				nameStr;
	int					strLength;
public:
	damageText();
	~damageText();

	inline D3DXVECTOR3& getPos(void) { return pos; }
	inline void setPos(const D3DXVECTOR3& temp) { this->pos = temp; }

	inline string& getName(void) { return nameStr; }
	inline int& getStrLength(void) { return strLength; }

	void init(int damage, LHS::FONTCOLOR color);
	void update(void);
	void render(void);
};

