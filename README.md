# Cub3D

## Introduction
Cub3D is a 3D game project developed as part of the 42 school curriculum. The project is inspired by the classic Wolfenstein 3D game and involves creating a basic 3D game engine using ray-casting.

## Features
- **3D Graphics**: Render a 3D environment using ray-casting.
- **Player Movement**: Navigate through the game world with smooth player controls.
- **Wall Collision Detection**: Prevent the player from passing through walls.
- **Sprite Rendering**: Displays a sprite for a pistol the player has in the hand.
- **Minimap**: Display a 2D overview of the current level.
- **Configurable Levels**: Load game levels from configuration files.

## Installation
1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/cub3d.git
    cd cub3d
    ```
2. Compile the project:
    ```sh
    make
    ```
3. Run the game:
    ```sh
    ./cub3d test.cub
    ```

## Usage
- **W**: Move forward
- **S**: Move backward
- **A**: Strafe left
- **D**: Strafe right
- **Left Arrow**: Rotate view left
- **Right Arrow**: Rotate view right
- **ESC**: Quit the game
- **Mouse**: Rotate your view left and right with the mosue

## Map Configuration
The game levels are defined in `.cub` files. Here is a basic example:
   ```
    NO ./textures/wall_north.xpm
    SO ./textures/wall_south.xpm
    WE ./textures/wall_west.xpm
    EA ./textures/wall_east.xpm
    S ./textures/sprite.xpm
    F 220,100,0
    C 225,30,0

    1111111111111111111
    1000000000110000001
    1011000001110000001
    1001000000000000001
    1111111110110000011
    1000000000110000011
    1000000000000000011
    1000000111111111111
    1000000000000000001
    1111111111111111111
  ```
