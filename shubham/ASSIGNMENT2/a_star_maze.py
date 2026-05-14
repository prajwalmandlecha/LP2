import heapq

class Node:
    """A node class for A* Pathfinding"""
    def __init__(self, parent=None, position=None):
        self.parent = parent
        self.position = position

        self.g = 0  # Cost from start to current node
        self.h = 0  # Heuristic (estimated cost from current to goal)
        self.f = 0  # Total cost (g + h)

    def __eq__(self, other):
        return self.position == other.position
    
    def __lt__(self, other):
        return self.f < other.f

    def __hash__(self):
        return hash(self.position)

def a_star_maze(maze, start, end):
    """
    Returns a list of tuples as a path from the given start to the given end in the given maze
    """
    # Create start and end node
    start_node = Node(None, start)
    end_node = Node(None, end)

    # Initialize both open and closed lists
    open_list = []
    closed_set = set()

    # Add the start node
    heapq.heappush(open_list, start_node)

    # Move directions: Up, Down, Left, Right
    directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]

    # Loop until you find the end
    while open_list:
        # Get the current node
        current_node = heapq.heappop(open_list)
        closed_set.add(current_node.position)

        # Found the goal
        if current_node == end_node:
            path = []
            current = current_node
            while current is not None:
                path.append(current.position)
                current = current.parent
            return path[::-1] # Return reversed path

        # Generate children
        for move in directions:
            # Get node position
            node_position = (current_node.position[0] + move[0], current_node.position[1] + move[1])

            # Make sure within range
            if node_position[0] > (len(maze) - 1) or node_position[0] < 0 or node_position[1] > (len(maze[len(maze)-1]) - 1) or node_position[1] < 0:
                continue

            # Make sure walkable terrain (0 represents open path, 1 represents wall)
            if maze[node_position[0]][node_position[1]] != 0:
                continue

            # If the child is already in the closed set, skip it
            if node_position in closed_set:
                continue
                
            # Create new node
            new_node = Node(current_node, node_position)

            # Calculate f, g, and h values
            new_node.g = current_node.g + 1
            # Manhattan distance to goal
            new_node.h = abs(new_node.position[0] - end_node.position[0]) + abs(new_node.position[1] - end_node.position[1])
            new_node.f = new_node.g + new_node.h

            # Check if this node is already in open_list with a lower f-cost
            # For strict correctness we should check, but in a simple 2D unweighted grid, 
            # this basic check works fine with closed_set
            
            # Add the child to the open list
            heapq.heappush(open_list, new_node)

    return None # No path found

def print_maze_with_path(maze, path):
    if not path:
        print("No path found.")
        return
        
    maze_copy = [row[:] for row in maze]
    
    # Mark the path
    for r, c in path:
        if maze_copy[r][c] == 0:
            maze_copy[r][c] = '*'
            
    # Mark start and end
    start_r, start_c = path[0]
    end_r, end_c = path[-1]
    maze_copy[start_r][start_c] = 'S'
    maze_copy[end_r][end_c] = 'E'
    
    for row in maze_copy:
        print(" ".join(str(cell) for cell in row))

if __name__ == '__main__':
    # 0 = open path, 1 = obstacle/wall
    maze = [
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 1, 1, 1, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    ]

    start_point = (0, 0)
    end_point = (7, 6)

    print("Initial Maze (0: Path, 1: Wall):")
    for row in maze:
        print(" ".join(str(cell) for cell in row))
        
    print(f"\nFinding path from {start_point} to {end_point}...")
    path = a_star_maze(maze, start_point, end_point)
    
    print("\nSolved Maze (S: Start, E: End, *: Path):")
    print_maze_with_path(maze, path)
