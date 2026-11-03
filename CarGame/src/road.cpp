#include "road.h"
#include "game_config.h"

Road::Road()
{
    roadOffset = 0.0f;
}

void Road::update(float deltaTime)
{
    // Changes the offset based on elapsed time.
    roadOffset += 200.0f * deltaTime;
    int patternHeight = GameConfig::DASH_HEIGHT + GameConfig::DASH_GAP;
    
    if (roadOffset >= patternHeight)
        roadOffset -= patternHeight;
}

void Road::render(SDL_Renderer* renderer) const // Draws the road using the current offset
{   
	int roadX = GameConfig::ROAD_X;
	int roadWidth = GameConfig::ROAD_WIDTH;
	int roadRight = roadX + roadWidth;

    // Road Surface
	SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255); // Set draw color to dark gray

	SDL_Rect roadRect = { roadX, 0, roadWidth, GameConfig::WINDOW_HEIGHT };
	SDL_RenderFillRect(renderer, &roadRect);

	// Road Boundaries
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set draw color to white
	SDL_RenderDrawLine(renderer, roadX, 0, roadX, GameConfig::WINDOW_HEIGHT); // Left boundary
	SDL_RenderDrawLine(renderer, roadX + roadWidth, 0, roadX + roadWidth, GameConfig::WINDOW_HEIGHT); // Right boundary

	// Lane Divider
	int laneDividerX = roadX + GameConfig::LANE_WIDTH;
	int patternHeight = GameConfig::DASH_HEIGHT + GameConfig::DASH_GAP;

	for (int y = -patternHeight; y < GameConfig::WINDOW_HEIGHT; y += patternHeight)
	{
		int dashY = y + static_cast<int>(roadOffset);

		SDL_RenderDrawLine(renderer, laneDividerX, dashY, laneDividerX, dashY + GameConfig::DASH_HEIGHT);
	}
}
    