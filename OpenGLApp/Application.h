#pragma once

#include "stdincludes.h"



#include "Timer.h"
#include "Camera.h"

#include "Renderer.h"
#include "Entity.h"
#include "World.h"


class Application
{
public:
	Application(void);
	~Application(void);

	void Init(int, char **);
	void Update();
	void Draw();

	void DrawLifebar();

protected:
	World		world;
	Camera		camera;

	GLuint		lifebarBorder;
	GLuint		lifebarFill;
};