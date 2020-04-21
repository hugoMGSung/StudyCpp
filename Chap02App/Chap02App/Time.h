#pragma once

class Time {
private:
	int hour, min, sec;

public:
	void SetTime(int h, int m, int s);
	void OutTime();
};