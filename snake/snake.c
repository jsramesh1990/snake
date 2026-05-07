#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 40
#define HEIGHT 20
#define MAX_LENGTH 100

typedef struct {
    int x;
    int y;
} Segment;

Segment snake[MAX_LENGTH];
int length = 5;

int foodX, foodY;

enum Direction {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum Direction dir;

int gameOver = 0;
int score = 0;

void setup() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    srand(time(0));

    dir = RIGHT;

    // Initial snake position
    for (int i = 0; i < length; i++) {
        snake[i].x = WIDTH / 2 - i;
        snake[i].y = HEIGHT / 2;
    }

    // Food position
    foodX = rand() % (WIDTH - 2) + 1;
    foodY = rand() % (HEIGHT - 2) + 1;
}

void draw() {
    clear();

    // Top wall
    for (int i = 0; i < WIDTH; i++) {
        mvprintw(0, i, "#");
    }

    // Bottom wall
    for (int i = 0; i < WIDTH; i++) {
        mvprintw(HEIGHT - 1, i, "#");
    }

    // Side walls
    for (int i = 0; i < HEIGHT; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, WIDTH - 1, "#");
    }

    // Draw food
    mvprintw(foodY, foodX, "*");

    // Draw snake head
    mvprintw(snake[0].y, snake[0].x, "O");

    // Draw snake body
    for (int i = 1; i < length; i++) {
        mvprintw(snake[i].y, snake[i].x, "o");
    }

    // Score
    mvprintw(HEIGHT, 0, "Score: %d", score);

    refresh();
}

void input() {
    int ch = getch();

    switch (ch) {
        case KEY_LEFT:
            if (dir != RIGHT)
                dir = LEFT;
            break;

        case KEY_RIGHT:
            if (dir != LEFT)
                dir = RIGHT;
            break;

        case KEY_UP:
            if (dir != DOWN)
                dir = UP;
            break;

        case KEY_DOWN:
            if (dir != UP)
                dir = DOWN;
            break;

        case 'q':
            gameOver = 1;
            break;
    }
}

void logic() {
    // Move body
    for (int i = length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    // Move head
    switch (dir) {
        case LEFT:
            snake[0].x--;
            break;

        case RIGHT:
            snake[0].x++;
            break;

        case UP:
            snake[0].y--;
            break;

        case DOWN:
            snake[0].y++;
            break;

        default:
            break;
    }

    // Collision with wall
    if (snake[0].x <= 0 || snake[0].x >= WIDTH - 1 ||
        snake[0].y <= 0 || snake[0].y >= HEIGHT - 1) {
        gameOver = 1;
    }

    // Collision with self
    for (int i = 1; i < length; i++) {
        if (snake[0].x == snake[i].x &&
            snake[0].y == snake[i].y) {
            gameOver = 1;
        }
    }

    // Eat food
    if (snake[0].x == foodX && snake[0].y == foodY) {
        score += 10;

        if (length < MAX_LENGTH)
            length++;

        foodX = rand() % (WIDTH - 2) + 1;
        foodY = rand() % (HEIGHT - 2) + 1;
    }
}

void cleanup() {
    endwin();
}

int main() {
    setup();

    while (!gameOver) {
        draw();
        input();
        logic();

        usleep(100000); // 100ms
    }

    cleanup();

    printf("Game Over!\n");
    printf("Final Score: %d\n", score);

    return 0;
}
