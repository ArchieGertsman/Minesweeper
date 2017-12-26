#include "utils/window.h"
#include <SDL/SDL.h>
#include "board/board.h"
#include "utils/utils.h"

int main(int argc, char **argv) {
	
	Window window("Window", Utils::SCR_WIDTH, Utils::SCR_HEIGHT);
	Text::initNumbers();
	
	Board board;

	while (!window.closed()) {
		board.draw();
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			board.pollEvents(event);
			window.pollEvents(event);
		}
		window.clear();
	}

	return 0;
}