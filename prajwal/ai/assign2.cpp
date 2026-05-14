#include <bits/stdc++.h>

using namespace std;

vector<string> WORD_LIST = {
    "cold", "cord", "card", "ward", "warm",
    "gold", "goad", "load", "toad", "word",
    "worm", "work", "pork", "park", "part",
    "cart", "care", "corn", "dark", "dart"};

const int LEN = 20;

bool is_neighbour(string a, string b)
{
    int count = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            count++;
    }
    return count == 1;
}

void bfs(vector<vector<int>> &adj, int start, int end)
{
    queue<int> q;
    q.push(start);
    vector<int> visited(LEN, false);
    visited[start] = true;
    int steps = 0;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        steps++;
        cout << "Step " << steps << " : Visited Word " << WORD_LIST[node] << "\n";
        if (node == end)
        {
            cout << "found the word " << WORD_LIST[node] << " in " << steps << " steps\n";
            return;
        }

        for (int neighbour : adj[node])
        {
            if (!visited[neighbour])
            {
                q.push(neighbour);
                visited[neighbour] = true;
            }
        }
    }
}

void dfs(vector<vector<int>> &adj, int start, int end)
{
    stack<int> s;
    s.push(start);
    vector<int> visited(LEN, false);
    visited[start] = true;
    int steps = 0;
    while (!s.empty())
    {
        int node = s.top();
        s.pop();
        steps++;
        cout << "Step " << steps << " : Visited Word " << WORD_LIST[node] << "\n";
        if (node == end)
        {
            cout << "found the word " << WORD_LIST[node] << " in " << steps << " steps\n";
            return;
        }

        for (int neighbour : adj[node])
        {
            if (!visited[neighbour])
            {
                s.push(neighbour);
                visited[neighbour] = true;
            }
        }
    }
}

int getH(string a, string b)
{
    int h = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            h++;
    }
    return h;
}

void astar(vector<vector<int>> &adj, int start, int end)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> parent(LEN, -1);
    vector<int> gscore(LEN, INT_MAX);
    vector<bool> visited(LEN, false);
    pq.push({getH(WORD_LIST[start], WORD_LIST[end]), start});
    parent[start] = -1;
    gscore[start] = 0;

    while (!pq.empty())
    {
        pair<int, int> curr = pq.top();
        pq.pop();

        if (visited[curr.second])
            continue;
        visited[curr.second] = true;

        if (curr.second == end)
        {
            stack<int> path;
            int node = curr.second;
            while (node != -1)
            {
                path.push(node);
                node = parent[node];
            }
            cout << "PATH: ";
            int count = 0;
            while (!path.empty())
            {
                node = path.top();
                cout << WORD_LIST[node] << " ";
                path.pop();
                count++;
            }
            cout << "\n";
            cout << "Cost: " << count << "\n";
            return;
        }
        int newgscore = gscore[curr.second] + 1;
        for (int neighbour : adj[curr.second])
        {
            if (newgscore < gscore[neighbour])
            {
                gscore[neighbour] = newgscore;
                parent[neighbour] = curr.second;
                int fscore = gscore[neighbour] + getH(WORD_LIST[neighbour], WORD_LIST[end]);
                pq.push({fscore, neighbour});
            }
        }
    }
}

int main()
{
    vector<vector<int>> adj(LEN);

    map<string, int> wordToIndex;
    for (int i = 0; i < LEN; i++)
    {
        wordToIndex[WORD_LIST[i]] = i;
    }

    for (int i = 0; i < LEN; i++)
    {
        for (int j = 0; j < LEN; j++)
        {
            if (i != j && is_neighbour(WORD_LIST[i], WORD_LIST[j]))
            {
                adj[i].push_back(j);
            }
        }
    }

    cout << "DEBUG: adjacency list\n";
    for (int i = 0; i < LEN; i++)
    {
        cout << WORD_LIST[i] << " :";
        for (int j = 0; j < adj[i].size(); j++)
        {
            cout << WORD_LIST[adj[i][j]] << " ";
        }
        cout << "\n";
    }
    cout << "END: adjacency list\n\n\n\n\n";

    string startWord, endWord;
    cout << "Available words: ";
    for (const string &s : WORD_LIST)
        cout << s << " ";

    cout << "\n\nEnter starting word: ";
    cin >> startWord;
    cout << "Enter target word: ";
    cin >> endWord;

    cout << "BFS:\n";
    bfs(adj, wordToIndex[startWord], wordToIndex[endWord]);
    cout << "\nDFS:\n";
    dfs(adj, wordToIndex[startWord], wordToIndex[endWord]);

    cout << "\nA* Search:\n";
    astar(adj, wordToIndex[startWord], wordToIndex[endWord]);

    return 0;
}