#pragma once
#include <iostream>
class InputManager {
public:
	static InputManager& getInstance() {
		static InputManager instance;
		return instance;
	}

	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;

	bool KeyDown(int iKeyIndex);
	bool KeyStillDown(int iKeyIndex);
	bool KeyUp(int iKeyIndex);
	bool KeyStillUp(int iKeyIndex);
	bool MouseDown(int iButton);
	bool MouseStillDown(int iButton);
	bool MouseUp(int iButton);
	bool MouseStillUp(int iButton);

	void Update();

protected:
	const Uint8* keys;
	std::unique_ptr<Uint8> oldKeys;
	int keyCount;
	int mouseX;
	int mouseY;
	Uint8 buttons;
	Uint8 oldButtons;

private:
	InputManager() {
		keyCount = 0;
		keys = SDL_GetKeyboardState(&keyCount);
		buttons = SDL_GetRelativeMouseState(&mouseX, &mouseY);
		oldKeys = std::unique_ptr<Uint8>(new Uint8[keyCount]);
		std::cout << "I am alive!" << std::endl;
	};
	
	~InputManager() {
		std::cout << "You killed me ;-;" << std::endl;
	};
	
};
