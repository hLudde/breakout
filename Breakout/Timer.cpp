#include <SDL.h>
#include "Timer.h"

Timer::Timer() {
	now = SDL_GetPerformanceCounter();
}

void Timer::UpdateDeltaTime() {
	last = now;
	now = SDL_GetPerformanceCounter();
	deltaTime = static_cast<double>(now - last) * 1000 / SDL_GetPerformanceFrequency();
	if(deltaTime>20) {
		deltaTime = static_cast<double>(20);
	}
}

double Timer::GetDeltaTime() const {
	return deltaTime;
}
