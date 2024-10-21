import sys
from pythonds.graphs import PriorityQueue, Graph, Vertex

def prim(G, start):
    pq = PriorityQueue()
    for v in G:
        v.setDistance(sys.maxsize)
        v.setPred(None)
    start.setDistance(0)
    pq.buildHeap([(v.getDistance(), v) for v in G])
    while not pq.isEmpty():
        currentVert = pq.delMin()
        for nextVert in currentVert.getConnections():
            newCost = currentVert.getWeight(nextVert)
            if nextVert in pq and newCost < nextVert.getDistance():
                nextVert.setPred(currentVert)
                nextVert.setDistance(newCost)
                pq.decreaseKey(nextVert, newCost)

# Example graph creation and test
g = Graph()

# Adding vertices and edges to the graph
g.addVertex('A')
g.addVertex('B')
g.addVertex('C')
g.addVertex('D')

g.addEdge('A', 'B', 1)  # Edge from A to B with weight 1
g.addEdge('A', 'C', 3)  # Edge from A to C with weight 3
g.addEdge('B', 'C', 4)  # Edge from B to C with weight 4
g.addEdge('B', 'D', 2)  # Edge from B to D with weight 2

# Running Prim's algorithm on the graph starting from vertex 'A'
prim(g, g.getVertex('A'))

# Print the minimum spanning tree
for v in g:
    if v.getPred():
        print(f"Edge: {v.getPred().getId()} - {v.getId()}, Weight: {v.getWeight(v.getPred())}")
