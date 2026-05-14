from collections import deque

class Graph:
    def __init__(self):
        self.graph = {}

    def add_edge(self, u, v):
        if u not in self.graph:
            self.graph[u] = []
        if v not in self.graph:
            self.graph[v] = []
        self.graph[u].append(v)
        self.graph[v].append(u)

    def dfs(self, vertex, visited=None):
        if visited is None:
            visited = set()
            
        visited.add(vertex)
        print(vertex, end=" ")
        
        for neighbor in self.graph.get(vertex, []):
            if neighbor not in visited:
                self.dfs(neighbor, visited)

    def bfs(self, start_vertex):
        visited = set()
        queue = deque([start_vertex])
        visited.add(start_vertex)
        
        while queue:
            vertex = queue.popleft()
            print(vertex, end=" ")
            
            for neighbor in self.graph.get(vertex, []):
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)

if __name__ == "__main__":
    g = Graph()
    n=int(input("Enter the number of vertices: "))
    m=int(input("Enter the number of edges: "))
    for i in range(m):  
        u,v=map(int,input("Enter the edge (u v): ").split())
        g.add_edge(u, v)

    start_node = int(input("Enter the starting vertex: "))

    print("Depth First Search:")
    g.dfs(start_node)
    print("\n")

    print("Breadth First Search:")
    g.bfs(start_node)
    print()
