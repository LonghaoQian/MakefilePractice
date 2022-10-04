/*************************************************************

Copyright(C) 2022 Longhao Qian

This program is free software; you can redistribute it and / or
modify it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program;
if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

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