#include "AnimatedSpriteRenderComponent.h"
#include "movementComponent.h"
#include "Entity.h"
AnimatedSpriteRenderComponent::AnimatedSpriteRenderComponent(Entity *owner, GLuint *textures, unsigned int numFrames, float delay, float w, float h) : RenderComponent(owner)
{
	textureIDs.reserve(numFrames);
	for(unsigned int i = 0; i < numFrames; i++)
	{
		textureIDs.push_back(textures[i]);
	}
	this->delay = delay;
	width = w;
	height = h;
	rotationCenter.Set(0,0);
	positionAnchor.Set(0,0);
	flipX = false;
	flipY = false;
	tint = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
	currentFrame = 0;
	timeAccum = 0.0f;
}

AnimatedSpriteRenderComponent::~AnimatedSpriteRenderComponent(void)
{
}

void AnimatedSpriteRenderComponent::Draw()
{
	Transform *transform = &GetOwner()->transform;
	Vector2 p = transform->GetPosition();
	float   r = transform->GetRotation();
	float s = transform->GetScale();
	Renderer::DrawTexturedQuad(textureIDs[currentFrame], p - positionAnchor, width * s, height * s, r, rotationCenter, flipX, flipY, tint);
}

void AnimatedSpriteRenderComponent::Update(float deltaTime)
{
	timeAccum += deltaTime;
	if(timeAccum > delay)
	{
		timeAccum -= delay;
		currentFrame = (currentFrame + 1) % textureIDs.size();
	}
}