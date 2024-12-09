#include <iostream>

#include <SDL2/SDL.h> 
#include <stdio.h>

// clang++ main.c -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2

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

int main(int argc, char* argv[]){

    SDL_Window* window=nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }

    window = SDL_CreateWindow("I LOVE SDL !!!111",20, 20, 400,400,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


// variables !!
    bool gameIsRunning = true;
    int linePos = 0;
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    bool isW = false;
    bool isS = false;

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
                    isW = true;
                    break;

                    case SDLK_s:
                    isS = true;
                    break;
                }
            }
            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                    isW = false;
                    break;
                    case SDLK_s:
                    isS = false;
                    break;
                }
            }
        }   

        if (isW == true) {linePos -= 1;}
        if (isS == true) {linePos += 1;}
        linePos = clamp(linePos,0,350);

        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);

        SDL_RenderDrawLine(renderer,10,linePos,10,linePos+50);

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyWindow(window);
        
    SDL_Quit();
    return 0;
}

