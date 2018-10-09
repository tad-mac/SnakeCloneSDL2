#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <string>

// Declaring Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int PLAY_HEIGHT = 440;
const int PLAYER_START_SPEED = 1;
const int PLAYER_HEAD_WIDTH = 40;
const int PLAYER_HEAD_HEIGHT = 40;
const int PLAYER_START_X = 50;
const int PLAYER_START_Y = 30;
const char *font_path = "assets/font/FreeSans.ttf";

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
SDL_Texture* score_text = NULL;
SDL_Rect score_rect;
TTF_Font* font = NULL;

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

    TTF_Init();
    font = TTF_OpenFont(font_path, 24);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }


    return success;
}

void close(){

    SDL_DestroyWindow( window );
    renderer = NULL;
    window = NULL;

    SDL_Quit();
}


// int printScore(int score){
//     score++;
//     sprintf(StringScore, "%d", score);
//     strcat(ScoreText, StringScore);
//     return score;
// }

//colors the background white
void fillBackground(){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, NULL);
}

void RenderText(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect){
    int text_width = 12;
    int text_height = 12;
    SDL_Surface *surface;
    SDL_Color textColor = {0, 0, 0, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}


void DrawText(){
    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
    SDL_RenderCopy(renderer, score_text, NULL, &score_rect);
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
            SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
            SDL_RenderFillRect(renderer, &head);

        }

        //moves the snake up
        void up(){
            y = y - speed;
            if (y < PLAYER_START_Y){
                y = PLAYER_START_Y;
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

class Food{
    public:
        SDL_Rect rect;
        SDL_Surface* surface;
        bool eaten = false;
        int x = 100; 
        int y = 100;

        // void make(){
            
        // }
        void appear(){
            rect.w = PLAYER_HEAD_WIDTH;
            rect.h = PLAYER_HEAD_HEIGHT;
            rect.x = rand() % 600;
            rect.y = rand() % 400;
        }

        void draw(){
            SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
        }

};

int main( int argc, char* args[] ){

    //using time as the random generator seed
    int score = 0;
    char StringScore[32];
    char ScoreText[100] = "Score: ";
    srand(time(0));
    
    bool quit = false;
    SDL_Event e;
    Snake player;
    Food food;
    food.eaten = true;
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
                // handles quiting events (pressing the X, etc)
                if( e.type == SDL_QUIT ) { 
                    quit = true; 
                }
                //debugging - moves the food and adds 1 to the score
                if(e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_f)
                        {
                            food.eaten = true;
                            score = score + 1;
                            sprintf(StringScore, "%d", score);
                            strcat(ScoreText, StringScore);   
                        }
                    }

            }

//keyboard event handling *****************************************************************************************************

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
                if(player.direction != move_left){
                    player.direction = move_right;
                    printf("X: %d, Y: %d \n", player.x, player.y );
                }
            }

            if (keypressed[SDL_SCANCODE_A] || keypressed[SDL_SCANCODE_LEFT]){
                if(player.direction != move_right){
                    player.direction = move_left;
                    printf("X: %d, Y: %d \n", player.x, player.y );
                }
            }

//setting player directiopm ***************************************************************************************************

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
                printf("Game Over!\n");
                quit = true;
            }

            if (food.eaten == true){
                food.appear();
                food.eaten = false;
                printf("Food has appeared! 1\n");
            }

            
            SDL_Delay(10);
            fillBackground();
            if (food.eaten == false){
                food.draw();
            }
            food.draw();
            player.draw();
            RenderText(renderer, 0, 0, ScoreText, font, &score_text, &score_rect);
            DrawText();

            SDL_RenderPresent(renderer);
        }
    }
    
    close();
    return 0;
}