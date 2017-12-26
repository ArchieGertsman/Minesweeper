#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../utils/window.h"
#include "../utils/utils.h"
#include "../utils/text.h"

class Tile {
public:
	static int WIDTH, HEIGHT;	// dimentions of a tile in pixels

	int x = 0, y = 0;				// coordinates of tile
	bool contains_mine = false;		// does the tile contain a mine?
	bool flagged = false;			// is the tile flagged?
	bool revealed = false;			// are the tile's contentes revealed?
	int digit = 0;					// digit representing # of mines around tile
	Text digit_text;				// Actual text representing "digit" on the screen

public:
	void draw() const;				// draws tile to the screen based on the above conditions

private:
	SDL_Texture *_mine_texture = Utils::loadTexture("res/mine.png");	// texture of the mine
	SDL_Texture *_flag_texture = Utils::loadTexture("res/flag.png");	// texture of the flag
};