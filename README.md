# DOOM: RETRO 3D ENGINE (BONUS EDITION)
---

## 📖 ABOUT THE PROJECT

A custom **first-person 3D game engine** built from scratch in C, heavily inspired by id Software's legendary **DOOM (1993)** and **Wolfenstein 3D**.

This engine uses **Digital Differential Analysis (DDA) Raycasting** to transform a 2D map matrix into a fully interactive 3D environment with real-time lighting simulation, texture mapping, mouse camera controls, dynamic minimap, and animated proximity doors.

---

## 💥 KEY ENGINE FEATURES

### 🚪 Animated Proximity Doors
- **State-Driven Animation:** Doors slice open and close smoothly across state frames instead of popping instantly.
- **Radial Proximity Interaction:** Door triggers utilize **Euclidean Distance** calculations $\left(\sqrt{\Delta x^2 + \Delta y^2}\right)$, allowing players to activate doors from any angle when close enough.

### 🖱️ Free-Look Mouse Control
- Native X11 event trapping (`MotionNotify`) for fluid, zero-latency 360° horizontal camera panning via mouse movement.

### 🗺️ Dynamic Tactical Minimap
- Real-time 2D HUD overlay displaying map layout, player coordinates, directional vector, and active door states.

### 🧱 Advanced Texture & Environment Rendering
- Wall texture mapping (N, S, E, W faces).
- Floor and ceiling color rendering.
- Axis-aligned box collision detection to prevent wall-clipping and smooth sliding.

---

## 🛠️ ARCHITECTURE & REPOSITORY STRUCTURE

```text
DOOM_GAME/
├── BONUS/
│   ├── includes/       # Engine headers & structures
│   ├── srcs/           # Raycasting core, doors, mouse & events
│   ├── gnl/            # Stream reading utility
│   ├── libft/          # Core C library
│   ├── maps/           # Campaign & stress-test map files
│   └── maps_01/        # Additional level layouts
├── textures/           # Wall assets & animated door sprites
├── minilibx-linux/     # MiniLibX graphical library
├── Makefile            # Project build system
└── README.md           # Engine documentation
```

---

## ⚡ QUICK START & COMPILATION

### System Prerequisites

- **OS:** Linux
- **Compiler:** `gcc` or `clang`
- **Build System:** `make`
- **Graphics Support:** X11 development libraries (`libXext-dev`, `libX11-dev`)

### Installation & Build

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/equintas/DOOM_GAME.git](https://github.com/equintas/DOOM_GAME.git)
   cd DOOM_GAME
   ```

2. **Compile the engine (Bonus Build):**
   ```bash
   make bonus
   ```

3. **Useful Makefile Commands:**
   ```bash
   make bonus   # Compiles the executable
   make clean   # Removes object files (.o)
   make fclean  # Removes objects and binaries
   make re      # Rebuilds the entire project from scratch
   ```

### Execution

```bash
./cub3D_bonus BONUS/maps/bonus_map.cub
```

---

## 🎮 CONTROLS & GAMEPLAY

```text
       [W] - Move Forward
 [A] - Strafe Left    [S] - Move Backward    [D] - Strafe Right

 [Mouse Left / Right]  -  Rotate Camera
 [←] / [→]             -  Rotate Camera (Keyboard)
 [E] / [F] / [Space]   -  Interact with Doors
 [ESC]                 -  Exit Engine
```

---

## 📐 LEVEL DESIGN & MAP SPECIFICATION (`.cub`)

Maps are defined via `.cub` files containing texture paths, color codes, and a grid boundary surrounded by walls (`1`).

### Entity Index

| Symbol | Description | Walkable |
| :---: | :--- | :---: |
| `0` | Open floor space | Yes |
| `1` | Solid wall | No |
| `D` | Closed Door (Interactive) | No (Unlocks when open) |
| `O` | Opened Door | Yes |
| `N` / `S` / `E` / `W` | Player Spawn Point & Initial Orientation | Yes |

### Example Level Layout (`bonus_map.cub`)

```text
NO textures/north.xpm
SO textures/south.xpm
WE textures/west.xpm
EA textures/east.xpm

F 40,40,40
C 100,20,20

11111111111111
10000001000001
1001110D111001
10010000001001
100100N0001001
10011111111001
10000000000001
11111111111111
```

---

## 🔬 TECHNICAL ENGINE HIGHLIGHTS

### 1. DDA Raycasting Engine
Performs incremental grid stepping per vertical screen column, eliminating expensive floating-point trigonometric calls during runtime rendering.

### 2. Perpendicular Distance Calculation
Prevents the **fisheye distortion effect** by projecting wall collision distances back onto the player's camera plane rather than calculating Euclidean distance to the camera origin:

$$\text{perp\_wall\_dist} = \text{side\_dist}_x - \text{delta\_dist}_x$$

### 3. Proximity Door Trigger
Distance threshold checking ensures doors only open when the player is within $1.2$ units of the door tile center:

$$\text{distance} = \sqrt{(P_x - (D_x + 0.5))^2 + (P_y - (D_y + 0.5))^2}$$

---
