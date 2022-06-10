#ifndef JOHNSONCURCITALG_H
#define JOHNSONCURCITALG_H

#include "GraphCommon.h"
#include "unordered_map"
namespace GraphAnalysis {
    using Loop = std::vector<NodeIndex>;
    class JohnsonCurcitAlg {
    public:
        JohnsonCurcitAlg(const AdjacencyXi& adjacencyMatrix,
                         const std::vector<NodeList>& scc_,
                         unsigned int numOfNodes);
        virtual ~JohnsonCurcitAlg();
        void Reset(const AdjacencyXi& adjacencyMatrix, 
                   const std::vector<NodeList>& Scc,
                   unsigned int numOfNodes);
        std::vector<Loop> GetResult();
        void DisplayConnectionMatrix();
        void DisplayNodeConnectionList();
        void DisplayNodeBuffer();
        void DisplayBlockedMap();
        void DisplayBlockedList();
        void DisplayNodeSccNumber();
    private:
        bool CheckAdjacencyMatrix();
        void DfsTraverseTree(NodeIndex root);
        void RecordResult();
        void PopBlockedMap(NodeIndex start);
        bool IsInBlockedMap();
        NodeIndex numofNodes;
        AdjacencyXi adjacency;
        NodeBuffer nodeBuffer;
        std::vector<std::vector<NodeIndex>> blockedMap;
        std::vector<bool> blockedList;
        std::vector<bool> inCycle;
        std::vector<NodeList> scc;
        std::vector<NodeIndex> nodeSccNumber;
        std::vector<Loop> res;
    };
}
#endif