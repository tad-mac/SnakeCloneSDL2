#include <SDL2/SDL.h>
#include <stdio.h>

// Declaring Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Setting Pointer to NULL
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

//loading sub systems
bool init(){
    bool success = true;

    if(SDL_Init( SDL_INIT_VIDEO ) <0){
        success = false;
    }
    else {
        window = SDL_CreateWindow("SNAKE CLONE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    }

    return success;
}

void close(){
    //Deallocate surface
    SDL_FreeSurface( screenSurface );
    screenSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] ){
    bool quit = false;
    SDL_Event e;
    if(!init()){
        printf("Window could not initialized!, Error: %s\n", SDL_GetError());    
    }
    else {
        while(!quit){
            while( SDL_PollEvent( &e ) != 0 ) { 
            //User requests quit 
                if( e.type == SDL_QUIT ) { 
                    quit = true; 
                } 
            }
            //Get window surface 
            screenSurface = SDL_GetWindowSurface( window );
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            SDL_UpdateWindowSurface( window );
        }
    }

    close();

    return 0;
}
