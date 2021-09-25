#include "DefineController.h"

mt19937 DefineController::engine((unsigned int)time(nullptr));
int DefineController::_nOfBlock;
BlockType DefineController::_useOfBlock;
std::queue<BlockType> DefineController::containQ;
Direction DefineController::_direction = Direction::North;
KeyMode DefineController::_keyMode = KeyMode::None;
State DefineController::_state = State::None;

void DefineController::Init()
{
	SetContainBlockTypes();
	SetBlockType();
}

void DefineController::SetContainBlockTypes(int nOfBlock)
{
	_nOfBlock = nOfBlock;
	for (int i = 0; i < _nOfBlock; ++i) {
		uniform_int_distribution<int> dist(0, 6);	
		containQ.push((BlockType)(dist(engine)));
	}
}

void DefineController::SetBlockType()
{
	if (containQ.empty())
		SetContainBlockTypes();

	if (!containQ.empty()) {
		_useOfBlock = containQ.front();
		containQ.pop();
	}
}

const BlockType DefineController::GetBlockType()
{
	return (BlockType)((int)_useOfBlock * 4);
}

const int DefineController::GetFirstBlockTypeY()
{
	return ((int)_useOfBlock * 2);
}

const int DefineController::GetFirstBlockTypeX()
{
	return (((int)_useOfBlock * 2) + 1);
}

const int DefineController::GetFirstGraphicBlockType()
{
	return ((int)_useOfBlock * 4);
}

const int DefineController::GetFirstGraphicNextRotationBlockType()
{
	return ((int)_useOfBlock * 4) + (int)GetNextDirection();
}

const int DefineController::GetNextGraphicBlockType()
{
	return (GetNextBlockType() * 4);
}

const int DefineController::GetNextBlockType()
{
	if (containQ.empty())
		SetContainBlockTypes();

	return (int)containQ.front();
}

void DefineController::SetDirection(bool collision)
{
	if (collision)
		_direction = Direction::North;

	if (!collision && _direction == Direction::North)
		_direction = Direction::East;
	else if (_direction == Direction::East)
		_direction = Direction::South;
	else if (_direction == Direction::South)
		_direction = Direction::West;
	else if (_direction == Direction::West)
		_direction = Direction::North;
}

const Direction DefineController::GetDirection()
{
	return _direction;
}

const Direction DefineController::GetNextDirection()
{
	return (Direction)(((int)_direction + 1) % 4);
}

void DefineController::SetState(State state)
{
	_state = state;
}
const State DefineController::GetState()
{
	return _state;
}
