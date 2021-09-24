#include "Board.h"
#include "Manager.h"
#include "ConsoleHelper.h"
#include "PlayerController.h"
#include "DefineController.h"
#include "Block.h"
#include "Collision.h"

void Board::Init(PlayerController& playerC, Block& block, Collision& collision, const int y, const int x)
{
	_y = y;
	_x = x;

	GridInit();
	TitleInit();
	GameGuiInit();

	_playerC = &playerC;
	_block = &block;
	_collision = &collision;

	Title(6);
}

void Board::GridInit()
{
	grid = new int*[_y];
	for (int i = 0; i < _y; ++i) {
		grid[i] = new int[_x];
		memset(grid[i], 0, sizeof(grid[i]) * _x);

		for (int j = 0; j < _x; ++j) {
			if (i != _y - 1) {
				if (j == 0 || j == _x - 1)
					grid[i][j] = (int)TerrainType::Wall;
			}
			else
				grid[i][j] = (int)TerrainType::Wall;
		}
	}
}

void Board::TitleInit()
{
	const static char Title[][33] = {
		"¡á¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡á",
		"¡á¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡á",
		"¡á¡à¡à¡à¡à¡à_TETRIS_¡à¡à¡à¡à¡à¡á",
		"¡á¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡á",
		"¡á¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡à¡á",
		"                ",
		" Please Enter Any Key to Start"
	};

	titleYsize = 7;
	title2D = std::move(Title);
}

void Board::GameGuiInit()
{
	const static char GameGui[][33] = {
		{"Next Block"},
	};

	const static char gameGui2[][33] = {
		{"Next Rotation Curr Block"},
	};

	gameGuiYsize = 1;
	gameGui2D = std::move(GameGui);
	gameGui2D2 = std::move(gameGui2);
}

void Board::SetGridType(const int y, const int x, const TerrainType tType)
{
	grid[y][x] = (int)tType;
}

const TerrainType Board::GetGridTerrainType(const int y, const int x)
{ 
	if (y < 0 || y >= _y || x < 0 || x >= _x)
		return TerrainType::Outside;

	return (TerrainType)grid[y][x];
}

const int Board::GetMapSizeY()
{
	return this->_y;
}

const int Board::GetMapSizeX()
{
	return this->_x;
}

void Board::Title(const int x)
{
	for (int i = 0; i < sizeof(title2D[0]) * titleYsize / sizeof(title2D[0]); ++i) {
		ConsoleHelper::SetCursorPosition(x, i + 1);
		for (int j = 0; j < sizeof(title2D[i]) / sizeof(char); ++j)
			cout << title2D[i][j];

		cout << endl;
	}

	Manager::Input().Getch();
}

void Board::GameGui(const int x)
{
	for (int i = 0; i < sizeof(gameGui2D[0]) * gameGuiYsize / sizeof(gameGui2D[0]); ++i) {
		ConsoleHelper::SetCursorPosition(x, i + 1);
		cout << gameGui2D[i];
	}

	int bType = (int)DefineController::GetNextGraphicBlockType();
	for (int i = 0; i < 4; ++i) {
		ConsoleHelper::SetCursorPosition(x + 1, i + gameGuiYsize + 2);
		cout << _block->GetGraphic3D()[bType][i];
	}

	/*for (int i = 0; i < sizeof(gameGui2D2[0]) * gameGuiYsize / sizeof(gameGui2D2[0]); ++i) {
		ConsoleHelper::SetCursorPosition(x, i + 10);
		cout << gameGui2D2[i];
	}

	int bRotType = (int)DefineController::GetFirstGraphicNextRotationBlockType();
	for (int i = 0; i < 4; ++i) {
		ConsoleHelper::SetCursorPosition(x + 1, i + 12);
		cout << _block->GetGraphic3D()[bRotType][i];
	}*/
}

void Board::GameScreen() 
{
	GameGui(35);

	for (int i = 0; i < _y; i++) {
		ConsoleHelper::SetCursorPosition(6, i + 1);
		for (int j = 0; j < _x; j++) {
			if (grid[i][j] == (int)TerrainType::None)
				cout << "¡à";
			else if (grid[i][j] == (int)TerrainType::Wall)
				cout << "¢Ì";
			else if (grid[i][j] == (int)TerrainType::Block) {
				if (i == *_playerC->GetY() && j == *_playerC->GetX())
					cout << "¡Ü";
				else
					cout << "¡á";	
			}
			else if (grid[i][j] == (int)TerrainType::VirtualBlock)
					cout << "¡ß";
			else if (grid[i][j] == (int)TerrainType::Rock)
				cout << "¢Ã";
		}

		cout << endl;
	}

	/*cout << endl;
	cout << "PlayerInfo " << "Y:" << *_playerC->GetY() << ", X:" << *_playerC->GetX() << endl;
	cout << "CurrDirection:" << (int)DefineController::GetDirection() << endl;
	cout << "BlockCoord:" << endl;
	const int* blockY = &_block->GetCoordY();
	const int* blockX = &_block->GetCoordX();
	for (int i = 0; i < 4; ++i)
		cout << '[' << i << ']' << "Y: " << blockY[i] << " [" << i << ']' << "X: " << blockX[i] << endl;*/
	
	// rockArray code
	cout << endl;
	for (size_t i = 0; i < _y - 1; ++i) {
		ConsoleHelper::SetCursorPosition(6 + i * 2, 21);
		cout << _block->GetRockArray(i);
	}
	ConsoleHelper::SetCursorPosition(6, 22);
	cout << endl << _block->GetMinRockY();
}

void Board::GridToClear()
{
	const int *blockY = &_block->GetCoordY();
	const int *blockX = &_block->GetCoordX();
	const int virYIdx = _collision->GetCollisionIdx();

	for (int i = 0; i < 4; ++i) {
		grid[blockY[i]][blockX[i]] = (int)TerrainType::None;
		grid[blockY[i] + virYIdx][blockX[i]] = (int)TerrainType::None;
	}
}

void Board::Render()
{
	GameScreen();
	GridToClear();
}
