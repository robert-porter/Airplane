#pragma once
#include "rendercomponent.h"

class StaticSpriteRenderComponent :
	public RenderComponent
{
public:
	StaticSpriteRenderComponent(Entity *owner);
	StaticSpriteRenderComponent(Entity *owner, GLuint texture, float width, float height, int z);
	virtual ~StaticSpriteRenderComponent(void);


	void	SetWidth(float w) { width = w; }
	void	SetHeight(float h) { height = h; }
	void	SetRotationCenter(const Vector2 v) { rotationCenter = v; }

	virtual void Update(float deltaTime) { }
	virtual void Draw();
//private:
//	std::string name;
	GLuint		textureID;
	Vector2		positionAnchor;
	Vector2		rotationCenter;
	float		width;
	float		height;
	bool		flipX;
	bool		flipY;
	Color4f		tint;
};
