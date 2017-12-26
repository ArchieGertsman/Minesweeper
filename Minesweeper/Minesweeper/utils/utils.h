#pragma once
#include <random>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "window.h"
#include <iostream>
#include <map>
#include <array>

namespace Utils
{
	static int SCR_WIDTH = 1002;
	static int SCR_HEIGHT = 722;

	inline int randomNumber(int min, int max) {
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
		return dist(rng);
	}

	inline SDL_Texture *loadTexture(const std::string &file_path) {
		auto surface = IMG_Load(file_path.c_str());
		if (!surface)
			std::cout << "failed to create board\'s surface\n";
		
		auto texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
		if (!texture)
			std::cout << "failed to create board\'s texture\n";
		
		SDL_FreeSurface(surface);
		return texture;
	}

	inline int roundDown(int num, int multiple) {
		return (num / multiple) * multiple;
	}
}