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

#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <unordered_map>
#include "GraphCommon.h"
namespace GraphAnalysis
{
using Path = std::vector<NodeIndex>;
struct DijkstraRes {
    Path path;
    double cost;
    bool valid;
};
class Dijkstra
{
   public:
    Dijkstra(const AdjacencyXi &adjacencyMatrix, const PathCostXd &pathCost,
             unsigned int numOfNodes);
    virtual ~Dijkstra();
    DijkstraRes GetResult(NodeIndex source, NodeIndex destination);
    void PrintConnectionMatrix();
    void PrintNodeConnectionList();
    void PrintPathCostMatrix();
    void Reset(const AdjacencyXi &adjacencyMatrix, const PathCostXd &pathCost,
               unsigned int numOfNodes);
    double GetDist(NodeIndex index);
    bool GreaterCost(double a, double b);

   private:
    bool CheckAdjacencyMatrix();
    bool BfsTraverseTree(NodeIndex source, NodeIndex destination);
    void RecordResult(NodeIndex destination);
    NodeIndex numberOfNodes{0u};
    AdjacencyXi adjacency;
    PathCostXd pathCost;
    std::vector<Node> nodeList;
    std::unordered_map<NodeIndex, double> dist;
    std::vector<NodeIndex> parent;
    std::vector<bool> visited;
    Path path;
};
}  // namespace GraphAnalysis
#endif