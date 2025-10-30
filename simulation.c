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



// loop pour compter herbe ?



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

    int grid_width = gridGetWidth(sim->grid);
    int grid_height = gridGetHeight(sim->grid);

    int max_priority = 0;

    // make a table to know which animals have already played this turn
    bool **played = malloc(sizeof(bool *) * grid_height);
        for (int i = 0; i < grid_height; i++) {
            played[i] = malloc(sizeof(bool) * grid_width);
            for (int j = 0; j < grid_width; j++) {
                played[i][j] = false;
            }
        }

    // find max priority
    for (int row = 0; row < grid_height; row++) {
        for (int col = 0; col < grid_width; col++) {
            Position pos;
            pos.row = row;
            pos.col = col;

            if (gridCellIsAnimal(sim->grid, pos)) {
                Animal *animal = gridGetAnimal(sim->grid, pos);
                int priority = animalGetPriority(animal);
                if (priority > max_priority) {
                    max_priority = priority;
                }
            }
        }
    }

    for (int p = 0; p <= max_priority; p++) {     // go trough all priorities

        for (int row = 0; row < grid_height; row++) {
            for (int col = 0; col < grid_width; col++) {
                
                Position pos;

                pos.row = row;
                pos.col = col;

                if (gridCellIsAnimal(sim->grid, pos)) {
                    Animal *animal = gridGetAnimal(sim->grid, pos);
                        if (animalGetPriority(animal) == p && !played[row][col]) {

                            if (animalGetEnergy(animal) <= 0) {
                                gridMakeEmpty(sim->grid, pos);
                                break;
                            }

                            played[row][col] = true;

                            Action action = animalFindAction(animal, sim->grid, pos);

                            // lose energy for the turn
                            animalLoseEnergy(animal);

                            // move the animal
                            Position new_pos = {pos.row + action.move.drow, pos.col + action.move.dcol};
                            gridMoveAnimal(sim->grid, pos, new_pos);
                            gridMakeEmpty(sim->grid, pos); 

                            // eat if possible
                            if (action.eat) {
                                animalEat(animal);
                                gridMakeEmpty(sim->grid, new_pos);
                                if (gridCellIsGrass(sim->grid, new_pos)) {
                                    sim->grass_count -= 1;
                                }
                                if (animalIsRabbit(animal)) {
                                    sim->rabbit_count -= 1;
                                }
                            }

                            // reproduce if possible
                            Animal *baby_animal = animalCreateBaby(animal);
                            if (!animalReproduce(animal)==NULL) {;
                                simulationAddAnimal(sim, baby_animal, pos);
                                played[pos.row][pos.col] = true;    // baby has played this turn
                                animalLoseEnergy(animal);

                            }

                        }
                }

                if (gridCellIsGrass(sim->grid, pos)) {
                    int adjacent_grass = 0;

                    // check adjacent cells
                    for (int drow = -1; drow <= 1; drow++) {
                        for (int dcol = -1; dcol <= 1; dcol++) {
                            if (abs(drow) + abs(dcol) == 1) { // only orthogonal neighbors
                                Position neighbor_pos;
                                neighbor_pos.row = pos.row + drow;
                                neighbor_pos.col = pos.col + dcol;
                                if (gridCellIsGrass(sim->grid, neighbor_pos)) {
                                    adjacent_grass++;
                                }
                            }
                        }
                    }

                    double probability = grassProb + adjacent_grass * grassIncProb;
                    if ((double)rand() / RAND_MAX < probability) {
                        simulationAddGrass(sim, pos);
                    }
                }

            }

        }

    }

    for (int row = 0; row < grid_height; row++) {
        free(played[row]);
    }
    free(played);

    return;
}

Grid *simulationGetGrid(Simulation *sim)
{
    return sim->grid;
}

