#include "Engine.hpp"

int main()
{
	Engine viewer3D;
	if (viewer3D.init())
	{
		viewer3D.run();
	}

}