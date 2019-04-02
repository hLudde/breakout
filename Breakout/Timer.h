#pragma once
class Timer {
public:

	static Timer& GetInstance() {
		static Timer instance;
		return instance;
	}
	Timer(Timer const&) = delete;
	void operator=(Timer const&) = delete;

	void UpdateDeltaTime();
	double GetDeltaTime() const;

private:

	Uint64 now;
	Uint64 last = 0;
	double deltaTime = 0;

	Timer();
	~Timer() = default;
};