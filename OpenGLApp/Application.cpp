#include "stdincludes.h"

#include "Application.h"
#include "MathUtils.h"
#include "ConfigFile.h"
#include "EntityFactory.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "Renderer.h"
#include "RenderList.h"
#include "Airplane.h"

Application::Application(void) 
{

}

Application::~Application(void)
{

}

void Application::Update()
{
	FrameTimer::Frame();

	if(GetAsyncKeyState('Q'))
		camera.SetType(Camera::CT_FIRST_PERSON);
	if(GetAsyncKeyState('E'))
		camera.SetType(Camera::CT_THIRD_PERSON);

	world.Update();


	glutPostRedisplay();
}

void Application::Draw()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
//	camera.SetFrame(world.dude->movementComponent->GetPosition(), world.dude->movementComponent->GetRotation());
   


	for(unsigned int i = 0; i < world.entities.size(); i++)
	{
		RenderComponent *renderComponent = (RenderComponent *)world.entities[i]->visual;
		if ( renderComponent )
			renderComponent->Update(FrameTimer::DeltaTime());
	}

	glPushMatrix();
	glLoadIdentity();
	glScalef(1.0f/camera.extents.x, 1.0f/camera.extents.y, 1.0f);
	glRotatef(-180.0f/PI*camera.rotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-camera.position.x, -camera.position.y, 0.0f);
	
	RenderList renderList;

	for(unsigned int i = 0; i < world.entities.size(); i++)
	{
		RenderComponent *renderComponent = (RenderComponent *)world.entities[i]->visual;
		
		if ( renderComponent && world.entities[i]->IsValid() )
			renderList.Add(renderComponent);
	}
	renderList.Sort();
	renderList.Draw();
	
	//glPopMatrix();
	
	for(unsigned int i = 0; i < world.entities.size(); i++)
	{
		glColor4f(1, 0, 0, 1);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		CollisionComponent *c = (CollisionComponent *)world.entities[i]->shape;
		if ( c )
			c->Draw();
	}
	

	DrawLifebar();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}


void Application::Init(int argc, char **argv)
{
	ConfigFile cfgFile("appconfig");
	int width = cfgFile.GetInt("width");
	int height = cfgFile.GetInt("height");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("S2");

	lifebarBorder = Renderer::GetTexture("lifebarBorder.png");
	lifebarFill = Renderer::GetTexture("lifebar.png");

	FrameTimer::Start();



	world.dude = EntityFactory::CreatePlayer(Vector2(0.0f, 0.0f), 0.0f);

	EntityFactory::CreatePowerup(Vector2(3,3), 0, 0);
	EntityFactory::CreateBounds(camera.extents.Length() * 1.5f);
	EntityFactory::CreateSpawner();

	EntityFactory::CreateBackground();

}

void Application::DrawLifebar()
{
	float lifebarHeight = 14.0f;
	float borderThickness = 2.0f;
	float lifebarWidth = 128.0f;
	float fillHeight = lifebarHeight - 2.0f * borderThickness;
	float maxFillWidth = lifebarWidth - 2.0f * borderThickness;
	float fillWidth = maxFillWidth * world.dude->health / world.dude->maxHealth;

	float pixelToCamScale = camera.extents.x * 2.0f/500.0f;

	float fullHeight = 1.6f;
	float height = fullHeight * world.dude->health / 100.0f;

	Vector2 lifebarPos(-2.5f, 3.3f);

	Vector2 fillOffset = pixelToCamScale * Vector2(maxFillWidth/2.0 - fillWidth/2.0f, 0.0f);

	Renderer::DrawTexturedQuad(lifebarBorder, lifebarPos, lifebarWidth * pixelToCamScale, lifebarHeight * pixelToCamScale, 0.0f, Vector2(0.0f,0.0f), false, false, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	Renderer::DrawTexturedQuad(lifebarFill, lifebarPos - fillOffset, fillWidth * pixelToCamScale, fillHeight * pixelToCamScale, 0.0f, Vector2(0.0f,0.0f), false, false, Color4f(1.0f, 1.0f, 1.0f, 1.0f));

}