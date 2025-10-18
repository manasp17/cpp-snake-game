# C++ Snake (terminal)

Simple terminal-based Snake game written in C++ for Windows consoles.

Features
- Simple ASCII rendering using `std::cout` and `system("cls")`.
- Keyboard input via `<conio.h>`: arrow keys and WASD supported.
- Wrap-around walls (snake appears on opposite side).
- Fruit placement avoids the snake body.

Files
- `main.cpp` — full source.

Build (Windows)

This project uses Windows-specific headers (`<conio.h>`, `<windows.h>`). It builds on Windows with either MinGW/MSYS2 `g++` or Visual Studio (MSVC).

1) Using MSYS2 (recommended)

- Install MSYS2: https://www.msys2.org/
- Open the "MSYS2 MinGW 64-bit" shell and run:

```sh
pacman -Syu
# close and re-open the MinGW 64-bit shell after the first step
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```

- Then from PowerShell or the MSYS2 MinGW shell compile:

```powershell
cd 'C:\Users\manas\Downloads\cpp-snake-game'
g++ .\main.cpp -O2 -std=c++17 -o .\snake.exe
.\snake.exe
```

2) Using MinGW-w64 standalone installer

- Install MinGW-w64 and add the `bin` directory to your PATH.
- Compile as above using `g++` in PowerShell.

3) Using Visual Studio (MSVC)

- Install Visual Studio or the Build Tools.
- Open the "x64 Native Tools Command Prompt" (so `cl.exe` is on PATH) and run:

```cmd
cl /EHsc "C:\Users\manas\Downloads\cpp-snake-game\main.cpp" /Fe:"C:\Users\manas\Downloads\cpp-snake-game\snake.exe"
```

Controls
- Arrow keys or WASD to move the snake.
- Press `x` (or `X`) to quit.

Notes
- The game uses a fixed-size tail array (capacity 100). That keeps the code simple but you could replace it with `std::vector` for dynamic growth.
- If the game seems to exit immediately when run from your editor, try running it from a normal PowerShell window (not the task runner) to ensure the process stays attached to a console.
- To slow the game for debugging, increase the `Sleep(100)` in `main.cpp`.

Troubleshooting
- `g++` not recognized: make sure MinGW/MSYS2 is installed and the `bin` folder is on PATH.
- Arrow keys not working in some terminals: run the exe in the Windows Console (cmd.exe / PowerShell) rather than some integrated terminals which may remap keys.

License
- Public domain / MIT — use as you wish.

Enjoy! If you want I can:
- Add a small `build.ps1` helper to compile+run from PowerShell.
- Convert the code to use `std::vector` for the tail and add a few unit tests for helper functions.
