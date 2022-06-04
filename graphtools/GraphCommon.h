#ifndef GRAPHCOMMON_H
#define GRAPHCOMMON_H
/*
    common definitions with for graph analysis
*/
#include <Eigen/Core>
#include <stack>
#include <vector>
#include <list>
#include <iostream>
#include <utility>
#include <algorithm>

namespace GraphAnalysis {
    /* Adjacency matrix
      Adjacency matrix: C
      C(i, j) = 1 : a directed path from node i to node j
      C(i, j) = 0 : no path between i and j
    */
    using AdjacencyXi = Eigen::MatrixXi;
    /* Path cost matrix
      Path cost: C
      C(i, j) = a : the cost of traversing from node i to node j
    */
    using PathCostXd = Eigen::MatrixXd;
    /* Node cost vector
      Node cost: C
      C(i) = a : cost of staying on node i
    */
    using NodeCostXd = Eigen::VectorXd;
    using NodeIndex = unsigned int;
    using NodeList = std::vector<NodeIndex>;
    // definition of a node
    struct Node {
      std::list<std::pair<unsigned int, double>> edgeList;
      unsigned int index{0};
      double nodeCost{0.0};
      Node(unsigned int index_, double nodeCost_): 
      index(index_), 
      nodeCost(nodeCost_)
      {}
      void AddAdjacent(unsigned int index, double cost)
      {
          edgeList.push_back({index, cost});
      }
    };
    /*
      a stack buffer. Provides interface to read all data
    */
    class NodeBuffer{
      public:
         NodeBuffer(unsigned int maxSize_);
         virtual ~NodeBuffer();
         void Reset(unsigned int intmaxSize_);
         void Push(const Node& node);
         void Pop();
         void PopTopEdgeList();
         Node Top();
         unsigned int GetBufferSize();
         bool IsEmpty();
         bool ExceedSizeLimit();
         Node GetBufferElement(unsigned int index);
         std::pair<bool, int> IsInBuffer(unsigned int index);
         void DisplayElementbyIndex(unsigned int index);
      private:
         std::vector<Node> buffer; // store the node data
         // store flag indicating whether a node is inbuffer
         std::vector<std::pair<bool, unsigned int>> inbuffer;
         unsigned int maxSize{0};
    };
    // convert adjacency into node
    std::vector<Node> GetNodeFromAdjMatrix(const AdjacencyXi& input);
}

#endif