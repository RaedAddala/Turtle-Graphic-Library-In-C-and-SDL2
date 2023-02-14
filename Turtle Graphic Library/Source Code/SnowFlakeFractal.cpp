#include"../Headers/SnowFlakeFractal.hpp"
#include"../Headers/GTurtle.hpp"

#include <cmath>

/*
	The generator will take two points : 
	x----------------------x
	and generate some edges in the middle so we will always have something like this : 
	x----x|some edges|x----x 
	which means that we will always have two edges one at the start and the other in the end
*/
static constexpr float ToRadian = (static_cast<float>(M_PI) / 180.0f);
extern GTurtle* Turtle;

FractalGenerator::FractalGenerator()
	:Startx(0.0f),Starty(0.0f),Endx(0.0f),Endy(0.0f),NodesAngle({}), Points({}),StartDefined(true), EndDefined(true),MustBeComputed(false),numEdges(0)
{};
FractalGenerator::FractalGenerator(float Startx, float Starty, float Endx, float Endy)
	:Startx(Startx), Starty(Starty), Endx(Endx), Endy(Endy), NodesAngle({}), Points({{Startx,Starty},{Endx,Endy}}), StartDefined(true), EndDefined(true), MustBeComputed(true), numEdges(1)
{};
FractalGenerator::FractalGenerator(float Startx, float Starty ,float Endx, float Endy, std::vector<float> Nodes)
	:Startx(Startx), Starty(Starty), Endx(Endx), Endy(Endy), NodesAngle(Nodes), Points({}),StartDefined(true),EndDefined(true),MustBeComputed(true),numEdges( 2 + Nodes.size())
{
	Compute();
};
void FractalGenerator::SetStartPoint(float x, float y) 
{
	Startx = x;
	Starty = y;
	StartDefined = true;
	if (EndDefined && numEdges == 0) numEdges = 1;
};
void FractalGenerator::SetEndPoint(float x, float y) 
{
	Endx = x;
	Endy = y;
	EndDefined = true;
	if (StartDefined && numEdges == 0) numEdges = 1;
};
void FractalGenerator::AddNode(float angle)
{
	NodesAngle.emplace_back(angle);
	numEdges = 2 + NodesAngle.size();
};

bool FractalGenerator::Compute() 
{
	if (!StartDefined || !EndDefined) return false;
	Points.clear();
	Points.emplace_back(Startx,Starty);

	if (numEdges > 1)
	{
		// We need to calculate the length of each individual edge : the original length / the number of segments 
		// the number of segments is calculated throught the projection of each edge on the x-axis
		/*
				 /
				/ -120
			   /\
			  /  \
			 /    \			==> In this case the # of segments = 2 + |cos(60)| + |cos(-120)| = 3
		____/60____\____ 
		*/

		float nbSegs = 2.0f;
		float cumulativeAngle = 0.0f;
		for (float& i : NodesAngle)
		{
			cumulativeAngle += i;
			nbSegs += fabsf(cosf(cumulativeAngle * ToRadian));
		}
		float InitialLength = SDL_sqrtf( (Endx-Startx)* (Endx - Startx) + (Endy - Starty) * (Endy - Starty));
		float edgeLength = InitialLength / nbSegs;
		float temp = Turtle->GetLength();
		Turtle->DrawModeOff();
		Turtle->setLength(edgeLength);
		Turtle->setPos(Startx,Starty);
		Turtle->LookAt(Endx, Endy); // The First Edge
		Turtle->Step();
		Points.emplace_back(Turtle->GetPosX(), Turtle->GetPosY());
		for (auto& cur : NodesAngle)
		{
			Turtle->RotateLeft(cur);
			Turtle->Step();
			Points.emplace_back(Turtle->GetPosX(), Turtle->GetPosY());
		}
		Turtle->setLength(temp);
		Turtle->DrawModeOn();
	}
	Points.emplace_back(Endx, Endy);
	return true;
};
bool FractalGenerator::GetEdge(float& x1, float& y1, float& x2, float& y2, int index) 
{
	if (index > (numEdges - 1)) return false;
	if (MustBeComputed == false)
	{
		MustBeComputed = true;
		Compute();
	}
	x1 = Points[index].first;
	y1 = Points[index].second;
	x2 = Points[index+1LL].first;
	y2 = Points[index+1LL].second;
	return true;
};

