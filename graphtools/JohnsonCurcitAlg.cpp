#include "JohnsonCurcitAlg.h"
namespace GraphAnalysis {
    JohnsonCurcitAlg::JohnsonCurcitAlg(const AdjacencyXi& adjacencyMatrix, 
                                       const std::vector<NodeList>& scc_,
                                       unsigned int numOfNodes_) :
                                       nodeBuffer(numOfNodes_)
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
        numOfNodes = numOfNodes_;
        adjacency = adjacencyMatrix;
        scc = Scc;
        // reset all lists
        blockedMap.clear();
        blockedMap.shrink_to_fit();
        blockedMap.reserve(numOfNodes);
        blockedList.clear();
        blockedList.shrink_to_fit();
        blockedList.reserve(numOfNodes);
        inCycle.clear();
        inCycle.shrink_to_fit();
        inCycle.reserve(numOfNodes);
        visited.clear();
        visited.shrink_to_fit();
        visited.reserve(numOfNodes);
        nodeSccNumber.clear();
        nodeSccNumber.shrink_to_fit();
        nodeSccNumber.reserve(numOfNodes);
        for (NodeIndex i = 0; i < numOfNodes; i++) {
            blockedMap.emplace_back(std::vector<NodeIndex>());
            blockedList.push_back(false);
            inCycle.push_back(false);
            visited.push_back(false);
            nodeSccNumber.push_back(0);
        }
        // update nodeSccNumber
        for (auto it = scc.begin(); it != scc.end(); it++) {
            for (auto it1 = it->begin(); it1 != it->end(); it1++) {
                nodeSccNumber[*it1] = it - scc.begin();
            }
        }
        res.clear();
        res.shrink_to_fit();
        // update the adjacency matrix
        ModifyAdjacencyMatrix();
        // reset nodeConnectionlist
        nodeList.clear();
        nodeList.shrink_to_fit();
        nodeList = GetNodeFromAdjMatrix(adjacency);
        // reset buffer
        nodeBuffer.Reset(numOfNodes_);
    }
    std::vector<Loop> JohnsonCurcitAlg::GetResult()
    {
        // iterate for every node in every scc
        for (auto it = scc.begin(); it != scc.end(); it++) {
            // begin with the node with the lowest index in each
            // scc
            std::sort(it->begin(), it->end());
            for (auto t : *it) {
                if (!visited[t]) {
                    DfsTraverseTree(t);
                }
            }
        }
        return res;
    }
    void JohnsonCurcitAlg::PrintConnectionMatrix()
    {
        std::cout<<"the adjacency matrix is: \n";
        std::cout<<adjacency<<'\n';
    }
    void JohnsonCurcitAlg::PrintNodeConnectionList()
    {
        std::cout<<"the node list is: \n";
        for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
            std::cout<<"index: "<<it->index<<", edge List: ";
            for (auto it1 = it->edgeList.begin(); it1 != it->edgeList.end(); it1++) {
                std::cout<<it1->first<<", ";
            }
            std::cout<<'\n';
        }
    }
    void JohnsonCurcitAlg::PrintNodeBuffer()
    {
        std::cout<<"the node buffer is: \n";
        for (NodeIndex i = 0; i < nodeBuffer.GetBufferSize(); i++) {
            std::cout<<nodeBuffer.GetBufferElement(i).index<<'\n';
        }
        std::cout<<"end of the node buffer \n";
    }
    void JohnsonCurcitAlg::PrintBlockedMap()
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
    void JohnsonCurcitAlg::PrintBlockedList()
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
    void JohnsonCurcitAlg::PrintNodeSccNumber()
    {
        std::cout<<"the node scc list is: \n";
        for (auto it = nodeSccNumber.begin(); it != nodeSccNumber.end(); it++) {
            std::cout<<"index "<<it - nodeSccNumber.begin()<<": "<<*it<<'\n';
        }
    }
    void JohnsonCurcitAlg::PrintInCycle()
    {
        std::cout<<"the in cycle list is: \n";
        for (auto it = inCycle.begin(); it != inCycle.end(); it++) {
            std::cout<<it - inCycle.begin()<<": ";
            if (*it) {
                std::cout<<" in cycle \n";
            } else {
                std::cout<<" not in cycle \n";
            }
        }
    }
    bool JohnsonCurcitAlg::CheckAdjacencyMatrix()
    {
        if (numOfNodes == 0 || numOfNodes != adjacency.cols()) {
            return false;
        }
        return true;
    }
    void JohnsonCurcitAlg::ModifyAdjacencyMatrix()
    {
        // remove node connections in between different sccs
        for (auto it = nodeSccNumber.begin(); it != nodeSccNumber.end(); it++) {
            auto index = it - nodeSccNumber.begin();
            for (NodeIndex i = 0; i < numOfNodes; i++) {
                if (nodeSccNumber[i] != *it) {
                    adjacency(index, i) = 0;
                }
            }
        }
    }
    void JohnsonCurcitAlg::DfsTraverseTree(NodeIndex root)
    {
        int counter = 0;
        // add the root index into the nodebuffer
        AddNodeToBuffer(root);
        while (!nodeBuffer.IsEmpty()) {
            std::cout<<"---iteration counter "<<counter<<" ---- \n";
            std::cout<<"currrent index : " <<nodeBuffer.Top().index<<'\n';
            if (nodeBuffer.Top().edgeList.empty()) {
                // if the current top has no child, check whether it
                // leads to the root
                if (inCycle[nodeBuffer.Top().index]) {
                    // if it leads to the root, then unblock it according to the 
                    // blocked map
                    PopBlockedMap(nodeBuffer.Top().index);
                } else {
                    // if no path from any of the children leads to the root,
                    // then add the index to the block map
                    AddNodeToBlockedMap(nodeBuffer.Top().index);
                }
                // pop the top
                nodeBuffer.Pop();
            } else {
                // if there still are children left in the edgeList,
                // check whether the children is in the visited array
                if (visited[nodeBuffer.Top().edgeList.back().first]) {
                    // if the child is visited, pop and skip
                    nodeBuffer.Top().edgeList.pop_back();
                    continue;
                }
                if (nodeBuffer.Top().edgeList.back().first == root) {
                    // if the child is the root, means that there may be
                    // a path to the root for all its ancestors
                    // update inCycle
                    UpdateInCycle();
                    // record this cycle
                    RecordResult();
                    // pop this child
                    nodeBuffer.Top().edgeList.pop_back();
                } else if (!blockedList[nodeBuffer.Top().edgeList.back().first]) {
                    // if this child is not the root, and it is not blocked
                    // then add the child into buffer
                    auto temp = nodeBuffer.Top().edgeList.back().first;
                    // pop this child
                    nodeBuffer.Top().edgeList.pop_back();
                    AddNodeToBuffer(temp);
                } else {
                    // if this child is not the root, but it is blocked
                    // then skip thie child
                    nodeBuffer.Top().edgeList.pop_back();
                }
                PrintNodeBuffer();
                PrintBlockedList();
                PrintBlockedMap();
                PrintInCycle();
                counter++;
            }
        }
        // unblock all at the end of the traverse
        for (NodeIndex i = 0; i < numOfNodes; i++) {
            inCycle[i] = false;
            blockedList[i] = false;
        }
        // add the root into visited array
        visited[root] = true;
    }
    void JohnsonCurcitAlg::RecordResult()
    {
        // add an empty loop
        res.push_back(Loop());
        // push the node from nodelist into buffer
        for (NodeIndex i = 0; i < nodeBuffer.GetBufferSize(); i++) {
            res.back().push_back(nodeBuffer.GetBufferElement(i).index);
        }
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
    void JohnsonCurcitAlg::AddNodeToBuffer(NodeIndex index)
    {
        nodeBuffer.Push(nodeList[index]);
        blockedList[index] = true;
    }
    void JohnsonCurcitAlg::AddNodeToBlockedMap(NodeIndex index)
    {
        // add index to blocked map because no path from any of its
        // child leads to the root.
        // therefore, every child becomes a road block
        for (NodeIndex i = 0; i < numOfNodes; i++) {
            if (adjacency(index, i) == 1 &&
                std::find(blockedMap[i].begin(), blockedMap[i].end(), index) == blockedMap[i].end()) {
                blockedMap[i].push_back(index);
            }
        }
    }
    void JohnsonCurcitAlg::UpdateInCycle()
    {
        // flag all the elements in node buffer
        // if the current top leads to the root
        for (NodeIndex i = 0; i < nodeBuffer.GetBufferSize(); i++) {
            inCycle[nodeBuffer.GetBufferElement(i).index] = true;
        }
    }
}