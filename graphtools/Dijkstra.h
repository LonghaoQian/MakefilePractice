#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <queue>
#include "GraphCommon.h"
namespace GraphAnalysis {
    using Path = std::vector<NodeIndex>;
    class Dijkstra {
    public:
        Dijkstra(const AdjacencyXi& adjacencyMatrix,
                 const PathCostXd& pathCost,
                 const NodeCostXd& nodeCost,
                 unsigned int numOfNodes);
        virtual ~Dijkstra();
        std::vector<Path> GetResult();
    private:
        AdjacencyXi adjacency;
        std::priority_queue<double> buffer;
        std::vector<Node> nodeList;
        std::vector<double> dist;
        std::vector<NodeIndex> parent;
    };
}
#endif