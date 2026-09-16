#define SDL_MAIN_HANDLED

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

namespace
{
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 720;

    void cleanup(SDL_Window* window,
                 SDL_Renderer* renderer,
                 SDL_Texture* imageTexture,
                 SDL_Texture* textTexture,
                 TTF_Font* font,
                 Mix_Chunk* sound)
    {
        if (sound)
            Mix_FreeChunk(sound);

        if (textTexture)
            SDL_DestroyTexture(textTexture);

        if (imageTexture)
            SDL_DestroyTexture(imageTexture);

        if (font)
            TTF_CloseFont(font);

        if (renderer)
            SDL_DestroyRenderer(renderer);

        if (window)
            SDL_DestroyWindow(window);

        Mix_CloseAudio();
        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}

int main()
{
    std::cout << "SDL2 Game Template starting...\n";

    // ------------------------------------------------------------
    // 1. Initialize SDL2
    // ------------------------------------------------------------
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        std::cerr << "SDL_Init failed: "
                  << SDL_GetError() << '\n';

        return 1;
    }

    // ------------------------------------------------------------
    // 2. Initialize SDL_image
    //    PNG is required for this smoke test.
    // ------------------------------------------------------------
    constexpr int imageFlags = IMG_INIT_PNG;

    if ((IMG_Init(imageFlags) & imageFlags) != imageFlags)
    {
        std::cerr << "SDL_image initialization failed: "
                  << IMG_GetError() << '\n';

        SDL_Quit();
        return 1;
    }

    // ------------------------------------------------------------
    // 3. Initialize SDL_ttf
    // ------------------------------------------------------------
    if (TTF_Init() != 0)
    {
        std::cerr << "SDL_ttf initialization failed: "
                  << TTF_GetError() << '\n';

        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // ------------------------------------------------------------
    // 4. Initialize SDL_mixer
    //
    // Audio is optional for now.
    // If the Windows audio device cannot be opened,
    // the application continues so that SDL2/image/ttf
    // can still be tested.
    // ------------------------------------------------------------
    bool audioAvailable = true;

    if (Mix_Init(0) != 0)
    {
        std::cerr << "SDL_mixer initialization failed: "
                  << Mix_GetError() << '\n';

        audioAvailable = false;
    }

    if (audioAvailable)
    {
        if (Mix_OpenAudio(
                44100,
                MIX_DEFAULT_FORMAT,
                2,
                2048) != 0)
        {
            std::cerr << "Warning: Mix_OpenAudio failed: "
                      << Mix_GetError() << '\n';

            std::cerr << "Continuing without audio.\n";

            audioAvailable = false;
        }
    }

    // ------------------------------------------------------------
    // 5. Create SDL window
    // ------------------------------------------------------------
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Game Template",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window)
    {
        std::cerr << "Window creation failed: "
                  << SDL_GetError() << '\n';

        cleanup(
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr
        );

        return 1;
    }

    // ------------------------------------------------------------
    // 6. Create renderer
    // ------------------------------------------------------------
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer)
    {
        std::cerr << "Renderer creation failed: "
                  << SDL_GetError() << '\n';

        cleanup(
            window,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr
        );

        return 1;
    }

    // ------------------------------------------------------------
    // 7. Asset paths
    // ------------------------------------------------------------
    const std::string assetRoot = "assets/";

    const std::string imagePath =
        assetRoot + "images/car.png";

    const std::string soundPath =
        assetRoot + "audio/beep.wav";

    // ------------------------------------------------------------
    // 8. Load font
    //
    // Uses Windows Arial so the template does not need
    // to ship a font file.
    // ------------------------------------------------------------
    const char* fontPath = "C:/Windows/Fonts/arial.ttf";

    TTF_Font* font = TTF_OpenFont(
        fontPath,
        42
    );

    if (!font)
    {
        std::cerr << "TTF_OpenFont failed: "
                  << TTF_GetError() << '\n';

        cleanup(
            window,
            renderer,
            nullptr,
            nullptr,
            nullptr,
            nullptr
        );

        return 1;
    }

    // ------------------------------------------------------------
    // 9. Load PNG image
    // ------------------------------------------------------------
    SDL_Surface* imageSurface =
        IMG_Load(imagePath.c_str());

    if (!imageSurface)
    {
        std::cerr << "IMG_Load failed: "
                  << IMG_GetError() << '\n';

        cleanup(
            window,
            renderer,
            nullptr,
            nullptr,
            font,
            nullptr
        );

        return 1;
    }

    SDL_Texture* imageTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            imageSurface
        );

    SDL_FreeSurface(imageSurface);

    if (!imageTexture)
    {
        std::cerr
            << "SDL_CreateTextureFromSurface failed: "
            << SDL_GetError()
            << '\n';

        cleanup(
            window,
            renderer,
            nullptr,
            nullptr,
            font,
            nullptr
        );

        return 1;
    }

    // ------------------------------------------------------------
    // 10. Create text
    // ------------------------------------------------------------
    SDL_Color textColor{
        255,
        255,
        255,
        255
    };

    SDL_Surface* textSurface =
        TTF_RenderUTF8_Blended(
            font,
            "SDL2 + CMake + vcpkg + Visual Studio",
            textColor
        );

    if (!textSurface)
    {
        std::cerr
            << "TTF_RenderUTF8_Blended failed: "
            << TTF_GetError()
            << '\n';

        cleanup(
            window,
            renderer,
            imageTexture,
            nullptr,
            font,
            nullptr
        );

        return 1;
    }

    SDL_Texture* textTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            textSurface
        );

    SDL_FreeSurface(textSurface);

    if (!textTexture)
    {
        std::cerr
            << "SDL_CreateTextureFromSurface "
               "(text) failed: "
            << SDL_GetError()
            << '\n';

        cleanup(
            window,
            renderer,
            imageTexture,
            nullptr,
            font,
            nullptr
        );

        return 1;
    }

    // ------------------------------------------------------------
    // 11. Load and play WAV
    //
    // Audio is optional. Failure does not stop the
    // application.
    // ------------------------------------------------------------
    Mix_Chunk* sound = nullptr;

    if (audioAvailable)
    {
        sound = Mix_LoadWAV(
            soundPath.c_str()
        );

        if (!sound)
        {
            std::cerr
                << "Warning: Mix_LoadWAV failed: "
                << Mix_GetError()
                << '\n';

            audioAvailable = false;
        }
    }

    if (audioAvailable && sound)
    {
        if (Mix_PlayChannel(
                -1,
                sound,
                0
            ) == -1)
        {
            std::cerr
                << "Warning: Mix_PlayChannel failed: "
                << Mix_GetError()
                << '\n';

            audioAvailable = false;
        }
    }

    // ------------------------------------------------------------
    // 12. Determine image dimensions
    // ------------------------------------------------------------
    int imageWidth = 0;
    int imageHeight = 0;

    SDL_QueryTexture(
        imageTexture,
        nullptr,
        nullptr,
        &imageWidth,
        &imageHeight
    );

    // ------------------------------------------------------------
    // 13. Determine text dimensions
    // ------------------------------------------------------------
    int textWidth = 0;
    int textHeight = 0;

    SDL_QueryTexture(
        textTexture,
        nullptr,
        nullptr,
        &textWidth,
        &textHeight
    );

    // ------------------------------------------------------------
    // 14. Position image
    // ------------------------------------------------------------
    const SDL_Rect imageRect{
        WINDOW_WIDTH / 2 - imageWidth / 2,
        WINDOW_HEIGHT / 2 - imageHeight / 2 + 40,
        imageWidth,
        imageHeight
    };

    // ------------------------------------------------------------
    // 15. Position text
    // ------------------------------------------------------------
    const SDL_Rect textRect{
        WINDOW_WIDTH / 2 - textWidth / 2,
        80,
        textWidth,
        textHeight
    };

    // ------------------------------------------------------------
    // 16. Main event loop
    // ------------------------------------------------------------
    bool running = true;

    SDL_Event event{};

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            // Close window
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            // ESC key closes application
            else if (
                event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_ESCAPE
            )
            {
                running = false;
            }
        }

        // --------------------------------------------------------
        // Clear screen
        // --------------------------------------------------------
        SDL_SetRenderDrawColor(
            renderer,
            25,
            25,
            25,
            255
        );

        SDL_RenderClear(renderer);

        // --------------------------------------------------------
        // Draw text
        // --------------------------------------------------------
        SDL_RenderCopy(
            renderer,
            textTexture,
            nullptr,
            &textRect
        );

        // --------------------------------------------------------
        // Draw image
        // --------------------------------------------------------
        SDL_RenderCopy(
            renderer,
            imageTexture,
            nullptr,
            &imageRect
        );

        // --------------------------------------------------------
        // Present frame
        // --------------------------------------------------------
        SDL_RenderPresent(renderer);
    }

    // ------------------------------------------------------------
    // 17. Cleanup
    // ------------------------------------------------------------
    cleanup(
        window,
        renderer,
        imageTexture,
        textTexture,
        font,
        sound
    );

    std::cout
        << "SDL2 Game Template completed successfully.\n";

    return 0;
}