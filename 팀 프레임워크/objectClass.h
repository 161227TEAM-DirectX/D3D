#pragma once
#include "iGameNode.h"

#define NUMBER 188  //오브젝트수

enum objectUi { OBJOFF = 0, OBJON };

struct OBJECTUI
{
	LPDIRECT3DTEXTURE9 tex;
	RECT rc1, rc2, rc3;
	int uiNumber;
};

class objectClass : public iGameNode
{
private:
	vector<baseObject*> _object;
	vector<light*> _light;

private:
	OBJECTUI _build[NUMBER];
	int numberObject;       //오브젝트넘버

public:
	objectClass();
	~objectClass();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void){}
	void render(camera* camera);

	void objectUp(POINT mouse, int arrayS, int arrayE);
	void storm1();
	void storm2();
	void storm3();
	void storm4();
	void storm5();

	void storm6();
	void storm7();
	void storm8();
	void storm9();
	void storm10();

	void ruinstage1();
	void ruinstage2();
	void ruinstage3();
	void ruinstage4();
	void ruinstage5();
	void ruinstage6();
	void ruinstage7();

	void piramid1();
	void piramid2();
	void piramid3();
	void piramid4();


	int getnumberObject(void) { return numberObject; }
	vector<baseObject*> getObject(void) { return _object; }
	OBJECTUI* getOBJECTUL(void) { return _build; }

};

