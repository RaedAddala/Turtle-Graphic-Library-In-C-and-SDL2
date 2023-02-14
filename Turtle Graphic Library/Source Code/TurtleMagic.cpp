#include"../Headers/TurtleMagic.hpp"
#include"../Headers/SnowFlakeFractal.hpp"
extern GTurtle* Turtle;

void TurtleDoMagic()
{
	if (Turtle)
	{
		Turtle->SetDrawColor({ 100,25,50,255 });
		FractalGenerator Generator(100.0f, 100.0f, 480.0f, 400.0f);
		Generator.AddNode(60.0f);
		Generator.AddNode(-150.0f);
		Generator.AddNode(0.0f);
		Generator.AddNode(150.0f);
		Generator.AddNode(-30.0f);
		if (Generator.Compute())
		{
			float x1, y1, x2, y2;
			for (int i = 0; i < Generator.numEdges; ++i)
			{
				Generator.GetEdge(x1, y1, x2, y2, i);
				SDL_RenderDrawLine(Renderer, static_cast<int>(x1), static_cast<int>(yal1), static_cast<int>(x2), static_cast<int>(y2));
			}
		}
	}
}