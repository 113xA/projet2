#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "constants.h"
#include "grid.h"
#include "position.h"
#include "action.h"

#include "simulation.h"

struct Simulation_t
{
    // Add the simulation fields here.
};

Simulation *simulationCreate(int height, int width)
{
    return NULL;
}

void simulationFree(Simulation *sim)
{
    return;
}

void simulationAddGrass(Simulation *sim, Position pos)
{
    return;
}

void simulationAddAnimal(Simulation *sim, Animal *animal, Position pos)
{
    return;
}

int simulationCountAnimals(Simulation *sim, char *name)
{
    return 0;
}

int simulationCountGrass(Simulation *sim)
{
    return 0;
}

void simulationStep(Simulation *sim)
{
    return;
}

Grid *simulationGetGrid(Simulation *sim)
{
    return NULL;
}
