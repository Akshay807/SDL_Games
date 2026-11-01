##Project Structure

CarGame/
│
├── include/
│   ├── game.h
│   ├── game_config.h
│   ├── vehicle.h
│   ├── player_car.h
│   ├── obstacle.h
│   ├── road.h
│   ├── input_handler.h
│   └── collision.h
│
├── src/
│   ├── main.cpp
│   ├── game.cpp
│   ├── vehicle.cpp
│   ├── player_car.cpp
│   ├── obstacle.cpp
│   ├── road.cpp
│   ├── input_handler.cpp
│   └── collision.cpp
│
├── assets/
├── docs/
└── CMakeLists.txt


##Milestones
M1. Foundation and architecture
Foundation done

- [x] Visual Studio + CMake + vcpkg + SDL2 setup
- [x] Basic Vehicle class
- [x] SDL window and renderer
- [x] Vehicle movement and boundaries
- [x] Road and lane markings
- [x] Delta-time-based scrolling
- [ ] Refactor into proper Game architecture

M2. Core OOP architecture
- Game class — lifecycle and coordination
- Vehicle — common base class
- PlayerCar — player-specific behavior
- Obstacle — enemy traffic
- Road — road rendering and scrolling
- InputHandler — keyboard input
- Composition, inheritance and polymorphism

M3. Racing mechanics
- Player lane switching and movement
- Multiple obstacles
- Obstacle spawning and removal
- Collision detection
- Speed and difficulty progression
- Score calculation

M4. Game experience
- Car and road sprites
- Scrolling background
- Main menu
- Score and high-score display
- Lives and game-over screen
- Restart and pause functionality
- Sound effects and music

M5. Advanced C++ and game engineering
- Smart pointers and resource management
- STL containers and algorithms
- RAII and constructors/destructors
- Event-driven design
- Separation of concerns
- Basic design patterns where useful
- Debugging and performance optimization

M6. Testing and delivery
- Unit testing important game logic
- Test collision and movement edge cases
- Git and GitHub repository
- CMake release build
- Executable packaging
- README and architecture documentation
