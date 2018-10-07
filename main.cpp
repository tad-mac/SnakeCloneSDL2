#include <SDL2/SDL.h>
#include <stdio.h>

// Declaring Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int PLAYER_START_SPEED = 1;
const int PLAYER_HEAD_WIDTH = 40;
const int PLAYER_HEAD_HEIGHT = 40;
const int PLAYER_START_X = 30;
const int PLAYER_START_Y = 30;


//Setting Pointer to NULL
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        success = false;
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

void fillBackground(){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, NULL);
}

class Snake{
    

    public:
        SDL_Rect head;
        SDL_Surface* surface;
        int length, speed, x, y;
        
        
        void make(){

            head.x = PLAYER_START_X;
            x = PLAYER_START_X;
            y = PLAYER_START_Y;
            head.y = PLAYER_START_Y;
            head.w = PLAYER_HEAD_WIDTH;
            head.h = PLAYER_HEAD_HEIGHT; 
            speed = PLAYER_START_SPEED;
        }

        void draw(){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &head);

        }

        void up(){
            y = y - speed;
            head.y = y;
        }

        void down(){
            y = y + speed;
            head.y = y;
        }

        void right(){
            x = x + speed;
            head.x = x;
        }

        void left(){
            x = x - speed;
            head.x = x;
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
    player.make();
    
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

            if (keypressed[SDL_SCANCODE_ESCAPE]){
                quit = true; 

            }            

            if (keypressed[SDL_SCANCODE_W] || keypressed[SDL_SCANCODE_UP]){
                player.up();
                printf("X: %d, Y: %d \n", player.x, player.y );

            }

            if (keypressed[SDL_SCANCODE_S] || keypressed[SDL_SCANCODE_DOWN]){
                player.down();
                printf("X: %d, Y: %d \n", player.x, player.y );

            }
            if (keypressed[SDL_SCANCODE_D] || keypressed[SDL_SCANCODE_RIGHT]){
                player.right();
                printf("X: %d, Y: %d \n", player.x, player.y );

            }

            if (keypressed[SDL_SCANCODE_A] || keypressed[SDL_SCANCODE_LEFT]){
                player.left();
                printf("X: %d, Y: %d \n", player.x, player.y );

            }
            SDL_Delay(10);
            fillBackground();
            player.draw();
            SDL_RenderPresent(renderer);
        }
    }
    
    close();
    return 0;
}