#include <stdlib.h>
#include <limits.h> // Need for INT_MIN

#include "animal.h"
#include "grid.h"
#include "constants.h"
#include "position.h"
#include "action.h"

#include "wolf.h"

struct Cell_Val_t
{
    Position position;
    int value;
};

Action wolfFindAction (Animal *wolf, Grid *grid, Position position)
{
    Action action;
    int scoreMax = INT_MIN;
    int row = position.row;
    int col = position.col;
    int k = 0;

    Position tabPos[13];
    int r = 0;

    for(int currentRow = -2; currentRow <= 2; currentRow++)
    {
        for(int currentCol = -2; currentCol <= 2; currentCol++)
        {
            if(abs(currentRow) + abs(currentCol) <= 2)
            {
                tabPos[r].row = row + currentRow;
                tabPos[r].col = col + currentCol;
                r++;
            }
        }
    }

    Cell_Val cell[5];
    Cell_Val chosenCells[5];
    Cell_Val finalCell;
    int nbCells = 0;

    for (int i = 0; i < 13; i++)  //vérification de la légitimié des cases
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

        if(gridFindClosestAnimal(grid, cell[i].position, wolfMaxDistance, wolfName) == 0)
        {
            cell[i].value = INT_MIN;
            continue;
        }

        int closestRabbit = gridFindClosestAnimal(grid, cell[i].position, wolfMaxDistance, rabbitName);

        cell[i].value = -closestRabbit;
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

    if(!gridFindClosestAnimal(grid, finalCell.position, wolfMaxDistance, rabbitName))
    {
        action.eat = true;
    }

    else if(gridFindClosestAnimal(grid, finalCell.position, rabbitMaxDistance, rabbitName))
    {
        action.eat = false;
    }

    return action;
}

Animal *reproduceWolf(Animal *wolf)
{
    int wolfEnergy = animalGetEnergy(wolf);

    if(wolfEnergy >= wolfReproduceThreshold)
    {
        Animal *newWolf;
        newWolf = wolfCreate();
        animalLoseEnergy(wolf);
        return newWolf;
    }

    else
        return NULL;
}




Animal *wolfCreate(void)
{
    Animal *NewWolf = animalCreate(wolfName, wolfPriority, wolfInitEnergy, wolfActionEnergy, wolfEatEnergy, 
                                  wolfFindAction, reproduceWolf);
    return NewWolf;
}
