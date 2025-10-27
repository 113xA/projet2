#include <stdlib.h>
#include <limits.h> // Need for INT_MIN

#include "animal.h"
#include "grid.h"
#include "constants.h"
#include "position.h"
#include "action.h"

#include "rabbit.h"

Action rabbitFindAction(Animal *rabbit, Grid *grid, Position position)
{
    

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
