#include <SDL.h>
#include "InputManager.h"

void InputManager::Update() {
	std::memcpy(oldKeys.get(), keys, keyCount * sizeof(Uint8));
	oldButtons = buttons;
	SDL_PumpEvents();
	buttons = SDL_GetRelativeMouseState(&mouseX, &mouseY);
}

bool InputManager::KeyUp(const int iKeyIndex) const {
	return !keys[iKeyIndex] && oldKeys.get()[iKeyIndex];	
}

bool InputManager::KeyStillUp(const int iKeyIndex) const {
	return !keys[iKeyIndex] && !oldKeys.get()[iKeyIndex];
}

bool InputManager::KeyDown(const int iKeyIndex) const {
	return keys[iKeyIndex] && !oldKeys.get()[iKeyIndex];
}

bool InputManager::KeyStillDown(const int iKeyIndex) const {
	return keys[iKeyIndex] && oldKeys.get()[iKeyIndex];
}

bool InputManager::MouseUp(const int iButton) const {
	return !(buttons & SDL_BUTTON(iButton)) && (oldButtons & SDL_BUTTON(iButton));
}

bool InputManager::MouseStillUp(const int iButton) const {
	return !(buttons & SDL_BUTTON(iButton)) && !(oldButtons & SDL_BUTTON(iButton));
}

bool InputManager::MouseDown(const int iButton) const {
	return (buttons & SDL_BUTTON(iButton)) && !(oldButtons & SDL_BUTTON(iButton));
}

bool InputManager::MouseStillDown(const int iButton) const {
	return (buttons & SDL_BUTTON(iButton)) && (oldButtons & SDL_BUTTON(iButton));
}
