#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define screen_width 55
#define screen_height 50

#define map_width 50
#define map_height 25
char map[screen_height][screen_width];

int score = 0;
int stop = 0;

typedef struct {

    float x;
    float y;
    float speed;
    int dx;
    int dy;
    int lenght;
    int direction;
    BOOL new_game;

} SNake;
SNake snake;



int count_coord = 0;
int array_coord_x[10000];
int array_coord_y[10000];


void init_snake()
{
    snake.x = (map_width - snake.lenght) / 2;
    snake.y = map_height / 2;
    snake.speed = 0.3;
    snake.lenght = 10;
    snake.direction = 1;
    snake.new_game = FALSE;
}

void put_snake()
{
    map[snake.dy][snake.dx] = 'x';
}

void move_snake(float x, float y)
{
    snake.x = x;
    snake.y = y;

    snake.dx = (int)round(snake.x);
    snake.dy = (int)round(snake.y);


    array_coord_x[count_coord] = snake.dx;
    array_coord_y[count_coord] = snake.dy;

    count_coord++;
}

void add_tail()
{
    for (int i = count_coord-1-snake.lenght; i < count_coord-3; i++)
        map[array_coord_y[i]][array_coord_x[i]] = 'o';
}

void eat_itself()
{

    for (int i = count_coord-2-snake.lenght; i < count_coord-6; i++)
    {
        if ((snake.dx == array_coord_x[i-1]) && (snake.dy == array_coord_y[i-1]))
            if (snake.direction != 5)
                snake.direction = 0;
    }

}

void border()
{
    if (snake.dx > map_width-2 || snake.dx < 1 || snake.dy > map_height-2 || snake.dy < 1)
    {
        if (snake.direction != 5)
            snake.direction = 0;
    }
}

void key_input()
{
    if (snake.direction != 0 && snake.direction != 5)
        if (GetKeyState(VK_LEFT) < 0)
            if (snake.direction != 2) snake.direction = 1;

    if (snake.direction != 0 && snake.direction != 5)
        if (GetKeyState(VK_RIGHT) < 0)
            if (snake.direction != 1) snake.direction = 2;

    if (snake.direction != 0 && snake.direction != 5)
        if (GetKeyState(VK_UP) < 0)
            if (snake.direction != 4) snake.direction = 3;

    if (snake.direction != 0 && snake.direction != 5)
        if (GetKeyState(VK_DOWN) < 0)
            if (snake.direction != 3) snake.direction = 4;
}

void logic_move(int x)
{
    if (x == 1) move_snake(snake.x-snake.speed, snake.y);

    if (x == 2) move_snake(snake.x+snake.speed, snake.y);

    if (x == 3) move_snake(snake.x, snake.y-snake.speed);

    if (x == 4) move_snake(snake.x, snake.y+snake.speed);

}

typedef struct {
    int x;
    int y;
} FOod;
FOod food;

void init_food()
{
    srand(time(NULL));
    food.x = 0;
    food.y = 0;
    food.x = rand() % 20;
    food.y = rand() % 20;
}


void eat_food()
{
    if (food.x > 46 || food.x < 1)
            food.x = rand() % 40;

    if (food.y > 22 || food.y < 1)
        food.y = rand() % 20;

    if (snake.dx == food.x && snake.dy == food.y)
    {
        food.x = 0;
        food.y = 0;

        food.x = rand() % 40;
        food.y = rand() % 20;


        snake.lenght += 5;
        score += 1;
        snake.speed += 0.01;
        if (snake.speed > 0.7);
            snake.speed = 0.3;
    }
}

void put_food()
{
    map[food.y][food.x] = '*';
}

void init_map()
{
    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            map[i][j] = '#';
        }
    }
    for (int i = 1; i < map_width-1; i++)
        for (int j = 1; j < map_height-1; j++)
            map[j][i] = ' ';
}

void show()
{
    int new_game = 2;
    int clear = 0;

    for (int i = 0; i < map_height; i++)
    {

        if (snake.direction == 0)
        {
            snake.new_game = TRUE;
            clear = 1;
            snake.direction = 5;
        }

        if (clear == 1)
        {
            system("cls");
            clear = 0;
        }

        if (!snake.new_game)
        {
            printf("%s", map[i]);
        }

        if (snake.new_game)
        {
            printf("\n\n\n\n\t\t\t         By Kipchak :)");
            printf("\n\n\n\n\n\t\t\t     You scored %d points", score);
            printf("\n\n\n\n\n\t\t      Do you want to start a new game? 0/1: ");
            scanf("%d", &new_game);

        }

        if (new_game == 1)
        {
            snake.lenght = 10;
            int x = (map_width - snake.lenght) / 2;
            int y = map_height / 2;
            memset(&array_coord_x, 0, 10000);
            memset(&array_coord_y, 0, 10000);
            count_coord = 0;
            move_snake(x, y);
            int rand_dir = 0;
            rand_dir = rand() % 5;
            if (rand_dir == 0) rand_dir = 1;
            if (rand_dir == 5) rand_dir = 4;
            snake.direction = rand_dir;
            snake.speed = 0.3;
            snake.new_game = FALSE;
            score = 0;
            new_game = 2;
            clear = 1;
        }

        if (new_game == 0)
        {
            snake.new_game = FALSE;
            system("cls");
            stop = 1;
        }

        if (new_game > 2 || new_game < 0)
        {
            snake.new_game = FALSE;
            system("cls");
            stop = 1;
        }

        if (clear == 1)
        {
            system("cls");
            clear = 0;
        }

        if (i == 5)
            printf("   score: %d", score);

        if (i == 15)
            printf("   Snake control <-- -->");

        if (i < map_height-1)
                printf("\n");

    }


}

void set_cursor(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main()
{

    init_snake();
    init_food();
    do
    {
        set_cursor(0, 0);
        init_map();

        put_food();

        add_tail();
        put_snake();
        key_input();
        logic_move(snake.direction);

        eat_food();
        eat_itself();

        border();


        show();
        Sleep(50);
    }
    while(stop != 1);

    return 0;
}
