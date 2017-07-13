#include "iGameNode.h"
//
class xPlayer;
class cUIPlayer;
class cUICinema;

class cMinimapPlayerTest : public iGameNode
{
private:
	xPlayer* _player;
	camera* _mainCamera;
	lightDirection* _sceneBaseDirectionLight;
	terrain* _terrain;
	cUIPlayer* m_pUIPlayer;
	cUICinema* m_pUICinema;

public:
	cMinimapPlayerTest();
	virtual ~cMinimapPlayerTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
