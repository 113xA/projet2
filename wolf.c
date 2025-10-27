#include <stdlib.h>
#include <limits.h> // Need for INT_MIN

#include "animal.h"
#include "grid.h"
#include "constants.h"
#include "position.h"
#include "action.h"

#include "wolf.h"

Action wolfFindAction (Animal *wolf, Grid *grid, Position position)
{

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
