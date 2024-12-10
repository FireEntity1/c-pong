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
int delta() {
    int lastFrameTime, currentFrameTime, deltaTime;
    lastFrameTime = currentFrameTime;
    currentFrameTime = SDL_GetTicks();
    deltaTime = currentFrameTime - lastFrameTime;
    return deltaTime;
}

void reset(int *paddlePos,int *ballPosX, int *ballPosY, bool*direction) {
    // paddlePos = 0;
    *ballPosX = 200;
    *ballPosY = 200;
    *direction = true;
}

int main(int argc, char* argv[]){

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

    const int DESIRED_FPS = 120;
    const int FRAME_TARGET_TIME = 1000 / DESIRED_FPS;

    int linePos = 0;
    bool inputMap[3] = {false,false,false}; // w, s
    int ballPos[2] = {200,200};
    bool ballDir[2] = {true,true};

    while(gameIsRunning){
        Uint32 frameStart = SDL_GetTicks();

        SDL_Event event;

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
        if (*inputMap == true) {linePos -= 2;}
        if (*(inputMap+1) == true) {linePos += 2;}
        linePos = clamp(linePos,0,350);

        // draw stuff!
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);

        SDL_RenderDrawLine(renderer,10,linePos,10,linePos+50);

        SDL_Rect ball;
        ball.h = 5;
        ball.w = 5;
        ball.x = ballPos[0];
        ball.y = ballPos[1];

        if (ballPos[0] >= 400) {
            ballDir[0] = false; 
        } else if (ballPos[0] <= 10) {
            if (linePos < ballPos[1] && linePos+50 > ballPos[1]) {
                ballDir[0] = true;
            } else {
                reset(&linePos,&ballPos[0],&ballPos[1],&ballDir[0]);
            }
        }

        if (ballPos[1] >= 400) {
            ballDir[1] = false;
        } else if (ballPos[1] <= 0) {
            ballDir[1] = true; 
        }

        if (ballDir[0]) {
            ballPos[0] += 2;
        } else {
            ballPos[0] -= 2;
        }

        if (ballDir[1]) {
            ballPos[1] += 1;
        } else {
            ballPos[1] -= 1;
        }

        SDL_RenderDrawRect(renderer, &ball);
        // SDL_RenderCopy(renderer,imageTexture,NULL,NULL);

        SDL_RenderPresent(renderer);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_TARGET_TIME > frameTime) {
        SDL_Delay(FRAME_TARGET_TIME - frameTime);
}
    }

    SDL_DestroyWindow(window);
        
    SDL_Quit();
    return 0;
}