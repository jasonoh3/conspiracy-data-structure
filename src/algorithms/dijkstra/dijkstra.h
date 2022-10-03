#pragma once

#include "../../graph/graph.h"
using Node = Graph::Node;
using Edge = Graph::Edge;

#include <limits>
using std::numeric_limits;

/* A shortest weighted path solver using Dijkstra's algorithm */
class Dijkstra {
    public:
        /* Default constructor */
        Dijkstra();
        
        /** Getter for the shortest weighted path
            @return the shortest path
        */
        vector<int> getPath() const;

        /** Getter for the length of the shortest weighted path
            @return the length of the path
        */
        int getLength() const;

        /** Getter for the sum of the shortest weight path
            @return sum of the weight path 
        */
        int getSumOfPath() const;

        /** The actual solver for dijkstra's algorithm
            @param graph the subgraph to use the algorithm on
            @param startNode the initial node for the algorithm to start on
            @param targetNode the end node we are trying to make a path to
            @return the shortest weighted path from startNode to targetNode
        */
        void solve(const Graph & graph, int startNode, int targetNode);

    private:
        int inf = numeric_limits<int>::max();
        vector<int> shortestPath;
        int sumOfPath = 0;
};
