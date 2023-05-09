#include "raylib.h"
#include "stdlib.h"
#include <cstdio>
#include <iostream>

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

    std::vector<Cell *> links;

    int randValue;
    Cell(int row, int column)
    {
        this->randValue = rand() % 5;
    };
    Cell()
    {
        this->randValue = rand() % 5;
    };

    void print() { printf("%d\t", this->randValue); }

    void setRow(int row) { this->row = row; }
    void setColumn(int column) { this->column = column; }
    std::vector<Cell *> getNeighbors()
    {
        std::vector<Cell *> neighbors;
        if (this->north != nullptr)
            neighbors.push_back(this->north);
        if (this->south != nullptr)
            neighbors.push_back(this->south);
        if (this->west != nullptr)
            neighbors.push_back(this->west);
        if (this->east != nullptr)
            neighbors.push_back(this->east);

        return neighbors;
    }

    void link(Cell *cell, bool bidi = true)
    {
        links.push_back(cell);
        if (bidi)
        {
            cell->link(this, false);
        }
    }

    void unlink(Cell cell, bool bidi = true)
    {
        auto it = std::find_if(links.begin(), links.end(), [&cell](const Cell &obj)
                               { return obj == cell; });
        if (it != links.end())
        {
            auto index = std::distance(links.begin(), it);
            links.erase(index);
            if(bidi) {
                cell->unlink(this);
            }
        }

    }

    bool operator==(const Cell &cell) const
    {
        return row == cell.row and column == cell.column;
    }

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

                this->cells[i][j].north = this->getCell(i - 1, j);
                this->cells[i][j].south = this->getCell(i + 1, j);
                this->cells[i][j].east = this->getCell(i, j + 1);
                this->cells[i][j].west = this->getCell(i, j - 1);
            }
        }
    }

    Cell *getCell(int row, int col)
    {
        if (row > 0 && row < this->rows && columns > 0 && columns < this->columns)
        {
            return &this->cells[row][col];
        }
        return nullptr;
    }

    Cell *eachCell()
    {
        auto temp = new Cell[this->rows * this->columns];
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->columns; j++)
            {
                temp[i + 1 * j] = this->cells[i][j];
            }
        }

        return temp;
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

    int size()
    {
        return this->columns * this->rows;
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
