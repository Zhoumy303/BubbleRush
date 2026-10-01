# Deep Sea Bubble Rush

> A Global Game Jam 2025 entry — a 2D mini-game about a clownfish finding its way home through dark, winding deep-sea tunnels.

<img width="967" height="545" alt="image" src="https://github.com/user-attachments/assets/86bc414d-d2c4-40dc-8767-04a9b87fdabf" />

## Game Overview

Deep Sea Bubble Rush is a 2D deep-sea adventure mini-game developed in C++ with the EGE graphics library. Players control a clownfish swept into the deep sea by a storm, collecting bubbles, breaking through obstacles, and avoiding dangerous schools of fish in dark tunnels to finally return to safe waters.

The game blends adventure, puzzle-solving, and hidden elements: bright coral is the key to opening hidden areas; bubbles serve both as a resource for the dash skill and as the key to breaking obstacles; the deeper the water, the darker the color and the higher the difficulty.

<img width="967" height="540" alt="image" src="https://github.com/user-attachments/assets/02c28686-6017-4d08-840e-03355b19941b" />

## Project Structure

```
gam jam/
├── src/                # Source code
│   ├── bubble.cpp      # Main game program
│   └── map_editor.cpp  # Map editor (originally Map Editor.cpp)
├── assets/             # Runtime game assets (images have been renamed to lowercase filenames)
├── data/               # Level data
│   ├── map1.save       # Collision data for the first map
│   └── game.txt        # Collision data for expanded/hidden areas
├── docs/               # Documentation and backup assets
│   ├── screenshots/    # Screenshots/assets from development
│   ├── unused_assets/  # Unused art assets
│   └── snippets.cpp    # Code snippets/backup code library (originally Code Library.cpp)
├── build/              # Build output (added to .gitignore)
└── README.md
```

## Controls

### In-game (`bubble.cpp`)

| Key | Function |
|------|------|
| `Space` | Swim forward |
| `Shift` + `Space` | Swim faster |
| `F` | Turn left |
| `J` | Turn right |
| `E` | Consume one bubble to dash / break obstacles |
| `Q` | Collect nearby bubbles / trigger hidden bottles |
| `R` | Return to checkpoint and restart |

- Swimming into a whirlpool will pull you in and deal damage.
- Getting close to dangerous fish reduces health; after taking damage, you have brief invincibility.
- Dashing into a "door" can open it; some hidden areas require using a dash at a specific location or collecting bottles to unlock.

### Map Editor (`map_editor.cpp`)

| Key | Function |
|------|------|
| Right mouse button | Toggle drawing mode: walkable / non-walkable / trap |
| Left mouse button | Draw terrain (range mode / single-cell mode) |
| `O` | Switch to range mode |
| `P` | Switch to single-cell mode |
| `U` | Save the current map to `data/game.txt` |
| `I` | Import a map from `data/game.txt` |

When the editor starts, it asks for the map width and height and loads `assets/map2.png` as the background image.

## Build and Run

### Requirements

- Windows OS
- A C++ compiler (MinGW-w64 or MSVC recommended)
- [EGE (Easy Graphics Engine)](https://xege.org/) graphics library

### Compilation Example (MinGW)

```bash
cd src
g++ -o ../build/bubble.exe bubble.cpp -lgraphics -lgdi32 -lwinmm -static-libgcc -static-libstdc++
```

> Note: The exact linker parameters depend on how EGE is installed. If using Visual Studio, create a new empty project and add `bubble.cpp`, configure the EGE header and library paths, then compile.

### Running

After compilation, run from the project root directory:

```bash
./build/bubble.exe
```

> The program loads images from `assets/` and maps from `data/`, so it must be run from the project root directory to ensure the relative paths are correct.

## Level Design

- **Level 1**: Bright shallow-sea reefs; get familiar with controls and basic collection.
- **Level 2**: Deeper blue waters; hidden obstacles and more complex tunnels begin to appear.
- **Level 3**: The darkest deep-sea maze; you need to carefully manage bubble resources to complete it.

## Art and Assets

- The pixel art was hand-drawn in Procreate and exported as transparent PNG assets.
- Game assets now use lowercase filenames, and case references in the source code have been corrected to avoid missing files after cloning on case-sensitive systems such as Linux/macOS.

## Developer Notes

- `src/bubble.cpp` is the main game and can be compiled directly.
- `src/map_editor.cpp` is the internal map editor used to generate `data/game.txt`.
- `docs/snippets.cpp` contains code snippets/drafts kept from previous projects; it is not required to run this game.
- The `build/` directory is used for build output; it is included in `.gitignore` by default and will not be committed to GitHub.

## Acknowledgments

A Global Game Jam 2025 entry. Thanks to my teammates for their joint efforts in planning, art, programming, and level design.
