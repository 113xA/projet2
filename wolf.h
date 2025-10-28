#ifndef WOLF_H
#define WOLF_H

#include "animal.h"


/**
 * @brief Opaque declaration of a cell with its value and its position.
 *
 */
typedef struct Cell_Val_t Cell_Val;

/**
 * @brief Create a wolf.
 *
 * @return Animal*
 */
Animal *wolfCreate(void);

#endif
