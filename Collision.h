#pragma once

class PlayerController;
class Block;
class Board;

class Collision
{
private:
	class PlayerController* _player;
	class Block* _block;
	class Board* _board;

	int collisionIdx;

public:
	void Init(PlayerController& player, Block& block, Board& board);
	const int GetCollisionIdx();
	void OnCollisionBeVersionGravity(const int virtual_y);
	void OnVirtualCollisionPoint();
	void OnVerticalDropMode();
	void OnCollisionBeVersionRotation(const int virtual_y, const int virtual_x);
	void OnCollisionBeVersionAuto(int virtual_y, int virtual_x);
	void OnCollisionGridCheck();
	const bool NextCollisionToNotice(const int *coordY, const int *coordX, bool isCollision, const int distanceY = 0, const int distanceX = 0);
};

