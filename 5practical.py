# robust_mst_visualize.py
import sys
import traceback

try:
    import networkx as nx
    import matplotlib.pyplot as plt
except Exception as e:
    print("Error importing required packages. Make sure 'networkx' and 'matplotlib' are installed.")
    print("Install with: pip install networkx matplotlib")
    print("Import error:", e)
    sys.exit(1)

def build_graph_data():
    departments = ['CS', 'EE', 'ME', 'CE']
    edges = [
        ('CS', 'EE', 4),
        ('CS', 'ME', 6),
        ('CS', 'CE', 8),
        ('EE', 'ME', 3),
        ('EE', 'CE', 5),
        ('ME', 'CE', 7)
    ]
    return departments, edges

def print_adjacency_list_matrix(departments, edges):
    index = {dept: i for i, dept in enumerate(departments)}
    n = len(departments)

    # adjacency list
    adj_list = {dept: [] for dept in departments}
    for src, dest, dist in edges:
        adj_list[src].append((dest, dist))
        adj_list[dest].append((src, dist))

    print("Adjacency List:")
    for k, v in adj_list.items():
        print(f"{k}: {v}")

    # adjacency matrix
    adj_matrix = [[0] * n for _ in range(n)]
    for src, dest, dist in edges:
        i, j = index[src], index[dest]
        adj_matrix[i][j] = dist
        adj_matrix[j][i] = dist

    print("\nAdjacency Matrix:")
    for row in adj_matrix:
        print(row)

    return adj_list

# Kruskal's algorithm with union-find
def kruskal(departments, edges):
    parent = {dept: dept for dept in departments}
    rank = {dept: 0 for dept in departments}

    def find(u):
        # path compression
        if parent[u] != u:
            parent[u] = find(parent[u])
        return parent[u]

    def union(u, v):
        ru, rv = find(u), find(v)
        if ru == rv:
            return False
        if rank[ru] < rank[rv]:
            parent[ru] = rv
        elif rank[rv] < rank[ru]:
            parent[rv] = ru
        else:
            parent[rv] = ru
            rank[ru] += 1
        return True

    mst = []
    edges_sorted = sorted(edges, key=lambda x: x[2])
    for u, v, w in edges_sorted:
        if union(u, v):
            mst.append((u, v, w))
    return mst

# Simple Prim (works on small graphs / educational)
def prim_simple(departments, adj_list):
    if not departments:
        return []
    start = departments[0]
    visited = set([start])
    mst = []

    while len(visited) < len(departments):
        min_edge = None
        for src in list(visited):
            for dest, dist in adj_list.get(src, []):
                if dest not in visited:
                    if min_edge is None or dist < min_edge[2]:
                        min_edge = (src, dest, dist)
        if min_edge is None:
            break
        _, dest, _ = min_edge
        visited.add(dest)
        mst.append(min_edge)
    return mst

def draw_and_save(nodes, edges, title, filename):
    try:
        G = nx.Graph()
        G.add_weighted_edges_from(edges)
        # deterministic layout
        pos = nx.spring_layout(G, seed=42)
        labels = nx.get_edge_attributes(G, 'weight')
        plt.figure(figsize=(6, 4))
        nx.draw(
            G, pos, with_labels=True, node_color='lightblue',
            node_size=1200, font_size=10, font_weight='bold', edgecolors='black'
        )
        nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
        plt.title(title)
        plt.tight_layout()
        plt.savefig(filename)
        plt.close()
        print(f"Saved graph '{title}' to: {filename}")
    except Exception:
        print("Error when drawing/saving graph. Traceback:")
        traceback.print_exc()

def main():
    try:
        departments, edges = build_graph_data()

        adj_list = print_adjacency_list_matrix(departments, edges)

        mst_kruskal = kruskal(departments, edges)
        print("\nKruskal's MST:")
        for e in mst_kruskal:
            print(e)

        mst_prim = prim_simple(departments, adj_list)
        print("\nPrim's MST:")
        for e in mst_prim:
            print(e)

        # Save images instead of show (works in headless env)
        draw_and_save(departments, edges, "Original Campus Graph", "original_graph.png")
        draw_and_save(departments, mst_kruskal, "MST by Kruskal", "mst_kruskal.png")
        draw_and_save(departments, mst_prim, "MST by Prim", "mst_prim.png")

    except Exception:
        print("An unexpected error occurred. Full traceback:")
        traceback.print_exc()

if __name__ == "__main__":
    main()
