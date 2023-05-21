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

#ifndef FINDSTRONGCOMPONENTS_H
#define FINDSTRONGCOMPONENTS_H
#include "GraphCommon.h"
namespace GraphAnalysis
{
/*
    Wrapper class of Scc Tarjan method
*/
class SccTarjan
{
   public:
    SccTarjan(const AdjacencyXi &input, NodeIndex numOfNodes);
    std::vector<NodeList> GetResult();
    void Reset(const AdjacencyXi &input, NodeIndex numOfNodes);
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
}  // namespace GraphAnalysis
#endif