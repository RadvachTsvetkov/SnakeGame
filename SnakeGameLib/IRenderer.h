#ifndef __IRENDERER_H_INCLUDED__
#define __IRENDERER_H_INCLUDED__

#include <memory>
#include "MapValue.h"

class IRenderer
{
public:
	virtual void Render(const std::unique_ptr<MapValue[]> &map, int mapWidth, int mapHeight) = 0;
	virtual void RenderSingleMessage(const std::string &msg) = 0;
};

#endif