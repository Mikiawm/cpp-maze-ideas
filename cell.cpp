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
    Cell(int row, int column)
    {
        this->randValue = rand() % 5;
    };
    Cell()
    {
        this->randValue = rand() % 5;
    };

    void setRow(int row) { this->row = row; }
    void setColumn(int column) { this->column = column; }
    ~Cell();
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
            this->cells[i] = new Cell[columns];
            for (int j = 0; j < columns; j++)
            {
                this->cells[i][j].setRow(i);
                this->cells[i][j].setColumn(i);

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
            printf("\n");
        }
    };
};

int main()
{
    // Cell * cell = new Cell;

    // printf("%d", cell->randValue);

    Grid *grid = new Grid(10, 10);

    grid->print();
}

Cell::~Cell()
{
    delete this;
}
