import networkx as nx
import random

def generate_directed_graph(num_nodes, num_edges):
    G = nx.DiGraph()

    # Create nodes
    for i in range(num_nodes):
        G.add_node(i)

    # Generate random edges to ensure no isolated nodes
    for i in range(num_nodes):
        source = i
        target = random.randint(0, num_nodes-1)
        while target == source:
            target = random.randint(0, num_nodes-1)
        G.add_edge(source, target)

    # Generate remaining edges
    edges_added = num_nodes
    while edges_added < num_edges:
        source = random.randint(0, num_nodes-1)
        target = random.randint(0, num_nodes-1)
        if source != target and not G.has_edge(source, target):
            G.add_edge(source, target)
            edges_added += 1

    return G

def print_edges(G):
    for edge in G.edges():
        print(edge[0], edge[1])

# Parameters for the graph
num_edges = int(input())
# num_nodes = num_edges // 2
num_nodes = num_edges

# Generate graph
graph = generate_directed_graph(num_nodes, num_edges)

# Print edges
print_edges(graph)
