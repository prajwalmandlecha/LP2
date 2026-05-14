#include <bits/stdc++.h>

using namespace std;

void dfsrec(vector<vector<int>> &adj, vector<int> &visited, int node)
{
    cout << "visited " << node << "\n";
    visited[node] = true;

    for (int neighbour : adj[node])
    {
        if (!visited[neighbour])
        {
            visited[neighbour] = true;
            dfsrec(adj, visited, neighbour);
        }
    }
}

void dfs(vector<vector<int>> &adj)
{
    int n = adj.size();
    vector<int> visited(n);
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
            dfsrec(adj, visited, i);
    }
}

void bfsrec(vector<vector<int>> &adj, vector<int> &visited, int node)
{
    queue<int> q;
    q.push(node);
    while (!q.empty())
    {
        int temp = q.front();
        q.pop();
        visited[temp] = true;
        cout << "visited " << temp << "\n";

        for (int neighbour : adj[temp])
        {
            if (!visited[neighbour])
            {
                visited[neighbour] = true;
                q.push(neighbour);
            }
        }
    }
}

void bfs(vector<vector<int>> &adj)
{
    int n = adj.size();
    vector<int> visited(n);
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
            bfsrec(adj, visited, i);
    }
}

int main()
{
    int n = 6;
    vector<vector<int>> adj = {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1, 5},
        {2, 4}};

    cout << "dfs traversal: ";
    dfs(adj);
    cout << "bfs traversal: ";
    bfs(adj);
    return 0;
}