#include <SDL.h>
#include <chrono>
#include <random>

int data[30000];
int dataoverwrite[30000];

int cnt;

const int checkneighbours[8] = {
	-101,-100,-99,-1,1,99,100,101
};
int random(int x) {
	std::uniform_int_distribution<int> dist(0, x);
	int time = std::chrono::high_resolution_clock().now().time_since_epoch().count();
	std::default_random_engine rand(time);
	int randf = dist(rand);
	if (randf == 0) {
		return 1;
	}
}
int main(int argc, char* argv[]) {
	SDL_INIT_EVERYTHING;
	SDL_Window *window;
	SDL_Renderer *render;
	window = SDL_CreateWindow("yeet", 50, 50, 1000, 1000, NULL);
	render = SDL_CreateRenderer(window, 0, NULL);
	SDL_Rect rect;
	rect.h = 10;
	rect.w = 10;
	for (int i = 0; i < 30000; i+=3) {
		data[i] = (i / 3) % 100;
		data[i + 1] = i / 300;
		data[i + 2] = random(10);
	}
	while (true) {
		SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
		for (int i = 0; i < 30000; i += 3) {
			if (data[i + 2] == 1) {
				rect.x = data[i] * 10;
				rect.y = data[i + 1] * 10;
				SDL_RenderDrawRect(render,&rect);
			}
		}
		for (int i = 0; i < 30000; i+=3) {
			cnt = 0;
			for (int i2 = 0; i2 < sizeof(checkneighbours) / 4; i2++) {
				if (data[i + checkneighbours[i2] * 3 + 2] == 1) {
					cnt += 1;
				}
			}
			dataoverwrite[i] = data[i];
			dataoverwrite[i + 1] = data[i + 1];
			if (data[i + 2] == 1 && cnt > 1 && cnt < 4) {
				dataoverwrite[i + 2] = 1;
			}
			else if (data[i + 2] == 0 && cnt == 3) {
				dataoverwrite[i + 2] = 1;
			}
			else {
				dataoverwrite[i + 2] = 0;
			}
		}
		for (int i = 0; i < 30000; i++) {
			data[i] = dataoverwrite[i];
		}
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderPresent(render);
		SDL_RenderClear(render);
		
	}
	return 0;
}
