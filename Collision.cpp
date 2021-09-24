#include "Collision.h"
#include "PlayerController.h"
#include "DefineController.h"
#include "Block.h"
#include "Board.h"
#include "pch.h"
#include "ConsoleHelper.h"

void Collision::Init(PlayerController& player, Block& block, Board& board)
{
	_block = &block;
	_board = &board;
	_player = &player;

	collisionIdx = 0;
}

const int Collision::GetCollisionIdx()
{
	return collisionIdx;
}

void Collision::OnCollisionBeVersionGravity(const int virtual_y)
{
	const int* blockY = &_block->GetCoordY();
	const int* blockX = &_block->GetCoordX();

	_block->RTVirtualCalculator(virtual_y);
	const int* virBlockY = &_block->GetVirCoordY();
	
	for (int i = 0; i < 4; ++i) {
		TerrainType tType = _board->GetGridTerrainType(virBlockY[i], blockX[i]);
		if (tType == TerrainType::Wall || tType == TerrainType::Rock) {
			for (int j = 0; j < 4; ++j) {
				_board->SetGridType(blockY[j], blockX[j], TerrainType::Rock);

				_block->RockArrayCalculate(blockY[j], 1);
				_block->MinRockYCalculate(blockY[j]);
			}

			if (_block->GetMinRockY() == 0)
				cout << "gameover";

			_player->SetStartPoint(1, 3);

			DefineController::SetBlockType();
			DefineController::SetDirection(true);

			return;
		}
	}

	_player->YCalculate(virtual_y);
}

void Collision::OnVirtualCollisionPoint()
{
	const int* blockY = &_block->GetCoordY();
	const int* blockX = &_block->GetCoordX();
	bool isCollision = false;
	int cnt = _board->GetMapSizeY() - *_player->GetY();

	for (int i = 0; i <= cnt; ++i) {
		isCollision = NextCollisionToNotice(blockY, blockX, isCollision, i);
		if (isCollision) {
			collisionIdx = i - 1;

			break;
		}
	}
}

void Collision::OnVerticalDropMode()
{
	const int* blockY = &_block->GetCoordY();
	const int* blockX = &_block->GetCoordX();

	for (int i = 0; i < 4; ++i) {
		_board->SetGridType(blockY[i] + collisionIdx, blockX[i], TerrainType::Rock);
		_block->RockArrayCalculate(blockY[i] + collisionIdx, 1);
		_block->MinRockYCalculate(blockY[i] + collisionIdx);
	}

	if (_block->GetMinRockY() == 0)
		cout << "gameover";

	_player->SetStartPoint(1, 3);

	DefineController::SetBlockType();
	DefineController::SetDirection(true);
}

void Collision::OnCollisionBeVersionRotation(const int virtual_y, const int virtual_x)
{
	if (DefineController::GetBlockType() == BlockType::O ||
		virtual_y == 1 && virtual_x == -1 || virtual_y == 1 && virtual_x == 1)
		return;

	_block->RTVirtualRotationCalculator(virtual_y, virtual_x);
	const int* nextVirRotBlockY = &_block->GetVirRotCoordY();
	const int* nextVirRotBlockX = &_block->GetVirRotCoordX();

	pair<int, int> infoOfminY = make_pair(99, 0);
	pair<int, int> infoOfmaxY = make_pair(0, 0);
	pair<int, int> infoOfminX = make_pair(99, 0);
	pair<int, int> infoOfmaxX = make_pair(0, 0);
	for (int i = 0; i < 4; ++i) {
		if (infoOfminY.first > nextVirRotBlockY[i]) {
			infoOfminY.first = nextVirRotBlockY[i];
			infoOfminY.second = i;
		}
		if (infoOfmaxY.first <= nextVirRotBlockY[i]) {
			infoOfmaxY.first = nextVirRotBlockY[i];
			infoOfmaxY.second = i;
		}
		if (infoOfminX.first > nextVirRotBlockX[i]) {
			infoOfminX.first = nextVirRotBlockX[i];
			infoOfminX.second = i;
		}
		if (infoOfmaxX.first <= nextVirRotBlockX[i]) {
			infoOfmaxX.first = nextVirRotBlockX[i];
			infoOfmaxX.second = i;
		}
	}

	/*ConsoleHelper::SetCursorPosition(36, 16);
	cout << "BlockCoord:" << endl;
	for (int i = 0; i < 4; ++i) {
		ConsoleHelper::SetCursorPosition(36, i + 17);
		cout << '[' << i << ']' << "Y: " << nextVirRotBlockY[i] << " [" << i << ']' << "X: " << nextVirRotBlockX[i] << endl;
	}*/

	TerrainType collisionType = TerrainType::None;
	int distanceY = 0, distanceX = 0;
	int distance = 0;
	bool isCollision = false;
	isCollision = NextCollisionToNotice(nextVirRotBlockY, nextVirRotBlockX, isCollision);
	if (isCollision) {
		isCollision = false;

		collisionType = _board->GetGridTerrainType(nextVirRotBlockY[collisionIdx], nextVirRotBlockX[collisionIdx]);
	}

	if (collisionType == TerrainType::Outside || collisionType == TerrainType::Wall || collisionType == TerrainType::Rock) {
		if (infoOfminX.first <= 0 || virtual_x == -1) {
			distanceX = _block->GetNextRotVirRtCoord3DX(infoOfminX.second);
			if (distanceX < 0)
				distanceX = -distanceX;

			distance = distanceX + (-virtual_x);
			isCollision = NextCollisionToNotice(nextVirRotBlockY, nextVirRotBlockX, isCollision, 0, distance);
			if (isCollision)
				return;
		}
		else if (infoOfmaxX.first >= _board->GetMapSizeX() - 1 || virtual_x == 1) {
			distanceX = _block->GetNextRotVirRtCoord3DX(infoOfmaxX.second);

			distance = (distanceX + virtual_x);
			isCollision = NextCollisionToNotice(nextVirRotBlockY, nextVirRotBlockX, isCollision, 0, -distance);
			if (isCollision)
				return;

			distanceX = -distanceX;
		}
		else if (infoOfmaxY.first >= _board->GetMapSizeY() - 1 || virtual_y == 1 || virtual_y == 0) {
			distanceY = _block->GetNextRotVirRtCoord3DY(infoOfmaxY.second);

			distance = (distanceY + virtual_y);
			isCollision = NextCollisionToNotice(nextVirRotBlockY, nextVirRotBlockX, isCollision, -distance, 0);
			if (isCollision)
				return;

			distanceY = -distanceY;
		}
		else if (infoOfminY.first <= 0 || virtual_y == 1 || virtual_y == 0) {
			distanceY = _block->GetNextRotVirRtCoord3DY(infoOfminY.second);

			distance = (distanceY + virtual_y);
			isCollision = NextCollisionToNotice(nextVirRotBlockY, nextVirRotBlockX, isCollision, distance, 0);
			if (isCollision)
				return;
		}
	}	
	else {
		distanceY = virtual_y;
		distanceX = virtual_x;
	}

	_player->YCalculate(distanceY);
	_player->XCalculate(distanceX);

	DefineController::SetDirection();
}

void Collision::OnCollisionBeVersionAuto(int virtual_y, int virtual_x)
{
	_block->RTVirtualCalculator(virtual_y, virtual_x);
	const int* virBlockY = &_block->GetVirCoordY();
	const int* virBlockX = &_block->GetVirCoordX();
	bool isCollision = false;

	if (virtual_y == 1 && virtual_x == -1 || virtual_y == 1 && virtual_x == 1) {
		const int* blockY = &_block->GetCoordY();
		const int* blockX = &_block->GetCoordX();

		isCollision = NextCollisionToNotice(virBlockY, virBlockX, isCollision);
		if (isCollision) {
			bool isDownCollision = false;
			isDownCollision = NextCollisionToNotice(blockY, virBlockX, isDownCollision);
			if (isDownCollision) {
				virtual_x = 0;

				bool isLeftRightCollision = false;
				isLeftRightCollision = NextCollisionToNotice(virBlockY, blockX, isLeftRightCollision);
				if (isLeftRightCollision)
					virtual_y = 0;
			}
			else
				virtual_y = 0;
		}
	}
	else {
		isCollision = NextCollisionToNotice(virBlockY, virBlockX, isCollision);
		if (isCollision)
			return;
	}

	_player->YCalculate(virtual_y);
	_player->XCalculate(virtual_x);
}

void Collision::OnCollisionGridCheck()
{
	int gridSizeY = _board->GetMapSizeY();
	int gridSizeX = _board->GetMapSizeX();
	int minRockY = _block->GetMinRockY();
	int i, j;

	for (i = (gridSizeY - 2); i >= minRockY; --i) {
		if (_block->GetRockArray(i) == _board->GetMapSizeX() - 2) 
			_block->LineOfPairSecondCalculate(1);
		else if (i != (gridSizeY - 2) && _block->GetRockArray(i + 1) == 10 && _block->GetRockArray(i) != 10) {
			_block->SetLineOfPairFirst(i);
			
			for (j = 1; j <= _block->GetLineOfPairSecond(_block->GetLineSize()); ++j)
				_block->SetRockArray(i + j, 0);

			if (_block->GetLineSize() == 1)
				break;

			_block->LineSizeCalculate(1);
		}

		if (_block->GetRockArray(i) == 10 && minRockY == i) {
			_block->SetLineOfPairFirst(i - 1);

			for (j = 0; j < _block->GetLineOfPairSecond(_block->GetLineSize()); ++j)
				_block->SetRockArray(i + j, 0);

			break;
		}
	}

	int sp0 = _block->GetLineOfPairFirst(0);
	if (sp0 != 0) {
		int sp1 = _block->GetLineOfPairFirst(1);
		int lineN0 = _block->GetLineOfPairSecond(0);
		int lineN1 = _block->GetLineOfPairSecond(1);

		for (i = 1; i <= gridSizeX - 2; ++i) {
			for (j = 1; j <= lineN0; ++j)
				_board->SetGridType(sp0 + j, i, TerrainType::None);
			for (j = 1; j <= lineN1; ++j)
				_board->SetGridType(sp1 + j, i, TerrainType::None);

			_board->Render();
		}

		int cnt = 0;
		int currY = 0;
		int totalN = 0;
		int currStartPoint = sp0;
		int currLineN = lineN0;
		if (sp1 == 0) {
			cnt = 1;
			totalN = sp0 - minRockY + 1;
		}
		else {
			cnt = 2 ;
			totalN = sp0 - sp1; 
		}

		while (cnt--) {
			for (i = 0; i < totalN; ++i) {				
				currY = currStartPoint - i;
				for (j = 1; j <= (gridSizeX - 2); ++j) {
					if (_board->GetGridTerrainType(currY, j) == TerrainType::Rock) {
						_board->SetGridType(currY, j, TerrainType::None);
						_board->SetGridType(currY + currLineN, j, TerrainType::Rock);
					}
				}

				_block->SetRockArray(currY + currLineN, _block->GetRockArray(currY));
				_block->SetRockArray(currY, 0);
			}

			if (cnt == 1) {
				currStartPoint = sp1;
				totalN = sp1 - minRockY + 1;
				currLineN += lineN1;
			}
		}

		_block->MinRockYCalculate2(currLineN);
	}

	_block->LineOfPairInit();
}

const bool Collision::NextCollisionToNotice(const int* coordY, const int* coordX, bool isCollision, const int distanceY, const int distanceX)
{
	for (int i = 0; i < 4; ++i) {
		TerrainType tType = _board->GetGridTerrainType(coordY[i] + distanceY, coordX[i] + distanceX);
		if (tType == TerrainType::Outside || tType == TerrainType::Wall || tType == TerrainType::Rock) {
			collisionIdx = i;
			isCollision = true;

			break;
		}
	}

	return isCollision;
}
