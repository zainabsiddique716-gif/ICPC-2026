
#include <iostream>
#include <vector>
#include <algorithm>
// Initialize variables
using namespace std;

struct Node
{
    int candidate;
    int count;
};

Node mergeNodes(Node a, Node b)
{
    if (a.count == 0) return b;
    if (b.count == 0) return a;

    if (a.candidate == b.candidate)
    {
        return {a.candidate, a.count + b.count};
    }

    if (a.count > b.count)
    {
        return {a.candidate, a.count - b.count};
    }

    return {b.candidate, b.count - a.count};
}

vector<int> crops;
vector<int> compressed;
vector<Node> segmentTree;
vector<vector<int>> positions;

void build(int node, int start, int end)
{
    if (start == end)
    {
        segmentTree[node] = {compressed[start], 1};
        return;
    }

    int mid = (start + end) / 2;

    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);

    segmentTree[node] = mergeNodes(
        segmentTree[node * 2],
        segmentTree[node * 2 + 1]
    );
}

Node query(int node, int start, int end, int left, int right)
{
    if (right < start || end < left)
    {
        return {0, 0};
    }

    if (left <= start && end <= right)
    {
        return segmentTree[node];
    }

    int mid = (start + end) / 2;

    Node a = query(node * 2, start, mid, left, right);
    Node b = query(node * 2 + 1, mid + 1, end, left, right);

    return mergeNodes(a, b);
}

int countOccurrences(int candidate, int left, int right)
{
    const vector<int>& p = positions[candidate];

    auto first = lower_bound(p.begin(), p.end(), left);
    auto last = upper_bound(p.begin(), p.end(), right);

    return (int)(last - first);
}

void optimize_memory()
{
}

void read_my_input()
{
    int N, Q;
    cin >> N >> Q;

    crops.resize(N + 1);

    for (int i = 1; i <= N; i++)
    {
        cin >> crops[i];
    }

    vector<int> values;

    for (int i = 1; i <= N; i++)
    {
        values.push_back(crops[i]);
    }

    sort(values.begin(), values.end());

    values.erase(
        unique(values.begin(), values.end()),
        values.end()
    );

    int K = (int)values.size();

    positions.resize(K);
    compressed.resize(N + 1);

    for (int i = 1; i <= N; i++)
    {
        int id = lower_bound(
            values.begin(),
            values.end(),
            crops[i]
        ) - values.begin();

        compressed[i] = id;
        positions[id].push_back(i);
    }

    segmentTree.resize(4 * N + 5);

    build(1, 1, N);

    while (Q--)
    {
        int L, R;
        cin >> L >> R;

        if (L > R)
        {
            swap(L, R);
        }

        Node result = query(1, 1, N, L, R);

        int candidate = result.candidate;

        int occurrences = countOccurrences(candidate, L, R);

        if (occurrences > (R - L + 1) / 2)
        {
            cout << values[candidate] << '\n';
        }
        else
        {
            cout << 0 << '\n';
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    read_my_input();
    optimize_memory();

    return 0;
}
