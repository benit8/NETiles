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
, m_offset(0, 0)
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

	std::string line;
	if (!std::getline(ifs, line))
		return (false);
	if (line.compare(0, 3, "LVL") != 0) {
		std::cerr << filepath << ": Unknown file format" << std::endl;
		return (false);
	}

	while (std::getline(ifs, line)) {
		if (line.empty())
			continue;

		std::istringstream iss(line);
		Tile t;
		iss >> t.pos.x;
		iss >> t.pos.y;
		iss >> t.tex.x;
		iss >> t.tex.y;
		iss >> t.walkable;

		if (iss.peek() != -1) {
			t.tele = true;
			iss >> t.telePos.x;
			iss >> t.telePos.y;
		}

		iss.ignore(100, '\n');
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

	reposition();

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

////////////////////////////////////////////////////////////////////////////////

void Map::clear()
{
	m_tiles.clear();
}

void Map::render(sf::RenderWindow &target, bool displayTileTypes)
{
	sf::VertexArray va(sf::Quads);

	for (size_t i = 0; i < m_tiles.size(); ++i) {
		// Top left
		sf::Vertex tl;
		tl.position = sf::Vector2f(m_tiles[i].pos);
		tl.position += sf::Vector2f(m_offset);
		tl.texCoords = sf::Vector2f(m_tiles[i].tex) * float(TILE_SIZE);
		if (m_isClipboard)
			tl.color = sf::Color(255, 255, 255, 128);
		else if (displayTileTypes)
			tl.color = m_tiles[i].getColorType();
		va.append(tl);

		// Top right
		sf::Vertex tr;
		tr.position = sf::Vector2f(m_tiles[i].pos);
		tr.position += sf::Vector2f(1, 0);
		tr.position += sf::Vector2f(m_offset);
		tr.texCoords = sf::Vector2f(m_tiles[i].tex) * float(TILE_SIZE);
		tr.texCoords += sf::Vector2f(TILE_SIZE, 0);
		if (m_isClipboard)
			tr.color = sf::Color(255, 255, 255, 128);
		else if (displayTileTypes)
			tr.color = m_tiles[i].getColorType();
		va.append(tr);

		// Bottom right
		sf::Vertex br;
		br.position = sf::Vector2f(m_tiles[i].pos);
		br.position += sf::Vector2f(1, 1);
		br.position += sf::Vector2f(m_offset);
		br.texCoords = sf::Vector2f(m_tiles[i].tex) * float(TILE_SIZE);
		br.texCoords += sf::Vector2f(TILE_SIZE, TILE_SIZE);
		if (m_isClipboard)
			br.color = sf::Color(255, 255, 255, 128);
		else if (displayTileTypes)
			br.color = m_tiles[i].getColorType();
		va.append(br);

		// Bottom left
		sf::Vertex bl;
		bl.position = sf::Vector2f(m_tiles[i].pos);
		bl.position += sf::Vector2f(0, 1);
		bl.position += sf::Vector2f(m_offset);
		bl.texCoords = sf::Vector2f(m_tiles[i].tex) * float(TILE_SIZE);
		bl.texCoords += sf::Vector2f(0, TILE_SIZE);
		if (m_isClipboard)
			bl.color = sf::Color(255, 255, 255, 128);
		else if (displayTileTypes)
			bl.color = m_tiles[i].getColorType();
		va.append(bl);
	}

	if (va.getVertexCount() > 0)
		target.draw(va, m_renderStates);
}

void Map::renderRepeated(sf::RenderWindow &target, const sf::Vector2i &area, bool displayTileTypes)
{
	sf::VertexArray va(sf::Quads);
	sf::Vector2i size = getSize();

	for (int y = 0; y < area.y || y < 1; ++y) {
		for (int x = 0; x < area.x || x < 1; ++x) {
			Tile *t = getTile(x % size.x, y % size.y);
			if (!t)
				continue;

			// Top left
			sf::Vertex tl;
			tl.position = sf::Vector2f(x, y);
			tl.position += sf::Vector2f(m_offset);
			tl.texCoords = sf::Vector2f(t->tex) * float(TILE_SIZE);
			if (m_isClipboard)
				tl.color = sf::Color(255, 255, 255, 128);
			else if (displayTileTypes)
				tl.color = t->getColorType();
			va.append(tl);

			// Top right
			sf::Vertex tr;
			tr.position = sf::Vector2f(x, y);
			tr.position += sf::Vector2f(1, 0);
			tr.position += sf::Vector2f(m_offset);
			tr.texCoords = sf::Vector2f(t->tex) * float(TILE_SIZE);
			tr.texCoords += sf::Vector2f(TILE_SIZE, 0);
			if (m_isClipboard)
				tr.color = sf::Color(255, 255, 255, 128);
			else if (displayTileTypes)
				tr.color = t->getColorType();
			va.append(tr);

			// Bottom right
			sf::Vertex br;
			br.position = sf::Vector2f(x, y);
			br.position += sf::Vector2f(1, 1);
			br.position += sf::Vector2f(m_offset);
			br.texCoords = sf::Vector2f(t->tex) * float(TILE_SIZE);
			br.texCoords += sf::Vector2f(TILE_SIZE, TILE_SIZE);
			if (m_isClipboard)
				br.color = sf::Color(255, 255, 255, 128);
			else if (displayTileTypes)
				br.color = t->getColorType();
			va.append(br);

			// Bottom left
			sf::Vertex bl;
			bl.position = sf::Vector2f(x, y);
			bl.position += sf::Vector2f(0, 1);
			bl.position += sf::Vector2f(m_offset);
			bl.texCoords = sf::Vector2f(t->tex) * float(TILE_SIZE);
			bl.texCoords += sf::Vector2f(0, TILE_SIZE);
			if (m_isClipboard)
				bl.color = sf::Color(255, 255, 255, 128);
			else if (displayTileTypes)
				bl.color = t->getColorType();
			va.append(bl);
		}
	}

	if (va.getVertexCount() > 0)
		target.draw(va, m_renderStates);
}

////////////////////////////////////////////////////////////////////////////////

void Map::setOffset(int x, int y)
{
	setOffset(sf::Vector2i(x, y));
}

void Map::setOffset(const sf::Vector2i &offset)
{
	m_offset = offset;
}

////////////////////////////////////////////////////////////////////////////////

void Map::setTile(const Tile &tile)
{
	Tile *t = getTile(tile.pos);
	if (t)
		*t = tile;
	else {
		m_tiles.push_back(tile);
		m_sorted = false;
	}
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
		m_sorted = false;
	}
}

void Map::deleteTile(const sf::Vector2i &pos)
{
	for (size_t i = 0; i < m_tiles.size(); ++i) {
		if (m_tiles[i].pos == pos) {
			m_tiles.erase(m_tiles.begin() + i);
			return;
		}
	}
}

void Map::deleteTile(int x, int y)
{
	deleteTile(sf::Vector2i(x, y));
}

Tile *Map::getTile(const sf::Vector2i &pos)
{
	for (size_t i = 0; i < m_tiles.size(); ++i) {
		if (m_tiles[i].pos == pos)
			return &m_tiles[i];
	}
	return NULL;
}

Tile *Map::getTile(int x, int y)
{
	return getTile(sf::Vector2i(x, y));
}

////////////////////////////////////////////////////////////////////////////////

const std::string &Map::getMapPath()
{
	return m_mapPath;
}

sf::Vector2i Map::getSize()
{
	return getBottomRightPosition() + sf::Vector2i(1, 1);
}

sf::Vector2i Map::getCenter()
{
	return getSize() / 2;
}

sf::Vector2i Map::getTopLeftPosition()
{
	sf::Vector2i topLeft = m_tiles[0].pos;

	for (size_t i = 1; i < m_tiles.size(); ++i) {
		if (m_tiles[i].pos.x < topLeft.x)
			topLeft.x = m_tiles[i].pos.x;
		if (m_tiles[i].pos.y < topLeft.y)
			topLeft.y = m_tiles[i].pos.y;
	}

	return topLeft;
}

sf::Vector2i Map::getBottomRightPosition()
{
	sf::Vector2i botRight = m_tiles[0].pos;

	for (size_t i = 0; i < m_tiles.size(); ++i) {
		if (m_tiles[i].pos.x > botRight.x)
			botRight.x = m_tiles[i].pos.x;
		if (m_tiles[i].pos.y > botRight.y)
			botRight.y = m_tiles[i].pos.y;
	}

	return botRight;
}

////////////////////////////////////////////////////////////////////////////////

void Map::setClipboard(bool isClipboard)
{
	m_isClipboard = isClipboard;
}

bool Map::isClipboard()
{
	return m_isClipboard;
}

////////////////////////////////////////////////////////////////////////////////

void Map::sortTiles()
{
	if (m_sorted)
		return;

	std::sort(m_tiles.begin(), m_tiles.end(), [](Tile a, Tile b){
		if (a.pos.x == b.pos.x)
			return a.pos.y < b.pos.y;
		return a.pos.x < b.pos.x;
	});

	m_sorted = true;
}

void Map::reposition()
{
	sortTiles();

	sf::Vector2i topLeft = getTopLeftPosition();
	for (std::vector<Tile>::reverse_iterator it = m_tiles.rbegin(); it != m_tiles.rend(); ++it) {
		it->pos -= topLeft;
	}
}

////////////////////////////////////////////////////////////////////////////////

};