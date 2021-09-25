#pragma once

#include "SceneManager.h"
#include "InputManager.h"
#include "KeyManager.h"

class Manager
{
private:
	SceneManager* scene;
	InputManager* input;
	KeyManager* key;
	
public:
	// 그냥 리턴을 하면 오브젝트가 복사가 된다.
	// 레퍼런스 형태로 복사를 한다.
	static Manager& Instance() {
		static Manager instance;
		return instance;
	}

	static SceneManager& Scene() {	
		return *(Instance().scene);
	}

	static InputManager& Input() {
		return *(Instance().input);
	}

	static KeyManager& Key() {
		return *(Instance().key);
	}

	Manager() {
		scene = new SceneManager();
		input = new InputManager();
		key = new KeyManager();

		scene->Init();
		key->Init();
	};
	// obj가 obj를 copy를 할 경우 두 개의 인스턴스가 생기는 것이기 때문에 막는다.
	// copy constructor 복사 생성자
	Manager(const Manager&) = delete;
	// copy assignment 복사 대입 연산자
	Manager& operator= (const Manager&) = delete;

	static void Update() 
	{
		Input().UseKeyAction();
	}
};


