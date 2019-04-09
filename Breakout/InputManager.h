#pragma once
#include <iostream>
class InputManager {
public:
	static InputManager& GetInstance() {
		static InputManager instance;
		return instance;
	}

	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;

	bool KeyDown(int iKeyIndex) const;
	bool KeyStillDown(int iKeyIndex) const;
	bool KeyUp(int iKeyIndex) const;
	bool KeyStillUp(int iKeyIndex) const;
	bool MouseDown(int iButton) const;
	bool MouseStillDown(int iButton) const;
	bool MouseUp(int iButton) const;
	bool MouseStillUp(int iButton) const;

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
		std::cout << "Created an instance of InputManager!" << std::endl;
	};
	
	~InputManager() {
		std::cout << "Killed InputManager!" << std::endl;
	};
	
};
