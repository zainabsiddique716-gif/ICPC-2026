#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

const int MAX_NODES = 505;

struct Event {
    int fromNode;
    int toNode;
    long long timestamp;
};

bool compareEvents(const Event& eventA, const Event& eventB) {
    if (eventA.timestamp != eventB.timestamp) {
        return eventA.timestamp < eventB.timestamp;
    }
    if (eventA.fromNode != eventB.fromNode) {
        return eventA.fromNode < eventB.fromNode;
    }
    return eventA.toNode < eventB.toNode;
}

int main() {
    int totalNodes, totalEvents;
    long long maxTimeDifference;

    cout << "Enter total nodes, total events, and max time difference: ";
    if (!(cin >> totalNodes >> totalEvents >> maxTimeDifference)) {
        return 0;
    }

    if (totalEvents < 3) {
        cout << "Result: 0 0 0" << endl;
        return 0;
    }

    vector<Event> eventList(totalEvents);

    cout << "Enter each event (fromNode toNode timestamp):" << endl;
    for (int i = 0; i < totalEvents; i++) {
        cin >> eventList[i].fromNode >> eventList[i].toNode >> eventList[i].timestamp;
    }

    sort(eventList.begin(), eventList.end(), compareEvents);

    long long countType1 = 0;
    long long countType2 = 0;
    long long countType3 = 0;

    for (int i = 0; i < totalEvents; i++) {
        int nodeA = eventList[i].fromNode;
        int nodeB = eventList[i].toNode;
        long long time1 = eventList[i].timestamp;

        if (nodeA == nodeB) continue;

        for (int j = i + 1; j < totalEvents; j++) {
            long long time2 = eventList[j].timestamp;

            if (time2 - time1 > maxTimeDifference) break;
            if (time2 == time1) continue;

            int nodeU2 = eventList[j].fromNode;
            int nodeV2 = eventList[j].toNode;

            int targetU3 = -1;
            int targetV3 = -1;
            int patternType = 0;

            if (nodeU2 == nodeB && nodeV2 != nodeA && nodeV2 != nodeB) {
                targetU3 = nodeV2;
                targetV3 = nodeA;
                patternType = 1;
            } else if (nodeU2 == nodeA && nodeV2 != nodeA && nodeV2 != nodeB) {
                targetU3 = nodeB;
                targetV3 = nodeV2;
                patternType = 2;
            } else if (nodeV2 == nodeB && nodeU2 != nodeA && nodeU2 != nodeB) {
                targetU3 = nodeB;
                targetV3 = nodeA;
                patternType = 3;
            }

            if (patternType == 0) continue;

            for (int k = j + 1; k < totalEvents; k++) {
                long long time3 = eventList[k].timestamp;

                if (time3 - time1 > maxTimeDifference) break;
                if (time3 == time2) continue;

                if (eventList[k].fromNode == targetU3 && eventList[k].toNode == targetV3) {
                    if (patternType == 1) countType1++;
                    else if (patternType == 2) countType2++;
                    else if (patternType == 3) countType3++;
                }
            }
        }
    }

    cout << "Result: " << countType1 << " " << countType2 << " " << countType3 << endl;

    return 0;
}
