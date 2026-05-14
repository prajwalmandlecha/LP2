#include <bits/stdc++.h>

using namespace std;

int n = 4;

bool issafe(vector<string> &v, int row, int col)
{
    for (int i = 0; i < col; i++)
    {
        if (v[row][i] == 'Q')
        {
            return false;
        }
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (v[i][j] == 'Q')
        {
            return false;
        }
    }
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
    {
        if (v[i][j] == 'Q')
        {
            return false;
        }
    }
    return true;
}

void placebycolumn(vector<vector<string>> &ans, vector<string> &v, int col)
{
    if (col == n)
    {
        ans.push_back(v);
        return;
    }

    for (int row = 0; row < n; row++)
    {
        if (issafe(v, row, col))
        {
            v[row][col] = 'Q';
            placebycolumn(ans, v, col + 1);
            v[row][col] = '.';
        }
    }
}

int main()
{
    vector<string> v = {
        "....", "....", "....", "...."};
    vector<vector<string>> ans;
    placebycolumn(ans, v, 0);

    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << ans[i][j] << "\n";
        }
        cout << "\n";
    }

    return 0;
}