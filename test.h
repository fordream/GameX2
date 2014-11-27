#pragma once
#include "GameX.h"

struct Maple{
	int x, y;
	float angle;
	int life;
	int v;
	RGBAData c;
};

class GameMain : public GameX{
private:
	vector<Maple> maples;

	int y;

public:
	GameMain(string title, int cx, int cy, int maxfps);
	//~GameMain();
	void Update();
	//void Begin();
	//void End();
};