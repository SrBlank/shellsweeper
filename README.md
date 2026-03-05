# ShellSweeper

Terminal Minesweeper written in C++ using ncurses.

### Dependencies

- CMake
- A C++20 compatible compiler
- ncurses

On Ubuntu/Debian:

```
sudo apt install cmake build-essential libncurses-dev
```

### Install

#### APT Repository

ShellSweeper can be installed on Ubuntu and Debian-based systems using the official APT repository.

Install the repository signing key

```
curl -fsSL https://srblank.github.io/shellsweeper/key.gpg \
| sudo gpg --dearmor -o /usr/share/keyrings/shellsweeper.gpg
```

Add the ShellSweeper repository

```
echo "deb [arch=amd64 signed-by=/usr/share/keyrings/shellsweeper.gpg] https://srblank.github.io/shellsweeper stable main" \
| sudo tee /etc/apt/sources.list.d/shellsweeper.list
```

Update package lists 

```
sudo apt update
```

Install ShellSweeper

```
sudo apt install shellsweeper
```

Run the game

```
shellsweeper
```

#### Direct .deb installation

If you prefer not to add the repository:

```
wget https://srblank.github.io/shellsweeper/shellsweeper_1.0.5_amd64.deb
sudo apt install ./shellsweeper_1.0.5_amd64.deb
```


#### Local Build

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

### Uninstall

#### APT Repository

Remove the package and cleanup

```
sudo apt remove shellsweeper
sudo apt autoremove
```

Remove the repository

```
sudo rm /etc/apt/sources.list.d/shellsweeper.list
```

Remove the repository signing key

```
sudo rm /usr/share/keyrings/shellsweeper.gpg
```

Refresh apt

```
sudo apt update
```