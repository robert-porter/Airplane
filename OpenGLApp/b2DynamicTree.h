/*
* Copyright (c) 2009 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef B2_DYNAMIC_TREE_H
#define B2_DYNAMIC_TREE_H

#include "Vector2.h"

typedef float float32;
typedef int   int32;
typedef unsigned uint32;

/// This is used to fatten AABBs in the dynamic tree. This allows proxies
/// to move by a small amount without triggering a tree adjustment.
/// This is in meters.
#define b2_aabbExtension		0.1f

/// This is used to fatten AABBs in the dynamic tree. This is used to predict
/// the future position based on the current displacement.
/// This is a dimensionless multiplier.
#define b2_aabbMultiplier		2.0f

/// Implement this function to use your own memory allocator.
void* b2Alloc(int32 size);

/// If you implement b2Alloc, you should also implement this function.
void b2Free(void* mem);

inline Vector2 b2Abs(const Vector2& a)
{
	return Vector2(fabs(a.x), fabs(a.y));
}


template <typename T>
inline T b2Min(T a, T b)
{
	return a < b ? a : b;
}

inline Vector2 b2Min(const Vector2& a, const Vector2& b)
{
	return Vector2(b2Min(a.x, b.x), b2Min(a.y, b.y));
}

template <typename T>
inline T b2Max(T a, T b)
{
	return a > b ? a : b;
}

inline Vector2 b2Max(const Vector2& a, const Vector2& b)
{
	return Vector2(b2Max(a.x, b.x), b2Max(a.y, b.y));
}
/// A dynamic AABB tree broad-phase, inspired by Nathanael Presson's btDbvt.
/// Ray-cast input data. The ray extends from p1 to p1 + maxFraction * (p2 - p1).
struct b2RayCastInput
{
	Vector2 p1, p2;
	float32 maxFraction;
};

/// Ray-cast output data. The ray hits at p1 + fraction * (p2 - p1), where p1 and p2
/// come from b2RayCastInput.
struct b2RayCastOutput
{
	Vector2 normal;
	float32 fraction;
};

/// An axis aligned bounding box.
struct b2AABB
{
	/// Verify that the bounds are sorted.
	bool IsValid() const;

	/// Get the center of the AABB.
	Vector2 GetCenter() const
	{
		return 0.5f * (lowerBound + upperBound);
	}

	/// Get the extents of the AABB (half-widths).
	Vector2 GetExtents() const
	{
		return 0.5f * (upperBound - lowerBound);
	}

	/// Combine two AABBs into this one.
	void Combine(const b2AABB& aabb1, const b2AABB& aabb2)
	{
		lowerBound = b2Min(aabb1.lowerBound, aabb2.lowerBound);
		upperBound = b2Max(aabb1.upperBound, aabb2.upperBound);
	}

	/// Does this aabb contain the provided AABB.
	bool Contains(const b2AABB& aabb) const
	{
		bool result = true;
		result = result && lowerBound.x <= aabb.lowerBound.x;
		result = result && lowerBound.y <= aabb.lowerBound.y;
		result = result && aabb.upperBound.x <= upperBound.x;
		result = result && aabb.upperBound.y <= upperBound.y;
		return result;
	}

	bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input) const;

	Vector2 lowerBound;	///< the lower vertex
	Vector2 upperBound;	///< the upper vertex
};


#define b2_nullNode (-1)

/// A node in the dynamic tree. The client does not interact with this directly.
struct b2DynamicTreeNode
{
	bool IsLeaf() const
	{
		return child1 == b2_nullNode;
	}

	/// This is the fattened AABB.
	b2AABB aabb;

	//int32 userData;
	void* userData;

	union
	{
		int32 parent;
		int32 next;
	};

	int32 child1;
	int32 child2;
};

/// A dynamic tree arranges data in a binary tree to accelerate
/// queries such as volume queries and ray casts. Leafs are proxies
/// with an AABB. In the tree we expand the proxy AABB by b2_fatAABBFactor
/// so that the proxy AABB is bigger than the client object. This allows the client
/// object to move by small amounts without triggering a tree update.
///
/// Nodes are pooled and relocatable, so we use node indices rather than pointers.
class b2DynamicTree
{
public:

	/// Constructing the tree initializes the node pool.
	b2DynamicTree();

	/// Destroy the tree, freeing the node pool.
	~b2DynamicTree();

	/// Create a proxy. Provide a tight fitting AABB and a userData pointer.
	int32 CreateProxy(const b2AABB& aabb, void* userData);

	/// Destroy a proxy. This asserts if the id is invalid.
	void DestroyProxy(int32 proxyId);

	/// Move a proxy with a swepted AABB. If the proxy has moved outside of its fattened AABB,
	/// then the proxy is removed from the tree and re-inserted. Otherwise
	/// the function returns immediately.
	/// @return true if the proxy was re-inserted.
	bool MoveProxy(int32 proxyId, const b2AABB& aabb1, const Vector2& displacement);

	/// Perform some iterations to re-balance the tree.
	void Rebalance(int32 iterations);

	/// Get proxy user data.
	/// @return the proxy user data or 0 if the id is invalid.
	void* GetUserData(int32 proxyId) const;

	/// Get the fat AABB for a proxy.
	const b2AABB& GetFatAABB(int32 proxyId) const;

	/// Compute the height of the tree.
	int32 ComputeHeight() const;

	/// Query an AABB for overlapping proxies. The callback class
	/// is called for each proxy that overlaps the supplied AABB.
	template <typename T>
	void Query(T* callback, const b2AABB& aabb) const;

	/// Ray-cast against the proxies in the tree. This relies on the callback
	/// to perform a exact ray-cast in the case were the proxy contains a shape.
	/// The callback also performs the any collision filtering. This has performance
	/// roughly equal to k * log(n), where k is the number of collisions and n is the
	/// number of proxies in the tree.
	/// @param input the ray-cast input data. The ray extends from p1 to p1 + maxFraction * (p2 - p1).
	/// @param callback a callback class that is called for each proxy that is hit by the ray.
	template <typename T>
	void RayCast(T* callback, const b2RayCastInput& input) const;

private:

	int32 AllocateNode();
	void FreeNode(int32 node);

	void InsertLeaf(int32 node);
	void RemoveLeaf(int32 node);

	int32 ComputeHeight(int32 nodeId) const;

	int32 m_root;

	b2DynamicTreeNode* m_nodes;
	int32 m_nodeCount;
	int32 m_nodeCapacity;

	int32 m_freeList;

	/// This is used incrementally traverse the tree for re-balancing.
	uint32 m_path;

	int32 m_insertionCount;
};

inline void* b2DynamicTree::GetUserData(int32 proxyId) const
{
	assert(0 <= proxyId && proxyId < m_nodeCapacity);
	return m_nodes[proxyId].userData;
}

inline const b2AABB& b2DynamicTree::GetFatAABB(int32 proxyId) const
{
	assert(0 <= proxyId && proxyId < m_nodeCapacity);
	return m_nodes[proxyId].aabb;
}

template <typename T>
inline void b2DynamicTree::Query(T* callback, const b2AABB& aabb) const
{
	const int32 k_stackSize = 128;
	int32 stack[k_stackSize];

	int32 count = 0;
	stack[count++] = m_root;

	while (count > 0)
	{
		int32 nodeId = stack[--count];
		if (nodeId == b2_nullNode)
		{
			continue;
		}

		const b2DynamicTreeNode* node = m_nodes + nodeId;

		if (b2TestOverlap(node->aabb, aabb))
		{
			if (node->IsLeaf())
			{
				bool proceed = callback->QueryCallback(nodeId);
				if (proceed == false)
				{
					return;
				}
			}
			else
			{
				if (count < k_stackSize)
				{
					stack[count++] = node->child1;
				}

				if (count < k_stackSize)
				{
					stack[count++] = node->child2;
				}
			}
		}
	}
}

template <typename T>
inline void b2DynamicTree::RayCast(T* callback, const b2RayCastInput& input) const
{
	Vector2 p1 = input.p1;
	Vector2 p2 = input.p2;
	Vector2 r = p2 - p1;
	assert(r.LengthSquared() > 0.0f);
	r.Normalize();

	// v is perpendicular to the segment.
	Vector2 v = b2Cross(1.0f, r);
	Vector2 abs_v = b2Abs(v);

	// Separating axis for segment (Gino, p80).
	// |dot(v, p1 - c)| > dot(|v|, h)

	float32 maxFraction = input.maxFraction;

	// Build a bounding box for the segment.
	b2AABB segmentAABB;
	{
		Vector2 t = p1 + maxFraction * (p2 - p1);
		segmentAABB.lowerBound = b2Min(p1, t);
		segmentAABB.upperBound = b2Max(p1, t);
	}

	const int32 k_stackSize = 128;
	int32 stack[k_stackSize];

	int32 count = 0;
	stack[count++] = m_root;

	while (count > 0)
	{
		int32 nodeId = stack[--count];
		if (nodeId == b2_nullNode)
		{
			continue;
		}

		const b2DynamicTreeNode* node = m_nodes + nodeId;

		if (b2TestOverlap(node->aabb, segmentAABB) == false)
		{
			continue;
		}

		// Separating axis for segment (Gino, p80).
		// |dot(v, p1 - c)| > dot(|v|, h)
		Vector2 c = node->aabb.GetCenter();
		Vector2 h = node->aabb.GetExtents();
		float32 separation = b2Abs(b2Dot(v, p1 - c)) - b2Dot(abs_v, h);
		if (separation > 0.0f)
		{
			continue;
		}

		if (node->IsLeaf())
		{
			b2RayCastInput subInput;
			subInput.p1 = input.p1;
			subInput.p2 = input.p2;
			subInput.maxFraction = maxFraction;

			float32 value = callback->RayCastCallback(subInput, nodeId);

			if (value == 0.0f)
			{
				// The client has terminated the ray cast.
				return;
			}

			if (value > 0.0f)
			{
				// Update segment bounding box.
				maxFraction = value;
				Vector2 t = p1 + maxFraction * (p2 - p1);
				segmentAABB.lowerBound = b2Min(p1, t);
				segmentAABB.upperBound = b2Max(p1, t);
			}
		}
		else
		{
			if (count < k_stackSize)
			{
				stack[count++] = node->child1;
			}

			if (count < k_stackSize)
			{
				stack[count++] = node->child2;
			}
		}
	}
}

#endif
