#include "src/AnalyzeGraphs.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

int main() {
    vector<string> dirs = {"data/wico-graph/Other_Graphs/","data/wico-graph/5G_Conspiracy_Graphs/", "data/wico-graph/Non_Conspiracy_Graphs/"};
    AnalyzeGraphs results = AnalyzeGraphs(dirs);
    results.exportResults("wico_graph_results.csv");

    return 0;
}
