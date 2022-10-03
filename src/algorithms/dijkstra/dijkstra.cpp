#include "dijkstra.h"

using std::find;
using std::reverse;

#include <unordered_map>
using std::unordered_map;

#include <queue>
using std::priority_queue;

#include <vector>
using std::vector;

#include <utility>
using std::pair;

Dijkstra::Dijkstra() { }

vector<int> Dijkstra::getPath() const {
    return shortestPath;
}

int Dijkstra::getLength() const {
    if (shortestPath.size() >= 2) {
        return shortestPath.size() - 1;
    }
    return 0;
}

int Dijkstra::getSumOfPath() const {
    return sumOfPath;
}

/* Private helper function object to compare pairs in the minHeap */
struct comparison {
    /** operator() overloaded such that we can compare pairs
        @param pair1 the first pair to be compared in the minHeap
        @param pair2 the second pair to be compared in the minHeap
        @return true if pair1's distance > pair2's distance, else false
    */
    bool operator()(const pair<int, int>& pair1, const pair<int, int>& pair2) {
        return pair1.second > pair2.second;
    }
};

void Dijkstra::solve(const Graph & graph, int startNode, int targetNode) {
    // Initialze and declare these instances in this function
    // because they should only be locally saved
    unordered_map<int, int> distance; // distance from startNode to its current node
    unordered_map<int, int> prev;
    vector<int> visited_vertices;
    priority_queue<pair<int, int>, vector<pair<int, int>>, comparison> minHeap;

    // Iterate through all the nodes && populate both hashmaps
    for (auto it = graph.begin(); it != graph.end(); it++) {
        distance[it->first] = inf;
        prev[it->first] = -1;
    }

    // The start node distance = 0 && has already been visited
    distance[startNode] = 0;
    visited_vertices.push_back(startNode);

    // Iterate through the neighbors of the start node && record data in respective hashmap
    list<Edge> incidentList(graph.incidentEdges(startNode));
    for (auto neighbor : incidentList) {
        distance[neighbor.dest_id] = neighbor.weight;
        prev[neighbor.dest_id] = startNode;

        pair<int, int> nextNode(neighbor.dest_id, neighbor.weight);
        minHeap.push(nextNode);
    }

    // Go through each node (if necessary) && use dijkstra's algorithm
    int totalNodes = graph.getNumNodes();
    for (int i = 0; i < totalNodes; ++i) {
        if (minHeap.size() == 0) {break;}
        pair<int, int> node = minHeap.top(); minHeap.pop();
        visited_vertices.push_back(node.first);
        
        list<Edge> list(graph.incidentEdges(node.first));
        for (auto neighbor : list) {
            // Check if the node has been visited
            if (find(visited_vertices.begin(), 
                    visited_vertices.end(), 
                    neighbor.dest_id) != visited_vertices.end()) {continue;}

            // Main part of dijsktra's algorithm
            // Calcualtes the shortest weighted path and updates hashmap
            int edgeWeight = neighbor.weight;
            if (distance[node.first] + edgeWeight < distance[neighbor.dest_id]) {
                distance[neighbor.dest_id] = distance[node.first] + edgeWeight;
                prev[neighbor.dest_id] = node.first;
            }

            pair<int, int> nextNode(neighbor.dest_id, distance[neighbor.dest_id]);
            minHeap.push(nextNode);
        }
    }

    // Record distance from start node to end node
    // Also, check if distance is inf
    if (distance[targetNode] == inf) {
        sumOfPath = 0;
    } else {
        sumOfPath = distance[targetNode];
    }

    // Clears path, backtracks shortest weighted path, and records it
    shortestPath.clear();
    int nodeID = targetNode;
    shortestPath.push_back(nodeID);

    while (prev.find(nodeID) != prev.end()) {
        nodeID = prev[nodeID];
        shortestPath.push_back(nodeID);
    }
    shortestPath.pop_back();
    
    // If there is <= 1 path length,
    // then there are no edges, meaning no path
    if (shortestPath.size() <= 1) {
        shortestPath.clear();
    } else {
        reverse(shortestPath.begin(), shortestPath.end());
    }
}