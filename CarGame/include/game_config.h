#pragma once

namespace GameConfig
{
	constexpr int WINDOW_WIDTH = 1280;
	constexpr int WINDOW_HEIGHT = 720;

	constexpr int ROAD_WIDTH = 600;
	constexpr int ROAD_X = (WINDOW_WIDTH - ROAD_WIDTH) / 2;

	constexpr int LANE_COUNT = 2;
	constexpr int LANE_WIDTH = ROAD_WIDTH / LANE_COUNT;

	constexpr int DASH_HEIGHT = 40;
	constexpr int DASH_GAP = 30;
}
