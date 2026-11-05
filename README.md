# FabIO_2D
A game engine created with C++, SDL, OpenGL and Box2D

## Build

Clone the repository, then run these commands from its root folder.

### Windows (Visual Studio 2022)

```
cmake --preset vs2022
cmake --build --preset vs2022
```

Or open the generated `build-vs/GameEngine.sln` and press F5 (Game is the startup project).

### macOS (Xcode)

```
cmake --preset xcode
cmake --build --preset xcode
```

Or open `build-xcode/GameEngine.xcodeproj`.

### Any OS (Ninja, command line / VS Code / CLion)

```
cmake --preset ninja
cmake --build --preset ninja
```

## Run

Run the game from the repository root so relative paths such as `shaders/` and `assets/` resolve:

```
./build/Game/Game                       # Ninja (Linux/macOS)
build\Game\Game.exe                     # Ninja (Windows)
build-vs\Game\Debug\Game.exe            # Visual Studio
```