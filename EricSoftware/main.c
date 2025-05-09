#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SDL_FLAGS SDL_INIT_VIDEO

#define WINDOW_TITLE "placeholder"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// makes easier to pass around into functions as a struct
struct game {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	bool isRunning;
};

// sans complier issues
bool game_init_sdl(struct game *g);
void leave(struct game* g);
void pgrm_run(struct game* g);
void events(struct game* g);
void draw(struct game* g);
bool pgrm_new(struct game* g);

// initialize "game"
bool game_init_sdl(struct game* g) {
	if (!SDL_Init(SDL_FLAGS)) {
		SDL_Log("SDL Init Error: %s", SDL_GetError());
		return false;
	}
	
	// create window
	g->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (g->window == NULL) {
		SDL_Log("SDL Window Error: %s", SDL_GetError());
		return false;
	}

	// create renderer
	g->renderer = SDL_CreateRenderer(g->window, NULL);
	if (g->renderer == NULL) {
		SDL_Log("SDL Renderer Error: %s", SDL_GetError());
		return false;
	}

	return true;
}

// free memory function
void leave(struct game *g) {
	if (g->renderer) {
		SDL_DestroyRenderer(g->renderer);
		g->renderer = NULL;
	}
	if (g->window) {
		SDL_DestroyWindow(g->window);
		g->window = NULL;
	}
	SDL_Quit();
	printf("Things were purged from memory don't panick.\n");
}

// event function
void events(struct game *g) {
	while (SDL_PollEvent(&g->event)) {
		switch (g->event.type) {
		case SDL_EVENT_QUIT:
			g->isRunning = false;
			printf("Successfully quit.\n");
			break;
		default:
			break;
		}
	}
}

//draw

void draw(struct game* g) {
	SDL_RenderClear(g->renderer);
	SDL_RenderPresent(g->renderer);
}

// run prgram fucnction
void pgrm_run(struct game *g) {
	while (g->isRunning) {
		events(g);
		//SDL_SetRenderDrawColor(g->renderer, 69, 0, 190, 255);
		draw(g);

		SDL_Delay(300);
	}
}

// prgoram constrcutor
bool pgrm_new(struct game* g){
	if (!game_init_sdl(g)) {
		return false;
	}
	g->isRunning = true;
	return true;

}

int main(int argc, char* argv[]) {
	bool exit_status = EXIT_FAILURE;

	struct game foundation = {0};

	if (pgrm_new(&foundation)) {
		pgrm_run(&foundation);
		exit_status = EXIT_SUCCESS;
	}

	leave(&foundation);
	return exit_status;
}

//OLD
/*
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

}*/