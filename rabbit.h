#ifndef RABBIT_H
#define RABBIT_H

#include "animal.h"


/**
 * @brief Opaque declaration of a cell with its value and its position.
 *
 */
typedef struct Cell_Val_t Cell_Val;

/**
 * @brief Create a rabbit.
 *
 * @return Animal*
 */
Animal *rabbitCreate(void);

#endif
