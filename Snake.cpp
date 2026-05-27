/* Snake Game using C++
developed by TheKittyKat,
improved by Nazim Nazari
December 2017 */

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

void run();
void printMap();
void initMap();
void move(int dx, int dy);
void update();
void changeDirection(char key);
void clearScreen();
void generateFood();
int kbhit();
int getch();

char getMapValue(int value);

// Map dimensions
constexpr int mapwidth = 20;
constexpr int mapheight = 20;
constexpr int size = mapwidth * mapheight;

// Snake head details
int headxpos;
int headypos;
int direction;

// Amount of food the snake has (How long the body is)
int food = 4;

// Determine if game is running
bool running;

int main()
{
    run();
    return 0;
}

// Main game function
void run()
{
    // Initialize the map
    initMap();
    running = true;
    while (running)
    {
        // If a key is pressed
        if (kbhit())
        {
            // Change to direction determined by key pressed
            changeDirection(getch());
        }
        // Update the map
        update();

        // Clear the screen
        clearScreen();

        // Print the map
        printMap();

        // delay 0.4 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    // Game Text
    cout << "\t\tGame Over!" << endl
         << "\t\tYour score is: " << food;

    // Stop console from closing instantly
    cin.ignore();
}

// Changes snake direction from input
void changeDirection(char key)
{
    /*
      W
    A + D
      S
      1
    4 + 2
      3
    */
    switch (key)
    {
    case 'w':
        if (direction != 2)
            direction = 0;
        break;
    case 'd':
        if (direction != 3)
            direction = 1;
        break;
    case 's':
        if (direction != 4)
            direction = 2;
        break;
    case 'a':
        if (direction != 5)
            direction = 3;
        break;
    }
}

// Moves snake head to new location
void move(int dx, int dy)
{
    // determine new head position
    int newx = headxpos + dx;
    int newy = headypos + dy;

    // Check if there is food at location
    if (map[newx + newy * mapwidth] == -2)
    {
        // Increase food value (body length)
        food++;

        // Generate new food on map
        generateFood();
    }

    // Check location is free
    else if (map[newx + newy * mapwidth] != 0)
    {
        running = false;
    }

    // Move head to new location
    headxpos = newx;
    headypos = newy;
    map[headxpos + headypos * mapwidth] = food + 1;
}

// Clears screen
void clearScreen()
{
    // Clear the screen
    system("cls");
}

// Generates new food on map
void generateFood()
{
    int x = 0;
    int y = 0;
    do
    {
        // Generate random x and y values within the map
        x = rand() % (mapwidth - 2) + 1;
        y = rand() % (mapheight - 2) + 1;

        // If location is not free try again
    } while (map[x + y * mapwidth] != 0);

    // Place new food
    map[x + y * mapwidth] = -2;
}

int kbhit()
{
    struct termios oldt, newt;
    int oldf;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int getch()
{
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// Updates the map
void update()
{
    // Move in direction indicated
    switch (direction)
    {
    case 0:
        move(-1, 0);
        break;
    case 1:
        move(0, 1);
        break;
    case 2:
        move(1, 0);
        break;
    case 3:
        move(0, -1);
        break;
    }
}
std::vector<int> map(mapwidth *mapheight);
// Initializes map
void initMap()
{
    // Places the initual head location in middle of map
    headxpos = mapwidth / 2;
    headypos = mapheight / 2;
    map[headxpos + headypos * mapwidth] = 1;

    // Places top and bottom walls
    for (int x = 0; x < mapwidth; ++x)
    {
        map[x] = -1;
        map[x + (mapheight - 1) * mapwidth] = -1;
    }

    // Places left and right walls
    for (int y = 0; y < mapheight; y++)
    {
        map[0 + y * mapwidth] = -1;
        map[(mapwidth - 1) + y * mapwidth] = -1;
    }

    // Generates first food
    generateFood();
}

// Prints the map to console
void printMap()
{
    for (int x = 0; x < mapwidth; ++x)
    {
        for (int y = 0; y < mapheight; ++y)
        {
            // Prints the value at current x,y location
            cout << getMapValue(map[x + y * mapwidth]);
        }
        // Ends the line for next x value
        cout << endl;
    }
}

// Returns graphical character for display from map value
char getMapValue(int value)
{
    // Returns a part of snake body
    if (value > 0)
        return 'o';

    switch (value)
    {
        // Return wall
    case -1:
        return 'X';
        // Return food
    case -2:
        return 'O';
    }
}