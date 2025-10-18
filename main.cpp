#include <iostream>
#include <conio.h>   // for _kbhit(), _getch() — works on Windows
#include <cstdlib>
#include <ctime>
#include <windows.h> // for Sleep()

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
// debug switch
#define DEBUG 1
// forward declaration so Setup() can call PlaceFruit()
void PlaceFruit();

void Setup() {
    srand(time(0));
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    // initialize tail and counters first (PlaceFruit uses nTail/tail arrays)
    score = 0;
    nTail = 0;
    for (int i = 0; i < 100; ++i) { tailX[i] = tailY[i] = -1; }
    // place first fruit avoiding the snake
    PlaceFruit();
}

// Place fruit at a location not occupied by the snake
void PlaceFruit() {
    bool ok = false;
    while (!ok) {
        ok = true;
        fruitX = rand() % width;
        fruitY = rand() % height;
        if (fruitX == x && fruitY == y) ok = false;
        for (int i = 0; i < nTail && ok; ++i) {
            if (tailX[i] == fruitX && tailY[i] == fruitY) ok = false;
        }
    }
#if DEBUG
    cerr << "[DEBUG] Placed fruit at (" << fruitX << "," << fruitY << ")\n";
#endif
}

void Draw() {
    system("cls"); // clear screen (use "clear" on Mac/Linux)
    // Top border
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#"; // left border
            if (i == y && j == x)
                cout << "O"; // snake head
            else if (i == fruitY && j == fruitX)
                cout << "F"; // fruit
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // tail piece
                        printTail = true;
                        break;
                    }
                }
                if (!printTail) cout << " ";
            }
            if (j == width - 1) cout << "#"; // right border
        }
        cout << endl;
    }

    // Bottom border
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        int ch = _getch();
        // arrow keys return 0 or 224 then the code
        if (ch == 0 || ch == 224) ch = _getch();
        switch (ch) {
        case 'a': case 'A': if (dir != RIGHT) dir = LEFT; break;
        case 'd': case 'D': if (dir != LEFT) dir = RIGHT; break;
        case 'w': case 'W': if (dir != DOWN) dir = UP; break;
        case 's': case 'S': if (dir != UP) dir = DOWN; break;
        case 75: if (dir != RIGHT) dir = LEFT; break;  // left arrow
        case 77: if (dir != LEFT) dir = RIGHT; break; // right arrow
        case 72: if (dir != DOWN) dir = UP; break;    // up arrow
        case 80: if (dir != UP) dir = DOWN; break;  // down arrow
        case 'x': case 'X': gameOver = true; break;
        }
    }
}

void Logic() {
    // move tail: each segment takes the place of the previous one
    int prevX = x;
    int prevY = y;
    int prev2X, prev2Y;
    for (int i = 0; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:  x--; break;
    case RIGHT: x++; break;
    case UP:    y--; break;
    case DOWN:  y++; break;
    default:    break;
    }

    // Wrap-around walls (optional — change if you want game over)
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // Check if fruit eaten
    if (x == fruitX && y == fruitY) {
        score += 10;
        if (nTail < 99) {
            nTail++;
        }
#if DEBUG
        cerr << "[DEBUG] Ate fruit at (" << x << "," << y << "), score=" << score << ", nTail=" << nTail << "\n";
#endif
        PlaceFruit();
    }

    // Check if snake hits itself
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
#if DEBUG
            cerr << "[DEBUG] Collision with tail at (" << x << "," << y << ") seg=" << i << "\n";
#endif
            break;
        }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // control speed
    }
    cout << "\nGame Over! Final Score: " << score << endl;
    return 0;
}
