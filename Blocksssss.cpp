#include "Block.h"
#include "PlayerController.h"
#include "DefineController.h"
#include "Board.h"
#include "Collision.h"

void Block::Init(PlayerController& playerC, Board& board, Collision& collision)
{
	_playerC = &playerC;
	_board = &board;
	_collision = &collision;

	coordY = coordX = nullptr;
	graphic3D = nullptr;
	rtCoord3D = nullptr;
	btY = btX = 0;

	CoordinateYXInit();
	CreateGraphic3D();
	CreateRtCoordinate3D();
}

void Block::InitOfRockBlock()
{
	rockArray = new int[_board->GetMapSizeY() - 1]{ 0, };
	LineOfRockInit();
}

void Block::CoordinateYXInit()
{
	coordY = new int[4]{1,1,1,1};
	coordX = new int[4]{1,1,1,1};
	virCoordY = new int[4]{ 1,1,1,1 };
	virCoordX = new int[4]{ 1,1,1,1 };
	virRotCoordY = new int[4]{1,1,1,1};
	virRotCoordX = new int[4]{1,1,1,1};
}

void Block::CreateGraphic3D()
{
	const static char Graphics[28][4][9]{
		// I
		{ {"        "}, {"бсбсбсбс"}, {"        "}, {"        "} },
		{ {"бс      "}, {"бс      "}, {"бс      "}, {"бс      "} },
		{ {"        "}, {"бсбсбсбс"}, {"        "}, {"        "} },
		{ {"бс      "}, {"бс      "}, {"бс      "}, {"бс      "} },
		// O
		{ {"бсбс    "}, {"бсбс    "}, {"        "}, {"        "} },
		{ {"бсбс    "}, {"бсбс    "}, {"        "}, {"        "} },
		{ {"бсбс    "}, {"бсбс    "}, {"        "}, {"        "} },
		{ {"бсбс    "}, {"бсбс    "}, {"        "}, {"        "} },
		// T
		{ {"  бс    "}, {"бсбсбс  "}, {"        "}, {"        "} },
		{ {"  бс    "}, {"  бсбс  "}, {"  бс    "}, {"        "} },
		{ {"        "}, {"бсбсбс  "}, {"  бс    "}, {"        "} },
		{ {"  бс    "}, {"бсбс    "}, {"  бс    "}, {"        "} },
		// L
		{ {"    бс  "}, {"бсбсбс  "}, {"        "}, {"        "} },
		{ {"  бс    "}, {"  бс    "}, {"  бсбс  "}, {"        "} },
		{ {"        "}, {"бсбсбс  "}, {"бс      "}, {"        "} },
		{ {"бсбс    "}, {"  бс    "}, {"  бс    "}, {"        "} },
		// J
		{ {"бс      "}, {"бсбсбс  "}, {"        "}, {"        "} },
		{ {"  бсбс  "}, {"  бс    "}, {"  бс    "}, {"        "} },
		{ {"        "}, {"бсбсбс  "}, {"    бс  "}, {"        "} },
		{ {"  бс    "}, {"  бс    "}, {"бсбс    "}, {"        "} },
		// S
		{ {"  бсбс  "}, {"бсбс    "}, {"        "}, {"        "} },
		{ {"  бс    "}, {"  бсбс  "}, {"    бс  "}, {"        "} },
		{ {"  бсбс  "}, {"бсбс    "}, {"        "}, {"        "} },
		{ {"  бс    "}, {"  бсбс  "}, {"    бс  "}, {"        "} },
		// Z
		{ {"бсбс    "}, {"  бсбс  "}, {"        "}, {"        "} },
		{ {"    бс  "}, {"  бсбс  "}, {"  бс    "}, {"        "} },
		{ {"бсбс    "}, {"  бсбс  "}, {"        "}, {"        "}  },
		{ {"    бс  "}, {"  бсбс  "}, {"  бс    "}, {"        "}  },
	};

	graphic3D = std::move(Graphics);
}

void Block::CreateRtCoordinate3D()
{
	const static int RtCoords[14][4][4]{
		// I.Y
	{
		{0, 0, 0, 0},
		{-1, 0, 1, 2},
		{0, 0, 0, 0},
		{-1, 0, 1, 2},
	},
		// I.X
	{
		{-2, -1, 0, 1},
		{0, 0, 0, 0},
		{-2, -1, 0, 1},
		{0, 0, 0, 0},
	},
		// O.Y
	{
		{0, 1, 0, 1},
		{0, 1, 0, 1},
		{0, 1, 0, 1},
		{0, 1, 0, 1},
	},
		// O.X
	{
		{-1, -1, 0, 0},
		{-1, -1, 0, 0},
		{-1, -1, 0, 0},
		{-1, -1, 0, 0},
	},
		// T.Y
	{
		{0, -1, 0, 0},
		{-1, 0, 1, 0},
		{0, 0, 1, 0},
		{0, -1, 0, 1},
	},
		// T.X
	{
		{-1, 0, 0, 1},
		{0, 0, 0, 1},
		{-1, 0, 0, 1},
		{-1, 0, 0, 0}
	},
		// L.Y
	{
		{0, 0, 0, -1},
		{-1, 0, 1, 1},
		{0, 1, 0, 0},
		{-1, -1, 0, 1}
	},
		// L.X
	{
		{-1, 0, 1, 1},
		{0, 0, 0, 1},
		{-1, -1, 0, 1},
		{-1, 0, 0, 0},
	},
		// J.Y
	{
		{-1, 0, 0, 0},
		{-1, 0, 1, -1},
		{0, 0, 0, 1},
		{1, -1, 0, 1}
	},
		// J.X
	{
		{-1, -1, 0, 1},
		{0, 0, 0, 1},
		{-1, 0, 1, 1},
		{-1, 0, 0, 0},
	},
		// S.Y
	{
		{1, 0, 1, 0},
		{-1, 0, 0, 1},
		{1, 0, 1, 0},
		{-1, 0, 0, 1},
	},
		// S.X
	{
		{-1, 0, 0, 1},
		{0, 0, 1, 1},
		{-1, 0, 0, 1},
		{0, 0, 1, 1},
	},
		// Z.Y
	{
		{0, 0, 1, 1},
		{0, 1, -1, 0},
		{0, 0, 1, 1},
		{0, 1, -1, 0},
	},
		// Z.X
	{
		{-1, 0, 0, 1},
		{0, 0, 1, 1},
		{-1, 0, 0, 1},
		{0, 0, 1, 1},
	},
	};

	rtCoord3D = std::move(RtCoords);
}

Graphic3D Block::GetGraphic3D()
{
	return graphic3D;
}

Rt3D Block::GetRtCoord3D()
{
	return rtCoord3D;
}

const int Block::GetRtCoord3DY(const int y_1d)
{
	return rtCoord3D[btY][(int)DefineController::GetDirection()][y_1d];
}

const int Block::GetRtCoord3DX(const int x_1d)
{
	return rtCoord3D[btX][(int)DefineController::GetDirection()][x_1d];
}

const int Block::GetNextRotVirRtCoord3DY(const int y_1d)
{
	return rtCoord3D[btY][(int)DefineController::GetNextDirection()][y_1d];
}

const int Block::GetNextRotVirRtCoord3DX(const int x_1d)
{
	return rtCoord3D[btX][(int)DefineController::GetNextDirection()][x_1d];
}

const int& Block::GetCoordY()
{
	return *this->coordY;
}

const int& Block::GetCoordX()
{
	return *this->coordX;
}

const int& Block::GetVirCoordY()
{
	return *this->virCoordY;
}

const int& Block::GetVirCoordX()
{
	return *this->virCoordX;
}

const int& Block::GetVirRotCoordY()
{
	return *this->virRotCoordY;
}

const int& Block::GetVirRotCoordX()
{
	return *this->virRotCoordX;
}

void Block::RTCalculator()
{
	btY = (int)DefineController::GetFirstBlockTypeY();
	btX = (int)DefineController::GetFirstBlockTypeX();
	const int dir = (int)DefineController::GetDirection();

	int distanceX = *_playerC->GetX() + rtCoord3D[btX][dir][0];
	if (distanceX == 0)
		_playerC->XCalculate(1);

	for (int i = 0; i < 4; ++i) {
		coordY[i] = *_playerC->GetY() + rtCoord3D[btY][dir][i];
		coordX[i] = *_playerC->GetX() + rtCoord3D[btX][dir][i];

		_board->SetGridType(coordY[i], coordX[i], TerrainType::Block);
	}

	_collision->OnVirtualCollisionPoint();
	int virY = _collision->GetCollisionIdx();

	for (int i = 0; i < 4; ++i)
		_board->SetGridType(coordY[i] + virY, coordX[i], TerrainType::VirtualBlock);
}

void Block::RTVirtualCalculator(const int virtual_y, const int virtual_x)
{
	const int dir = (int)DefineController::GetDirection();
	for (int i = 0; i < 4; ++i) {
		virCoordY[i] = *_playerC->GetY() + virtual_y + rtCoord3D[btY][dir][i];
		virCoordX[i] = *_playerC->GetX() + virtual_x + rtCoord3D[btX][dir][i];
	}
}

void Block::RTVirtualRotationCalculator(const int virtual_y, const int virtual_x)
{
	const int dir = (int)DefineController::GetNextDirection();
	for (int i = 0; i < 4; ++i) {
		virRotCoordY[i] = *_playerC->GetY() + virtual_y + rtCoord3D[btY][dir][i];
		virRotCoordX[i] = *_playerC->GetX() + virtual_x + rtCoord3D[btX][dir][i];
	}
}

void Block::SetRockArray(const int y, const int value)
{
	rockArray[y] = value;
}

void Block::RockArrayCalculate(const int y, const int n)
{
	rockArray[y] += n;
}

const int Block::GetRockArray(const int y)
{
	return rockArray[y];
}

void Block::LineOfRockInit()
{
	for (int i = 0; i < 2; ++i)
		lineOfPair[i].first = lineOfPair[i].second = 0;
	
	lineSize = 0;
	minRockY = _board->GetMapSizeY() - 2;
}

void Block::LineOfPairInit()
{
	for (int i = 0; i < 2; ++i)
		lineOfPair[i].first = lineOfPair[i].second = 0;

	lineSize = 0;
}

void Block::SetLineOfPairFirst(const int y)
{
	lineOfPair[lineSize].first = y;
}

const int Block::GetLineOfPairFirst(const int idx)
{
	return lineOfPair[idx].first;
}

void Block::SetLineOfPairSecond(const int y)
{
	lineOfPair[lineSize].second = y;
}

void Block::LineOfPairSecondCalculate(const int n)
{
	lineOfPair[lineSize].second += n;
}

const int Block::GetLineOfPairSecond(const int idx)
{
	return lineOfPair[idx].second;
}

void Block::LineSizeCalculate(const int n)
{
	lineSize += n;
}

const int Block::GetLineSize()
{
	return lineSize;
}

void Block::MinRockYCalculate(const int target)
{
	minRockY = min(minRockY, target);
}

void Block::MinRockYCalculate2(const int n)
{
	minRockY += n;
}

const int Block::GetMinRockY()
{
	return minRockY;
}


