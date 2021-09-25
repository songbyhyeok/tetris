#pragma once

enum class TerrainType;

class PlayerController;
class Block;
class Collision;

class Board
{
private:
	PlayerController* _playerC;
	Block* _block;
	Collision* _collision;
	
	int _y, _x;
	int titleYsize;
	int gameGuiYsize;
	const char (*title2D)[33];
	const char (*gameGui2D)[33];
	const char (*gameGui2D2)[33];
	int** grid;

public:
	void Init(PlayerController &playerC, Block &block, Collision& collision, const int y, const int x);
	void GridInit();
	void TitleInit();
	void GameGuiInit();
	const int GetMapSizeY();
	const int GetMapSizeX();
	void SetGridType(const int y, const int x, const TerrainType tType);
	const TerrainType GetGridTerrainType(const int y, const int x);
	void Title(const int x);
	void GameGui(const int x);
	void GameScreen();
	void GridToClear();
	void Render();
};

