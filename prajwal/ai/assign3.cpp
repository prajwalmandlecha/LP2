#include <bits/stdc++.h>

using namespace std;

void selectionsort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        int mini = i;
        for (int j = i; j < n; j++)
        {
            if (arr[j] < arr[mini])
            {
                mini = j;
            }
        }
        swap(arr[mini], arr[i]);
    }
}

vector<int> jobscheduling(vector<int> &deadline, vector<int> &profit)
{
    vector<pair<int, int>> jobpairs;
    int n = deadline.size();
    for (int i = 0; i < n; i++)
    {
        jobpairs.push_back({deadline[i], profit[i]});
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> ans = {0, 0};
    for (int i = 0; i < n; i++)
    {
        if (jobpairs[i].first > pq.size())
        {
            pq.push(jobpairs[i].second);
        }
        else
        {
            pq.pop();
            pq.push(jobpairs[i].second);
        }
    }

    while (!pq.empty())
    {
        ans[1] += pq.top();
        pq.pop();
        ans[0]++;
    }

    return ans;
}

int prims(int V, vector<vector<int>> &adj)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> visited(V, false);

    int res = 0;

    pq.push({0, 0});

    cout << "MST using prims: ";

    while (!pq.empty())
    {
        auto p = pq.top();
        pq.pop();

        int wt = p.first;
        int u = p.second;

        if (visited[u])
            continue;
        visited[u] = true;
        cout << u << " ";
        res += wt;

        for (int v = 0; v < V; v++)
        {
            if (adj[u][v] != 0 && !visited[v])
            {
                pq.push({adj[u][v], v});
            }
        }
    }
    cout << "\nMin Dist: " << res << endl;
    return res;
}



int main()
{
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    selectionsort(arr);
    for (int x : arr)
        cout << x << " ";
    cout << "\n";

    vector<int> profits = {20, 10, 40, 30};
    vector<int> deadlines = {4, 1, 1, 1};

    vector<int> jobRes = jobscheduling(profits, deadlines);
    cout << "Total Jobs Done: " << jobRes[0] << "\n";
    cout << "Max Profit: " << jobRes[1] << "\n\n";

    int V;
    cout << "Enter no. of locations: ";
    cin >> V;
    vector<vector<int>> adj(V, vector<int>(V, 0));
    int n;
    cout << "Enter number of directly connected locations: ";
    cin >> n;
    int loc1, loc2, dist;
    cout << "Enter distance between two directly connected locations in the form: loc1 loc2 dist\n";
    for (int i = 0; i < n; i++)
    {
        cin >> loc1 >> loc2 >> dist;
        adj[loc1][loc2] = dist;
        adj[loc2][loc1] = dist;
    }
    cout << "Best way to visit all locations:";
    prims(V, adj);

    return 0;
}