
#include "Game.h"


//////////////////////////////////////////////////////////////////////////
// Main global function
//////////////////////////////////////////////////////////////////////////
int main()
{
	// Init Game
	CGame::Create();
	GAME->Run();
	CGame::Destroy();

	return 0;
}

void CGame::Init()
{
	CGEApp::Init();
}

void CGame::Release()
{
	CGEApp::Release();
}