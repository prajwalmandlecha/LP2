def solve_n_queens(n):
    """
    Solves the N-Queens problem using Backtracking and Branch & Bound.
    The branch and bound part is implemented using boolean arrays to track
    which columns and diagonals are already occupied, bounding the search early in O(1) time.
    """
    board = [["." for _ in range(n)] for _ in range(n)]
    solutions = []
    
    # Branch and Bound constraint arrays
    cols = [False] * n
    diag1 = [False] * (2 * n - 1)  # Tracks main diagonals: row + col
    diag2 = [False] * (2 * n - 1)  # Tracks anti-diagonals: row - col + (n - 1)
    
    def backtrack(row):
        # Base case: All queens are placed perfectly
        if row == n:
            solutions.append([" ".join(r) for r in board])
            return
        
        for col in range(n):
            # Bound: If the column or any diagonal is under attack, prune this branch
            if cols[col] or diag1[row + col] or diag2[row - col + n - 1]:
                continue
            
            
            # Place the queen
            board[row][col] = "Q"
            cols[col] = diag1[row + col] = diag2[row - col + n - 1] = True
            
            # Branch out to the next row
            backtrack(row + 1)
            
            # Backtrack: Remove the queen and undo constraints
            board[row][col] = "."
            cols[col] = diag1[row + col] = diag2[row - col + n - 1] = False
            
    backtrack(0)
    return solutions

if __name__ == "__main__":
    n = 4
    solutions = solve_n_queens(n)
    
    print(f"Found {len(solutions)} solutions for {n}-Queens:\n")
    for idx, sol in enumerate(solutions):
        print(f"Solution {idx + 1}:")
        for row in sol:
            print(row)
        print()
