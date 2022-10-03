#pragma once

#include "../dfs/dfs.h"
#include "../../graph/graph.h"

#include <vector>
#include <stack>
#include <unordered_map>
#include <queue>

using std::unordered_map;
using std::vector;
using std::stack;
using std::queue;

/* A class that implements Kosaraju's algorithm for 
   getting strongly connected components */
class SCC {
    public:
        /** SCC solver for the input graph
            @param g the graph to find sccs of
        */
        SCC(const Graph & g);

        /** Gets the number of strongly connected components of the graph
            @return the scc count
        */
        int getSCCCount() const;
        
        /** Gets all of the nodes of the graph 
            partitioned into their respective scc
            @return a 2d vector of the sccs
        */
        vector<vector<int>> getAllSCC() const;

    private:
        int scc_count_ = 0;

        //stack representing the order to visit nodes on second dfs
        stack<int> s;
        
        //map from node id to an int whether or not it was visited
        unordered_map<int, bool>visited_;

        //a partition of each node id into its respective component
        vector<vector<int>> sccs_;

        void findSCC(const Graph & g, const Graph & g_tran);

        void sortTopological(int id, const Graph & g);
};  
