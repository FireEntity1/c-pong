#include <iostream>

#include <SDL2/SDL.h> 
#include <stdio.h>
#include <SDL_image.h>

// clang++ main.c -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -I/Library/Frameworks/SDL2_image.framework/Headers  -framework SDL2_image

int clamp(int x,int min, int max) {
    if (x<min) {
        return min;
    }
    else if (x>max)
    {
        return max;
    }
    else {
        return x;
    }
    
}

void renderText(char txt[10]) {
    return;
}

int main(int argc, char* argv[]){

    Uint32 black = 255;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "sdl brokey :(" <<
                  SDL_GetError();
    } else {
        std::cout << "sdl worky!\n";
    }

    SDL_Window* window = SDL_CreateWindow("C Pong",20, 20, 400,400,SDL_WINDOW_SHOWN);


    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    IMG_Init(IMG_INIT_PNG);

    SDL_Surface *image;
    image = IMG_Load("pong.png");
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_Rect imgRect;
    imgRect.x = 50;
    imgRect.y = 50;
    imgRect.w = 100;
    imgRect.h = 50;

    SDL_FillRect(image, &imgRect, SDL_MapRGB(image->format, 0, 0, 0));
    // variables !!
    bool gameIsRunning = true;
    int linePos = 0;

    bool inputMap[3] = {false,false,false}; // w, s


    int lastFrameTime, currentFrameTime, deltaTime;
    while(gameIsRunning){
        SDL_Event event;

        lastFrameTime = currentFrameTime;
        currentFrameTime = SDL_GetTicks();
        deltaTime = currentFrameTime - lastFrameTime;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            } if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                    inputMap[0] = true;
                    break;

                    case SDLK_s:
                    inputMap[1] = true;
                    break;
                }
            }
            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                    inputMap[0] = false;
                    break;
                    case SDLK_s:
                    inputMap[1] = false;
                    break;
                }
            }
        }   

        // paddle movement + boundaries
        if (*inputMap == true) {linePos -= 1;}
        if (*(inputMap+1) == true) {linePos += 1;}
        linePos = clamp(linePos,0,350);

        // draw stuff!
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);

        SDL_RenderDrawLine(renderer,10,linePos,10,linePos+50);

        SDL_RenderCopy(renderer,imageTexture,NULL,NULL);

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyWindow(window);
        
    SDL_Quit();
    return 0;
}

