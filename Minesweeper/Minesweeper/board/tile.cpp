#include "tile.h"

int Tile::WIDTH = 40;
int Tile::HEIGHT = 40;

void Tile::draw() const {
	// rect object used to display tile
	SDL_Rect tile = { x + 2, y + 2, WIDTH - 2, HEIGHT - 2 };
	
	// if the tile isn't revealed then fill with blue.
	if (!this->revealed) {
		SDL_SetRenderDrawColor(Window::renderer, 0, 100, 255, 255);
		SDL_RenderFillRect(Window::renderer, &tile);

		// if tile is flagged then draw a flag on tile.
		if (this->flagged) {
			SDL_Rect flag = { x + 1, y + 1, WIDTH, HEIGHT };
			SDL_RenderCopy(Window::renderer, _flag_texture, nullptr, &tile);
		}
	}
	else {
		/*  if tile is revealed and doesn't havea mine then display 
			the # of mines around the tile */
		if (!contains_mine) {
			SDL_SetRenderDrawColor(Window::renderer, 220, 220, 220, 255);
			SDL_RenderFillRect(Window::renderer, &tile);

			digit_text.display(
				x + (WIDTH / 2) - (digit_text.getTextWidth() / 2),
				y + (HEIGHT / 2) - (digit_text.getTextHeight() / 2),
				Window::renderer
				);
		}
		else {
			// if revealed and contains mine then fill with red and draw mine
			SDL_SetRenderDrawColor(Window::renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(Window::renderer, &tile);

			SDL_Rect flag = { x, y, WIDTH, HEIGHT };
			SDL_RenderCopy(Window::renderer, _mine_texture, nullptr, &tile);
		}
	}
}