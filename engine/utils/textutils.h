#pragma once

#include <sstream>
#include <SDL2/SDL_ttf.h>

void renderText(SDL_Renderer *renderer, Position position, const std::string& text, int size, bool center = false) {

  TTF_Font *roboto = TTF_OpenFont("../assets/Roboto.ttf", size);
  SDL_Surface *textSurface = TTF_RenderText_Solid(roboto, text.c_str(), {0, 0, 0});

  if (center) {
    position -= {(float) textSurface->w / 2, (float) textSurface->h / 2};
  }

  SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_Rect r{(int) position.x, (int) position.y, textSurface->w, textSurface->h};

  SDL_RenderCopy(renderer, textTexture, nullptr, &r);

  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(textTexture);

  TTF_CloseFont(roboto);

}