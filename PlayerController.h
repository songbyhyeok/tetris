#pragma once

class Block;
class Board;
class Collision;

class PlayerController
{
private:
	Block* _block;
	Board* _board;
	Collision* _collision;

	int _y, _x;
	// 10 m/s 마다 이동할 목적 00.1초 개념
	int sumStayTick = 0;
	int sumMoveTick = 0;
	const int NONE_TICK = 1000; 
	const int MOVE_TICK = 80;

public:
	void Init(Collision& collision, const int y, const int x);
	void YCalculate(const int y);
	void SetStartPoint(const int y, const int x);
	const int *GetY();
	void XCalculate(const int x);
	const int *GetX();
	void OnStayMode();
	void OnMoveMentMode();
	void Update(const int deltaTick);
};

