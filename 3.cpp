#include <iostream>
#include <algorithm>

using namespace std;

struct Event {
    int fromNode;
    int toNode;
    long long timestamp;
    int originalIndex;
};

bool compareEvents(const Event& firstEvent, const Event& secondEvent) {
    if (firstEvent.timestamp != secondEvent.timestamp) {
        return firstEvent.timestamp < secondEvent.timestamp;
    }
    return firstEvent.originalIndex < secondEvent.originalIndex;
}

int main() {
    int totalNodes, totalEvents;
    long long maxTimeDiff;

    cout << "Enter total nodes, total events, and max time difference: ";
    if (!(cin >> totalNodes >> totalEvents >> maxTimeDiff)) {
        return 0;
    }

    if (totalEvents < 3) {
        cout << "Result: 0 0 0" << endl;
        return 0;
    }

    Event* eventList = new Event[totalEvents];

    cout << "Enter each event (fromNode toNode timestamp):" << endl;
    for (int i = 0; i < totalEvents; i++) {
        cin >> eventList[i].fromNode >> eventList[i].toNode >> eventList[i].timestamp;
        eventList[i].originalIndex = i;
    }

    sort(eventList, eventList + totalEvents, compareEvents);

    long long countType1 = 0;
    long long countType2 = 0;
    long long countType3 = 0;

    for (int i = 0; i < totalEvents; i++) {
        int nodeA = eventList[i].fromNode;
        int nodeB = eventList[i].toNode;
        long long time1 = eventList[i].timestamp;

        if (nodeA == nodeB) continue;

        for (int j = i + 1; j < totalEvents; j++) {
            if (eventList[j].timestamp - time1 > maxTimeDiff) {
                break;
            }

            int nodeC = eventList[j].fromNode;
            int nodeD = eventList[j].toNode;

            if (nodeC == nodeD) continue;
            if (nodeA == nodeC && nodeB == nodeD) continue;

            for (int k = j + 1; k < totalEvents; k++) {
                if (eventList[k].timestamp - time1 > maxTimeDiff) {
                    break;
                }

                int nodeE = eventList[k].fromNode;
                int nodeF = eventList[k].toNode;

                if (nodeE == nodeF) continue;
                if (nodeA == nodeE && nodeB == nodeF) continue;
                if (nodeC == nodeE && nodeD == nodeF) continue;

                if (nodeB == nodeC && nodeD == nodeE && nodeF == nodeA &&
                    nodeA != nodeB && nodeA != nodeD && nodeB != nodeD) {
                    countType1++;
                }

                if (nodeA == nodeC && nodeB == nodeE && nodeD == nodeF &&
                    nodeA != nodeB && nodeA != nodeD && nodeB != nodeD) {
                    countType2++;
                }

                if (nodeA == nodeE && nodeB == nodeD && nodeC == nodeF &&
                    nodeA != nodeB && nodeA != nodeC && nodeB != nodeC) {
                    countType3++;
                }
            }
        }
    }

    cout << "Result: " << countType1 << " " << countType2 << " " << countType3 << endl;

    delete[] eventList;

    return 0;
}
