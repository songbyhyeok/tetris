#include "KeyManager.h"
#include "DefineController.h"

void KeyManager::Init()
{
    BitSetInit();
    VirtualKeyInit();
    _isMispres = false;
}

void KeyManager::BitSetInit()
{
    for (int i = 0; i < KEY_MAX_COUNT; ++i) {
        keyUp.set(i, false);
        keyDown.set(i, false);
    }
}

void KeyManager::VirtualKeyInit()
{
    virtualKey_Y = virtualKey_X = 0;
}

void KeyManager::SetIsMisPress(const bool tf)
{
    _isMispres = tf;
}

const bool KeyManager::GetIsMisPress()
{
    return _isMispres;
}

void KeyManager::SetVirtualKey_Y(const int y)
{
    virtualKey_Y = y;
}

void KeyManager::VirtualKey_Y_Calculate(const int n)
{
    virtualKey_Y += n;
}

const int KeyManager::GetVirtualKey_Y()
{
    return virtualKey_Y;
}

void KeyManager::SetVirtualKey_X(const int x)
{
    virtualKey_X = x;
}

void KeyManager::VirtualKey_X_Calculate(const int n)
{
    virtualKey_X += n;
}

const int KeyManager::GetVirtualKey_X()
{
    return virtualKey_X;
}

void KeyManager::SetKetUp(const int key, const bool state)
{
    keyUp.set(key, state);
}

const bitset<KEY_MAX_COUNT> KeyManager::GetkeyUp()
{
    return keyUp;
}

void KeyManager::SetKetDown(const int key, const bool state)
{
    keyDown.set(key, state);
}

const bitset<KEY_MAX_COUNT> KeyManager::GetkeyDown()
{
    return keyDown;
}

const bool KeyManager::IsOnceKeyDown(const int key)
{
    if (_isMispres) {
        _isMispres = false;

        return false;
    }

    if (GetAsyncKeyState(key) & 0x8000) {
        if (keyDown[key] == false) {
            keyDown.set(key, true);

            return true;
        }
   }

    keyDown.set(key, false);

    return false;
}

const bool KeyManager::IsOnceKeyUp(const int key)
{
    if (_isMispres) {
        _isMispres = false;

        return false;
    }

    if (GetAsyncKeyState(key) & 0x8000)
        keyUp.set(key, true);
    else {
        if (keyUp[key] == true) {
            keyUp.set(key, false);

            return true;
        }
    }

    return false;
}

const bool KeyManager::IsStayKeyDown(const int key)
{
    if (_isMispres) {
        _isMispres = false;

        return false;
    }

    if (GetAsyncKeyState(key) & 0x8000)
        return true;

   return false;
}

const bool KeyManager::IsToggleKey(const int key)
{
    if ((GetAsyncKeyState(key) == 0x0000) ||
        ((GetAsyncKeyState(key) & 0x0001)))
        return true;

    if (((GetAsyncKeyState(key) & 0x8000) == false))
        return false;
}
