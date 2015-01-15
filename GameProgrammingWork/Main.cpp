#include <iostream>
#include <SDL.h>

using namespace std;

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	SDL_Window * window = SDL_CreateWindow("CST8237 First Program Tho", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, SDL_WINDOW_SHOWN);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	float posX = 100.0f, posY = 100.0f;
	float endPointOffsetX = 10.0f, endPointOffsetY = 0.0f;
	float oldTime, currentTime, deltaTime;
	float speed = 10.0f;

	//Get the time at the beginning of our game loop so that we can track the elapsed difference
	oldTime = SDL_GetTicks();
	currentTime = oldTime;

	while (true)
	{
		SDL_Event evt;
		SDL_PollEvent(&evt);

		//Calculating the difference since our last loop
		oldTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - oldTime) / 1000;

		//Check for user input
		if (evt.type == SDL_KEYDOWN)
		{
			SDL_KeyboardEvent &keyboardEvt = evt.key;
			SDL_Keycode &keyCode = keyboardEvt.keysym.sym;

			

			switch (keyCode)
			{
			case SDLK_UP:
				posY -= (speed * deltaTime);
				break;
			case SDLK_DOWN:
				posY += (speed * deltaTime);
				break;
			default:
				break;
			}
		}

		//set the draw color for our screen
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		
		

		//clear the renderer with the current draw color
		SDL_RenderClear(renderer);

		// set the draw color for our point
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		
		float transformedEndPointX = posX + endPointOffsetX;
		float transformedEndPointY = posY + endPointOffsetY;

		float rotation = 10.0f;
		float rX = endPointOffsetX * cos(rotation) + endPointOffsetX *sin (rotation);

		// present what is in our renderer to our window
		//SDL_RenderDrawPoint(renderer, posX, posY);
		SDL_RenderDrawLine(renderer, posX, posY, transformedEndPointX, transformedEndPointY);

		posY = (posY < 640) ? posY + 1 : posY;

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}