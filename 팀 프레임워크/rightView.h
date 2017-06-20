#pragma once
#include "iGameNode.h"

#define DEFENV 6   //물하단메뉴 오브젝트수      
#define DEFTER 6   //지형하단메뉴 오브젝트수  

class objectClass;
class rightSmallGrid;

//상단 메뉴
enum UISTAGE { UIOFF = 0, UION };
//오브젝트 중단메뉴
enum OBSTAGE { STORMTOWN1 =1, STROMTOWN2, RUINSTAGE, PIRAMID };
//오브젝트 하단메뉴
enum OBSTAGEDOWN { ONEOFF = 1, TWOOFF, THREEOFF };
//환경 중단메뉴
enum ENVSTAGE { WATERMIDDLE = 1, SKYMIDDLE ,NODEINSTAL,NODELINK,MONSTER };
//지형 중단메뉴
enum TERSTAGE { TILEMAP1 =1, TILEMAP2,TILEMAP3,TILEMAP4,SPLAT,TERRAWMAP,TERHEIGHT };
//UI컨트롤 메뉴
enum CONTROL { CONTROLOFF = 0, CONTROLLEFT, CONTROLRIGHT };

struct UI
{
	LPDIRECT3DTEXTURE9 tex;
	RECT rc1, rc2, rc3;
	int uiNumber;
};


class rightView : public iGameNode
{
private:
	
	//작은 그리드
	rightSmallGrid* _rightSmallGrid;
	//오브젝트
	objectClass* _objectClass;
	camera		 _mainCamera;

public:
	//예시
	UI _ObjectButton[6];

	//변화가없는 UI
	UI _UIBACK;
	UI _UIkind;
	UI _UIsize[2];
	UI _UIcontrol[2];
	UI _UIsizeHeight[2];
	UI _UInodeHeight[2];

	//상단메뉴
	UI _TOPbutton[3];

	//중단메뉴
	UI _OBJbutton;
	UI _ENVbutton;
	UI _TERRIANbutton;

	//조절 메뉴
	UI _heightContorol[2];
	UI _nodeInstalContorol[2];
	UI _nodeLinkContorol[2];

	//오브하단 메뉴
	UI _OBJstorm1Button[5];
	UI _OBJGO;
	UI _OBJback;
	UI _OBJstorm2Button[5];
	UI _OBJruinButton[7];
	UI _OBJpiramidButton[4];

	//환경하단 메뉴
	UI _ENVwaterButton[DEFENV];
	UI _ENVskyButton[DEFENV];

	//지형하단 메뉴
	UI _NumberTile1Button[DEFTER];
	UI _NumberTile2Button[DEFTER];
	UI _NumberTile3Button[DEFTER];
	UI _NumberTile4Button[DEFTER];
	UI _NumberSplatButton[DEFTER];
	UI _NumberRawButton[DEFTER];

private:
	UI _plus;
	UI _minus;

private:
	//일시적인 마우스 
	POINT mouse;

private:
	float scaleNumber;       //스케일 조정 넘버
	int numberEnv;           //환경맵  넘버
	int numberwater;         //물 넘버
	int numberHeight;        //높이 넘버
	int numberObject;        //오브젝트 넘버
	float plusMinus;

	//이렇게 만들면 get, set함수가 만들어진다.
	//초기화는 멤버 이니셜 라이징에서 해준다
	SYNTHESIZE(int, numberNodeInstal, GSnumberNodeInstal);
	SYNTHESIZE(int, numberNodelink, GSnumberNodelink);
	SYNTHESIZE(bool,boolTile1, GSboolTile1);
	SYNTHESIZE(bool, boolTile2, GSboolTile2);
	SYNTHESIZE(bool, boolTile3, GSboolTile3);
	SYNTHESIZE(bool, boolTile4, GSboolTile4);
	SYNTHESIZE(bool, boolRaw, GSboolRaw);
	SYNTHESIZE(bool, boolSplate, GSboolSplate);
	SYNTHESIZE(int, numberTile1, GSnumberTile1);
	SYNTHESIZE(int, numberTile2, GSnumberTile2);
	SYNTHESIZE(int, numberTile3, GSnumberTile3);
	SYNTHESIZE(int, numberTile4, GSnumberTile4);
	SYNTHESIZE(int, numberRaw, GSnumberRaw);
	SYNTHESIZE(int, numberSplate, GSnumberSplate);
	
private:
	D3DXVECTOR3 lookPos;
	float RotateAngle;
	float RotateRadian;

public:
	rightView();
	~rightView();
	
	HRESULT init(void);
	void release(void);
	void update(void);
	void EXKEY(void);
	void render(void);

	//상단메뉴 함수
	void buttonTop();
	void buttonTopUdate();
	//오브젝트 중간메뉴 함수
	void buttonObMiddle();
	void buttonObUpdate();
	//환경 중간메뉴 함수
	void buttonENVMiddle();
	void buttonENvUdate();
	//지형 중간메뉴 함수
	void buttonTerMiddle();
	void buttonTerUdate();

	//렌더부분
	void Render(void);

	//get,set
	int getnumberObject(void) { return numberObject; }

	int getnumberwater(void) { return numberwater; }
	void setnumberwater(float _numberwater) { numberwater = _numberwater; }

	int getNumberHeight(void) { return numberHeight; }
	void setNumberHeight(float _numberHeight) { numberHeight = _numberHeight; }

	float getScaleNumber(void) { return scaleNumber; }
	void setScaleNumber(float _scaleNumber) { scaleNumber = _scaleNumber; }

	float getNumberEnv(void) { return numberEnv; }
	void setNumberEnv(float _numberEnv) { numberEnv = _numberEnv; }
};

