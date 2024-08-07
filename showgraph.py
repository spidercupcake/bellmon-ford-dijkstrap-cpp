import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

# Define the weighted adjacency matrix
adj_matrix = np.array([
    [0, 2, 0, 4],
    [2, 0, 3, 0],
    [0, 3, 0, 1],
    [4, 0, 1, 0]
])

# Create a graph from the weighted adjacency matrix
G = nx.from_numpy_matrix(adj_matrix, create_using=nx.DiGraph)  # Use DiGraph for directed graphs

# Draw the graph
pos = nx.spring_layout(G)  # positions for all nodes
nx.draw_networkx_nodes(G, pos, node_size=700)
nx.draw_networkx_edges(G, pos, width=2)
nx.draw_networkx_labels(G, pos, font_size=12, font_family='sans-serif')

# Draw edge labels
edge_labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

# Display the graph
plt.title('Weighted Graph Visualization from Adjacency Matrix')
plt.show()
