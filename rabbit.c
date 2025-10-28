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
    int scoreMax = INT_MIN;
    int row = position.row;
    int col = position.col;
    int k = 0;

    Position tabPos[5];
    int i = 0;

    for(int currentRow = -1; currentRow <= 1; currentRow++)
    {
        for(int currentCol = -1; currentCol <= 1; currentCol++)
        {
            if(abs(currentRow) + abs(currentCol) <= 1)
            {
                tabPos[i].row = row + currentRow;
                tabPos[i].col = col + currentCol;
                i++;
            }
        }
    }

    Cell_Val cell[5];
    Cell_Val chosenCells[5];
    Cell_Val finalCell;
    int nbCells = 0;

    for (int i = 0; i < 5; i++)  //vérification de la légitimié des cases
    {
        if(gridCellIsOutside(grid, tabPos[i]) == true)
        {
            continue;
        }

        cell[nbCells].position = tabPos[i];
        nbCells++;
    }

    for (int i = 0; i < nbCells; i++)        //attribution des scores
    {
        int currentRow = cell[i].position.row;
        int currentCol = cell[i].position.col;

        if(gridCellIsAnimal(grid, cell[i].position) == true && currentCol != col && currentRow != row)
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

            if(k)
            {
                for(int j = 0; j <= k; j++)
                {
                    chosenCells[j].value = currentScore;
                    chosenCells[j].position = currentPosition;
                }
            }
            continue;
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
