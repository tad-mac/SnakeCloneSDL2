#include <SDL2/SDL.h>
#include <stdio.h>

// Declaring Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int PLAYER_START_SPEED = 2;

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
    SDL_FreeSurface( screenSurface );
    SDL_DestroyWindow( window );
    screenSurface = NULL;
    window = NULL;

    SDL_Quit();
}

class Snake{
    
    public:
        int length, speed, x, y;

        void up(){
            y = y - speed;
        }

        void down(){
            y = y + speed;
        }

        void right(){
            x = x - speed;
        }

        void left(){
            x = x + speed;
        }

        void grow(){
            length++;
        }

        void speedUp(){
            speed++;
        }
    
};

class food{

};

int main( int argc, char* args[] ){
    bool quit = false;
    SDL_Event e;
    Snake player;
    player.speed = PLAYER_START_SPEED;
    if(!init()){
        printf("Window could not initialized! Error: %s\n", SDL_GetError());    
    }
    else {
        while(!quit){
            SDL_PumpEvents();
            const Uint8 *keypressed = SDL_GetKeyboardState(NULL);

            while( SDL_PollEvent( &e ) != 0 ) { 
                if( e.type == SDL_QUIT ) { 
                    quit = true; 
                } 
            }

            if (keypressed[SDL_SCANCODE_A] || keypressed[SDL_SCANCODE_UP]){
                player.up();
                printf("X: %d, Y: %d \n", player.x, player.y );

            }
            screenSurface = SDL_GetWindowSurface( window );
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            SDL_UpdateWindowSurface( window );
        }
    }

    close();

    return 0;
}
