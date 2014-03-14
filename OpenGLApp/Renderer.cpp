#include "stdincludes.h"
#include "Renderer.h"


std::map<std::string, GLuint> Renderer::textures;

void Renderer::DrawTexturedQuad(GLuint textureID, const Vector2 &centerPos, float w, float h, 
								float angle, const Vector2 &rotationCenter, bool flipX, bool flipY, const Color4f &tint)
{
	Vector2 vertices[4];
	Vector2 texCoords[4];

	float hw = w/2.0, hh = h/2.0;


	vertices[0].Set( - hw,  + hh);
	vertices[1].Set( - hw,  - hh);
	vertices[2].Set( + hw,  - hh);
	vertices[3].Set( + hw,  + hh);

	if(flipX)
	{
		texCoords[0].x = 1.0f;
		texCoords[1].x = 1.0f;
		texCoords[2].x = 0.0f;
		texCoords[3].x = 0.0f;
	}
	else
	{
		texCoords[0].x = 0.0f;
		texCoords[1].x = 0.0f;
		texCoords[2].x = 1.0f;
		texCoords[3].x = 1.0f;
	}
	
	if(flipY)
	{
		texCoords[0].y = 0.0f;
		texCoords[1].y = 1.0f;
		texCoords[2].y = 1.0f;
		texCoords[3].y = 0.0f;
	}
	else
	{
		texCoords[0].y = 1.0f;
		texCoords[1].y = 0.0f;
		texCoords[2].y = 0.0f;
		texCoords[3].y = 1.0f;
	}

	Matrix2x2 rotation(angle);

	for(int i = 0; i < 4; i++)
	{
		vertices[i] = rotation * (vertices[i] - rotationCenter) + rotationCenter + centerPos;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	glColor4f(tint.r, tint.g, tint.b, tint.a);
	glTexCoord2f(texCoords[0].x, texCoords[0].y);
	glVertex2f(vertices[0].x, vertices[0].y);
	glTexCoord2f(texCoords[1].x, texCoords[1].y);
	glVertex2f(vertices[1].x, vertices[1].y);
	glTexCoord2f(texCoords[2].x, texCoords[2].y);
	glVertex2f(vertices[2].x, vertices[2].y);
	glTexCoord2f(texCoords[3].x, texCoords[3].y);
	glVertex2f(vertices[3].x, vertices[3].y);
	glEnd();
};

void Renderer::DrawCircle(const Vector2 p, float r)
	{
	int N = 18;
	glBegin(GL_LINE_LOOP);

	for ( int i = 0; i < N; i++ )
	{
		Vector2 v = p + r * Vector2(cosf(2.0f*PI*float(i)/float(N)), sinf(2.0f*PI*float(i)/float(N)));
		glVertex2f(v.x, v.y);
	}

	glEnd();
}

void Renderer::DrawCapsule(const Vector2 p, float rotation, Vector2 p0, Vector2 p1, float radius)
{
	const int N = 18;
	glBegin(GL_LINE_LOOP);
	Matrix2x2 rot(rotation);

	for ( int i = 0; i < N/2+1; i++ )
	{
		Vector2 v = p + rot * (p1 + radius * Vector2(cosf(2.0f*PI*float(i)/float(N)), sinf(2.0f*PI*float(i)/float(N))));
		glVertex2f(v.x, v.y);
	}

	
	for ( int i = N/2; i < N+1; i++ )
	{
		Vector2 v = p + rot * (p0 + radius * Vector2(cosf(2.0f*PI*float(i)/float(N)), sinf(2.0f*PI*float(i)/float(N))));
		glVertex2f(v.x, v.y);
	}

	glEnd();
	
}	

GLuint Renderer::GetTexture(const std::string& name)
{
	std::map<std::string, GLuint>::iterator iter = textures.find(name);

	if (iter != textures.end())
	{
		return iter->second;
	}

	GLuint textureID = Renderer::CreateTextureFromFile(name.c_str());
 
	textures.insert(std::make_pair(name, textureID));
	return textureID;
}

GLuint Renderer::CreateTextureFromFile(const char *fileName)
{
	return SOIL_load_OGL_texture(fileName, 4, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

void Renderer::DrawString(const Vector2 &p, const char *s)
{

	glMatrixMode(GL_PROJECTION);

	float w = 500; //glutGet(GLUT_WINDOW_WIDTH);
	float h = 500; //glutGet(GLUT_WINDOW_HEIGHT);

	glPushMatrix();

	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glScalef(1, -1, 1);
	glTranslatef(0, -h, 0);

	int length = strlen(s);
	float xoff = 0.0f;
	for(int i = 0; i < length; i++)
	{
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glRasterPos2f(p.x + xoff, p.y);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
		xoff += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	}

	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}