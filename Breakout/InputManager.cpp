#pragma once
#include <SDL.h>
#include "InputManager.h"

void InputManager::Update() {
	std::memcpy(oldKeys.get(), keys, keyCount * sizeof(Uint8));
	oldButtons = buttons;
	SDL_PumpEvents();
	buttons = SDL_GetRelativeMouseState(&mouseX, &mouseY);
}

bool InputManager::KeyUp(int iKeyIndex){
	return !keys[iKeyIndex] && oldKeys.get()[iKeyIndex];	
}

bool InputManager::KeyStillUp(int iKeyIndex){
	return !keys[iKeyIndex] && !oldKeys.get()[iKeyIndex];
}

bool InputManager::KeyDown(int iKeyIndex){
	return keys[iKeyIndex] && !oldKeys.get()[iKeyIndex];
}

bool InputManager::KeyStillDown(int iKeyIndex){
	return keys[iKeyIndex] && oldKeys.get()[iKeyIndex];
}

bool InputManager::MouseUp(int iButton){
	return !(buttons & SDL_BUTTON(iButton)) && (oldButtons & SDL_BUTTON(iButton));
}

bool InputManager::MouseStillUp(int iButton){
	return false; !(buttons & SDL_BUTTON(iButton)) && !(oldButtons & SDL_BUTTON(iButton));
}

bool InputManager::MouseDown(int iButton){
	return (buttons & SDL_BUTTON(iButton)) && !(oldButtons & SDL_BUTTON(iButton));
}

bool InputManager::MouseStillDown(int iButton){
	return (buttons & SDL_BUTTON(iButton)) && (oldButtons & SDL_BUTTON(iButton));
}