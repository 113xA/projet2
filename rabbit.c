#include <stdlib.h>
#include <limits.h> // Need for INT_MIN

#include "animal.h"
#include "grid.h"
#include "constants.h"
#include "position.h"
#include "action.h"

#include "rabbit.h"


struct Cell_Val_t
{
    Position position;
    int value;
};

Action rabbitFindAction(Animal *rabbit, Grid *grid, Position position)
{
    Action action;
    int k = 0;
    int scoreMax = INT_MIN;
    int row = position.row;
    int col = position.col;

    Position midCell = position;      //initialisation des différentes positions possibles
    Position leftCell = position;
    Position upperCell = position;
    Position underCell = position;
    Position rightCell = position;

    leftCell.col = col - 1;
    upperCell.row = row + 1;
    underCell.row = row - 1;
    rightCell.col = col + 1;


    Position tabPos[] = {midCell, leftCell, upperCell, underCell, rightCell};
    Cell_Val cell[5];
    Cell_Val chosenCells[5];
    Cell_Val finalCell;

    int nbCells = sizeof(cell) / sizeof(cell[0]);

    for (int i = 0, k = 0; i < 5; i++)  //vérification de la légitimié des cases
    {
        if(gridCellIsOutside(grid, tabPos[i]) == true)
        {
            continue;
        }

        cell[k].position = tabPos[i];
        k++;
    }

    for (int i = 0; i < nbCells; i++)        //attribution des scores
    {
        if(gridCellIsAnimal(grid, cell[i].position) == true)
        {
            cell[i].value = INT_MIN;
            continue;
        }

        int closestGrass = gridFindClosestGrass(grid, cell[i].position, rabbitMaxDistance);
        int closestWolf = gridFindClosestAnimal(grid, cell[i].position, rabbitMaxDistance, wolfName);
        int closestRabbit = gridFindClosestAnimal(grid, cell[i].position, rabbitMaxDistance, rabbitName);

        cell[i].value = -rabbitGrassWeight * closestGrass + rabbitWolfWeight * closestWolf;
    }

    for(int i = 0; i < nbCells; i++)    //détermination de la (des) case(s) avec le score maximal
    {
        int currentScore = cell[i].value;
        Position currentPosition = cell[i].position;

        if(currentScore > scoreMax)
        {
            chosenCells[k].value = currentScore;
            chosenCells[k].position = currentPosition;
            scoreMax = currentScore;
        }
        
        else if(currentScore == scoreMax)
        {
            k++;
            chosenCells[k].value = currentScore;
            chosenCells[k].position = currentPosition;
        }
    }

    if(k > 0)
    {
        int randomCell = rand() % (k + 1);
        finalCell.position = chosenCells[randomCell].position;
        finalCell.value = chosenCells[randomCell].value;
    }

    if(gridCellIsGrass(grid, finalCell.position) == true)
        action.eat = true;

    else if(gridCellIsGrass(grid, finalCell.position) == false)
        action.eat = false;

    action.move.drow = finalCell.position.row - position.row;
    action.move.dcol = finalCell.position.col - position.col;

    return action;
}

Animal *reproduceRabbit(Animal *rabbit)
{
    int rabbitEnergy = animalGetEnergy(rabbit);

    if(rabbitEnergy >= rabbitReproduceThreshold)
    {
        Animal *newRabbit;
        newRabbit = rabbitCreate();
        animalLoseEnergy(rabbit);
        return newRabbit;
    }

    else
        return NULL;
}

Animal *rabbitCreate(void)
{
    Animal *NewRabbit = animalCreate(rabbitName, rabbitPriority, rabbitInitEnergy, rabbitActionEnergy, rabbitEatEnergy, 
                                    rabbitFindAction, reproduceRabbit);

    return NewRabbit;
}
