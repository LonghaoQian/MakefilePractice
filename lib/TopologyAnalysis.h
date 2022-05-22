#ifndef TOPOLOGYANALYSIS
#define TOPOLOGYANALYSIS
#include <iostream>
#include <Eigen/Core>
#include <stack>
#include <vector>
#include <algorithm>
#include <utility>

namespace GraphTools {
   struct Node {
      std::stack<unsigned int> childIndex;
      unsigned int index;
      Node(unsigned int index_): index(index_)
      {}
   };
   // wrapper class of vector.
   // provide additional functions and quick search
   class NodeBuffer{
      public:
         NodeBuffer(unsigned int maxSize_);
         virtual ~NodeBuffer();
         void Reset(unsigned intmaxSize_);
         void Push(const Node& node);
         void Pop();
         unsigned int GetBufferSize();
         Node GetBufferElement(unsigned int index);
         std::pair<bool, int> IsInBuffer(unsigned int index);
         void DisplayElementbyIndex(unsigned int index);
      private:
         std::vector<Node> buffer;
         std::vector<std::pair<bool, int>> inbuffer;
         unsigned int maxSize{0};
   };
   struct Loop {
      std::vector<int> indexList;
      void Regularize()
      {
         std::sort(indexList.begin(), indexList.end());
      }
      bool Compare(const Loop& target)
      {
         if (target.indexList.size() != indexList.size()) {
            return false;
         }
         for (unsigned int i = 0; i <  indexList.size(); i++) {
            if (indexList[i] != target.indexList[i]) {
               return false;
            }
         }
         return true;
      }
   };
   class TopologyAnalysis {
      public:
      TopologyAnalysis(const Eigen::MatrixXi& connectionMatrix);
      bool RunLoopDetection();
      void Reset(const Eigen::MatrixXi& connectionMatrix);
      std::vector<Loop> GetResult();
      void DisplayConnectionMatrix();
      void DisplayNodeConnectionList();
      void DisplayNodeBuffer();
      virtual ~TopologyAnalysis();

      private:
      void CheckValidity();
      void UpdateNodeConnectionList();
      void ResetAllBuffers();

      void RecordLoopIndex(unsigned int currIndex);
      bool CheckIndexInBuffer(unsigned int currIndex);
      void TraceBackSearch();
      /*
         connectivity(
         subsystem_list[i]->GetSystemInfo().input_connection(j, 0), i) =
         1;
         connection matrix: C
         C(i, j): i from system, j to system
         C(i, j) = 1 : a directed connection from node i to node j
         i -> j
         C(i, j) = 0 : no connection between i and j
      */
      Eigen::MatrixXi connection;
      std::vector<Loop> loopIndex;
      NodeBuffer nodeBuffer;
      std::vector<Node> nodeConnectionList;
      bool connectionMatrixValid{false};
      unsigned int numOfNodes{0};
   };
}
#endif