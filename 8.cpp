#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
// Initialize variables

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    long long cost;
};

void optimize_memory() {
}

void read_my_input() {
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int totalNodes, totalEdges, totalTerminals;
    if (!(cin >> totalNodes >> totalEdges >> totalTerminals)) {
        return 0;
    }

    vector<int> terminalNodes(totalTerminals);
    for (int i = 0; i < totalTerminals; ++i) {
        cin >> terminalNodes[i];
    }

    vector<vector<Edge>> adjacencyList(totalNodes + 1);
    for (int i = 0; i < totalEdges; ++i) {
        int u, v, type;
        long long cost;
        cin >> u >> v >> type >> cost;
        if (type == 1) {
            cost = 0;
        }
        adjacencyList[u].push_back({v, cost});
        adjacencyList[v].push_back({u, cost});
    }

    int terminalMaskCount = 1 << totalTerminals;
    vector<vector<long long>> minCostDP(terminalMaskCount, vector<long long>(totalNodes + 1, INF));

    for (int i = 0; i < totalTerminals; ++i) {
        minCostDP[1 << i][terminalNodes[i]] = 0;
    }

    for (int mask = 1; mask < terminalMaskCount; ++mask) {
        for (int submask = (mask - 1) & mask; submask > 0; submask = (submask - 1) & mask) {
            int remainingSubmask = mask ^ submask;
            if (submask < remainingSubmask) continue;

            for (int u = 1; u <= totalNodes; ++u) {
                if (minCostDP[submask][u] < INF && minCostDP[remainingSubmask][u] < INF) {
                    minCostDP[mask][u] = min(minCostDP[mask][u], minCostDP[submask][u] + minCostDP[remainingSubmask][u]);
                }
            }
        }

        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> minHeap;
        for (int u = 1; u <= totalNodes; ++u) {
            if (minCostDP[mask][u] < INF) {
                minHeap.push({minCostDP[mask][u], u});
            }
        }

        while (!minHeap.empty()) {
            auto [currentCost, currentNode] = minHeap.top();
            minHeap.pop();

            if (currentCost > minCostDP[mask][currentNode]) {
                continue;
            }

            for (const auto& edge : adjacencyList[currentNode]) {
                int nextNode = edge.to;
                long long newCost = currentCost + edge.cost;

                if (newCost < minCostDP[mask][nextNode]) {
                    minCostDP[mask][nextNode] = newCost;
                    minHeap.push({newCost, nextNode});
                }
            }
        }
    }

    long long finalAnswer = INF;
    int fullMask = terminalMaskCount - 1;
    for (int u = 1; u <= totalNodes; ++u) {
        finalAnswer = min(finalAnswer, minCostDP[fullMask][u]);
    }

    if (finalAnswer >= INF / 2) {
        cout << -1 << "\n";
    } else {
        cout << finalAnswer << "\n";
    }

    optimize_memory();
    return 0;
}
