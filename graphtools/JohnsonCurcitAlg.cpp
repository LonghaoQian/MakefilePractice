#include "JohnsonCurcitAlg.h"
namespace GraphAnalysis {
    JohnsonCurcitAlg::JohnsonCurcitAlg(const AdjacencyXi& adjacencyMatrix, 
                                       const std::vector<NodeList>& scc_,
                                       unsigned int numOfNodes_) :
                                       numofNodes(numOfNodes_),
                                       nodeBuffer(numOfNodes_),
                                       blockedMap(numOfNodes_, std::vector<NodeIndex>()),
                                       blockedList(numOfNodes_, false),
                                       inCycle(numOfNodes_, false),
                                       scc(scc_),
                                       nodeSccNumber(numOfNodes_, 0u)
    {
        Reset(adjacencyMatrix, scc_, numOfNodes_);
    }
    JohnsonCurcitAlg::~JohnsonCurcitAlg()
    {

    }
    void JohnsonCurcitAlg::Reset(const AdjacencyXi& adjacencyMatrix, 
                   const std::vector<NodeList>& Scc,
                   unsigned int numOfNodes_)
    {
        numofNodes = numOfNodes_;
        adjacency = adjacencyMatrix;
        scc = Scc;
        // update nodeSccNumber
        for (auto it = scc.begin(); it != scc.end(); it++) {
            for (auto it1 = it->begin(); it1 != it->end(); it1++) {
                nodeSccNumber[*it1] = it - scc.begin();
            }
        }
    }
    std::vector<Loop> JohnsonCurcitAlg::GetResult()
    {
        // iterate for every node in every scc
        for (auto it = scc.begin(); it != scc.end(); it++) {

        }
        return res;
    }
    void JohnsonCurcitAlg::DisplayConnectionMatrix()
    {
        std::cout<<"the adjacency matrix is: \n";
        std::cout<<adjacency<<'\n';
    }
    void JohnsonCurcitAlg::DisplayBlockedMap()
    {
        std::cout<<"the blocked map is: \n";
        for (auto it = blockedMap.begin(); it != blockedMap.end(); it++) {
            if (!it->empty()) {
                std::cout<<it - blockedMap.begin()<<": ";
                for (auto t : *it) {
                    std::cout<<t<<", ";
                }
                std::cout<<'\n';
            }
        }
    }
    void JohnsonCurcitAlg::DisplayBlockedList()
    {
        std::cout<<"the blocked list is: \n";
        for (auto it = blockedList.begin(); it != blockedList.end(); it++) {
            std::cout<<it -blockedList.begin()<<": ";
            if (*it) {
                std::cout<<" blocked \n";
            } else {
                std::cout<<" unblocked \n";
            }
        }
    }
    void JohnsonCurcitAlg::DisplayNodeSccNumber()
    {
        std::cout<<"the node scc list is: \n";
        for (auto it = nodeSccNumber.begin(); it != nodeSccNumber.end(); it++) {
            std::cout<<"index "<<it - nodeSccNumber.begin()<<": "<<*it<<'\n';
        }
    }
    bool JohnsonCurcitAlg::CheckAdjacencyMatrix()
    {
        return false;
    }
    void JohnsonCurcitAlg::DfsTraverseTree(NodeIndex root)
    {
        root++;
    }
    void JohnsonCurcitAlg::RecordResult()
    {

    }
    void JohnsonCurcitAlg::PopBlockedMap(NodeIndex start)
    {
        if (blockedMap.empty()) {
            return;
        }
        std::stack<NodeIndex> buffer;
        buffer.push(start);
        while (!buffer.empty())
        {
            // check the whether the current top has a child
            if (blockedMap[buffer.top()].empty()) {
                // if there is no child, the top should be unblocked
                blockedList[buffer.top()] = false;
                // the pop the top
                buffer.pop();
            } else {
                // if the top has a child, push the child into the buffer
                auto tempIndex = blockedMap[buffer.top()].back();
                // remove this child
                blockedMap[buffer.top()].pop_back();
                // push the index into the buffer
                buffer.push(tempIndex);
            }
        }
    }
    bool JohnsonCurcitAlg::IsInBlockedMap()
    {
        return true;
    }
}