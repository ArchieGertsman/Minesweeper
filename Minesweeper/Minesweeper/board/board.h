#pragma once
#include "tile.h"
#include <vector>
#include <set>

class Board {
public:
	static int WIDTH, HEIGHT;	// dimentions of board in tiles

	Board();
	void draw() const;					// draws all the tiles
	void pollEvents(SDL_Event &event);	// polls events

private:
	void generateMines(int x, int y);			// generate mines at beginning of game given coordinates of first click
	int numberOfMines(int x, int y) const;		// # of mines around a given tile
	void openSurroundingTiles(int x, int y);	// opens all tiles around a given tile

private:
	std::vector<std::vector<Tile>> _tiles = 
		std::vector<std::vector<Tile>>(WIDTH, std::vector<Tile>(HEIGHT));	// array of all the tiles
	std::set<std::pair<int, int>> _mine_locations;							// locations of each mine
	bool _first_click = true;												// is the the first click of the game?
};