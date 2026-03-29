#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <random>


using namespace std;

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;
int ROAD_SPEED = 5;
int PLAYER_SPEED = 10;
int PADDING = 125; // From Right & Left

int GRASS_WIDTH = 22; // THis is calculated from trial & run

int PLAYER_CAR_HEIGHT = 150;
int PLAYER_CAR_WIDTH = 130;
int RIGHT_PADDING_PLAYER_CAR = WINDOW_WIDTH - PADDING - PLAYER_CAR_WIDTH;

int OPPONENT_CAR_HEIGHT = 150;
int OPPONENT_CAR_WIDTH = 60;

bool quit = false;
SDL_Event event;

SDL_Texture *loadTexture(const char *path, SDL_Renderer *renderer){
    SDL_Surface *surface = IMG_Load(path);
    if(!surface){
        cout<<"Problem creating an image on surface!!"<<endl;
        cout<<"IMG Load Error: "<<IMG_GetError()<<endl;
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
};


int main() {

    /*
    **********************************SETUP INITIALIZATION**********************************
    */

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout<<"SDL has failed to initialize"<<endl; 
        cout<<"SDL Initialization failed: "<<IMG_GetError()<<endl;
        return -1;
    }

    if(!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG)){
        cout<<"SDL2 image lib could not be initialized"<<endl;
        cout<<"SDL img load failed: "<<IMG_GetError()<<endl;
        SDL_Quit();
        return -1;
    }

    cout<<"SDL Successfully Initialized!"<<endl;

    SDL_Window *window = SDL_CreateWindow("Car Racing Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!window  || !renderer){
        cout<<"Problem creating SDL window!"<<endl;
        SDL_Quit();
        return -1;
    }

    // SDL_Delay(5000);

    SDL_Texture *roadTexture  = loadTexture("/home/miakshay/Akshay/C++_Setup/SDL2_GameDev_C++/better_road.png",        renderer);
    SDL_Texture *grassTexture = loadTexture("/home/miakshay/Akshay/C++_Setup/SDL2_GameDev_C++/roadside_grass.png",     renderer);
    SDL_Texture *playerCarTexture   = loadTexture("/home/miakshay/Akshay/C++_Setup/SDL2_GameDev_C++/car_image.png",    renderer);
    SDL_Texture *opponentCarTexture = loadTexture("/home/miakshay/Akshay/C++_Setup/SDL2_GameDev_C++/opponent_car.png", renderer);

    if(!roadTexture || !grassTexture || !playerCarTexture || !opponentCarTexture){
        cout<<"Load Texture has not been loaded"<<endl;
        cout<<"SDL texture load failed: "<<IMG_GetError()<<endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    /*
    *********************************MAKING OF ROAD LOGIC***********************************
    */

    SDL_Rect road1 = {0,              0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_Rect road2 = {0, -WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT};  // Initially we want the road to not be visible hence it kept at negative index.

    // Adding Grass
    SDL_Rect grass1Left = {0,              0, GRASS_WIDTH, WINDOW_HEIGHT};
    SDL_Rect grass2Left = {0, -WINDOW_HEIGHT, GRASS_WIDTH, WINDOW_HEIGHT};

    SDL_Rect grass1Right = {WINDOW_WIDTH - GRASS_WIDTH,              0,                GRASS_WIDTH, WINDOW_HEIGHT};
    SDL_Rect grass2Right = {WINDOW_WIDTH - GRASS_WIDTH, -WINDOW_HEIGHT, WINDOW_WIDTH - GRASS_WIDTH, WINDOW_HEIGHT};

    SDL_Rect playerCar   = {500, 400, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT};

    int minX = PADDING;
    int maxX = WINDOW_WIDTH - PADDING - OPPONENT_CAR_WIDTH;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(minX, maxX);

    int randomOpponentCarPosition = dist(gen);
    SDL_Rect opponentCar = {randomOpponentCarPosition, 0, OPPONENT_CAR_WIDTH, OPPONENT_CAR_HEIGHT};


    // Main or Game Loop
    while(!quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){     // TO keep the game window unless it is closed manually
                quit = true;
            }

            else if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym){
                    case SDLK_LEFT:
                        if (playerCar.x > PADDING){
                            playerCar.x -= PLAYER_SPEED;
                        }
                        break;

                    case SDLK_RIGHT:
                        if (playerCar.x < RIGHT_PADDING_PLAYER_CAR){
                            playerCar.x += PLAYER_SPEED;
                        }
                        break;

                    case SDLK_UP:
                        if (playerCar.y > 0){
                            playerCar.y -= PLAYER_SPEED;
                        }
                        break;

                    case SDLK_DOWN:
                        if (playerCar.y < WINDOW_HEIGHT - PLAYER_CAR_HEIGHT){
                            playerCar.y += PLAYER_SPEED;
                        }
                        break;
                }
            }
        }

        //Move Road
        road1.y += ROAD_SPEED; // Moving only the y-axis hence roadX.y.
        road2.y += ROAD_SPEED;

        if(road1.y >= WINDOW_HEIGHT){
            road1.y = road2.y - WINDOW_HEIGHT; 
        }

        if(road2.y >= WINDOW_HEIGHT){
            road2.y = road1.y - WINDOW_HEIGHT; 
        }

        //Move Left Grass
        grass1Left.y += ROAD_SPEED;
        grass2Left.y += ROAD_SPEED;

        if(grass1Left.y >= WINDOW_HEIGHT){
            grass1Left.y = grass2Left.y - WINDOW_HEIGHT; 
        }

        if(grass2Left.y >= WINDOW_HEIGHT){
            grass2Left.y = grass1Left.y - WINDOW_HEIGHT; 
        }

        //Move Right Grass
        grass1Right.y += ROAD_SPEED;
        grass2Right.y += ROAD_SPEED;

        if(grass1Right.y >= WINDOW_HEIGHT){
            grass1Right.y = grass2Right.y - WINDOW_HEIGHT; 
        }

        if(grass2Right.y >= WINDOW_HEIGHT){
            grass2Right.y = grass1Right.y - WINDOW_HEIGHT; 
        }

        //Move Opponent Car
        opponentCar.y += ROAD_SPEED + 5;

        if (opponentCar.y >= WINDOW_HEIGHT){
            opponentCar.y = -WINDOW_HEIGHT;
            uniform_int_distribution<> dist(minX, maxX);
            randomOpponentCarPosition = dist(gen);
            opponentCar.x = randomOpponentCarPosition;
        }

        //Collision Detection
        /* Case B
        1|--------|2 Player Car
         |        |    
         |____2   |
         |  O|    |
        4|___|____|3
        */        
        if ((opponentCar.x > playerCar.x) & (opponentCar.x < playerCar.x + PLAYER_CAR_WIDTH) & (opponentCar.y > playerCar.y) & (opponentCar.y < playerCar.y + PLAYER_CAR_HEIGHT)){
            // SDL_DestroyWindow(window);
        }



        //Render out
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, roadTexture, NULL, &road1);
        SDL_RenderCopy(renderer, roadTexture, NULL, &road2);

        SDL_RenderCopy(renderer, grassTexture, NULL, &grass1Left);
        SDL_RenderCopy(renderer, grassTexture, NULL, &grass2Left);

        SDL_RenderCopy(renderer, grassTexture, NULL, &grass1Right);
        SDL_RenderCopy(renderer, grassTexture, NULL, &grass2Right);

        SDL_RenderCopy(renderer, playerCarTexture, NULL, &playerCar);
        SDL_RenderCopy(renderer, opponentCarTexture, NULL, &opponentCar);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); //SDL_Delay(16); Approx 16 fps

    }

    SDL_DestroyTexture(roadTexture);
    SDL_DestroyTexture(grassTexture);
    SDL_DestroyTexture(playerCarTexture);
    SDL_DestroyTexture(opponentCarTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}