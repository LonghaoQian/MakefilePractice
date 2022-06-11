#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <queue>
#include <limits>
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
        void Reset(const AdjacencyXi& adjacencyMatrix, 
                   const PathCostXd& pathCost,
                   const NodeCostXd& nodeCost,
                   unsigned int numOfNodes);
        std::pair<std::vector<Path>, double> GetResult(NodeIndex destination);
        void PrintConnectionMatrix();
        void PrintNodeConnectionList();
    private:
        bool CheckAdjacencyMatrix();
        void BfsTraverseTree(NodeIndex root);
        void RecordResult();
        AdjacencyXi adjacency;
        std::priority_queue<double> buffer;
        std::vector<Node> nodeList;
        std::vector<double> dist;
        std::vector<NodeIndex> parent;
    };
}
#endif