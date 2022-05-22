#include "TopologyAnalysis.h"
namespace GraphTools {
    NodeBuffer::NodeBuffer(unsigned int maxSize_): 
        maxSize(maxSize_)
    {
        Reset(maxSize_);
    }

    NodeBuffer::~NodeBuffer()
    {

    }
    void NodeBuffer::Reset(unsigned intmaxSize_)
    {
        buffer.clear();
        buffer.shrink_to_fit();
        maxSize = intmaxSize_;
        buffer.reserve(maxSize);
        std::for_each(inbuffer.begin(), inbuffer.end(), [](std::pair<bool, int>& a){
            a.first = false;
            a.second = 0u;
        });
    }
    void NodeBuffer::Push(const Node& node)
    {
        buffer.emplace_back(node);
        inbuffer[node.index].first = true;
        inbuffer[node.index].second = buffer.size() - 1u;
    }
    void NodeBuffer::Pop()
    {
        inbuffer[buffer.back().index].first = false;
        inbuffer[buffer.back().index].second = 0u;
        buffer.pop_back();
    }
    Node NodeBuffer::Top()
    {
        return buffer.back();
    }
    bool NodeBuffer::IsEmpty()
    {
        return buffer.empty();
    }
    Node NodeBuffer::GetBufferElement(unsigned int index)
    {
        if (index >= GetBufferSize()) {
            return Node(0u);
        }
        return buffer[index];
    }
    std::pair<bool, int> NodeBuffer::IsInBuffer(unsigned int index)
    {
        return inbuffer[index];
    }
    unsigned int NodeBuffer::GetBufferSize()
    {
        return buffer.size();
    }
    void NodeBuffer::DisplayElementbyIndex(unsigned int index_)
    {
        auto it = std::find_if(buffer.begin(), buffer.end(), [index_](const Node& t){
            return t.index == index_;
        });
        if (it == buffer.end()) {
            std::cout<<"index = "<<index_<<" is not in buffer!\n";
        } else {
            std::cout<<"index = "<<index_<<" is in buffer. Current stack top is: "<<it->childIndex.top()<<"\n";
        }
    }

    TopologyAnalysis::TopologyAnalysis(const Eigen::MatrixXi& connectionMatrix) : 
        connection(connectionMatrix),
        nodeBuffer(0u),
        connectionMatrixValid(false),
        numOfNodes(0u)
    {
        CheckValidity();
        UpdateNodeConnectionList();
        ResetAllBuffers();
    }
    TopologyAnalysis::~TopologyAnalysis()
    {

    }
    bool TopologyAnalysis::RunLoopDetection()
    {
        if (connectionMatrixValid) {
            return false;
        }
        auto it = std::find_if(visitedNodeList.begin(), visitedNodeList.end(), [](bool a) {
            return !a;
        });
        while (it != visitedNodeList.end()) {
            TraceBackSearch(std::distance(visitedNodeList.begin(), it));
            it = std::find_if(visitedNodeList.begin(), visitedNodeList.end(), [](bool a) {
                return !a;
            });
        }
        return true;
    }
    void TopologyAnalysis::Reset(const Eigen::MatrixXi& connectionMatrix)
    {
        connection = connectionMatrix;
        CheckValidity();
        UpdateNodeConnectionList();
        ResetAllBuffers();
    }

    std::vector<Loop> TopologyAnalysis::GetResult()
    {
        return loopIndex;
    }

    void TopologyAnalysis::DisplayConnectionMatrix()
    {
        std::cout<<"The connection matrix is: \n";
        std::cout<<connection<<'\n';
    }
    void TopologyAnalysis::DisplayNodeConnectionList()
    {

    }
    void TopologyAnalysis::DisplayNodeBuffer()
    {
        std::cout<<"This node buffer is: \n";
        for (unsigned int i = 0; i < nodeBuffer.GetBufferSize(); i++) {
            std::cout<<"index: "<<nodeBuffer.GetBufferElement(i).index<<'\n';
        }
    }
    void TopologyAnalysis::CheckValidity()
    {
        // first check the size of the matrix
        if (connection.rows() == 0u) {
            connectionMatrixValid = false;
            return;
        }
        // then check whether the matrix is square
        if (connection.cols() != connection.rows()) {
            connectionMatrixValid = false;
        }
        connectionMatrixValid = true;
    }

    void TopologyAnalysis::UpdateNodeConnectionList()
    {
        /*
            connection matrix: C
            C(i, j): i from system, j to system
            C(i, j) = 1 : a directed connection from node i to node j
            i -> j
            C(i, j) = 0 : no connection between i and j
        */
        if (!connectionMatrixValid) {
            return;
        } 
        numOfNodes = static_cast<unsigned int>(connection.rows());
        nodeConnectionList.reserve(numOfNodes);
        for (unsigned int i = 0u; i < numOfNodes; i++) {
            nodeConnectionList.emplace_back(Node(i));
            for (unsigned int j = 0u; j < numOfNodes; j++) {
                if (connection(i, j) == 1) {
                    nodeConnectionList.back().childIndex.push(j);
                }
            }
        }
        visitedNodeList.clear();
        visitedNodeList.shrink_to_fit();
        visitedNodeList.reserve(numOfNodes);
        for (unsigned int i = 0; i < numOfNodes; i++) {
            visitedNodeList.push_back(false);
        }
    }

    void TopologyAnalysis::ResetAllBuffers()
    {
        for (unsigned int i = 0; i < numOfNodes; i++) {
            visitedNodeList[i] = false;
        }
        loopIndex.clear();
        loopIndex.shrink_to_fit();
        nodeBuffer.Reset(numOfNodes);
    }

    void TopologyAnalysis::RecordLoopIndex(unsigned int currIndex)
    {
        auto startNode = nodeBuffer.IsInBuffer(currIndex);
        if (!startNode.first) {
            return;
        }
        loopIndex.emplace_back(Loop());
        for (unsigned int i = startNode.second; i < nodeBuffer.GetBufferSize(); i++) {
            loopIndex.back().indexList.push_back(nodeBuffer.GetBufferElement(i).index);
        }
        loopIndex.back().Regularize();
    }

    bool TopologyAnalysis::CheckIndexInBuffer(unsigned int currIndex)
    {
        return nodeBuffer.IsInBuffer(currIndex).first;
    }

    void TopologyAnalysis::TraceBackSearch(unsigned int startIndex)
    {
        nodeBuffer.Reset(numOfNodes);
        nodeBuffer.Push(nodeConnectionList[startIndex]);
        while (!nodeBuffer.IsEmpty()) {
            if (nodeBuffer.Top().childIndex.empty()) {
                // if the childIndex is empty, pop the top
                nodeBuffer.Pop();
            } else {
                auto nextNode = nodeBuffer.Top().childIndex.top();
                nodeBuffer.Top().childIndex.pop();
                // if the childIndex is non-empty, check whether the childIndex top element is in the buffer
                if (CheckIndexInBuffer(nextNode)) {
                    // if the top childIndex is in the buffer, then record this loop
                    RecordLoopIndex(nextNode);
                } else {
                    // if the top childIndex is not in the buffer, push the node into the buffer and remove
                    // the top index
                    nodeBuffer.Push(nodeConnectionList[nextNode]);
                }
            }
        }
        // after finding all the loops containing startIndex, label this index as visited
        visitedNodeList[startIndex] = true;
    }
}