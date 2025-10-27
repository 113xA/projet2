#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "position.h"
#include "animal.h"

#include "grid.h"

struct Cell_t
{
    Animal *animal;
    bool is_grass;
    bool is_animal;
    bool is_empty;
}; 

struct Grid_t
{
    int width;
    int height;
    Cell **matrix;
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
    if (!grid) return NULL;

    grid->width = width;
    grid->height = height;


    grid->matrix = malloc(sizeof(Cell *) * height); // allocate rows (pointers)
    if (!grid->matrix) {
        free(grid);
        return NULL;
    }
    
    for (int i = 0; i < height; i++)
    {

        grid->matrix[i] = malloc(width * sizeof(Cell)); // allocate columns (cells)

        if (!grid->matrix[i]) {
            for (int k = 0; k < i; k++) free(grid->matrix[k]);
            free(grid->matrix);
            free(grid);
            return NULL;
        }

        for (int j = 0; j < width; j++) 
        {
            grid->matrix[i][j].animal = NULL;
            grid->matrix[i][j].is_grass = false;
            grid->matrix[i][j].is_animal = false;
            grid->matrix[i][j].is_empty = true;
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

    if (!gridCellIsEmpty(grid, pos)) {
        printf("Cell (%d, %d) is not empty, cannot add grass.\n", width, height);
        return;
    }

    if (gridCellIsGrass(grid, pos)) {
        printf("Warning, cell (%d, %d) is already grass, continuing ...\n", width, height);
    }
    
        grid->matrix[height][width].is_grass = true;  
        grid->matrix[height][width].is_animal = false;
        grid->matrix[height][width].is_empty = false;
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
        printf("Cell (%d, %d) is already an animal, cannot add animal.\n", width, height);
        return;
    }

    if (gridCellIsEmpty(grid, pos)) {
        grid->matrix[height][width].animal = animal;
        grid->matrix[height][width].is_empty = false;
        grid->matrix[height][width].is_animal = true;
        grid->matrix[height][width].is_grass = false;
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

    grid->matrix[new_pos.row][new_pos.col].animal = grid->matrix[pos.row][pos.col].animal;
    grid->matrix[new_pos.row][new_pos.col].is_empty = false;
    grid->matrix[new_pos.row][new_pos.col].is_animal = true;
    grid->matrix[new_pos.row][new_pos.col].is_grass = false;

    animalDie(grid->matrix[pos.row][pos.col].animal); 
    grid->matrix[pos.row][pos.col].animal = NULL;
    grid->matrix[pos.row][pos.col].is_empty = true;
    grid->matrix[pos.row][pos.col].is_animal = false;
    grid->matrix[pos.row][pos.col].is_grass = false;
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
        animalDie(grid->matrix[pos.row][pos.col].animal);
        grid->matrix[pos.row][pos.col].animal = NULL;
        grid->matrix[pos.row][pos.col].is_animal = false;
        grid->matrix[pos.row][pos.col].is_grass = false;
        grid->matrix[pos.row][pos.col].is_empty = true;
        return
    }

    if (gridCellIsGrass(grid, pos)) {
        grid->matrix[pos.row][pos.col].is_grass = false;
        grid->matrix[pos.row][pos.col].is_animal = false;
        grid->matrix[pos.row][pos.col].is_empty = true;
        return
    }
}

bool gridCellIsOutside(Grid *grid, Position pos)
{
    if (pos.row >= 0 || pos.row < grid->height || pos.col >= 0 || pos.col < grid->width) {
        return false;
    }
    return true;
}

bool gridCellIsEmpty(Grid *grid, Position pos)
{
    if (gridCellIsOutside(grid, pos)) {
        printf("Position (%d, %d) is outside the grid, cannot check if empty.\n", pos.col, pos.row);
        return NULL;
    }

    if (grid->matrix[pos.row][pos.col].is_empty == false) {
        return false;
    }

    else {
        return true;
    }
}

bool gridCellIsGrass(Grid *grid, Position pos)
{
    if (gridCellIsOutside(grid, pos)) {
        printf("Position (%d, %d) is outside the grid, cannot check if grass.\n", pos.col, pos.row);
        return NULL;
    }

    if (grid->matrix[pos.row][pos.col].is_grass == true) {
        return true;
    }

    else {
        return false;
    }
}

bool gridCellIsAnimal(Grid *grid, Position pos)
{
    if (gridCellIsOutside(grid, pos)) {
        printf("Position (%d, %d) is outside the grid, cannot check if animal.\n", pos.col, pos.row);
        return NULL;
    }

    if (grid->matrix[pos.row][pos.col].is_animal == true) {
        return true;
    }

    else {
        return false;
    }
}

Animal *gridGetAnimal(Grid *grid, Position pos)
{
    if (gridCellIsOutside(grid, pos)) {
        printf("Position (%d, %d) is outside the grid, cannot get animal.\n", pos.col, pos.row);
        return NULL;
    }

    if (!gridCellIsAnimal(grid, pos)) {
        printf("Cell (%d, %d) does not contain an animal, cannot get animal.\n", pos.col, pos.row);
        return NULL;
    }

    else {
        return grid->matrix[pos.row][pos.col].animal;
    }
}

int gridFindClosestAnimal(Grid *grid, Position pos, int maxDistance, const char *name)  //in priority
{
    return maxDistance + 1;
}

int gridFindClosestGrass(Grid *grid, Position pos, int maxDistance)
{
    return maxDistance + 1;
}
