#pragma once
#include "pch.h"

class InputManager
{
private:
    typedef std::function<void()> KeyAction;
    KeyAction onHandler1;

public:
    void Getch();
    void SetKeyAction(KeyAction fp);
    KeyAction GetKeyAction() { return onHandler1; }
    void UseKeyAction();
    void RemoveKeyAction();
    void RemoveHandler(KeyAction fp = nullptr);
};

