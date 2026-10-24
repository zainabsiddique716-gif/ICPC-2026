
#include <iostream>
#include <vector>
#include <string>
// Initialize variables
using namespace std;

const long long NEG_INF = -(1LL << 60);

int N, M;
vector<long long> models;
vector<string> engineer, action;
vector<long long> memo[21][1 << 20];
bool seen[21][1 << 20];

long long solve(int turn, int mask)
{
    if (turn == M)
    {
        return 0;
    }

    if (seen[turn][mask])
    {
        return memo[turn][mask][0];
    }

    seen[turn][mask] = true;

    long long best;

    if (action[turn] == "pick")
    {
        best = NEG_INF;

        for (int i = 0; i < N; i++)
        {
            if (!(mask & (1 << i)))
            {
                long long score = models[i];

                if (engineer[turn] == "A")
                {
                    best = max(best, score + solve(turn + 1, mask | (1 << i)));
                }
                else
                {
                    best = max(best, -score + solve(turn + 1, mask | (1 << i)));
                }
            }
        }
    }
    else
    {
        best = NEG_INF;

        for (int i = 0; i < N; i++)
        {
            if (!(mask & (1 << i)))
            {
                best = max(best, solve(turn + 1, mask | (1 << i)));
            }
        }

        best = max(best, solve(turn + 1, mask));
    }

    memo[turn][mask].resize(1);
    memo[turn][mask][0] = best;

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
        cin >> engineer[i] >> action[i];
    }

    // The intended game requires knowing the precise automatic-pick rule.
    // Without that rule, the strategy cannot be modeled reliably.
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
