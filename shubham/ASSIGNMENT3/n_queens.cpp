#include <iostream>
#include <vector>
#include <string>

using namespace std;

class NQueens {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> solutions;
        vector<string> board(n, string(n, '.'));
        
        // Branch and Bound constraint arrays
        // Instead of conventionally scanning the board (O(N) check), we bound our space in O(1)
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n - 1, false); // Tracks main diagonals: row + col
        vector<bool> diag2(2 * n - 1, false); // Tracks anti-diagonals: row - col + (n - 1)
        
        backtrack(0, n, board, cols, diag1, diag2, solutions);
        return solutions;
    }

private:
    void backtrack(int row, int n, vector<string>& board, 
                   vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2, 
                   vector<vector<string>>& solutions) {
        // Base case: All queens are placed perfectly
        if (row == n) {
            solutions.push_back(board);
            return;
        }
        
        for (int col = 0; col < n; ++col) {
            // Bound: If the column or any diagonal is under attack, prune this branch
            if (cols[col] || diag1[row + col] || diag2[row - col + n - 1]) {
                continue;
            }
            
            // Place the queen
            board[row][col] = 'Q';
            cols[col] = diag1[row + col] = diag2[row - col + n - 1] = true;
            
            // Branch out to the next row
            backtrack(row + 1, n, board, cols, diag1, diag2, solutions);
            
            // Backtrack: Remove the queen and undo constraints
            board[row][col] = '.';
            cols[col] = diag1[row + col] = diag2[row - col + n - 1] = false;
        }
    }
};

int main() {
    int n = 4;
    NQueens solver;
    vector<vector<string>> solutions = solver.solveNQueens(n);
    
    cout << "Found " << solutions.size() << " solutions for " << n << "-Queens:\n\n";
    for (int i = 0; i < solutions.size(); ++i) {
        cout << "Solution " << i + 1 << ":\n";
        for (const string& row : solutions[i]) {
            for (char c : row) {
                cout << c << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    return 0;
}
