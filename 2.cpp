
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long INF = (1LL << 60);

int N, M;
vector<long long> models;
vector<char> engineer, action;
long long memo[21][1 << 20];
bool seen[21][1 << 20];

long long solve(int turn, int mask)
{
    if (turn == M)
    {
        return 0;
    }

    if (seen[turn][mask])
    {
        return memo[turn][mask];
    }

    seen[turn][mask] = true;

    long long best;

    if (engineer[turn] == 'A')
    {
        best = -INF;
    }
    else
    {
        best = INF;
    }

    for (int i = 0; i < N; i++)
    {
        if (mask & (1 << i))
        {
            continue;
        }

        int newMask = mask | (1 << i);
        long long value = solve(turn + 1, newMask);

        if (action[turn] == 'p')
        {
            if (engineer[turn] == 'A')
            {
                value += models[i];
            }
            else
            {
                value -= models[i];
            }
        }

        if (engineer[turn] == 'A')
        {
            best = max(best, value);
        }
        else
        {
            best = min(best, value);
        }
    }

    memo[turn][mask] = best;
    return best;
}

void optimize_memory()
{
}

void read_my_input()
{
    cin >> N;

    models.resize(N);

    for (int i = 0; i < N; i++)
    {
        cin >> models[i];
    }

    cin >> M;

    engineer.resize(M);
    action.resize(M);

    for (int i = 0; i < M; i++)
    {
        string x, y;
        cin >> x >> y;

        engineer[i] = x[0];
        action[i] = (y == "pick" ? 'p' : 'b');
    }

    sort(models.begin(), models.end(), greater<long long>());

    long long result = solve(0, 0);

    if (result > 0)
    {
        cout << "A " << result << '\n';
    }
    else
    {
        cout << "B " << -result << '\n';
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
