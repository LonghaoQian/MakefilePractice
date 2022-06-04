#include "FindStrongComponents.h"
namespace GraphAnalysis {
    SccTarjan::SccTarjan(const AdjacencyXi& input, NodeIndex numOfNodes) :
        numOfNodes(numOfNodes),
        dfsCounter{0},
        disc(numOfNodes, 0u),
        low(numOfNodes, 0u),
        dfsBuffer(numOfNodes),
        resBuffer(numOfNodes)
    {
        Reset(input, numOfNodes);
    }
    std::vector<NodeList> SccTarjan::GetResult()
    {
        for (NodeIndex i = 0; i < numOfNodes; i++) {
        // if node not visited, start from this node.
            if (disc[i] == 0) {
                DFSTreeTraverse(i);
            }
        }
        return res;
    }
    void SccTarjan::Reset(const AdjacencyXi& input, NodeIndex numOfNodes)
    {
        this->adjacency = input;
        this->numOfNodes = input.rows();
        inputValid = CheckAdjacencyMatrix();
        if (!inputValid) {
            return;
        }
        dfsCounter = 0u;
        disc.clear();
        disc.shrink_to_fit();
        low.clear();
        low.shrink_to_fit();
        for (NodeIndex i = 0; i < numOfNodes; i++) {
            disc.push_back(0u);
            low.push_back(0u);
        }
        dfsBuffer.Reset(numOfNodes);
        resBuffer.Reset(numOfNodes);
        nodeList = GetNodeFromAdjMatrix(input);
    }
    bool SccTarjan::GetStatus()
    {
        return inputValid;
    }
    void SccTarjan::PrintNodeList()
    {
        for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
            std::cout<<"index: "<<it->index<<", edge List: ";
            for (auto it1 = it->edgeList.begin(); it1 != it->edgeList.end(); it1++) {
                std::cout<<it1->first<<", ";
            }
            std::cout<<'\n';
        }
    }
    SccTarjan::~SccTarjan()
    {

    }
    bool SccTarjan::CheckAdjacencyMatrix()
    {
        if (numOfNodes == 0 || numOfNodes != adjacency.cols()) {
            return false;
        }
        return true;
    }
    void SccTarjan::DFSTreeTraverse(NodeIndex rootIndex)
    {
        // traverse from the root
        dfsBuffer.Reset(numOfNodes);
        // put the root into buffer
        AddNodeToBuffer(rootIndex);
        while (!dfsBuffer.IsEmpty()) {
            // if the adj is empty
            if (dfsBuffer.Top().edgeList.empty()) {
                // this node should be poped
                // first check whether this node is the head of the SCC
                if (disc[dfsBuffer.Top().index] == low[dfsBuffer.Top().index]) {
                    // if it is the head, record the result;
                    RecordResult(dfsBuffer.Top().index);
                }
                // pop the top
                auto tempChild = dfsBuffer.Top().index;
                dfsBuffer.Pop();
                // if the parent of this node exits, update the low array of its
                // parent
                if (!dfsBuffer.IsEmpty()) {
                    low[dfsBuffer.Top().index] = std::min(low[dfsBuffer.Top().index], 
                    low[tempChild]);
                }
            } else {
                // if the adj is no-empty, first check whether this
                // node is previously visited
                auto index = dfsBuffer.Top().edgeList.back().first;
                dfsBuffer.PopTopEdgeList();
                if (disc[index] == 0) {
                    // if not visited, add this node to the buffer
                    AddNodeToBuffer(index);
                } else if (resBuffer.IsInBuffer(index).first) {
                    // if this adj has been visited and is in the res buffer
                    // then this is a back edge
                    // adj is not added into the res buffer, but
                    // the low of the current node is updated
                    low[dfsBuffer.Top().index] = std::min(low[dfsBuffer.Top().index],
                    disc[index]);
                }
                // if the adj has been visited and is not in the res buffer
                // then this is a cross edge. Skip the cross edge
            }
        }
    }
    void SccTarjan::AddNodeToBuffer(NodeIndex index)
    {
        // increment the dfsCounter
        dfsCounter++;
        // add the node into the dfs buffer
        dfsBuffer.Push(nodeList[index]);
        // add the node into th res buffer
        resBuffer.Push(nodeList[index]);
        // update the root disc and low array
        disc[index] = dfsCounter;
        low[index] = dfsCounter;
    }
    void SccTarjan::RecordResult(NodeIndex index)
    {
        if (resBuffer.IsEmpty() || !resBuffer.IsInBuffer(index).first) {
            return;
        }
        // initialize the result
        res.emplace_back(NodeList());
        // pop the resBuffer and store it to scc until the index is poped
        while (resBuffer.Top().index != index) {
             res.back().push_back(resBuffer.Top().index);
             resBuffer.Pop();
        }
        res.back().push_back(resBuffer.Top().index);
        resBuffer.Pop();
    }
}