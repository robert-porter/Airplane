#pragma once

#include "Vector2.h"
#include "MathUtils.h"
#include "matrix2x2.h"

class Transform
{
public:
	Transform(Transform* relativeTo = NULL)
	{
		parent = relativeTo;
	}

	Transform(const Vector2 &pos, float rot, float scale, Transform* relativeTo = NULL)
	{
		position = pos;
		rotation = rot;
		this->scale = scale;
	}

	void Set(const Vector2 &pos, float rot, float scale, Transform* relativeTo = NULL)
	{
		position = pos;
		rotation = rot;
		this->scale = scale;
		parent = relativeTo;
	}

	void SetParent(Transform *relativeTo)
	{
		parent = relativeTo;
	}

	bool HasParent() const { return parent != NULL; }

	void SetIdentity() 
	{
		position.Set(0.0f, 0.0f);
		rotation = 0.0f;
		scale = 1.0f;
	}



	void SetPosition(const Vector2 &v) { position = v; }
	void SetRotation(float r) { rotation = r; }
	void SetScale(float s) { scale = s; }

	Vector2 GetPosition() const 
	{ 
		if(parent)
			return parent->GetPosition() + parent->GetScale()*Matrix2x2(parent->GetRotation()) * position;
		else 
			return position;
	}
	float GetRotation() const 
	{
		if(parent)
			return parent->GetRotation() + rotation;	
		else 
			return rotation;
	}
	float GetScale() const 
	{ 
		if ( parent )
			return parent->GetScale() * scale;
		else
		    return scale; 
	}

	void Translate(const Vector2& d) { position += d; }
	void RotateCCW(float r) { rotation += r; }
	void Scale(float s) { scale*=s; }

	Vector2 GetUp() const // Get local up in world coordinates;
	{ 
		float r = GetRotation();
		return Vector2(-sinf(r), cosf(r));
	}
	Vector2 GetRight() const // Get local right in world coordinates;
	{ 
		float r = GetRotation();
		return Vector2(cosf(r), sinf(r));
	}

	Vector2 TransformPoint(const Vector2 &v) const
	{
		Vector2 ret = v;
		ret=GetScale()*ret;
		ret=Matrix2x2(GetRotation())*ret;
		ret+=position;
		return ret;
	}

	Vector2 InverseTransformPoint(const Vector2 &v) const
	{
		Vector2 ret = v;
		ret-=position;
		ret=Matrix2x2(-GetRotation())*ret;
		ret=(1.0f/GetScale())*ret;
		return ret;
	}

private:
	Vector2 position;
	float rotation;
	float scale;
	Transform* parent;
};

	
