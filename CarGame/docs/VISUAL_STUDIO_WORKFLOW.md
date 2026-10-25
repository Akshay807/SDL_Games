# Visual Studio Workflow

## Open the project

In Visual Studio 2026:

**File → Open → Folder**

Choose the project folder containing `CMakeLists.txt`.

Visual Studio will detect the CMake project.

## Configure

Use the CMake configuration/preset selector and choose:

```text
windows-x64-debug
```

for normal development.

Use:

```text
windows-x64-release
```

for release builds.

## Build and debug

Set `SDL2GameTemplate` as the startup target. Press **F5** to build and launch under the Visual Studio debugger.

Use breakpoints in `src/main.cpp` to inspect SDL initialization, asset loading, event handling, and cleanup.

## Useful command-line equivalent

```powershell
cmake --preset windows-x64-debug
cmake --build --preset windows-x64-debug
.\build\Debug\SDL2GameTemplate.exe
```

## Important

Run CMake from a Visual Studio Developer PowerShell with the x64 toolchain available when doing command-line builds.
