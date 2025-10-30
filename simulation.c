#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "constants.h"
#include "grid.h"
#include "position.h"
#include "action.h"

#include "simulation.h"

#include "wolf.h"
#include "rabbit.h"
#include "wolf.c"
#include "rabbit.c"

struct Simulation_t
{
    Grid *grid;
    int wolf_count;
    int rabbit_count;
    int grass_count;
    int step_count;
    int animal_count;
    Animal **animals;
};

Simulation *simulationCreate(int height, int width)
{
    Simulation *sim = malloc(sizeof(Simulation));
    if (!sim) return NULL;

    sim->grid = gridCreateEmpty(height, width);
    if (!sim->grid) {
        free(sim);
        return NULL;
    }

    sim->animal_count = 0;
    sim->grass_count = 0;
    sim->step_count = 0;

    return sim;
}

void simulationFree(Simulation *sim)
{
    gridFree(sim->grid);
    free(sim);
    return;
}

void simulationAddGrass(Simulation *sim, Position pos)
{
    if (gridCellIsOutside(sim->grid, pos)) {
        printf("Position is outside the grid, cannot add grass.\n");
        return;
    }

    if (gridIsEmpty(sim->grid, pos)) {
        gridSetGrass(sim->grid, pos);
        sim->grass_count++;
    }

    return;
}

void simulationAddAnimal(Simulation *sim, Animal *animal, Position pos)
{
        if (gridCellIsOutside(sim->grid, pos)) {
        printf("Position is outside the grid, cannot add animal.\n");
        return;
    }

    if (gridIsEmpty(sim->grid, pos)) {
        gridSetAnimal(sim->grid, pos, animal);
        if (animalIsWolf(animal)) {
            sim->wolf_count++;
        }
        else if (animalIsRabbit(animal)) {
            sim->rabbit_count++;
        }
    }

    return;
}

int simulationCountAnimals(Simulation *sim, char *name)
{
    if (strcmp(name, "wolf") == 0) {
        return sim->wolf_count;
    }
    else if (strcmp(name, "rabbit") == 0) {
        return sim->rabbit_count;
    }

    return 0;
}

int simulationCountGrass(Simulation *sim)
{
    return sim->grass_count;
}

void simulationStep(Simulation *sim)
{
    int max_priority;
    int animal_count = sim->animal_count;
    char first, second;

    if (rabbitPriority > wolfPriority) {
        max_priority = rabbitPriority;
        char first = rabbitName;
        char second = wolfName;
    }

    else if (rabbitPriority > wolfPriority){
        max_priority = wolfPriority;
        char first = wolfName;
        char second = rabbitName;
    }


    for (int p = 0; p <= max_priority; p++) {       // go trough all priorities
        
        if (!strcmp(first,wolfName)){
            wolf
            rabbit
        }

        if (!strcmp(first,rabbitName)){
            rabbit
            wolf
        }










    }

    
    return;
}

Grid *simulationGetGrid(Simulation *sim)
{
    return sim->grid;
}

