#ifndef CONSTANTS_H
#define CONSTANTS_H

// The names of the animals
const char *rabbitName;
const char *wolfName;

// The priorities of the animals, the lower the faster.
const unsigned int wolfPriority;
const unsigned int rabbitPriority;

// The maximum distances the animals can see. Used when computing the scores.
const int rabbitMaxDistance;
const int wolfMaxDistance;

// Energy parameters related to the rabbit.

// Energy when created.
const int rabbitInitEnergy;
// Energy consumed when an action is performed.
const int rabbitActionEnergy;
// Energy gained when grass is eated.
const int rabbitEatEnergy;
// Energy lost when the rabbit reproduces.
const int rabbitReproduceEnergy;
// Energy threshold required for reproduction.
const int rabbitReproduceThreshold;

// Energy parameters related to the wolf.

// Energy when created.
const int wolfInitEnergy;
// Energy consumed when an action is performed.
const int wolfActionEnergy;
// Energy gained when grass is eated.
const int wolfEatEnergy;
// Energy lost when the wolf reproduces.
const int wolfReproduceEnergy;
// Energy threshold required for reproduction.
const int wolfReproduceThreshold;

// Weights used when computing the score of the rabbit.
const int rabbitGrassWeight;
const int rabbitWolfWeight;

// Probabilites used when making appear grass.
// The probability that some grass will appear on an empty cell is:
// P = grassProb + N * grassIncProb, where N is the number of adjacent cells with grass
// (0 <= N <= 4)
const double grassProb;
const double grassIncProb;

#endif
