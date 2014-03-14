#pragma once

#include "stdincludes.h"
#include "rendercomponent.h"

class AnimatedSpriteRenderComponent : public RenderComponent
{
public:
	AnimatedSpriteRenderComponent(Entity *owner, GLuint *textures, unsigned int numFrames, float delay, float w, float h);
	~AnimatedSpriteRenderComponent(void);

	void Draw();
	void Update(float deltaTime);

private:

	std::vector<GLuint> textureIDs;
	float			delay;

	float			timeAccum;
	unsigned int	currentFrame;

	Vector2			positionAnchor;
	Vector2			rotationCenter;
	float			width;
	float			height;
	bool			flipX;
	bool			flipY;
	Color4f			tint;
};
