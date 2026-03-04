# shellsweeper

Terminal Minesweeper written in C++ using ncurses.

### Dependencies

- CMake
- A C++20 compatible compiler
- ncurses

On Ubuntu/Debian:

```
sudo apt install cmake build-essential libncurses-dev
```

### Installation


Clone the repository

```
git clone https://github.com/SrBlank/shellsweeper.git
cd shellsweeper
```

Configure the project with CMake

```
cmake -B build
```

Build the project

```
cmake --build build
```

Run the game

```
./build/shellsweeper
```