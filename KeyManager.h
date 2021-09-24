#pragma once

#include "pch.h"

#define KEY_MAX_COUNT 166

/*
	   1. 0x0000 => 이전에 누른 적이 없고 호출 시점에서 안 눌린 상태
	   2. 0x0001 => 이전에 누른 적이 있고 호출 시점에서 안 눌린 상태
	   3. 0x8000 => 이전에 누른 적이 없고 호출 시점에서 눌린 상태
	   4. 0x8001 => 이전에 누른 적이 있고 호출 시점에서 눌린 상태
*/

class KeyManager
{
private:
	bitset<KEY_MAX_COUNT> keyUp;
	bitset<KEY_MAX_COUNT> keyDown;

	bool _isMispres;
	int virtualKey_Y;
	int virtualKey_X;

public:
	void Init();
	void BitSetInit();
	void VirtualKeyInit();
	void SetIsMisPress(const bool tf);
	const bool GetIsMisPress();
	void SetVirtualKey_Y(const int y);
	void VirtualKey_Y_Calculate(const int n);
	const int GetVirtualKey_Y();
	void SetVirtualKey_X(const int x);
	void VirtualKey_X_Calculate(const int n);
	const int GetVirtualKey_X();
	void SetKetUp(const int key, const bool state);
	const bitset<KEY_MAX_COUNT> GetkeyUp();
	void SetKetDown(const int key, const bool state);
	const bitset<KEY_MAX_COUNT> GetkeyDown();
	const bool IsOnceKeyDown(const int key);
	const bool IsOnceKeyUp(const int key);
	const bool IsStayKeyDown(const int key);
	const bool IsToggleKey(const int key);
};

