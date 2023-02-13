#include"../Headers/TurtleMagic.hpp"
extern GTurtle* Turtle;

void TurtleDoMagic()
{
	if (Turtle)
	{
		for (unsigned i = 0; i < 50; ++i)
		{
			for (unsigned j = 0; j < 12; ++j)
			{
				Turtle->RotateRight(30);
				Turtle->Step();
			}
			Turtle->RotateLeft(10);
			Turtle->AddRed(25);
			Turtle->AddBlue(10);
		}
	}
}