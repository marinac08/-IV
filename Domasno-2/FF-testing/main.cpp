#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class FordFulkersonDFS {
private:
    int numVertices;
    std::vector<std::vector<int>> graph;

    int dfs(int source, int sink, int currentFlow, std::vector<bool>& visited) {
        visited[source] = true;
        if (source == sink) return currentFlow;

        for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
            int residualCapacity = graph[source][neighbor];
            if (!visited[neighbor] && residualCapacity > 0) {
                int bottleneck = std::min(currentFlow, residualCapacity);
                int finalFlow = dfs(neighbor, sink, bottleneck, visited);

                if (finalFlow > 0) {
                    graph[source][neighbor] -= finalFlow;
                    graph[neighbor][source] += finalFlow;
                    return finalFlow;
                }
            }
        }
        return 0;
    }

public:
    FordFulkersonDFS(const std::vector<std::vector<int>>& inputGraph) {
        graph = inputGraph;
        numVertices = inputGraph.size();
    }

    int maxFlow(int source, int sink) {
        int maxFlowValue = 0;
        while (true) {
            std::vector<bool> visited(numVertices, false);
            int pathFlow = dfs(source, sink, INT_MAX, visited);
            if (pathFlow == 0) break;
            maxFlowValue += pathFlow;
        }
        return maxFlowValue;
    }
};

int main() {
    std::vector<std::vector<int>> ffKiller = {
        {0, 1000000, 1000000, 0}, {0, 0, 1, 1000000}, {0, 0, 0, 1000000}, {0, 0, 0, 0}
    };
    FordFulkersonDFS solver1(ffKiller);
    std::cout << "1. FF Killer Max Flow: " << solver1.maxFlow(0, 3) << " (Expected: 2000000)\n";

    std::vector<std::vector<int>> cp4Correct = {
        {0, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 0}, {0, 0, 0, 1, 0, 0}, 
        {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0}
    };
    FordFulkersonDFS solver2(cp4Correct);
    std::cout << "2. CP4 Correct Max Flow: " << solver2.maxFlow(0, 5) << " (Expected: 2)\n";

    std::vector<std::vector<int>> cs4234Demo = {
        {0, 3, 3, 0, 0}, {0, 0, 1, 2, 0}, {0, 0, 0, 0, 4}, {0, 0, 0, 0, 3}, {0, 0, 0, 0, 0}
    };
    FordFulkersonDFS solver3(cs4234Demo);
    std::cout << "3. CS4234 Demo Max Flow: " << solver3.maxFlow(0, 4) << " (Expected: 5)\n";

    std::vector<std::vector<int>> matchingWithCapacity = {
        {0, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 1, 1, 0}, 
        {0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 0, 0, 2}, {0, 0, 0, 0, 0, 0, 2}, {0, 0, 0, 0, 0, 0, 0}
    };
    FordFulkersonDFS solver4(matchingWithCapacity);
    std::cout << "4. Matching with Capacity Max Flow: " << solver4.maxFlow(0, 6) << " (Expected: 3)\n";

    return 0;
}
