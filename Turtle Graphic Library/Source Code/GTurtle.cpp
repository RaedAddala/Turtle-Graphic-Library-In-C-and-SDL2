#include"../Headers/GTurtle.hpp"
#include<math.h>
#include<algorithm>

static constexpr float ToRadian = (static_cast<float>(M_PI) / 180.0f);
static constexpr float ToDegree = (180.0f / static_cast<float>(M_PI));
static constexpr float HALF_PI = static_cast<float>(M_PI) / 2.0f;


GTurtle::GTurtle()
	:xPos(0), yPos(0), angle(0.0), length(1.0), DrawMode(SDL_FALSE), Color({ 255,255,255,255 }), Thickness(1)
{};
GTurtle::GTurtle(float x, float y) 
	:xPos(x), yPos(y), angle(0.0), length(1.0), DrawMode(SDL_FALSE), Color({ 255,255,255,255 }), Thickness(1)
{};
GTurtle::GTurtle(float x, float y, float length, float angle) 
	:xPos(x), yPos(y), angle(angle), length(length), DrawMode(SDL_FALSE), Color({ 255,255,255,255 }), Thickness(1)
{};
GTurtle::GTurtle(float x, float y, SDL_Color color)
	:xPos(x), yPos(y), angle(0.0), length(1.0), DrawMode(SDL_FALSE), Color(color), Thickness(1)
{};
GTurtle::GTurtle(float x, float y, float length, float angle, SDL_Color color)
	:xPos(x), yPos(y), angle(angle), length(length), DrawMode(SDL_FALSE), Color(color),Thickness(1)
{};
GTurtle::GTurtle(float x, float y, unsigned thickness, SDL_Color color) 
	:xPos(x), yPos(y), angle(0.0), length(1.0), DrawMode(SDL_FALSE), Color(color), Thickness(thickness)
{};
GTurtle::GTurtle(float x, float y, float length, float angle, unsigned thickness, SDL_Color color)
	:xPos(x), yPos(y), angle(angle), length(length), DrawMode(SDL_FALSE), Color(color), Thickness(thickness)
{};
GTurtle::GTurtle(float x, float y, unsigned thickness) 
	:xPos(x), yPos(y), angle(0.0), length(1.0), DrawMode(SDL_FALSE), Color({ 255,255,255,255 }), Thickness(thickness)
{};
void GTurtle::setPos(float x, float y)
{
	xPos = x;
	yPos = y;
};
void GTurtle::setAngle(float a)
{
	angle = a* ToRadian;
};
void GTurtle::setLength(float l)
{
	length = l;
};

void GTurtle::RotateRight(float angle)
{
	this->angle -= angle * ToRadian;
};
void GTurtle::RotateLeft(float angle)
{
	this->angle += angle * ToRadian;
};

void GTurtle::DrawModeOn()
{
	DrawMode = SDL_TRUE;
};
void GTurtle::DrawModeOff()
{
	DrawMode = SDL_FALSE;
};
void GTurtle::SetDrawColor(SDL_Color color = { 255,255,255,255 })
{
	Color = color;
};
void GTurtle::SetDrawThickness(unsigned thickness = 1)
{
	if (static_cast<unsigned>(WINDOW_HEIGHT) < thickness) Thickness = 1;
	Thickness = thickness;
};
void GTurtle::Step()
{
	float Sx = xPos, Sy = yPos;
	float Dx = Sx + length*cosf(angle);
	float Dy = Sy + length*sinf(angle);

	xPos = Dx;
	yPos = Dy;

	if (DrawMode == SDL_TRUE && Renderer != nullptr && length > 1)
	{
		SDL_SetRenderDrawColor(Renderer, Color.r, Color.g, Color.b, Color.a);
		SDL_RenderDrawLine(Renderer, static_cast<int>(lroundf(Sx)), static_cast<int>(lroundf(Sy))
								   , static_cast<int>(lroundf(Dx)), static_cast<int>(lroundf(Dy)));
		unsigned nbLines = (Thickness - 1) / 2;

		if(fabsf(Dx-Sx) > 1e4 ) 
			for(unsigned i = 1 ; i <= nbLines ; ++i)
				SDL_RenderDrawLine(Renderer, static_cast<int>(lroundf(Sx+i)), static_cast<int>(lroundf(Sy))
									       , static_cast<int>(lroundf(Dx+i)), static_cast<int>(lroundf(Dy)));
		else 
			for (unsigned i = nbLines+1; i < Thickness; ++i)
				SDL_RenderDrawLine(Renderer, static_cast<int>(lroundf(Sx)), static_cast<int>(lroundf(Sy + i))
										   , static_cast<int>(lroundf(Dx)), static_cast<int>(lroundf(Dy + i)));

		if (fabsf(Dy - Sy) > 1e4) 
			for (unsigned i = 1; i <= nbLines; ++i)
				SDL_RenderDrawLine(Renderer, static_cast<int>(lroundf(Sx)), static_cast<int>(lroundf(Sy+i))
										   , static_cast<int>(lroundf(Dx)), static_cast<int>(lroundf(Dy+i)));
		else
			for (unsigned i = nbLines + 1; i < Thickness; ++i)
				SDL_RenderDrawLine(Renderer, static_cast<int>(lroundf(Sx + i)), static_cast<int>(lroundf(Sy))
										   , static_cast<int>(lroundf(Dx + i)), static_cast<int>(lroundf(Dy)));
	}
};

void GTurtle::AddRed(Sint16 r)
{
	Color.r += static_cast<Uint8>(r);
};
void GTurtle::AddGreen(Sint16 g)
{
	Color.g += static_cast<Uint8>(g);
};
void GTurtle::AddBlue(Sint16 b)
{
	Color.b += static_cast<Uint8>(b);
};

void GTurtle::LookAt(float x, float y)
{
	float dx = x - xPos;
	float dy = y - yPos;

	if (dx == 0)
	{
		if (dy > 0.0f) angle = HALF_PI;
		else if (dy < 0.0f) angle = -HALF_PI;
	}
	else
	{
		angle = atanf(dy / dx);
		if (dx < 0.0f) angle += static_cast<float>(M_PI); 
		// atanf result will be in the domain ]-PI/2 , PI/2[ and for me in this context -60 and 300 are not the same 
		// I want negative to represent orientation.
	}
}
float  GTurtle::GetLength(void)
{
	return length;
}

float  GTurtle::GetPosX(void)
{
	return xPos;
}

float  GTurtle::GetPosY(void)
{
	return yPos;
}




