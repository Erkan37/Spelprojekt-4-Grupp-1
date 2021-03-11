#pragma once

namespace tson
{
	class Layer;
}

class TiledMap
{
public:
	bool Load(const std::string& aPath);
	void ParseLayer(tson::Layer*);

private:

};

