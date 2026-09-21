INF = 999

# Adjacency Matrix representation of the campus network
graph = [
    [0, 2, 0, 6, 0],
    [2, 0, 3, 8, 5],
    [0, 3, 0, 0, 7],
    [6, 8, 0, 0, 9],
    [0, 5, 7, 9, 0]
]

departments = ["Computer", "IT", "Mechanical", "Civil", "Library"]
V = len(graph)

# ---------------- Prim's Algorithm ---------------- #
def prim():
    selected = [False] * V
    selected[0] = True  # Start with the first vertex (Computer)
    edge = 0
    cost = 0
    
    print("\nMinimum Spanning Tree using Prim's Algorithm\n")
    
    while edge < V - 1:
        minimum = INF
        x = 0
        y = 0
        
        # Traverse through all vertices to find the minimum cut-edge
        for i in range(V):
            if selected[i]:
                for j in range(V):
                    # Edge must connect a selected vertex to an unselected one
                    if not selected[j] and graph[i][j]:
                        if graph[i][j] < minimum:
                            minimum = graph[i][j]
                            x = i
                            y = j
                            
        print(f"{departments[x]} -- {departments[y]} = {graph[x][y]}")
        cost += graph[x][y]
        selected[y] = True
        edge += 1
        
    print("Minimum Cost =", cost)

# ---------------- Kruskal's Algorithm ---------------- #
parent = []

def find(i):
    """Find the root parent of vertex i using path compression tracking."""
    while parent[i] != i:
        i = parent[i]
    return i

def union(i, j):
    """Union two disjoint sets by linking their root nodes."""
    root_i = find(i)
    root_j = find(j)
    parent[root_i] = root_j

def kruskal():
    edges = []
    
    # Extract all unique undirected edges from the adjacency matrix
    for i in range(V):
        for j in range(i + 1, V):
            if graph[i][j] != 0:
                edges.append((graph[i][j], i, j))
                
    # Sort all edges based on their weights in ascending order
    edges.sort()
    
    # Initialize Disjoint Set tracking structure
    parent.clear()
    for i in range(V):
        parent.append(i)
        
    cost = 0
    count = 0
    
    print("\nMinimum Spanning Tree using Kruskal's Algorithm\n")
    
    for w, u, v in edges:
        # Check if including this edge creates a cycle
        if find(u) != find(v):
            union(u, v)
            print(f"{departments[u]} -- {departments[v]} = {w}")
            cost += w
            count += 1
            
        # Stop execution once V-1 edges are added to the tree
        if count == V - 1:
            break
            
    print("Minimum Cost =", cost)

# ---------------- Main Program Loop ---------------- #
while True:
    print("\n1. Prim's Algorithm")
    print("2. Kruskal's Algorithm")
    print("3. Exit")
    
    try:
        choice = int(input("Enter Choice: "))
        if choice == 1:
            prim()
        elif choice == 2:
            kruskal()
        elif choice == 3:
            print("Program Ended")
            break
        else:
            print("Invalid Choice. Please enter 1, 2, or 3.")
    except ValueError:
        print("Invalid Input. Please enter a valid integer.")
