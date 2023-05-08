#include "raylib.h"
#include "stdlib.h"
#include <cstdio>

class Cell
{
private:
    /* data */
public:
    int row;
    int column;
    Cell *north;
    Cell *east;
    Cell *south;
    Cell *west;

    int randValue;
    Cell(int row, int column);
    Cell();

    void setRow(int row) { this->row = row; }
    void setColumn(int column) { this->column = column; }
    ~Cell();
};

Cell::Cell()
{
    this->randValue = rand() % 100;
};

class Grid
{
private:
    /* data */
public:
    int rows;
    int columns;
    int cellSize;

    Cell **cells;
    Grid(int rows, int columns, int cellSize = 15)
    {
        this->rows = rows;
        this->columns = columns;
        this->cellSize = cellSize;

        this->cells = new Cell *[rows];

        for (int i = 0; i < rows; i++)
        {
            // need to initialize with col/row
            cells[i] = new Cell[columns];
            for (int j = 0; j < columns; j++)
            {
                Cell cell = cells[i][j];
                cell.setRow(i);
                cell.setColumn(j);

                // cell.north = this->cells[i - 1][j];
                // cell.south = this->cells[i + 1][j];
                // cell.east = this->cells[i][j + 1];
                // cell.west = this->cells[i][j - 1];
            }
        }
    }
    Grid();
    ~Grid();

    void print()
    {
        for (int i = 0; i < this->rows; i++)
        {
            // need to initialize with col/row
            for (int j = 0; j < this->columns; j++)
            {
                printf("%d\t", this->cells[i][j].randValue);
            }
        }
    };
};

int main()
{
    InitWindow(800, 600, "My First Program");

    Vector2 ballPosition = {400.0f, 300.0f};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // clears the screen
        ClearBackground(BLACK);

        // get the mouse position
        Vector2 mousePosition = GetMousePosition();

        ballPosition = mousePosition;

        DrawCircleV(ballPosition, 20.0f, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
