#pragma once

#include "pch.h"
#include <queue>

typedef const char(*Graphic3D)[4][9];
typedef const int(*Rt3D)[4][4];

class PlayerController;
class Board;
class Collision;

class Block
{
private:
	PlayerController* _playerC;
	Board* _board;
	Collision* _collision;

	int* coordY, * coordX;
	int* virCoordY, * virCoordX;
	int* virRotCoordY, * virRotCoordX;
	const char(*graphic3D)[4][9];
	const int(*rtCoord3D)[4][4];
	int btY, btX;
	int* rockArray;
	pair<int, int> lineOfPair[2];
	int lineSize;
	int minRockY;

public:
	void Init(PlayerController& playerC, Board& board, Collision& collision);
	void InitOfRockBlock();
	void CoordinateYXInit();
	void CreateGraphic3D();
	void CreateRtCoordinate3D();
	Graphic3D GetGraphic3D();
	Rt3D GetRtCoord3D();
	const int GetRtCoord3DY(const int y_1d);
	const int GetRtCoord3DX(const int x_1d);
	const int GetNextRotVirRtCoord3DY(const int y_1d);
	const int GetNextRotVirRtCoord3DX(const int x_1d);
	const int& GetCoordY();
	const int& GetCoordX();
	const int& GetVirCoordY();
	const int& GetVirCoordX();
	const int& GetVirRotCoordY();
	const int& GetVirRotCoordX();
	void RTCalculator();
	void RTVirtualCalculator(const int virtual_y, const int virtual_x = 0);
	void RTVirtualRotationCalculator(const int virtual_y, const int virtual_x);
	void SetRockArray(const int y, const int value);
	void RockArrayCalculate(const int y, const int n);
	const int GetRockArray(const int y);
	void LineOfRockInit();
	void LineOfPairInit();
	void SetLineOfPairFirst(const int y);
	const int GetLineOfPairFirst(const int idx);
	void SetLineOfPairSecond(const int y);
	void LineOfPairSecondCalculate(const int n);
	const int GetLineOfPairSecond(const int idx);
	void LineSizeCalculate(const int n);
	const int GetLineSize();
	void MinRockYCalculate(const int target);
	void MinRockYCalculate2(const int n);
	const int GetMinRockY();
};

