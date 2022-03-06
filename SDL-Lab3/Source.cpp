#include<iostream>
#include<SDL.h>

const int win_width = 1280;
const int win_height = 640;

int askUserDraw()
{
	int choise;
	do {
		printf("Введите:\n1 - нарисовать конверт\n2 - нарисовать звёздное небо\n3 - нарисовать график\nВыбор:");
		scanf_s("%d", &choise);
	} while (choise > 3 || choise < 1);
	return choise;
}

void drawEnvelope(SDL_Renderer* ren)
{
	SDL_Rect rect{ win_width / 5,win_height / 5,win_width / 1.8,win_height / 1.8 };
	SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
	SDL_RenderDrawLine(ren, rect.x, rect.y, rect.x + rect.w / 2, rect.y + rect.h / 2);

	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderDrawLine(ren, rect.x + rect.w / 2, rect.y + rect.h / 2, rect.x + rect.w, rect.y);

	SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
	SDL_RenderDrawRect(ren, &rect);
}

void drawStarrySky(SDL_Renderer* ren)
{
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	
	float rad = M_PI / 180;
	float r = 15, step = 0.1;
	for (float angle = 0; angle < 360; angle += step)
	{
		r = 45 * sin(angle / sqrt(2)) * 35;
		SDL_RenderDrawLine(ren, sin(angle * rad) * r + win_width, cos(angle * rad) * r + 0, sin((angle + 0.1) * rad) * r + win_width, cos((angle + 0.1) * rad) * r + 0);
		r += step;
	}
}

void drawStreak(SDL_Renderer* ren, int x, int y, int win_w, int win_h, int scale)
{
	SDL_RenderDrawLine(ren, x, 0, x, win_h);
	SDL_RenderDrawLine(ren, 0, y, win_w, y);

	for (int i = x; i < win_w; i += scale)
	{
		SDL_RenderDrawLine(ren, i + scale, y - 8, i + scale, y + 8);
		SDL_RenderDrawLine(ren, win_w- i, y - 8, win_w- i, y + 8);
	}

	for (int i = y; i < win_h; i += scale)
	{
		SDL_RenderDrawLine(ren, x - 8, i + scale, x + 8, i + scale);
		SDL_RenderDrawLine(ren, x - 8, win_h - i, x + 8, win_h- i);
	}
}
void askUserCoefficients(float mas[4])
{
	for (int i = 0; i < 4; i++)
	{
		printf("Введите K%d коэффициент функции: ", i + 1);
		scanf_s("%f", &mas[i]);
	}
}
void drawGraph(SDL_Renderer* ren, int a, int b, int scale)
{
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	drawStreak(ren, win_width / 2, win_height/ 2, win_width, win_height, scale);
	SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
	float step = 0.01;
	float coeffs[4]; askUserCoefficients(coeffs);
	for (float i = a; i < b; i += step)
	{
		float x_s = i + step;
		SDL_RenderDrawLine(ren,
			win_width / 2 + i * scale,
			win_height / 2 - (coeffs[0] * (i + coeffs[1])*(i+coeffs[1]) + coeffs[2] * sqrt(i) + coeffs[3]) * scale,
			win_width / 2 + x_s * scale,
			win_height / 2 - (coeffs[0] * (x_s + coeffs[1]) * (x_s + coeffs[1]) + coeffs[2] * sqrt(x_s) + coeffs[3]) * scale);
	}
}

int main(int args,char* argv[])
{
	/*1.Конверт
	2.Звёздное небо
	3.Y = A(x + B) ^ 2 + Cx ^ 0.5 + D, [0; 10].*/
	system("chcp 1251"); system("cls");

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* win = SDL_CreateWindow("Semikin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(ren, 50, 50, 50, 255);
	SDL_RenderClear(ren);
	
	switch (askUserDraw())
	{
	case 1:
		drawEnvelope(ren);
		break;
	case 2:
		drawStarrySky(ren);
		break;
	case 3:
		drawGraph(ren, 0, 10, 15);
		break;
	}
	SDL_RenderPresent(ren);

	SDL_Delay(10000);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}