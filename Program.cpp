#include "pch.h"
#include "MainGame.h"

void Init();
void Release();

MainGame* mainGame;

int main(void) 
{
	Init();
	mainGame->Init();
	mainGame->Render();
	mainGame->Release();
	Release();

	return 0;
}

void Init()
{
	mainGame = new MainGame();
}

void Release()
{
	delete(mainGame);
}
