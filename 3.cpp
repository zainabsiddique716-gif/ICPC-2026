
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Event {
    int fromNode;
    int toNode;
    long long timestamp;
};

bool compareEvents(const Event& firstEvent, const Event& secondEvent) {
    return firstEvent.timestamp < secondEvent.timestamp;
}

void read_my_input() {
    int totalFriends, totalEvents;
    long long maxTimeWindow;

    cin >> totalFriends >> totalEvents >> maxTimeWindow;

    vector<Event> events(totalEvents);

    for (int i = 0; i < totalEvents; i++) {
        cin >> events[i].fromNode
            >> events[i].toNode
            >> events[i].timestamp;
    }

    sort(events.begin(), events.end(), compareEvents);

    vector<vector<long long>> edgeTimes(
        totalFriends * totalFriends
    );

    for (int i = 0; i < totalEvents; i++) {
        int edgeIndex =
            events[i].fromNode * totalFriends + events[i].toNode;

        edgeTimes[edgeIndex].push_back(events[i].timestamp);
    }

    long long countType1 = 0;
    long long countType2 = 0;
    long long countType3 = 0;

    for (int first = 0; first < totalEvents; first++) {
        int A = events[first].fromNode;
        int B = events[first].toNode;

        long long firstTime = events[first].timestamp;
        long long lastAllowedTime = firstTime + maxTimeWindow;

        for (int second = first + 1; second < totalEvents; second++) {
            long long secondTime = events[second].timestamp;

            if (secondTime >= lastAllowedTime) {
                if (secondTime > lastAllowedTime) {
                    break;
                }
            }

            if (secondTime <= firstTime) {
                continue;
            }

            int C = events[second].fromNode;
            int D = events[second].toNode;

            if (A == B || C == D) {
                continue;
            }

            if (C == B && D != A && D != B) {
                int edgeIndex = D * totalFriends + A;
                const vector<long long>& times = edgeTimes[edgeIndex];

                auto begin = upper_bound(times.begin(), times.end(), secondTime);
                auto end = upper_bound(times.begin(), times.end(), lastAllowedTime);

                countType1 += end - begin;
            }

            if (C == A && D != A && D != B) {
                int edgeIndex = B * totalFriends + D;
                const vector<long long>& times = edgeTimes[edgeIndex];

                auto begin = upper_bound(times.begin(), times.end(), secondTime);
                auto end = upper_bound(times.begin(), times.end(), lastAllowedTime);

                countType2 += end - begin;
            }

            if (D == B && C != A && C != B) {
                int edgeIndex = B * totalFriends + A;
                const vector<long long>& times = edgeTimes[edgeIndex];

                auto begin = upper_bound(times.begin(), times.end(), secondTime);
                auto end = upper_bound(times.begin(), times.end(), lastAllowedTime);

                countType3 += end - begin;
            }
        }
    }

    cout << countType1 << " "
         << countType2 << " "
         << countType3 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_my_input();

    return 0;
}
