#include "AnalyzeGraphs.h"

AnalyzeGraphs::AnalyzeGraphs(const vector<string>& directories) {
    directories_ = directories;
}

void AnalyzeGraphs::exportResults(const string & file_name) {

    std::ofstream output;
    output.open(file_name);

    //write column names
    output << "graph_type,nodes,edges,greatest_time,strongly_connected,path_length\n";
    for (auto& dir : directories_) {
        writeDirResults(dir, output);
    }

    output.close();
}

void AnalyzeGraphs::writeDirResults(const string & dir, std::ofstream & output) {

    int i = 1;
    while(true) {
        string num = std::to_string(i);
        string nodes = dir + num + node_file;
        string edges = dir + num + edge_file;
        try {
            Graph g = Graph(nodes, edges);
            int greatest_time = g.getTime(g.getGreatestNode());

            // scc
            SCC scc = SCC(g);
            
            // dijkstra
            Dijkstra d;
            d.solve(g, g.getGreatestNode(), g.getSourceID());
            int path_l = getInformationFlow(d.getLength(), d.getSumOfPath(), greatest_time);
            
            //write data to file
            string data;
            data += dir + ",";
            data += std::to_string(g.getNumNodes()) + ",";
            data += std::to_string(g.getNumEdges()) + ",";
            data += std::to_string(greatest_time) + ",";
            data += std::to_string(scc.getSCCCount()) + ",";
            data += std::to_string(path_l);
            data += "\n";

            output << data;
        } catch(std::invalid_argument) {
            // when you reach the end of the directory
            break;
        }
        i++;
    }

}

int AnalyzeGraphs::getInformationFlow(int path_length, int path_weight, int greatest_time) const {
    if (path_weight > greatest_time) {
        return 0;
    } else {
        return path_length;
    }
}