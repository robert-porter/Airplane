#include "StaticSpriteRenderComponent.h"

#include "Entity.h"
#include "MovementComponent.h"

StaticSpriteRenderComponent::StaticSpriteRenderComponent(Entity *owner, GLuint texture, float w, float h, int z) : RenderComponent(owner)
{
	textureID = texture;
	width = w;
	height = h;
	this->z = z;
	rotationCenter.Set(0,0);
	positionAnchor.Set(0,0);
	flipX = false;
	flipY = false;
	tint = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
}
StaticSpriteRenderComponent::StaticSpriteRenderComponent(Entity *owner) : RenderComponent(owner)
{
	width = 0.0f;
	height = 0.0f;
	rotationCenter.Set(0,0);
	positionAnchor.Set(0,0);
	flipX = false;
	flipY = false;
	tint = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
}



StaticSpriteRenderComponent::~StaticSpriteRenderComponent(void)
{
}

void StaticSpriteRenderComponent::Draw()
{
	Transform *transform = &GetOwner()->transform;
	Vector2 p = transform->GetPosition();
	float   r = transform->GetRotation();
	float s = transform->GetScale();

	Renderer::DrawTexturedQuad(textureID, p - positionAnchor, width * s, height * s, r, rotationCenter, flipX, flipY, tint);
}


