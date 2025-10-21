#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "position.h"
#include "animal.h"

#include "grid.h"

struct Grid_t
{
    // Add the grid fiels here.
};

int gridGetWidth(Grid *grid)
{
    return 0;
}

int gridGetHeight(Grid *grid)
{
    return 0;
}

Grid *gridCreateEmpty(int height, int width)
{
    return NULL;
}

void gridFree(Grid *grid)
{
    return;
}

void gridAddGrass(Grid *grid, Position pos)
{
    return;
}

void gridAddAnimal(Grid *grid, Animal *animal, Position pos)
{
    return;
}

void gridMoveAnimal(Grid *grid, Position pos, Position new_pos)
{
    return;
}

void gridMakeEmpty(Grid *grid, Position pos)
{
    return;
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
