#include "pathfinder.h"
#include "queue.h"
#include "pqueue.h"
#include <list>
#include <map>
#include <cmath>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include "Color.h"
#include "World.h"

using namespace std;

Path dijkstrasAlgorithm(const BasicGraph& graph, Vertex* source, Vertex* target) {
    PriorityQueue<Path> remaining;
    Set<Vertex*> visited;
    Path initial_path;

    initial_path.add(source);
    remaining.enqueue(initial_path, 0);

    while (!remaining.isEmpty()) {
        double curr_cost = remaining.peekPriority();
        Path curr_path = remaining.dequeue();
        Vertex* curr_vertex = curr_path[curr_path.size() - 1];

        visited.add(curr_vertex);
        curr_vertex->setColor(GREEN);
        if(curr_vertex == target) {
            return curr_path;
        }

        for (Vertex* successor : graph.getNeighbors(curr_vertex)) {
            Edge* next_edge = graph.getEdge(curr_vertex, successor);
            if(!visited.contains(successor)) {
                successor->setColor(YELLOW);
                Path new_path = curr_path;
                new_path.add(successor);

                double future_cost = next_edge->cost + curr_cost;
                remaining.enqueue(new_path, future_cost);
            }
        }
    }
    Path noPath;
    return noPath;
}

Path aStar(const BasicGraph& graph, Vertex* source, Vertex* target) {
    Set<Vertex*> visited;
    PriorityQueue<Path> remaining_path;
    Path initial_path;
    initial_path.add(source);
    remaining_path.enqueue(initial_path, heuristicFunction(source, target));

    while (!remaining_path.isEmpty()) {
        double cost_currVertex = remaining_path.peekPriority();
        Path curr_path = remaining_path.dequeue();
        Vertex* curr_vertex = curr_path[curr_path.size() - 1];

        visited.add(curr_vertex);
        curr_vertex->setColor(GREEN);
        if (curr_vertex == target) {
            return curr_path;
        }

        for (Vertex* successor: graph.getNeighbors(curr_vertex)) {
            if (!visited.contains(successor)) {
                successor->setColor(YELLOW);
                Edge* curr_edge = graph.getEdge(curr_vertex, successor);
                double new_cost = cost_currVertex + curr_edge->cost +
                        heuristicFunction(successor, target);
                Path new_path = curr_path;
                new_path.add(successor);
                remaining_path.enqueue(new_path, new_cost);
            }

        }
    }
    Path emptyPath;
    return emptyPath;
}



Vertex* find_parent(Vertex* vertex_inQuestion, unordered_map<Vertex*, Vertex*> &parents) {
    if (vertex_inQuestion != parents[vertex_inQuestion]) {
        parents[vertex_inQuestion] = find_parent(parents[vertex_inQuestion], parents);
    }
    return parents[vertex_inQuestion];
}

void union_by_ranks(Vertex* source, Vertex* destination, unordered_map<Vertex*,
                            Vertex*> &parents, unordered_map<Vertex*, int> &ranks) {

    Vertex* parent_source = find_parent(source, parents);
    Vertex* parent_destination = find_parent(destination, parents);

    if (ranks[parent_source] < ranks[parent_destination]) {
        parents[parent_source] = parent_destination;
    } else if (ranks[parent_source] > ranks[parent_destination]) {
        parents[parent_destination] = parent_source;
    } else {
        parents[parent_destination] = parent_source;
        ranks[parent_source]++;
    }
}

Set<Edge*> kruskal(const BasicGraph& graph) {
    Set<Edge*> mst_edges;
    Set<Edge*> graph_edges;
    Set<Vertex*> graph_vertices;
    PriorityQueue<Edge*> edge_queue;

    unordered_map<Vertex*, Vertex*> parents;
    unordered_map<Vertex*, int> ranks;
    int vertex_count = graph.size();

    graph_edges = graph.getEdgeSet();
    graph_vertices = graph.getVertexSet();


    for (auto edge = graph_edges.begin(); edge != graph_edges.end(); ++edge) {
        edge_queue.enqueue(*edge, (*edge)->cost);
    }

    for (auto vertex = graph_vertices.begin(); vertex != graph_vertices.end();
                ++vertex) {

        parents[*vertex] = *vertex;
        ranks[*vertex] = 0;
    }

    int index = 0;
    while (index < vertex_count - 1) {
        Edge* curr_edge = edge_queue.dequeue();
        Vertex* source = find_parent(curr_edge->start, parents);
        Vertex* destination = find_parent(curr_edge->end, parents);
        if (source != destination) {
            mst_edges.add(curr_edge);
            union_by_ranks(source, destination, parents, ranks);
            index++;
        }
    }
    return mst_edges;
}


