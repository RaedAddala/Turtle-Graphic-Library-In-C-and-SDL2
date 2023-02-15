#pragma once
#include<vector>
#include<utility>

class FractalGenerator {
public:
	FractalGenerator();
	FractalGenerator(float Startx, float Starty, float Endx, float Endy);
	FractalGenerator(float Startx, float Starty ,float Endx, float Endy, std::vector<float>);
	void SetStartPoint(float x, float y);
	void SetEndPoint(float x, float y);
	void AddNode(float angle);
	bool Compute();
	bool GetEdge(float& x1, float& y1, float& x2, float& y2, int index);
private:
	float Startx, Starty;
	float Endx, Endy;
	std::vector<float> NodesAngle;
	std::vector<std::pair<float, float>> Points;
	bool StartDefined,EndDefined;
	bool MustBeComputed;
public : 
	int numEdges;
};

class SnowFlakeFractal {
public:
	SnowFlakeFractal();
	SnowFlakeFractal(std::vector<std::pair<float, float>> Vertecies);
	void AddVertex(float xPos, float yPos);
	bool GetEdge(float& x1, float& y1, float& x2, float& y2, int index);
	int nbEdges(void);
private:
	std::vector<std::pair<float, float>> Vertecies;
};