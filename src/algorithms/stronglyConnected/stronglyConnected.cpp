#include "stronglyConnected.h"


SCC::SCC(const Graph & g) {
    Graph* tra = g.getTranspose();
    Graph transpose = *tra;
    delete tra;

    // set all nodes to unvisited
    for (auto it = g.begin(); it != g.end(); it++) {
        visited_.insert({it->first, false});
    }
    findSCC(g, transpose);
}

void SCC::sortTopological(int id, const Graph & g) {
    visited_[id] = true;
    for (auto& edge : g.incidentEdges(id)) {
        int to = edge.dest_id;
        if (!visited_[to]) {
            sortTopological(to, g);
        }
    }
    s.push(id);
}

void SCC::findSCC(const Graph & g, const Graph & g_tran) {
    // get order to visit nodes
    for (auto it = g.begin(); it != g.end(); it++) {
        if (!visited_[it->first]) {
            sortTopological(it->first, g);
        }
    }

    // reset all nodes to unvisited
    for (auto it = g.begin(); it != g.end(); it++) {
        visited_[it->first] = false;
    }

    // traverse in the opposite direction
    while (!s.empty()) {
        int node = s.top();
        s.pop();
        if (!visited_[node]) {
            vector<int> current_scc;
            DFS dfs_tran(node, g_tran);
            for (const auto& id : dfs_tran) {
                // add node to current component if it hasn't been visited
                if (!visited_[id]) {
                    current_scc.push_back(id);
                }
                visited_[id] = true;
            }
            sccs_.push_back(current_scc);
            scc_count_++;
        }
    }
}


int SCC::getSCCCount() const {
    return scc_count_;
}

vector<vector<int>> SCC::getAllSCC() const {
    return sccs_;
}