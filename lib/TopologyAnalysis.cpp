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
    }

    void TopologyAnalysis::ResetAllBuffers()
    {
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

    void TopologyAnalysis::TraceBackSearch()
    {

    }
}