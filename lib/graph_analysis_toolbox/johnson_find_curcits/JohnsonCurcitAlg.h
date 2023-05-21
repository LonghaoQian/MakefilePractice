/*************************************************************

MIT License

Copyright (c) 2023 Dr. Longhao Qian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*************************************************************/

#ifndef JOHNSONCURCITALG_H
#define JOHNSONCURCITALG_H

#include "GraphCommon.h"
namespace GraphAnalysis
{
using Loop = std::vector<NodeIndex>;
class JohnsonCurcitAlg
{
   public:
    JohnsonCurcitAlg(const AdjacencyXi &adjacencyMatrix,
                     const std::vector<NodeList> &scc_,
                     unsigned int numOfNodes);
    virtual ~JohnsonCurcitAlg();
    void Reset(const AdjacencyXi &adjacencyMatrix,
               const std::vector<NodeList> &Scc, unsigned int numOfNodes);
    std::vector<Loop> GetResult();
    void PrintConnectionMatrix();
    void PrintNodeConnectionList();
    void PrintNodeBuffer();
    void PrintBlockedMap();
    void PrintBlockedList();
    void PrintNodeSccNumber();
    void PrintInCycle();

   private:
    bool CheckAdjacencyMatrix();
    void ModifyAdjacencyMatrix();
    void DfsTraverseTree(NodeIndex root);
    void RecordResult();
    void PopBlockedMap(NodeIndex start);
    bool IsInBlockedMap();
    void AddNodeToBuffer(NodeIndex index);
    void AddNodeToBlockedMap(NodeIndex index);
    void UpdateInCycle();
    NodeIndex numOfNodes;
    AdjacencyXi adjacency;
    NodeBuffer nodeBuffer;
    std::vector<std::vector<NodeIndex>> blockedMap;
    std::vector<bool> blockedList;
    std::vector<bool> inCycle;
    std::vector<bool> visited;
    std::vector<NodeList> scc;
    std::vector<NodeIndex> nodeSccNumber;
    std::vector<Loop> res;
    std::vector<Node> nodeList;
};
}  // namespace GraphAnalysis
#endif