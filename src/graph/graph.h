#pragma once

#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>

using std::string;
using std::list;
using std::unordered_map;
using std::vector;

/* A class representing a graph as an adjacency list */
class Graph {
    public:
        /* A struct representing a weighted edge */
        struct Edge {
            const int source_id;
            const int dest_id;
            const int weight;
            Edge() : source_id(0), dest_id(0), weight(0) { }
            Edge(int start, int end, int w) : 
							source_id(start), dest_id(end), weight(w) { }
        };

        /* A struct representing a graph node, contains 
        the retweet time and the adjacency list of the node */
        struct Node {
            const int id;
            const int time;
            // all outgoing edges
            list<Edge> adjacency_list;
            Node() : id(0), time(0) { }
            Node(int nid, int ntime) : id(nid), time(ntime) { }
        };

        /* Default constructor */
        Graph();

        /** Constructs a graph from an node and edge list file
            @param node_file the csv file name of the node list and associated data
            @param edge_file the txt file name of the edge list (source id -> dest id)
        */
        Graph(const string & node_file, const string & edge_file);

        /** Inserts and edge into the adjacency list, 
            both nodes must already exist in the graph
            @param source_id the node id the edge leaves
            @param dest_id the node id the edge enters
            @param weight the weight of the edge
        */
        void insertEdge(int source_id, int dest_id, int weight);

        /** Inserts a vertex into the adjacency list
            @param id the unique id of the node
            @param time the time after the initial retweet
        */
        void insertVertex(int id, int time);

        /** Getter for the number of edges 
            @return the number of edges in the graph 
            (edge in both directions counts as two)
        */
        int getNumEdges() const;

        /** Getter for the number of nodes in the graph
            @return the number of nodes
        */
        int getNumNodes() const;

        /** Getter for the initial tweet of the subgraph 
            @return the node id of the initial tweet of the subgraph 
        */
        int getSourceID() const;

        /** Getter for the retweet time of specified node id
            @param id the node id
            @return the retweet time
        */
        int getTime(int id) const;

        /** Getter for the incident edges of specified node
            @param id the node id
            @return a list of edges coming out of the node
        */
        list<Edge> incidentEdges(int id) const;

        /** Getter for the node with the greatest retweet time
            @return the node id with the greatest retweet time
        */
        int getGreatestNode() const;

         /* Const iterators for iterating over all nodes in the graph */
		unordered_map<int, Node>::const_iterator begin() const;
		unordered_map<int, Node>::const_iterator end() const;
        
        /** Getter for the transpose of the graph (all edges reversed)
            @return a pointer to the graph transpose
        */
        Graph* getTranspose() const;

    private:
        // number of nodes
        int n = 0;
        // number of edges
        // 2 edges counted if edge goes in both directions
        int m = 0;

        // allows for constant time access from node id to node
        // each node has an adjacency list of edges
        unordered_map<int, Node> nodes;

         // the graph with all edges reversed, for scc
        unordered_map<int, Node> transpose;

        // the node that initially tweeted
        int source_id;

        // retweet with greatest time
        int greatest_time = 0;
        // node id with greatest retweet time
        int greatest_node = 0;

        // private constructor to return transpose graph
        Graph(const unordered_map<int, Node>& input_nodes, int num_nodes, int num_edges);

        void readEdges(std::istream& str);
        void readNodes(std::istream& str);

        // weight is the absolute value of the source 
		// node time - dest node time
        int getWeight(int source, int dest) const;
};
