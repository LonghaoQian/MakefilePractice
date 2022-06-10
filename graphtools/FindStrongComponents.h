#ifndef FINDSTRONGCOMPONENTS_H
#define FINDSTRONGCOMPONENTS_H
#include "GraphCommon.h"
namespace GraphAnalysis {
    /*
        Wrapper class of Scc Tarjan method
    */
    class SccTarjan {
    public:
        SccTarjan(const AdjacencyXi& input, NodeIndex numOfNodes);
        std::vector<NodeList> GetResult();
        void Reset(const AdjacencyXi& input, NodeIndex numOfNodes);
        bool GetStatus();
        void PrintNodeList();
        virtual ~SccTarjan();
    private:
        bool CheckAdjacencyMatrix();
        void DFSTreeTraverse(NodeIndex rootIndex);
        void RecordResult(NodeIndex rootIndex);
        void AddNodeToBuffer(NodeIndex index);
        AdjacencyXi adjacency;
        bool inputValid{false};
        NodeIndex numOfNodes{0u};
        unsigned int dfsCounter{0u};
        std::vector<NodeIndex> disc;
        std::vector<NodeIndex> low;
        NodeBuffer dfsBuffer;
        NodeBuffer resBuffer;
        std::vector<NodeList> res;
        std::vector<Node> nodeList;
    };
}
#endif