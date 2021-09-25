#pragma once

#include "pch.h"

enum class TerrainType
{
	None = 0,
	Wall,
	Block,
	VirtualBlock,
	Rock,
	Outside
};

enum class BlockType
{
	I = 0,
	O = 4,
	T = 8,
	L = 12,
	J = 16,
	S = 20,
	Z = 24
};

enum class Direction
{
	North = 0,
	East,
	South,
	West
};

enum class KeyMode
{
	None,
	Left,
	Right,
	Forward
};

enum class State
{
	None,
	Control
};

class DefineController
{
private:
	static mt19937 engine;
	static int _nOfBlock;
	static BlockType _useOfBlock;
	static std::queue<BlockType> containQ;
	static Direction _direction;
	static KeyMode _keyMode;
	static State _state;

public:
	static void Init();
	static void SetContainBlockTypes(int nOfBlock = 5);
	static void SetBlockType();
	static const BlockType GetBlockType();
	static const int GetFirstBlockTypeY();
	static const int GetFirstBlockTypeX();
	static const int GetFirstGraphicBlockType();
	static const int GetFirstGraphicNextRotationBlockType();
	static const int GetNextGraphicBlockType();
	static const int GetNextBlockType();
	static void SetDirection(bool collision = false);
	static const Direction GetDirection();
	static const Direction GetNextDirection();
	static void SetState(State state);
	static const State GetState();
};

