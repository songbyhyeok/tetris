#include "MainGame.h"
#include "DefineController.h"
#include "PlayerController.h"
#include "DefineController.h"
#include "Block.h"
#include "Board.h"
#include "Collision.h"
#include "Manager.h"
#include "ConsoleHelper.h"

void MainGame::Init()
{
	playerController = new PlayerController();
	block = new Block();
	board = new Board();
	collision = new Collision();

	DefineController::Init();
	block->Init(*playerController, *board, *collision);
	board->Init(*playerController, *block, *collision, 20, 12);
	block->InitOfRockBlock();
	collision->Init(*playerController, *block, *board);
	playerController->Init(*collision, 1, 3);

	WAIT_TICK = 1000 / 60;
	lastTick = 0;

	Manager::Scene().LoadScene();
}

void MainGame::Render()
{
	//Manager::Scene().GetNext()
	while (true) {
#pragma region 프레임 관리

		int currTick = clock();
		int elapsedTick = currTick - lastTick;
		if (elapsedTick < WAIT_TICK)
			continue;

		lastTick = currTick;

#pragma endregion

		playerController->Update(elapsedTick);
		block->RTCalculator();
		collision->OnCollisionGridCheck();
		board->Render();

		ConsoleHelper::ShowConsoleCursor(false);
	}
}

void MainGame::Release()
{
}
