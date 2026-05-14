import sys

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        # Adjacency matrix to represent the graph
        self.graph = [[0 for _ in range(vertices)] for _ in range(vertices)]

    def print_mst(self, parent):
        print("Edge \tWeight")
        total_cost = 0
        for i in range(1, self.V):
            weight = self.graph[i][parent[i]]
            print(f"{parent[i]} - {i} \t{weight}")
            total_cost += weight
        print(f"Total Cost: {total_cost}")

    def get_min_key(self, key, mst_set):
        """Find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree."""
        min_val = sys.maxsize
        min_index = -1

        for v in range(self.V):
            if key[v] < min_val and not mst_set[v]:
                min_val = key[v]
                min_index = v

        return min_index

    def prim_mst(self):
        """Construct and print MST for a graph represented using adjacency matrix representation."""
        # Key values used to pick minimum weight edge
        key = [sys.maxsize] * self.V
        # Array to store constructed MST
        parent = [None] * self.V
        
        # Include first vertex in MST
        key[0] = 0        
        mst_set = [False] * self.V
        parent[0] = -1  # First node is always root

        for _ in range(self.V):
            # Pick the minimum distance vertex from the set of vertices not yet processed
            u = self.get_min_key(key, mst_set)
            
            # Put the minimum distance vertex in the shortest path tree
            mst_set[u] = True

            # Update key value and parent index of the adjacent vertices of the picked vertex
            for v in range(self.V):
                # graph[u][v] > 0 means there is an edge and mst_set[v] is false for vertices not yet included in MST
                # Update key only if graph[u][v] is smaller than key[v]
                if self.graph[u][v] > 0 and not mst_set[v] and key[v] > self.graph[u][v]:
                    key[v] = self.graph[u][v]
                    parent[v] = u

        self.print_mst(parent)

if __name__ == '__main__':
    while True:
        print("\n--- Prim's MST Menu ---")
        print("1. Run with sample graph")
        print("2. Enter custom graph adjacency matrix")
        print("3. Exit")
        choice = input("Enter your choice (1-3): ")
        
        if choice == '1':
            g = Graph(5)
            g.graph = [
                [0, 2, 0, 6, 0],
                [2, 0, 3, 8, 5],
                [0, 3, 0, 0, 7],
                [6, 8, 0, 0, 9],
                [0, 5, 7, 9, 0]
            ]
            print("Prim's Minimum Spanning Tree:")
            g.prim_mst()
        elif choice == '2':
            try:
                v = int(input("Enter number of vertices: "))
                g = Graph(v)
                print(f"Enter the {v}x{v} adjacency matrix row by row (space separated):")
                matrix = []
                for i in range(v):
                    row = list(map(int, input().split()))
                    if len(row) != v:
                        print(f"Error: Expected {v} elements, got {len(row)}")
                        break
                    matrix.append(row)
                if len(matrix) == v:
                    g.graph = matrix
                    print("Prim's Minimum Spanning Tree:")
                    g.prim_mst()
            except ValueError:
                print("Invalid input. Please enter integers only.")
        elif choice == '3':
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please try again.")
