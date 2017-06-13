#pragma once
#include "singletonBase.h"

//�̱����� ��ӹ��� ���̵��� static���� ����� ���⶧����
//�Ϲ�Ŭ������ ���ӳ�带 ����Ϸ��� �ϸ� ������

//class gameNode;
//
//class sceneManager : public singletonBase <sceneManager>
//{
//private:
//	typedef map<string, gameNode*> mSceneList;
//	typedef map<string, gameNode*>::iterator miSceneList;
//
//private:
//	mSceneList _mSceneList;		//������ ��(ȭ��)���� ��Ƶ� ��
//	gameNode* _currentScene;	//�����
//
//public:
//	HRESULT init(void);
//	void release(void);
//	void update(void);
//	void render(void);
//
//	//���߰�
//	gameNode* addScene(string sceneName, gameNode* scene);
//
//	//������
//	HRESULT changeScene(string sceneName);
//
//	sceneManager() : _currentScene(NULL) {}
//	~sceneManager() {}
//};


class iGameNode;

class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, iGameNode*> mSceneList;
	typedef map<string, iGameNode*>::iterator miSceneList;

private:
	mSceneList _mSceneList;		//������ ��(ȭ��)���� ��Ƶ� ��
	iGameNode* _currentScene;	//�����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//���߰�
	iGameNode* addScene(string sceneName, iGameNode* scene, bool isSceneChange = true);

	//������
	HRESULT changeScene(string sceneName);

	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};