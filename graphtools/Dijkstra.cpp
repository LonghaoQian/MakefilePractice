#include "Dijkstra.h"
namespace GraphAnalysis {
    Dijkstra::Dijkstra(const AdjacencyXi& adjacencyMatrix,
                       const PathCostXd& pathCost,
                       const NodeCostXd& nodeCost,
                        unsigned int numOfNodes)

    {
        Reset(adjacencyMatrix, pathCost, nodeCost, numOfNodes);
    }
    Dijkstra::~Dijkstra()
    {

    }
    std::pair<Path, double> Dijkstra::GetResult(NodeIndex source, NodeIndex destination)
    {
        // clear buffer
        for (NodeIndex i = 0; i < numberOfNodes; i++) {
            dist[i] = -1.0;
            parent[i] = i;
            visited[i] = false;
        }
        // set the distanc of the source as 0
        dist[source] = 0u;
        BfsTraverseTree(source, destination);
        RecordResult(destination);
        return {path, dist[destination]};
    }
    void Dijkstra::PrintConnectionMatrix()
    {
        std::cout<<"connection matrix is: \n";
        std::cout<<adjacency<<'\n';
    }
    void Dijkstra::PrintNodeConnectionList()
    {
        std::cout<<"node list is: \n";
        for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
            std::cout<<"index: "<<it->index<<", edge List: ";
            for (auto it1 = it->edgeList.begin(); it1 != it->edgeList.end(); it1++) {
                std::cout<<it1->first<<", ";
            }
            std::cout<<'\n';
        }
    }
    void Dijkstra::PrintPathCostMatrix()
    {
        std::cout<<"path cost matrix is: \n";
        std::cout<<pathCost<<'\n';
    }
    void Dijkstra::PrintNodeCostVector()
    {
        std::cout<<"node cost vector is: \n";
        std::cout<<nodeCost<<'\n';
    }
    void Dijkstra::Reset(const AdjacencyXi& adjacencyMatrix, 
                          const PathCostXd& pathCost,
                          const NodeCostXd& nodeCost,
                          unsigned int numOfNodes)
    {
        this->numberOfNodes = numberOfNodes;
        adjacency = adjacencyMatrix;
        this->pathCost = pathCost;
        this->nodeCost = nodeCost;
        // update nodeList
        nodeList = GetNodeFromAdjMatrix(adjacency);
        // update cost
        for (NodeIndex i = 0; i < numberOfNodes; i++) {
            nodeList[i].nodeCost = nodeCost(i);
            for (auto it = nodeList[i].edgeList.begin(); 
                 it != nodeList[i].edgeList.end(); it++) {
                it->second = pathCost[it->first];
            }
        }
        // reset all buffer
        dist.clear();
        dist.reserve(numberOfNodes);
        parent.clear();
        parent.shrink_to_fit();
        parent.reserve(numberOfNodes);
        visited.clear();
        visited.shrink_to_fit();
        visited.reserve(numberOfNodes);
        path.clear();
        path.shrink_to_fit();
        path.reserve(numberOfNodes);
        for (NodeIndex i = 0; i < numberOfNodes; i++) {
            dist[i] = -1.0;
            parent.push_back(0);
            visited.push_back(false);
            path.push_back(0);
        }
    }
    double Dijkstra::GetDist(NodeIndex index)
    {
        return dist[index];
    }
    bool Dijkstra::CheckAdjacencyMatrix()
    {
        return true;
    }
    void Dijkstra::BfsTraverseTree(NodeIndex source, NodeIndex destination)
    {
        // if the cost of a is less or equal to b, 
        // then a comes before b
        auto cmp = [this](NodeIndex a, NodeIndex b){
            return !(this->GreaterCost(this->GetDist(a), this->GetDist(b)));
        };
        // std::priority_queue<NodeIndex, std::vector<NodeIndex>, decltype(cmp)> buffer(cmp);
        // push the source node to buffer
        std::vector<NodeIndex> nodeToVisit(numberOfNodes, 0);
        for (NodeIndex i = 0; i < numberOfNodes; i++) {
            nodeToVisit[i] = nodeList[i].index;
        }
        // 
        std::sort(nodeToVisit.begin(), nodeToVisit.end(), cmp);
        // look at the resultos
        for (auto t : nodeToVisit) {
            std::cout<<t<<'\n';
        }
        // reset some buffer
        while(!nodeToVisit.empty()) {
            // sort the nodeToVisit in ascending order
            std::sort(nodeToVisit.begin(), nodeToVisit.end(), cmp);
            // the last element is the one with the lowest dist
            auto root = nodeToVisit.back();
            visited[root] = true;
            nodeToVisit.pop_back();
            for (auto it = nodeList[root].edgeList.begin(); it != nodeList[root].edgeList.end(); it++) {
                if (!visited[it->first]) {
                    // if this is not removed, upate the dist value
                    auto cost = dist[root] + it->second;
                    if (dist[it->first] > cost) {
                        // update the dist and parent if the child
                        // dist is greater than the current cost
                        dist[it->first] = cost;
                        parent[it->first] = root;
                    }
                }
            }
        }
    }
    void Dijkstra::RecordResult(NodeIndex destination)
    {
        auto currIndex = destination;
        while (parent[currIndex] != currIndex)
        {
            path.push_back(currIndex);
            currIndex = parent[currIndex];
        }
        path.push_back(currIndex);
        std::reverse(path.begin(), path.end());
    }
    bool Dijkstra::GreaterCost(double a, double b)
    {
        // here negative means inf
        // if a and b are both negative, return false
        // if a is negative or a > b, return true
        // if a is positive or a <= b, return false
        if (a < 0 && b < 0) {
            return false;
        }
        // a or b must be greater or equal to zero
        if (a < 0) {
            // a is inf
            return true;
        }
        if (b < 0) {
            // b is inf
            return false;
        }
        // a and b must both be greater than zero
        return a > b;
    }
}