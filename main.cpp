#include "Viewer3D.hpp"


int main(void)
{
	Viewer3D viewer3D;

	if (viewer3D.init())
	{
		viewer3D.run();
	}

	return 0;
}
