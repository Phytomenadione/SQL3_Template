#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


int main(int argc, char* argv[]) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	if (result < 0) {
		SDL_Log("SDL Init Error: %s", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow("Generic Name", 800, 600, SDL_WINDOW_RESIZABLE);
	if (window == NULL) {
		SDL_Log("SDL Init Error: %s", SDL_GetError());
		return -2;
	}
	//UPDATED FUCKING DOCUMENATION
	renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == NULL) {
		SDL_Log("SDL Init Error: %s", SDL_GetError());
		return -3;
	}

	SDL_Log("SDL3 Initialized");

	// main loop
	SDL_Event event;
	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				SDL_Log("SDL3 Event Quit");
				quit = 1;
				break;
			case SDL_EVENT_KEY_DOWN:
				if (event.key.key == SDLK_ESCAPE) {
					SDL_Log("SDL3 Pressed ESC to quit");
					quit = 1;
					break;
				}
			}
		}

		// other things
		SDL_SetRenderDrawColor(renderer, 0, 0, 0xff,0);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}

	SDL_Log("SDL3 Shutdown");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;

}