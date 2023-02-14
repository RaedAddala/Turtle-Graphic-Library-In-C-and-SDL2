#pragma once
#include"global.hpp"

class GTurtle
{
public:
	GTurtle();
	GTurtle(float x, float y);
	GTurtle(float x, float y, float length, float angle);
	GTurtle(float x, float y,SDL_Color color);
	GTurtle(float x, float y, float length, float angle, SDL_Color color);
	GTurtle(float x, float y, unsigned thickness, SDL_Color color);
	GTurtle(float x, float y, float length, float angle, unsigned thickness, SDL_Color color);
	GTurtle(float x, float y, unsigned thickness);

	void setPos(float, float);
	void setAngle(float);
	void setLength(float);

	void RotateRight(float angle);
	void RotateLeft(float angle);

	void DrawModeOn();
	void DrawModeOff();
	void SetDrawColor(SDL_Color);
	void SetDrawThickness(unsigned);

	void AddRed(Sint16);
	void AddGreen(Sint16);
	void AddBlue(Sint16);

	void LookAt(float x, float y);
	float GetLength(void);
	float GetPosX(void);
	float GetPosY(void);
	void Step();

private:
	float xPos, yPos;
	float angle, length;
	SDL_bool DrawMode;
	SDL_Color Color;
	unsigned Thickness;
};
