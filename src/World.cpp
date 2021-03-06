#include "World.h"

static World* currentWorld = nullptr;

void setCurrentWorld(World* world) {
    currentWorld = world;
}

/*
 * Returns a 'heuristic' value, or rough estimation, of the distance between
 * this vertex and the given other vertex.
 * The heuristic function is guaranteed to be an 'admissible heuristic',
 * meaning that it is never an overestimation of the distance.
 * (The word 'extern' means this function is defined elsewhere.
 *  You do not need to worry about it.)
 */
double heuristicFunction(Vertex* from, Vertex* to) {
    if (!currentWorld) {
        return 0.0;
    } else {
        return currentWorld->heuristic(from, to);
    }
}
