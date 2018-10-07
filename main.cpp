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

//enumeratoring snakes movements
enum MOVE{
    move_up,
    move_down,
    move_left,
    move_right
};

//Setting Pointers to NULL
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


//loading sub systems
bool init(){
    bool success = true;

    if(SDL_Init( SDL_INIT_VIDEO ) <0){
        success = false;
    }
    else {
        window = SDL_CreateWindow("SNAKE CLONE", SDL_WINDOWPOS_UNDEFINED, 
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        success = false;
    }


    return success;
}

void close(){

    SDL_DestroyWindow( window );
    renderer = NULL;
    window = NULL;

    SDL_Quit();
}

//colors the background white
void fillBackground(){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, NULL);
}

class Snake{
    public:
        SDL_Rect head;
        SDL_Surface* surface;
        bool alive;
        int length, speed, x, y, direction;

        //sets the initial values of the snake
        void make(){
            alive = true;
            head.x = PLAYER_START_X;
            x = PLAYER_START_X;
            y = PLAYER_START_Y;
            head.y = PLAYER_START_Y;
            head.w = PLAYER_HEAD_WIDTH;
            head.h = PLAYER_HEAD_HEIGHT; 
            speed = PLAYER_START_SPEED;
            direction = move_right;
        }

        //draws the snake
        void draw(){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &head);

        }

        //moves the snake up
        void up(){
            y = y - speed;
            if (y < 0){
                y = 0;
                alive = false;
            }
            head.y = y;
        }

        //moves the snake down
        void down(){
            y = y + speed;
            if (y > SCREEN_HEIGHT - PLAYER_HEAD_HEIGHT){
                y = SCREEN_HEIGHT - PLAYER_HEAD_HEIGHT;
                alive = false;
            }
            head.y = y;
        }

        //moves the snake right
        void right(){
            x = x + speed;
            if (x > SCREEN_WIDTH - PLAYER_HEAD_WIDTH){
                x = SCREEN_WIDTH - PLAYER_HEAD_WIDTH;
                alive = false;
            }
            head.x = x;
        }

        //moves the snake left
        void left(){
            x = x - speed;
            if (x < 0){
                x = 0;
                alive = false;
            }
            head.x = x;
        }


        //increases the snakes length once a food piece is eaten
        void grow(){
            length++;
        }

        //speeds up the snake once a certain score is reached
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
    
    //main game loop starts
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
                if(player.direction != move_down){    
                    player.direction = move_up;
                    printf("X: %d, Y: %d \n", player.x, player.y );
                }
            }

            if (keypressed[SDL_SCANCODE_S] || keypressed[SDL_SCANCODE_DOWN]){
                if(player.direction != move_up){    
                    player.direction = move_down;
                    printf("X: %d, Y: %d \n", player.x, player.y );
                }

            }
            if (keypressed[SDL_SCANCODE_D] || keypressed[SDL_SCANCODE_RIGHT]){
                player.direction = move_right;
                printf("X: %d, Y: %d \n", player.x, player.y );

            }

            if (keypressed[SDL_SCANCODE_A] || keypressed[SDL_SCANCODE_LEFT]){
                player.direction = move_left;
                printf("X: %d, Y: %d \n", player.x, player.y );

            }

            if (player.direction == move_up){
                player.up();
            }

            else if (player.direction == move_down){
                player.down();
            }

            else if (player.direction == move_right){
                player.right();
            }

            else if (player.direction == move_left){
                player.left();
            }

            if (player.alive == false){
                quit = true;
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