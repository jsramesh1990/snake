
# Snake Game - Terminal Edition

A classic Snake game implemented in C using the **ncurses** library for Ubuntu 24 terminal. Control a snake, eat food, grow longer, and avoid collisions with walls and yourself.

## Features

- 🐍 **Smooth keyboard controls** with arrow keys
- 🎯 **Food collection** that increases score and snake length
- 🧱 **Wall collision detection** (game ends on boundary hit)
- 🔄 **Self-collision prevention** (can't run into yourself)
- 📊 **Real-time score display**
- ⚡ **Fixed game loop timing** (100ms per frame)
- ❌ **Quit option** (press 'q' to exit)

## Prerequisites

- **Ubuntu 24** (or any Linux distribution)
- **ncurses library** (terminal graphics library)
- **GCC compiler**

## Installation

### 1. Install ncurses library

```bash
sudo apt update
sudo apt install libncurses5-dev libncursesw5-dev
```

### 2. Create the source file

```bash
nano snake.c
```

Copy the complete C code from this repository into the file.

### 3. Compile the game

```bash
gcc snake.c -lncurses -o snake
```

For Unicode support (optional):
```bash
gcc snake.c -lncursesw -o snake
```

### 4. Run the game

```bash
./snake
```

## How to Play

### Objective
Control the snake to eat food (`*`) and grow longer. The game ends if you hit the walls or the snake's own body.

### Controls

| Key | Action |
|-----|--------|
| `←` (Left Arrow) | Move left |
| `→` (Right Arrow) | Move right |
| `↑` (Up Arrow) | Move up |
| `↓` (Down Arrow) | Move down |
| `q` | Quit game |

### Game Rules

1. Snake starts with length 5 in the middle of the screen
2. Head is represented by `O`, body by `o`
3. Food appears as `*` at random positions
4. Each food eaten:
   - Increases score by 10 points
   - Increases snake length by 1 segment
   - New food spawns at random location
5. **Collision conditions**:
   - Hitting walls (`#`) → Game Over
   - Hitting own body → Game Over

## Game Flow Example

```
########################################
#                                      #
#                                      #
#         ooO                          #
#                                      #
#                    *                 #
#                                      #
#                                      #
#                                      #
#                                      #
#                                      #
#                                      #
#                                      #
#                                      #
#                                      #
#                                      #
#                                      #
#                                      #
#                                      #
########################################
Score: 30
```

## Code Structure

| Component | Purpose |
|-----------|---------|
| `Segment` struct | Stores x,y coordinates of snake segments |
| `enum Direction` | Defines movement directions (STOP, LEFT, RIGHT, UP, DOWN) |
| `setup()` | Initializes ncurses, snake, food, and random seed |
| `draw()` | Renders walls, food, snake, and score |
| `input()` | Handles keyboard input and direction changes |
| `logic()` | Updates game state (movement, collisions, food eating) |
| `cleanup()` | Restores terminal settings |
| `main()` | Game loop controller |

### Key C Concepts Demonstrated

- **Structs** - Organizing snake segment coordinates
- **Arrays** - Storing snake body segments (`Segment snake[MAX_LENGTH]`)
- **Enums** - Direction state management
- **Pointers** - Implicit through array indexing
- **Loops** - Game loop, body movement, collision detection
- **Random number generation** - Food placement (`rand() % range`)
- **Timing** - Frame rate control (`usleep()`)
- **Terminal I/O** - ncurses library for raw terminal control

## Game Mechanics Explained

### Movement Logic

The snake moves by shifting all segments forward:
```c
for (int i = length - 1; i > 0; i--) {
    snake[i] = snake[i - 1];  // Each segment takes previous position
}
// Head moves independently based on direction
```

### Collision Detection

**Wall collision:**
```c
if (snake[0].x <= 0 || snake[0].x >= WIDTH - 1 ||
    snake[0].y <= 0 || snake[0].y >= HEIGHT - 1) {
    gameOver = 1;
}
```

**Self-collision:**
```c
for (int i = 1; i < length; i++) {
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
        gameOver = 1;
    }
}
```

### Food Eating
```c
if (snake[0].x == foodX && snake[0].y == foodY) {
    score += 10;
    if (length < MAX_LENGTH) length++;
    // Respawn food at random position
    foodX = rand() % (WIDTH - 2) + 1;
    foodY = rand() % (HEIGHT - 2) + 1;
}
```

## Customization Guide

### Change Game Speed

Modify the `usleep()` value in `main()`:
```c
usleep(100000);  // 100ms (slower = higher number)
usleep(50000);   // 50ms (faster)
usleep(200000);  // 200ms (slower)
```

### Change Game Area Size

Edit the constants:
```c
#define WIDTH 40   // Game width
#define HEIGHT 20  // Game height
```

### Change Starting Snake Length

```c
int length = 5;  // Change to desired starting length
```

### Change Score per Food

```c
score += 10;  // Change to any value
```

## Troubleshooting

| Issue | Solution |
|-------|----------|
| `fatal error: ncurses.h: No such file` | Install ncurses: `sudo apt install libncurses5-dev` |
| Arrow keys don't work | Use normal Ubuntu terminal (not VS Code terminal). Ensure `keypad(stdscr, TRUE)` is present |
| `usleep: command not found` | Include `<unistd.h>` header (already in code) |
| Game runs too fast/slow | Adjust `usleep()` value in main loop |
| Snake moves in opposite direction | Input validation prevents 180-degree turns (e.g., can't go left while moving right) |
| Terminal artifacts after exit | `endwin()` should restore terminal. If not, run `reset` command |
| Unicode characters not displaying | Compile with `-lncursesw` instead of `-lncurses` |

## Possible Enhancements

After mastering the basic version, try adding:

- ⚡ **Speed increase** - Gradually reduce delay as score increases
- 🎨 **Colors** - Use `start_color()` and `init_pair()` for colored snake/food
- ⏸️ **Pause functionality** - Press 'p' to pause/unpause
- 💾 **High score saving** - Persist best scores to a file
- 🧱 **Wrap-around walls** - Snake appears on opposite side
- 🍎 **Multiple food types** - Different points and effects
- 🤖 **AI snake mode** - Computer plays itself using pathfinding
- 🏆 **Levels** - Increasing difficulty with obstacles
- 📈 **Score multiplier** - Consecutive food bonuses
- 🔊 **Sound effects** - Terminal beep on food collection

## Advanced Enhancement Example: Speed Progression

Add to `logic()` function:
```c
// After eating food
static int speedCounter = 0;
speedCounter++;
if (speedCounter >= 5) {  // Every 5 foods
    int delay = 100000 - (score / 2);
    if (delay < 30000) delay = 30000;  // Minimum 30ms delay
    // Need to restructure game loop to use variable delay
}
```

## Building with Makefile

Create a `Makefile`:

```makefile
CC = gcc
CFLAGS = -Wall -O2
LIBS = -lncurses
TARGET = snake
SOURCES = snake.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

debug: $(SOURCES)
	$(CC) -g -o $(TARGET)-debug $(SOURCES) $(LIBS)
```

Usage:
```bash
make        # Compile
make run    # Compile and run
make clean  # Remove executable
make debug  # Build with debug symbols
```

## Learning Path Progression

After Snake, try these increasingly complex terminal games:

1. **Number Guessing** - Basic I/O, random numbers
2. **Tic-Tac-Toe** - 2D arrays, win condition logic
3. **Hangman** - Strings, file I/O, vectors
4. **Snake** (this project) - Real-time input, ncurses
5. **Tetris** - 2D arrays, rotation logic, scoring
6. **Pacman** - Pathfinding, ghosts AI, maze navigation
7. **Space Invaders** - Multiple entities, shooting mechanics

## Resources

- [ncurses Programming HOWTO](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/) - Comprehensive ncurses guide
- [C Reference](https://en.cppreference.com/w/c) - C standard library documentation
- [GCC Manual](https://gcc.gnu.org/onlinedocs/) - Compiler options

## License

Open source for educational purposes.

---

## Author

Created as a C programming and ncurses learning project for Ubuntu 24 terminal.

**Enjoy the game! 🐍🎮**
```

