#include "InputManager.h"
#include "pch.h"
#include "Manager.h"

void InputManager::Getch()
{
	_getch();
	system("cls");

	Manager::Key().SetIsMisPress(true);
}

void InputManager::SetKeyAction(KeyAction fp)
{
	onHandler1 = std::move(fp);
}

void InputManager::UseKeyAction()
{
	if (onHandler1)
		onHandler1();
}

void InputManager::RemoveKeyAction()
{
	onHandler1 = nullptr;
	cout << "removeKeyAction";
}

void InputManager::RemoveHandler(KeyAction fp)
{
	if (fp)
		RemoveKeyAction();
}
