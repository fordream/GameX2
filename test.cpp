#include "test.h"

GameMain::GameMain(string title, int cx, int cy, int maxfps) :GameX(title, cx, cy, maxfps){
	//随机数种子
	srand(clock());
	SetFontSize(20);
	y = 0;
	//Play("cc.mp3", 0);
	//cout << "music" << endl;
};

void GameMain::Update(){
	/*
	glBegin(GL_LINES);
	glColor3f(100, 100, 100);
	glVertex2f(0, 0);
	glVertex2f(100, 100);
	glEnd;
	*/

	//SetColor(RGBAData(255, 255, 255));

	Texture *tex = LoadTexture("qb.jpg");
	Draw(tex,Rect(100,100,627/3,886/3));


	for (vector<Maple>::iterator iter = maples.begin(); iter != maples.end();)
	{
		SetColor(RGBAData(iter->c.r, iter->c.g, iter->c.b, iter->life));
		Draw("Particle.png", iter->x, iter->y, 25, 20, iter->angle);
		iter->angle += 3;
		iter->life -= 5;
		iter->v++;
		iter->y += iter->v;
		if (iter->life <= 0)
		{
			//maples.erase(iter++);
			iter->life = 255;
			iter->x = rand() % 1000 * 1.440;
			iter->y = 0;
			if (iter->v > 20)
			{
				iter->v = 1;

				iter->c.r -= rand() % 100;
				if (iter->c.r < 0)iter->c.r = 0;
				if (iter->c.r == 0)iter->c.g -= rand() % 100;
				if (iter->c.g < 0)iter->c.g = 0;
				if (iter->c.g == 0)iter->c.b -= rand() % 100;
				if (iter->c.b < 0){ iter->c.b = 0; iter->c.r = iter->c.g = iter->c.b = 255; }

			}
			iter++;

		}
		else
			iter++;
	}
	static int count_time = 0;
	count_time++;
	if (count_time>30){
		for (int i = 0; i < 3; i++){
			Maple w;
			w.life = 255; w.angle = rand() % 100 * 3.60; w.y = 0; w.x = rand() % 1000 * (800.0/1000); w.v = 1;
			w.c.a = w.c.g = w.c.b = 255;
			maples.push_back(w);
		}
		count_time = 0;
	}

	SetColor(RGBAData(255, 255, 255));
	stringstream temp;
	temp << "FPS:" << GetFPS();
	Text(temp.str(), 0, 0);
	stringstream temp2;
	temp2 << "Number of Maples:" << maples.size();
	Text(temp2.str(), 0, 64);

}
