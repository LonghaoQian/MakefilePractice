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