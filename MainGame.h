#pragma once

class PlayerController;
class Block;
class Board;
class Collision;

class MainGame
{
private:
	PlayerController* playerController;
	Block* block;
	Board* board;
	Collision* collision;

	int WAIT_TICK;
	int lastTick;

public:
	void Init();
	void Render();
	void Release();
};

