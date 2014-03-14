#include <windows.h>
#include <gl\gl.h>
#include "glut.h"
#include "Application.h"
#include "stdincludes.h"


Application app;

void Draw()
{
	app.Draw();
}

void Update()
{	
	app.Update();
}

void main(int argc, char** argv)
{

	try { 
	app.Init(argc, argv);

	glutIdleFunc(Update);
	glutDisplayFunc(Draw);
	glutMainLoop();
	}
	catch(std::exception e)
	{
		std::cout<<e.what()<<std::endl;
	}
}
