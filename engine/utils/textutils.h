#pragma once

#include <sstream>
#include <SDL2/SDL_ttf.h>

void renderText(SDL_Renderer *renderer, Position position, const std::string &text, int size, bool center = false,
                SDL_Color color = {0, 0, 0});