#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <unordered_map>
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
        std::pair<Path, double> GetResult(NodeIndex source, NodeIndex destination);
        void PrintConnectionMatrix();
        void PrintNodeConnectionList();
        void PrintPathCostMatrix();
        void PrintNodeCostVector();
        void Reset(const AdjacencyXi& adjacencyMatrix, 
                   const PathCostXd& pathCost,
                   const NodeCostXd& nodeCost,
                   unsigned int numOfNodes);
        double GetDist(NodeIndex index);
        bool GreaterCost(double a, double b);
    private:
        bool CheckAdjacencyMatrix();
        void BfsTraverseTree(NodeIndex source, NodeIndex destination);
        void RecordResult(NodeIndex destination);
        NodeIndex numberOfNodes{0u};
        AdjacencyXi adjacency;
        PathCostXd pathCost;
        NodeCostXd nodeCost;
        std::vector<Node> nodeList;
        std::unordered_map<NodeIndex, double> dist;
        std::vector<NodeIndex> parent;
        std::vector<bool> visited;
        Path path;
    };
}
#endif