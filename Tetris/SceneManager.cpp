#include "SceneManager.h"
#include "pch.h"

void SceneManager::Init()
{
    next = false;
}

void SceneManager::LoadScene()
{
    next = true;
}

bool SceneManager::GetNext()
{
    return next;
}

