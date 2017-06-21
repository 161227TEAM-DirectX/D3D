#pragma once
#include "singletonBase.h"

class iGameNode;

class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, iGameNode*> mSceneList;
	typedef map<string, iGameNode*>::iterator miSceneList;

private:
	mSceneList _mSceneList;		//각각의 씬(화면)들을 담아둘 맵
	iGameNode* _currentScene;	//현재씬

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//씬추가
	iGameNode* addScene(string sceneName, iGameNode* scene, bool isSceneChange = false);

	//씬변경
	HRESULT changeScene(string sceneName);

	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};

//싱글톤을 상속받은 아이들은 static으로 만들어 지기때문에
//일반클래스인 게임노드를 사용하려고 하면 터진다

//class gameNode;
//
//class sceneManager : public singletonBase <sceneManager>
//{
//private:
//	typedef map<string, gameNode*> mSceneList;
//	typedef map<string, gameNode*>::iterator miSceneList;
//
//private:
//	mSceneList _mSceneList;		//각각의 씬(화면)들을 담아둘 맵
//	gameNode* _currentScene;	//현재씬
//
//public:
//	HRESULT init(void);
//	void release(void);
//	void update(void);
//	void render(void);
//
//	//씬추가
//	gameNode* addScene(string sceneName, gameNode* scene);
//
//	//씬변경
//	HRESULT changeScene(string sceneName);
//
//	sceneManager() : _currentScene(NULL) {}
//	~sceneManager() {}
//};


