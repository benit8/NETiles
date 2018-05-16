/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** Tiles / Map.cpp
*/

#include "Tiles/Map.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace Tiles
{

////////////////////////////////////////////////////////////////////////////////

Map::Map()
: Map("")
{
}

Map::Map(const std::string &mapPath)
: m_mapPath(mapPath)
{
	const sf::Texture &t = Ressource::Manager::getTexture("tileset0");
	m_renderStates.texture = &t;
}

////////////////////////////////////////////////////////////////////////////////

bool Map::loadFromFile(const std::string &mapPath)
{
	std::string filepath(mapPath);
	if (filepath.empty()) {
		if (!m_mapPath.empty())
			filepath = m_mapPath;
		else {
			std::cerr << "No path provided to load map" << std::endl;
			return false;
		}
	}

	std::ifstream ifs(filepath);
	if (!ifs.is_open()) {
		std::cerr << filepath << ": " << std::strerror(errno) << std::endl;
		return false;
	}

	ifs.ignore(100, '\n');

	while (ifs.good()) {
		Tile t;
		ifs >> t.pos.x;
		ifs >> t.pos.y;
		ifs >> t.tex.x;
		ifs >> t.tex.y;
		ifs >> t.walkable;

		if (ifs.peek() != '\n') {
			t.tele = true;
			ifs >> t.telePos.x;
			ifs >> t.telePos.y;
		}

		ifs.ignore(100, '\n');
		m_tiles.push_back(t);
	}

	ifs.close();
	return true;
}

bool Map::saveToFile(const std::string &mapPath)
{
	std::string filepath(mapPath);
	if (filepath.empty()) {
		if (!m_mapPath.empty())
			filepath = m_mapPath;
		else {
			std::cerr << "No path provided to save map" << std::endl;
			return false;
		}
	}

	std::ofstream ofs(filepath);
	if (!ofs.is_open()) {
		std::cerr << filepath << ": " << std::strerror(errno) << std::endl;
		return false;
	}

	std::sort(m_tiles.begin(), m_tiles.end(), [](Tile a, Tile b){
		if (a.pos.x == b.pos.x)
			return a.pos.y < b.pos.y;
		return a.pos.x < b.pos.x;
	});

	ofs << "LVL2" << std::endl;
	for (size_t i = 0; i < m_tiles.size(); ++i) {
		ofs << m_tiles[i].pos.x << " ";
		ofs << m_tiles[i].pos.y << " ";
		ofs << m_tiles[i].tex.x << " ";
		ofs << m_tiles[i].tex.y << " ";
		ofs << m_tiles[i].walkable;
		if (m_tiles[i].tele)
			ofs << " " << m_tiles[i].telePos.x << " " << m_tiles[i].telePos.y;
		ofs << std::endl;
	}

	ofs.close();
	return true;
}

void Map::render(sf::RenderWindow &target, bool displayTileTypes)
{
	sf::VertexArray va(sf::Quads);

	for (size_t i = 0; i < m_tiles.size(); ++i) {
		// Top left
		sf::Vertex tl;
		tl.position.x = m_tiles[i].pos.x * TILEMAP_TILE_SIZE;
		tl.position.y = m_tiles[i].pos.y * TILEMAP_TILE_SIZE;
		tl.texCoords.x = m_tiles[i].tex.x * TILESET_TILE_SIZE;
		tl.texCoords.y = m_tiles[i].tex.y * TILESET_TILE_SIZE;
		if (displayTileTypes)
			tl.color = m_tiles[i].getColorType();
		va.append(tl);

		// Top right
		sf::Vertex tr;
		tr.position.x = m_tiles[i].pos.x * TILEMAP_TILE_SIZE + TILEMAP_TILE_SIZE;
		tr.position.y = m_tiles[i].pos.y * TILEMAP_TILE_SIZE;
		tr.texCoords.x = m_tiles[i].tex.x * TILESET_TILE_SIZE + TILESET_TILE_SIZE;
		tr.texCoords.y = m_tiles[i].tex.y * TILESET_TILE_SIZE;
		if (displayTileTypes)
			tr.color = m_tiles[i].getColorType();
		va.append(tr);

		// Bottom right
		sf::Vertex br;
		br.position.x = m_tiles[i].pos.x * TILEMAP_TILE_SIZE + TILEMAP_TILE_SIZE;
		br.position.y = m_tiles[i].pos.y * TILEMAP_TILE_SIZE + TILEMAP_TILE_SIZE;
		br.texCoords.x = m_tiles[i].tex.x * TILESET_TILE_SIZE + TILESET_TILE_SIZE;
		br.texCoords.y = m_tiles[i].tex.y * TILESET_TILE_SIZE + TILESET_TILE_SIZE;
		if (displayTileTypes)
			br.color = m_tiles[i].getColorType();
		va.append(br);

		// Bottom left
		sf::Vertex bl;
		bl.position.x = m_tiles[i].pos.x * TILEMAP_TILE_SIZE;
		bl.position.y = m_tiles[i].pos.y * TILEMAP_TILE_SIZE + TILEMAP_TILE_SIZE;
		bl.texCoords.x = m_tiles[i].tex.x * TILESET_TILE_SIZE;
		bl.texCoords.y = m_tiles[i].tex.y * TILESET_TILE_SIZE + TILESET_TILE_SIZE;
		if (displayTileTypes)
			bl.color = m_tiles[i].getColorType();
		va.append(bl);
	}

	target.draw(va, m_renderStates);
}

void Map::setTile(const sf::Vector2i &pos, const sf::Vector2i &tex)
{
	Tile *t = getTile(pos);
	if (t) {
		t->pos = pos;
		t->tex = tex;
	}
	else {
		m_tiles.push_back(Tile(pos, tex));
	}
}

Tile *Map::getTile(const sf::Vector2i &pos)
{
	for (size_t i = 0; i < m_tiles.size(); ++i) {
		if (m_tiles[i].pos == pos)
			return &m_tiles[i];
	}
	return NULL;
}

void Map::removeTile(const sf::Vector2i &pos)
{
	for (size_t i = 0; i < m_tiles.size(); ++i) {
		if (m_tiles[i].pos == pos) {
			m_tiles.erase(m_tiles.begin() + i);
			return;
		}
	}
}

Tile *Map::getTile(int x, int y)
{
	return getTile(sf::Vector2i(x, y));
}

sf::Vector2i Map::getCenter()
{
	sf::Vector2i botRight;

	for (size_t i = 0; i < m_tiles.size(); ++i) {
		if (m_tiles[i].pos.x > botRight.x)
			botRight.x = m_tiles[i].pos.x;
		if (m_tiles[i].pos.y > botRight.y)
			botRight.y = m_tiles[i].pos.y;
	}
	return botRight * TILEMAP_TILE_SIZE / 2;
}

const std::string &Map::getMapPath()
{
	return m_mapPath;
}

////////////////////////////////////////////////////////////////////////////////

}