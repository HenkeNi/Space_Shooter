#pragma once
#include "Tile.h"

class Tilemap
{
public:
	Tilemap();

	void Update(float aDeltaTime);
	void Render(sf::RenderTarget& aTarget);



private:

	// Have one? sort after TileType (layer)
	std::vector<Tile> m_foregroundTiles; // Spikes / Cannons?
	std::vector<Tile> m_backgroundTiles;
};

