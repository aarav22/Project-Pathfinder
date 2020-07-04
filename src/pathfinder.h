#ifndef _pathfinder_h
#define _pathfinder_h

#include "basicgraph.h"
#include "set.h"
#include "vector.h"
#include "Color.h"

using Path = Vector<Vertex*>;

// The path-searching algorithms

Path dijkstrasAlgorithm(const BasicGraph& graph, Vertex* source, Vertex* target);
Path aStar(const BasicGraph& graph, Vertex* source, Vertex* target);

// The minimum spanning tree algorithm for random maze generation

Set<Edge*> kruskal(const BasicGraph& graph);

/*
 * Returns a 'heuristic' value, or rough estimation, of the distance between
 * this vertex and the given other vertex.
 * The heuristic function is guaranteed to be admissible.
 */

extern double heuristicFunction(Vertex* from, Vertex* to);

#endif

