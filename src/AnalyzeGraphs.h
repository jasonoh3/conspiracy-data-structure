#pragma once

#include "graph/graph.h"
#include "algorithms/dijkstra/dijkstra.h"
#include "algorithms/stronglyConnected/stronglyConnected.h"
#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

/* A class for running all graph algorithms on the data set and exporting results */
class AnalyzeGraphs {
    public:
        /** Constructor for analyzing graphs
            @param directories a vector of directories, each containing 
            a set of manually classified subgraphs of tweets
        */
        AnalyzeGraphs(const vector<string>& directories);

        /** Exports results of the graph algorithms on 
            all specified subgraphs to a csv file
            @param file_name the name of the file to export results to
        */
        void exportResults(const string & file_name);

    private:
        /** Helper function for the exportResults, which will write our final csv file
            @param dir the directory of which the data is in
            @param output the csv file the results are written in
        */
        void writeDirResults(const string & dir, std::ofstream & output);

        /** Private getter for the length of the shortest path if the information 
            flows through the follower network
            @param path_length the length of the path from Dijkstra's
            @param path_weight the weight of the shortest path
            @param greatest_time the greatest time after the intial tweet 
            @return the length of the shortest path if the path weight 
            is less than or equal to the greatest time, otherwise 0
        */
        int getInformationFlow(int path_length, int path_weight, int greatest_time) const;

        vector<string> directories_;
        const string node_file = "/nodes.csv";
        const string edge_file = "/edges.txt";
};
