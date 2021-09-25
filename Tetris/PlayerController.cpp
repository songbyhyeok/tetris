#include "PlayerController.h"
#include "pch.h"
#include "Manager.h"
#include "DefineController.h"
#include "Block.h"
#include "Board.h"
#include "Collision.h"

void PlayerController::Init(Collision& collision, const int y, const int x)
{
    _collision = &collision;

    SetStartPoint(y, x);
    Manager::Input().SetKeyAction(std::bind(&PlayerController::OnMoveMentMode, this));
}
    
void PlayerController::YCalculate(const int y)
{
    _y += y;
}

void PlayerController::SetStartPoint(const int y, const int x)
{
    _y = y;
    _x = x;
}

const int *PlayerController::GetY()
{
    return &this->_y;
}

void PlayerController::XCalculate(const int x)
{
    _x += x;
}

const int *PlayerController::GetX()
{
    return &this->_x;
}

void PlayerController::OnStayMode()
{
    sumStayTick = 0;
    Manager::Key().SetVirtualKey_Y(1);

    _collision->OnCollisionBeVersionGravity(Manager::Key().GetVirtualKey_Y());
}

void PlayerController::OnMoveMentMode()
{
    sumMoveTick = 0;
    Manager::Key().VirtualKeyInit();

    if (Manager::Key().IsOnceKeyDown(VK_SPACE)) {
        _collision->OnVerticalDropMode();

        return;
    }
    if (Manager::Key().IsStayKeyDown(VK_LEFT))
        Manager::Key().VirtualKey_X_Calculate(-1);
    if (Manager::Key().IsStayKeyDown(VK_RIGHT))
        Manager::Key().VirtualKey_X_Calculate(+1);
    if (Manager::Key().IsStayKeyDown(VK_DOWN))
        Manager::Key().VirtualKey_Y_Calculate(+1);
    if (Manager::Key().IsOnceKeyUp(VK_UP)) {
        _collision->OnCollisionBeVersionRotation(Manager::Key().GetVirtualKey_Y(), Manager::Key().GetVirtualKey_X());

        return;
    }

    _collision->OnCollisionBeVersionAuto(Manager::Key().GetVirtualKey_Y(), Manager::Key().GetVirtualKey_X());
}

void PlayerController::Update(const int deltaTick)
{
    // 100 m/s 보다 커진다면 실행한다.
    sumStayTick += deltaTick;
    sumMoveTick += deltaTick;
    if (sumStayTick >= NONE_TICK)
        OnStayMode();
    if (sumMoveTick >= MOVE_TICK)
        OnMoveMentMode();
}
