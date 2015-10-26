#ifndef __CONSOLERENDERER_H_INCLUDED__
#define __CONSOLERENDERER_H_INCLUDED__

#include "IRenderer.h"

class ConsoleRenderer : public IRenderer
{
private:
	MapValue GetMapValueFromPosition(const std::unique_ptr<MapValue[]> &map, int mapWidth, int row, int col);
	char GetMapChar(MapValue value);
public:
	virtual void Render(const std::unique_ptr<MapValue[]> &map, int mapWidth, int mapHeight) override;
	virtual void RenderSingleMessage(const std::string &msg) override;
};

#endif