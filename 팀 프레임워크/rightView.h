#pragma once
#include "iGameNode.h"

#define DEFENV 6   //���ϴܸ޴� ������Ʈ��      
#define DEFTER 6   //�����ϴܸ޴� ������Ʈ��  

class objectClass;
class rightSmallGrid;

//��� �޴�
enum UISTAGE { UIOFF = 0, UION };
//������Ʈ �ߴܸ޴�
enum OBSTAGE { STORMTOWN1 =1, STROMTOWN2, RUINSTAGE, PIRAMID };
//������Ʈ �ϴܸ޴�
enum OBSTAGEDOWN { ONEOFF = 1, TWOOFF, THREEOFF };
//ȯ�� �ߴܸ޴�
enum ENVSTAGE { WATERMIDDLE = 1, SKYMIDDLE ,NODEINSTAL,NODELINK,MONSTER };
//���� �ߴܸ޴�
enum TERSTAGE { TILEMAP1 =1, TILEMAP2,TILEMAP3,TILEMAP4,SPLAT,TERRAWMAP,TERHEIGHT };
//UI��Ʈ�� �޴�
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
	
	//���� �׸���
	rightSmallGrid* _rightSmallGrid;
	//������Ʈ
	objectClass* _objectClass;
	camera		 _mainCamera;

public:
	//����
	UI _ObjectButton[6];

	//��ȭ������ UI
	UI _UIBACK;
	UI _UIkind;
	UI _UIsize[2];
	UI _UIcontrol[2];
	UI _UIsizeHeight[2];
	UI _UInodeHeight[2];

	//��ܸ޴�
	UI _TOPbutton[3];

	//�ߴܸ޴�
	UI _OBJbutton;
	UI _ENVbutton;
	UI _TERRIANbutton;

	//���� �޴�
	UI _heightContorol[2];
	UI _nodeInstalContorol[2];
	UI _nodeLinkContorol[2];

	//�����ϴ� �޴�
	UI _OBJstorm1Button[5];
	UI _OBJGO;
	UI _OBJback;
	UI _OBJstorm2Button[5];
	UI _OBJruinButton[7];
	UI _OBJpiramidButton[4];

	//ȯ���ϴ� �޴�
	UI _ENVwaterButton[DEFENV];
	UI _ENVskyButton[DEFENV];

	//�����ϴ� �޴�
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
	//�Ͻ����� ���콺 
	POINT mouse;

private:
	float scaleNumber;       //������ ���� �ѹ�
	int numberEnv;           //ȯ���  �ѹ�
	int numberwater;         //�� �ѹ�
	int numberHeight;        //���� �ѹ�
	int numberObject;        //������Ʈ �ѹ�
	float plusMinus;

	//�̷��� ����� get, set�Լ��� ���������.
	//�ʱ�ȭ�� ��� �̴ϼ� ����¡���� ���ش�
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

	//��ܸ޴� �Լ�
	void buttonTop();
	void buttonTopUdate();
	//������Ʈ �߰��޴� �Լ�
	void buttonObMiddle();
	void buttonObUpdate();
	//ȯ�� �߰��޴� �Լ�
	void buttonENVMiddle();
	void buttonENvUdate();
	//���� �߰��޴� �Լ�
	void buttonTerMiddle();
	void buttonTerUdate();

	//�����κ�
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

