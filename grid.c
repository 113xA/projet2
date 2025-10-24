#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "position.h"
#include "animal.h"

#include "grid.h"

// struct cell ?

struct Grid_t
{
    int width;
    int height;
    char **matrix;
};

int gridGetWidth(Grid *grid)
{
    return grid->width;
}

int gridGetHeight(Grid *grid)
{
    return grid->height;
}

Grid *gridCreateEmpty(int height, int width)
{
    Grid *grid = malloc(sizeof(Grid));

    grid->width = width;
    grid->height = height;

    grid->matrix = malloc(sizeof(int *) * height);
    
    for (int i = 0; i < height; i++)
    {
        grid->matrix[i] = malloc(width * sizeof(char *));
        for (int j = 0; j < width; j++)
        {
            grid->matrix[i][j] = "Empty";
        }
    }

    return grid;
}

void gridFree(Grid *grid)
{
    for (int i = 0; i < grid->height; i++)
    {
        free(grid->matrix[i]);
    }
    free(grid->matrix);
    free(grid);
    return;
}

void gridAddGrass(Grid *grid, Position pos)
{
    unsigned width = pos.col;
    unsigned height = pos.row;

    if (gridCellIsOutside(grid, pos)) {
        printf("Position (%d, %d) is outside the grid, cannot add grass.\n", width, height);
        return;
    }

    if (gridCellIsGrass(grid, pos) || gridCellIsAnimal(grid, pos)) {
        printf("Cell (%d, %d) is not empty, cannot add grass.\n", width, height);
        return;
    }
    
    if (gridCellIsEmpty(grid, pos)) {
        grid->matrix[height][width] = "Grass";
    }    
}

void gridAddAnimal(Grid *grid, Animal *animal, Position pos)
{
    unsigned width = pos.col;
    unsigned height = pos.row;

    if (gridCellIsOutside(grid, pos)) {
        printf("Position (%d, %d) is outside the grid, cannot add animal.\n", width, height);
        return;
    }

    if (gridCellIsAnimal(grid, pos)) {
        printf("Cell (%d, %d) is not empty, cannot add animal.\n", width, height);
        return;
    }

    if (gridCellIsEmpty(grid, pos)) {
        animalGetName(animal);
        grid->matrix[height][width] = animalGetName(animal);
    }
}

void gridMoveAnimal(Grid *grid, Position pos, Position new_pos)
{
    if (gridCellIsOutside(grid, pos)) {
        printf("Original position (%d, %d) is outside the grid, cannot move animal.\n", pos.col, pos.row);
        return;
    }

    if (gridCellIsOutside(grid, new_pos)) {
        printf("New position (%d, %d) is outside the grid, cannot move animal.\n", new_pos.col, new_pos.row);
        return;
    }

    if (!gridCellIsAnimal(grid, pos)) {
        printf("Original cell (%d, %d) does not contain an animal, cannot move.\n", pos.col, pos.row);
        return;
    }

    if (gridCellIsAnimal(grid, new_pos)) {
        printf("New cell (%d, %d) already contains an animal, cannot move.\n", new_pos.col, new_pos.row);
        return;
    }

    grid->matrix[new_pos.row][new_pos.col] = grid->matrix[pos.row][pos.col];
    grid->matrix[pos.row][pos.col] = "Empty";       // Keep grass ?

    return;
}

void gridMakeEmpty(Grid *grid, Position pos)
{
    if (gridCellIsOutside(grid, pos)) {
        printf("Position (%d, %d) is outside the grid, cannot make empty.\n", pos.col, pos.row);
        return;
    }

    if (gridCellIsEmpty(grid, pos)) {
        printf("Warning, cell (%d, %d) is already empty, continuing ...\n", pos.col, pos.row);
    }

    if (gridCellIsAnimal(grid, pos)) {
        animalDie(gridGetAnimal(grid, pos));
    }

    grid->matrix[pos.row][pos.col] = "Empty";
}

bool gridCellIsOutside(Grid *grid, Position pos)
{
    
    return false;
}

bool gridCellIsEmpty(Grid *grid, Position pos)
{
    return true;
}

bool gridCellIsGrass(Grid *grid, Position pos)
{
    return false;
}

bool gridCellIsAnimal(Grid *grid, Position pos)
{
    return false;
}

Animal *gridGetAnimal(Grid *grid, Position pos)
{
    return NULL;
}

int gridFindClosestAnimal(Grid *grid, Position pos, int maxDistance, const char *name)
{
    return maxDistance + 1;
}

int gridFindClosestGrass(Grid *grid, Position pos, int maxDistance)
{
    return maxDistance + 1;
}
