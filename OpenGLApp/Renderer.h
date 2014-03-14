#pragma once
#include "Color4f.h"
#include "vector2.h"
#include "matrix2x2.h"
#include "MathUtils.h"


class Renderer
{
public:
	static void		ClearBuffers();
	static void		SwapBuffers();
	static void		DrawTexturedQuad(GLuint textureID, const Vector2 &centerPos, float w, float h,
									 float angle, const Vector2 &rotationCenter, bool flipX, bool flipY, const Color4f &tint);
	static void		DrawCircle(const Vector2 p, float r);
	static void		DrawCapsule(const Vector2 p, float rotation, Vector2 p0, Vector2 p1, float radius);
	static void     DrawString(const Vector2 &p, const char *s);

	static GLuint	GetTexture(const std::string& name);
private:
	static GLuint	CreateTextureFromFile(const char *fileName);

    static std::map<std::string, GLuint> textures;
};
