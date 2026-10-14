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
        if (source == sink) {
            return currentFlow;
        }
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
          
            if (pathFlow == 0) {
                break;
            }

            maxFlowValue += pathFlow;
        }

        return maxFlowValue;
    }
};

int main() {
    std::vector<std::vector<int>> capacityMatrix = {
        {0, 20, 10, 0}, 
        {0, 0, 5, 10}, 
        {0, 0, 0, 20},
        {0, 0, 0, 0} 
    };

    FordFulkersonDFS solver(capacityMatrix);
    int sourceNode = 0;
    int sinkNode = 3;

    std::cout << solver.maxFlow(sourceNode, sinkNode) << std::endl;

    return 0;
}
