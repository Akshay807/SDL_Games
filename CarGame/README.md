# SDL2 Game Template — Visual Studio + CMake + vcpkg

A reusable starting point for SDL2 C++ projects on Windows.

## Included

- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer
- CMake
- vcpkg manifest mode
- x64 Debug and Release CMake presets
- `src/` and `assets/` folders
- PNG image smoke test
- TTF text smoke test
- WAV audio smoke test
- Visual Studio / CMake workflow

## Requirements

- Visual Studio 2026 Community with C++ desktop development
- C++ CMake tools for Windows
- Windows 11 SDK
- vcpkg installed with Visual Studio
- CMake available from the Visual Studio environment

## Configure and build

Open a Visual Studio Developer PowerShell with x64 tools, then run from the project root:

### Debug

```powershell
cmake --preset windows-x64-debug
cmake --build --preset windows-x64-debug
```

Run:

```powershell
.\build\Debug\SDL2GameTemplate.exe
```

### Release

```powershell
cmake --preset windows-x64-release
cmake --build --preset windows-x64-release
```

Run:

```powershell
.\build\Release\SDL2GameTemplate.exe
```

## Visual Studio

Open the folder containing `CMakeLists.txt` in Visual Studio.

Visual Studio should detect the CMake project. Select the desired configure preset and build target. The generated executable can then be launched/debugged from Visual Studio.

## Template rules

1. Keep third-party dependencies in `vcpkg.json`.
2. Keep the vcpkg registry baseline in `vcpkg-configuration.json`.
3. Use the x64 triplet/configuration consistently with the x64 MSVC toolchain.
4. Do not manually add SDL include/lib directories when using the vcpkg CMake integration.
5. Do not link `SDL2::SDL2main` in this template because the program uses `SDL_MAIN_HANDLED` and a normal `int main()` entry point.
6. Put runtime assets under `assets/`.
7. Treat `build/` as generated output.
8. Keep reusable game code under `src/`.

## Current smoke test

The test application verifies:

- SDL window creation
- SDL renderer creation
- PNG loading through SDL_image
- text rendering through SDL_ttf
- WAV playback through SDL_mixer
- event processing
- clean shutdown

The font is loaded from the Windows Arial font location, so no font file is distributed in this template.
