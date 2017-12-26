#include "board.h"
#include "../utils/utils.h"

int Board::WIDTH = 25;
int Board::HEIGHT = 18;

Board::Board() {
	for (auto i = 0; i < WIDTH; ++i) {
		for (auto j = 0; j < HEIGHT; ++j) {
			// init location of each tile
			_tiles[i][j].x = i * Tile::WIDTH;
			_tiles[i][j].y = j * Tile::HEIGHT;
		}
	}
}

void Board::pollEvents(SDL_Event &event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {

		// if the coords of the click are within the board
		if (event.button.x >= 0 && event.button.x < (Utils::SCR_WIDTH - 2) && event.button.y >= 0 && event.button.y < (Utils::SCR_HEIGHT - 2)) {

			// convert screen coords to index coords
			int x = Utils::roundDown(event.button.x, Tile::WIDTH) / Tile::WIDTH;
			int y = Utils::roundDown(event.button.y, Tile::HEIGHT) / Tile::HEIGHT;

			// if tile is right clicked then flag that tile
			if (event.button.button == SDL_BUTTON_RIGHT) {
				if (!_tiles[x][y].revealed) {
					_tiles[x][y].flagged = !_tiles[x][y].flagged;
				}
			}

			// if tiles is left clicked then reveal that tile
			if (event.button.button == SDL_BUTTON_LEFT) {
				_tiles[x][y].revealed = true;

				// if first click of game then generate mines
				if (_first_click) {
					generateMines(x, y);
					_first_click = false;
				}

				/*  if the clicked tile doesn't have any mines around it
					then open all tiles around that tile */
				if (_tiles[x][y].digit == 0) {
					openSurroundingTiles(x, y);
				}

				// if the clicked tile contains a mine then game over and reveal all mines
				if (_tiles[x][y].contains_mine) {
					for (const auto &loc : _mine_locations) {
						_tiles[loc.first][loc.second].revealed = true;
					}
				}
			}
		}
	}
}

void Board::draw() const {
	for (const auto &tile_array : _tiles) {
		for (const auto &tile : tile_array) {
			// draws all tiles in the two-dimensional array
			tile.draw();
		}
	}
}

int Board::numberOfMines(int x, int y) const {
	int num_mines = 0;

	int x_min = (x == 0) ? 0 : (x - 1);
	int x_max = (x == WIDTH - 1) ? (WIDTH - 1) : (x + 1);

	int y_min = (y == 0) ? 0 : (y - 1);
	int y_max = (y == HEIGHT - 1) ? (HEIGHT - 1) : (y + 1);

	for (auto i = x_min; i <= x_max; ++i) {
		for (auto j = y_min; j <= y_max; ++j) {
			if (_tiles[i][j].contains_mine) {
				++num_mines;
			}
		}
	}

	return num_mines;
}


void Board::openSurroundingTiles(int x, int y) {
	int x_min = (x == 0) ? 0 : (x - 1);
	int x_max = (x == WIDTH - 1) ? (WIDTH - 1) : (x + 1);

	int y_min = (y == 0) ? 0 : (y - 1);
	int y_max = (y == HEIGHT - 1) ? (HEIGHT - 1) : (y + 1);

	for (auto i = x_min; i <= x_max; ++i) {
		for (auto j = y_min; j <= y_max; ++j) {
			if (_tiles[i][j].revealed) {
				continue;
			}
			_tiles[i][j].revealed = true;
			if (_tiles[i][j].digit == 0) {
				openSurroundingTiles(i, j);
			}
		}
	}
}

void Board::generateMines(int x, int y) {
	for (auto i = 0; _mine_locations.size() < (Board::WIDTH * Board::HEIGHT / 4.8); ++i) {
		// generate random locations
		std::pair<int, int> location = std::make_pair<int, int>(Utils::randomNumber(0, WIDTH - 1), Utils::randomNumber(0, HEIGHT - 1));

		/*  if the generated location isn't on or around the clicked location (given by the params)
			then use that as a mine location */
		if (!((location.first == x - 1 && location.second == y - 1) ||
			(location.first == x - 1 && location.second == y) ||
			(location.first == x - 1 && location.second == y + 1) ||
			(location.first == x && location.second == y - 1) ||
			(location.first == x && location.second == y) ||
			(location.first == x && location.second == y + 1) ||
			(location.first == x + 1 && location.second == y - 1) ||
			(location.first == x + 1 && location.second == y) ||
			(location.first == x + 1 && location.second == y + 1)
			))
		{
			_mine_locations.insert(location);
		}
	}
	for (const auto &loc : _mine_locations) {
		// place mines into tiles with the same locations as those generated previously
		_tiles[loc.first][loc.second].contains_mine = true;
	}

	for (auto i = 0; i < WIDTH; ++i) {
		for (auto j = 0; j < HEIGHT; ++j) {
			// label each tile with the # of mines around it
			int n = numberOfMines(i, j);
			_tiles[i][j].digit_text = Text::numbers[n];
			_tiles[i][j].digit = n;
		}
	}
}
