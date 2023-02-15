#include"../Headers/TurtleMagic.hpp"
#include"../Headers/SnowFlakeFractal.hpp"
extern GTurtle* Turtle;
void DrawEdge(float x1, float y1, float x2, float y2, int level,FractalGenerator& generator);
void TurtleDoMagic()
{
	if (Turtle)
	{
		FractalGenerator Generator;
		SnowFlakeFractal Shape;

		Shape.AddVertex(50.0f, 100.0f);
		Shape.AddVertex(350.0f, 280.0f);
		Shape.AddVertex(550.0f, 400.0f);

		Generator.AddNode(60.0f);
		Generator.AddNode(-120.0f);


		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
		float x1, y1, x2, y2;

		for (int j = 0; j < Shape.nbEdges(); ++j)
		{
			if (Shape.GetEdge(x1, y1, x2, y2, j))
				DrawEdge(x1, y1, x2, y2, 1,Generator);
		}

	}
}

// Recursive Drawing;
void DrawEdge(float x1,float y1, float x2, float y2, int level, FractalGenerator& generator)
{
	level--;
	if (level < 0) return;

	std::vector<std::pair<float, float>> Edges;
	Edges.reserve(generator.numEdges+1LL);
	generator.SetStartPoint(x1, y1);
	generator.SetEndPoint(x2, y2);
	generator.Compute();
	float genX1, genY1, genX2, genY2;
	for (int j = 0; j < generator.numEdges; j += 2)
	{
		if (generator.GetEdge(genX1, genY1, genX2, genY2, j))
		{
			Edges.emplace_back(genX1, genY1);
			Edges.emplace_back(genX2, genY2);
		}
	}
	generator.GetEdge(genX1, genY1, genX2, genY2, 0);
	Edges.emplace_back(genX1, genY1);
	for (int j = 0; j < generator.numEdges; ++j)
	{
		if (level == 0)
		{
			SDL_RenderDrawLine(Renderer,
				 static_cast<int>(SDL_roundf(Edges[j].first)) , static_cast<int>(SDL_roundf(Edges[j].second))
				,static_cast<int>(SDL_roundf(Edges[j+1].first)), static_cast<int>(SDL_roundf(Edges[j+1].second))
			);
		}
		else
		{
			DrawEdge(Edges[j].first, Edges[j].second, Edges[j + 1LL].first, Edges[j + 1LL].second, level,generator);
		}
	}

}