#include "lib/models/graph.h"

int main() {
    Graph *g = graphInit();

    graphVertexAdd(g);
    graphVertexAdd(g);
    graphVertexAdd(g);
    graphVertexAdd(g);
    graphVertexAdd(g);
    graphVertexAdd(g);

    graphEdgeAdd(g, 0, 1, 3);
    graphEdgeAdd(g, 0, 2, 8);
    graphEdgeAdd(g, 0, 3, 2);
    graphEdgeAdd(g, 0, 5, 7);
    graphEdgeAdd(g, 2, 0, 8);
    graphEdgeAdd(g, 2, 3, 1);
    graphEdgeAdd(g, 2, 4, 4);
    graphEdgeAdd(g, 3, 5, 1);
    graphEdgeAdd(g, 4, 3, 2);
    graphEdgeAdd(g, 4, 5, 5);
    graphEdgeAdd(g, 5, 4, 1);

    vectorPrint(graphShortestPath(g, 0, 4));

    vectorPrint(graphPath(g, 0, 4));

    graphPrint(g);

    graphFree(g);
    return 0;
}
