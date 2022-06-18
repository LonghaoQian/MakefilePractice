#include "Dijkstra.h"

GraphAnalysis::AdjacencyXi LoadTestCase()
{
    GraphAnalysis::AdjacencyXi connection(9, 9);
    connection(0, 1) = 1;
    connection(0, 7) = 1;

    connection(1, 2) = 1;
    connection(1, 8) = 1;
    connection(1, 6) = 1;

    connection(2, 0) = 1;
    connection(2, 1) = 1;
    connection(2, 3) = 1;
    connection(2, 5) = 1;

    connection(3, 4) = 1;

    connection(4, 1) = 1;

    connection(5, 3) = 1;

    connection(7, 8) = 1;
    connection(8, 7) = 1;
    return connection;
}

void main(void)
{
    auto adjacency = LoadTestCase();
}