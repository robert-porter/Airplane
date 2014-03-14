#pragma once

#include <algorithm>
#include "RenderComponent.h"


class RenderList
{
public:
	RenderList(void);
	~RenderList(void);
	static bool ZCmp(RenderComponent *lhs, RenderComponent *rhs)
	{
		return lhs->GetZ() < rhs->GetZ();
	}
	void Clear() { renderObjects.clear(); }
	void Add(RenderComponent *c) { renderObjects.push_back(c); }
	void Sort() { std::sort(renderObjects.begin(), renderObjects.end(), ZCmp); }
	void Draw() 
	{
		for(unsigned int i = 0; i < renderObjects.size(); i++) 
			renderObjects[i]->Draw(); 
	}

private:

	std::vector<RenderComponent *> renderObjects;
};
